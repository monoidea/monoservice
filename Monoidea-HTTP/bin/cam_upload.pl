#!/usr/bin/env perl

use strict;
use warnings;

use Log::Log4perl qw(:easy);
Log::Log4perl->easy_init($DEBUG);
 
use DateTime::Format::Strptime;
use Config::Simple;
use File::Basename;
use LWP::UserAgent;
use Monoidea::HTTP::Action::Login;
use Monoidea::HTTP::Action::Upload;

$ENV{"TZ"} = "UTC";

sub upload_file {
    my ($user_agent, $host, $username, $password, $filename) = @_;

    my $login_url = 'http://' . $host . '/people/login';
    my $logout_url = 'http://' . $host . '/people/logout';
    my $upload_url = 'http://' . $host . '/upload/put_cam';

    my @path_arr = split /\//, $filename;
    my $path_length = scalar(@path_arr);

    my $creation_year = $path_arr[$path_length - 4];
    my $creation_yday = $path_arr[$path_length - 3];
    my $creation_hour = $path_arr[$path_length - 2];
    my $creation_min = ($path_arr[$path_length - 1] =~ /[a-zA-Z-_]*(\d\d)*/)[0];
    my $creation_sec = '00';
    
    my $creation_time_str = $creation_year . ' ' . $creation_yday . ' ' . $creation_hour . ':' . $creation_min . ':' . $creation_sec;

    my $date_parser = DateTime::Format::Strptime::->new(
	pattern => ("%Y %j %T"),
	time_zone => 'GMT-0',
	);
    my $dt;

    $dt = $date_parser->parse_datetime($creation_time_str);
    my $creation_time = $dt->epoch();

    if($creation_time + 60 > time){
	return;
    }

    DEBUG "login: ****";

    my $login = Monoidea::HTTP::Action::Login->new(url => $login_url,
						   username => $username,
						   password => $password);
    $login->do_login($user_agent);

    DEBUG "upload - filename: " . $filename;
    DEBUG "upload - creation_time: " . $creation_time_str . "[" . $creation_time. "]";

    my $upload = Monoidea::HTTP::Action::Upload->new(url => $upload_url,
						     filename => basename($filename),
						     creation_time => $creation_time,
						     duration => 60,
						     media_file => $filename);
    my $response = $upload->do_upload($user_agent);

    if($response->is_success){
	DEBUG "response success - remove file: " . $filename;

	unlink $filename;
    }

    HTTP::Request::Common::GET($logout_url);
}

my $cfg = new Config::Simple('monoidea_http.conf');

my $cam_export_path = $cfg->param('cam_export_path');

my $host = $cfg->param('host');
my $username = $cfg->param('username');
my $password = $cfg->param('password');

my $user_agent = LWP::UserAgent->new();
$user_agent->cookie_jar( {} );

my $running = 1;

while($running){
    opendir(my $dir_year, $cam_export_path);

    my @file_year = readdir($dir_year);
    closedir($dir_year);

    foreach my $f_year (sort @file_year){
	if($f_year ne '.' && $f_year ne '..'){
	    opendir(my $dir_day, $cam_export_path . '/' . $f_year);

	    my @file_day = readdir($dir_day);
	    closedir($dir_day);

	    foreach my $f_day (sort @file_day){
		if($f_day ne '.' && $f_day ne '..'){
		    opendir(my $dir_hour, $cam_export_path . '/' . $f_year . '/' . $f_day);

		    my @file_hour = readdir($dir_hour);
		    closedir($dir_hour);

		    foreach my $f_hour (sort @file_hour){
			if($f_hour ne '.' && $f_hour ne '..'){
			    opendir(my $dir_min, $cam_export_path . '/' . $f_year . '/' . $f_day . '/' . $f_hour);

			    my @file_min = readdir($dir_min);
			    closedir($dir_min);

			    if(scalar @file_min > 2){
				DEBUG 'found files in: ' . $cam_export_path . '/' . $f_year . '/' . $f_day . "/" . $f_hour . "\n";
			    }

			    foreach my $f_min (sort @file_min){
				if($f_min ne '.' && $f_min ne '..'){
				    my $cam_filename = $cam_export_path . '/' . $f_year . '/' . $f_day . '/' . $f_hour . '/' . $f_min;

				    upload_file($user_agent, $host, $username, $password, $cam_filename);
				}
			    }
			}
		    }
		}
	    }
	}
    }

    sleep(60);
}

0;
