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

my $HTTP_STATUS_MESSAGE_OK = "OK";
my $HTTP_STATUS_CODE_OK = 200;

my $HTTP_STATUS_MESSAGE_MALFORMED = "Bad Request";
my $HTTP_STATUS_CODE_MALFORMED = 400;

my $HTTP_STATUS_MESSAGE_FORBIDDEN = "Forbidden";
my $HTTP_STATUS_CODE_FORBIDDEN = 403;

my $MONOSERVICE_UPLOAD_DEFAULT_USERNAME = "monothek";
my $MONOSERVICE_UPLOAD_DEFAULT_TOKEN = "monothek";

my $MONOSERVICE_UPLOAD_DEFAULT_BUFFER_SIZE = 131072;

sub monoservice_upload_write_status {
    my $status_message = $_[0];
    my $status_code = $_[1];
    
    print "HTTP/1.1 " . $status_code . " " . $status_message .  "\r\n";
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

# log file handle
open my $log_file, '>', '/dev/stderr';

# content type and its boundary
my $content_length;
my $content_type;

my $boundary;

# check content type
$content_type = $ENV{'CONTENT_TYPE'};
$content_length = $ENV{'CONTENT_LENGTH'};

if(!(defined $content_type &&
     defined $content_length)){
    monoservice_upload_write_status($HTTP_STATUS_MESSAGE_MALFORMED, $HTTP_STATUS_CODE_MALFORMED);
    
    exit(0);
}

if(!($content_type =~ /^Content-Type: multipart\/form-data;/)){
    monoservice_upload_write_status($HTTP_STATUS_MESSAGE_MALFORMED, $HTTP_STATUS_CODE_MALFORMED);
    
    exit(0);
}

# get boundary
($boundary) = ($content_type =~ /boundary=([\d\w'()+,-.\/:=?]+)/);

# print $log_file "got boundary: " . $boundary . "\n";

# find username and token
my $username;
my $token;

my $bytes;
my $bytes_read;

$bytes_read = read STDIN, $bytes, $MONOSERVICE_UPLOAD_DEFAULT_BUFFER_SIZE;

my @http_params = ($bytes =~ m/((?:\Q${boundary}\E(?:\r\n.*?){3})(?:(?=\r\n)))/sgmp);

for(my $i = 0; $i < scalar(@http_params); $i += 1){
#    print $log_file "nth: " . $i . "\n";
#    print $log_file $http_params[$i] . "\n";
    
    if($http_params[$i] =~ /Content-Disposition: form-data; name=\"username\"/g){
	($username) = $http_params[$i] =~ m/([\w\d\-_]+)$/;

	print $log_file "username: ****\n";
    }elsif($http_params[$i] =~ /Content-Disposition: form-data; name=\"token\"/g){
	($token) = $http_params[$i] =~ m/([\w\d\-_]+)$/;

	print $log_file "token : ****\n";
    }
}

# authenticate
if(!monoservice_upload_authenticate($username, $token)){
    monoservice_upload_write_status($HTTP_STATUS_MESSAGE_FORBIDDEN, $HTTP_STATUS_CODE_FORBIDDEN);

    exit(0);
}

if($bytes_read < $content_length){
    $bytes_read = read STDIN, $bytes, $content_length - $bytes_read, $bytes_read;
}

#TODO:JK: implement me
