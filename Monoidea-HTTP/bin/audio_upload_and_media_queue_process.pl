#!/usr/bin/env perl

use strict;
use warnings;

use Log::Log4perl qw(:easy);
Log::Log4perl->easy_init($DEBUG);

use DateTime::Format::Strptime;
use File::Basename;
use Config::Simple;
use LWP::UserAgent;
use Monoidea::HTTP::Action::Login;
use Monoidea::HTTP::Action::Upload;
use Monoidea::HTTP::Action::Export;

$ENV{"TZ"} = "UTC";

my $cfg = new Config::Simple('monoidea_http.conf');

my ($media_account_id, $audio_export_filename) = @ARGV;

if(!$media_account_id ||
   !$audio_export_filename){
    printf "audio_upload_and_media_queue_process.pl MEDIA_ACCOUNT_ID FILENAME\n";

    exit(0);
}

my $host = $cfg->param('host');
my $username = $cfg->param('username');
my $password = $cfg->param('password');

my $user_agent = LWP::UserAgent->new();
$user_agent->cookie_jar( {} );

my $login_url = 'http://' . $host . '/people/login';
my $logout_url = 'http://' . $host . '/people/logout';
my $upload_url = 'http://' . $host . '/upload/put_raw_audio';
my $export_url = 'http://' . $host . '/mediaqueue/export';

my $creation_time = 0;
my $duration = 0;
my $success = 0;

while(!$success){    
    my ($creation_year, $creation_yday, $creation_hour, $creation_min, $creation_sec);

    ($creation_year, $creation_yday, $creation_hour, $creation_min, $creation_sec, $duration) = basename($audio_export_filename) =~ m/snd-(\d\d\d\d)-(\d\d\d)-(\d\d)-(\d\d)-(\d\d)-(\d\d\d\d\d\d).wav/;

    my $creation_time_str = $creation_year . ' ' . $creation_yday . ' ' . $creation_hour . ':' . $creation_min . ':' . $creation_sec;

    my $date_parser = DateTime::Format::Strptime::->new(
	pattern => ("%Y %j %T"),
	time_zone => 'GMT-0',
	);
    my $dt;

    $dt = $date_parser->parse_datetime($creation_time_str);
    $creation_time = $dt->epoch();
    
    DEBUG "login: ****";

    my $login = Monoidea::HTTP::Action::Login->new(url => $login_url,
						   username => $username,
						   password => $password);
    $login->do_login($user_agent);

    DEBUG "upload - filename: " . $audio_export_filename;
    DEBUG "upload - creation_time: " . $creation_time_str . "[" . $creation_time. "]";

    my $upload = Monoidea::HTTP::Action::Upload->new(url => $upload_url,
						     filename => 'snd-' . $creation_year . '-' . $creation_yday . '-' . $creation_hour . '-' . $creation_min . '-' . $creation_sec . '.wav',
						     creation_time => $creation_time,
						     duration => $duration,
						     media_file => $audio_export_filename);
    my $response = $upload->do_upload($user_agent);

    if($response->is_success){
	$success = 1;

	DEBUG "response success - remove file: " . $audio_export_filename;

	unlink $audio_export_filename;
    }

    HTTP::Request::Common::GET($logout_url);

    if(!$success){
	DEBUG "upload failed - new attempt within 60 seconds";

	sleep(60);
    }
}

$success = 0;

while(!$success){
    DEBUG "login: ****";

    my $login = Monoidea::HTTP::Action::Login->new(url => $login_url,
						   username => $username,
						   password => $password);
    $login->do_login($user_agent);

    my $export = Monoidea::HTTP::Action::Export->new(url => $export_url,
						     media_account_id => $media_account_id,
						     creation_time => $creation_time,
						     duration => $duration);
    my $response = $export->do_export($user_agent);

    if($response->is_success){
	$success = 1;

	DEBUG "response success";
    }
}
