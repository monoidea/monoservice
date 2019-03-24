#!/usr/bin/env perl

# Monoservice - monoidea's monoservice
# Copyright (C) 2019 Joël Krähemann
#
# This file is part of Monoservice.
#
# Monoservice is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Monoservice is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Monoservice.  If not, see <http://www.gnu.org/licenses/>.

use Modern::Perl '2015';
use autodie;

use CGI;
use CGI::Header;

use File::HomeDir;

use lib "/var/cgi-bin";
use Monoservice::DB::MySQLConnectorManager;

use Glib;

use Data::Dumper qw(Dumper);

my $HTTP_STATUS_MESSAGE_OK = "OK";
my $HTTP_STATUS_CODE_OK = 200;

my $HTTP_STATUS_MESSAGE_MALFORMED = "Bad Request";
my $HTTP_STATUS_CODE_MALFORMED = 400;

my $HTTP_STATUS_MESSAGE_FORBIDDEN = "Forbidden";
my $HTTP_STATUS_CODE_FORBIDDEN = 403;

my $MONOSERVICE_UPLOAD_DEFAULT_USERNAME = "monothek";
my $MONOSERVICE_UPLOAD_DEFAULT_TOKEN = "monothek";

my $MONOSERVICE_UPLOAD_DEFAULT_BUFFER_SIZE = 131072;

my $MONOSERVICE_UPLOAD_DEFAULT_METHOD = "PUT";
my $MONOSERVICE_UPLOAD_DEFAULT_URI = "http://monothek.ch/upload/media";

my $MONOSERVICE_UPLOAD_DEFAULT_CONTENT_TYPE = "multipart/form-data";

my $MONOSERVICE_UPLOAD_VIDEO_DIRECTORY = File::HomeDir->my_home . "/monoservice/upload/media/video";
my $MONOSERVICE_UPLOAD_AUDIO_DIRECTORY = File::HomeDir->my_home . "/monoservice/upload/media/audio";

sub monoservice_upload_write_status {
    my $cgi_header = $_[0];
    my $status_message = $_[1];
    my $status_code = $_[2];

    $cgi_header->status($status_code . " " . $status_message);
}

sub monoservice_upload_authenticate{
    my $username = $_[0];
    my $token = $_[1];

    my $auth_username = $MONOSERVICE_UPLOAD_DEFAULT_USERNAME;
    my $auth_token = $MONOSERVICE_UPLOAD_DEFAULT_TOKEN;
    my $success = 0;

    if($username eq $auth_username &&
       $token eq $auth_token){
	$success = 1;
    }

    return($success);
}

my $cgi = CGI->new();
my $cgi_header = CGI::Header->new(query => $cgi,
    );

# log file handle
open my $log_file, '>', '/var/cgi-bin/log/log.txt'; #  '/dev/stderr'

# content type
my $content_length;
my $content_type;

# find username and token
my $username = $cgi->param('username');
my $token = $cgi->param('token');

print $log_file "username = ****\n";
print $log_file "token = ****\n";

# authenticate
if(!(defined $username && defined $token) ||
   monoservice_upload_authenticate($username, $token) == 0){
    monoservice_upload_write_status($cgi_header, $HTTP_STATUS_MESSAGE_FORBIDDEN, $HTTP_STATUS_CODE_FORBIDDEN);

    print $log_file "access denied\n";

    $cgi_header->finalize();
    
    print $CGI::header($cgi_header);

    exit(1);
}

# mysql connector
my $mysql_connector_manager = Monoservice::DB::MySQLConnectorManager->get_instance();
my $mysql_connector = $mysql_connector_manager->get_connector_by_hostname("localhost");

print $log_file "db_name = " . $mysql_connector->{db_name} . "\n";

# decode form data
my $filename;
my $file_content_type;
my $file;

# date
my $upload_timestamp;
my $str;
my $sec;
my $min;
my $hour;
my $mday;
my $mon;
my $year;
my $wday;
my $yday;
my $isdst;

$upload_timestamp = 0;

$str = $cgi->param('media-timestamp');

if(defined $str){
    $upload_timestamp = $str;
}

($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime($upload_timestamp);

# create directory
my $upload_dir;

$upload_dir = $MONOSERVICE_UPLOAD_AUDIO_DIRECTORY . "-" . ($year + 1900) . "-" . $mon . "-" . $mday . "-" . $hour . ":" . $min;

print $log_file $upload_dir . "\n";

monoservice_upload_write_status($cgi_header, $HTTP_STATUS_MESSAGE_OK, $HTTP_STATUS_CODE_OK);

$cgi_header->finalize();

print $CGI::header($cgi_header);

1;
