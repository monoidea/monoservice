#!/usr/bin/env perl

use strict;
use warnings;

use Log::Log4perl qw(:easy);
Log::Log4perl->easy_init($DEBUG);

use Config::Simple;
use Time::HiRes qw ( gettimeofday usleep );
use Date::Leapyear;
use File::Path;

$ENV{"TZ"} = "UTC";

my $cfg = new Config::Simple('monoidea_http.conf');

my $raspivid_path = $cfg->param('raspivid_path');
my $cam_export_path = $cfg->param('cam_export_path');

# presets
my $cam_width = $cfg->param('cam_width');
my $cam_height = $cfg->param('cam_height');
my $cam_fps = $cfg->param('cam_fps');
my $cam_birate = $cfg->param('cam_bitrate');

# wait for the next minute
my ($start_sec, $start_usec) = gettimeofday();

my $usec_per_sec = 1000000;

my $delay_usec = (60 * $usec_per_sec) - (($start_sec % 60) * $usec_per_sec) - ($start_usec);

DEBUG "delayed start - useconds: " . $delay_usec;
usleep($delay_usec);

my $running = 1;

while($running){
    my $capture_duration_msec = 60000;

    my ($time_sec, $time_usec) = gettimeofday();

    my ($current_sec, $current_min, $current_hour, $current_mday, $current_mon, $current_year, $current_wday, $current_yday, $current_isdst) = localtime($time_sec);
    $current_year += 1900;
    $current_mon += 1;

    my $capture_delay = $time_sec % 60;

    if($capture_delay != 0){
	if($capture_delay == 59){
	    $current_min++;
	}else{
	    if($capture_delay < 3){
		DEBUG "capture - compensate for being late: " . (60000 - ($capture_delay + $time_usec));

		$capture_duration_msec = 60000 - ($capture_delay + ($time_usec / 1000));
	    }elsif($capture_delay > 57){
		DEBUG "capture - compensate for being early: " . (($usec_per_sec - $time_usec) + ((60 - $capture_delay) * $usec_per_sec));
		$capture_duration_msec = 59999;
		$current_min++;

		usleep(($usec_per_sec - $time_usec) + ((60 - $capture_delay) * $usec_per_sec));
	    }else{
		ERROR "capture - failure";

		sleep(60 - $capture_delay);

		continue;
	    }
	}
    }

    if($current_min == 60){
	$current_min = 0;
	$current_hour++;

	if($current_hour == 24){
	    $current_hour = 0;
	    $current_yday++;

	    if($current_yday == 365 && !isleap($current_year) ||
	       $current_yday == 366 && isleap($current_year)){
		$current_yday = 0;
		$current_year++;
	    }
	}
    }

    File::Path->make_path($cam_export_path . '/' . $current_year . '/' . $current_yday . '/' . $current_hour);

    my $capture_filename = $cam_export_path . '/' . $current_year . '/' . $current_yday . '/' . $current_hour . '/' . sprintf("cam-%02d.h264", $current_min);

    my @raspivid_args = ($raspivid_path, '-t', $capture_duration_msec, '-w', $cam_width, '-h', $cam_height, '-fps', $cam_fps, '-b', $cam_bitrate, '-o', $capture_filename);

    DEBUG "capture - filename: " . $capture_filename;
    system(@raspivid_args);

#    sleep(60);
}
