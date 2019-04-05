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

use warnings;
use strict;
use Test::More tests => 7;

use File::Basename;
use LWP::UserAgent;

use Monoidea::HTTP::Action::Login;

BEGIN {
    use_ok( 'Monoidea::HTTP::Action::Upload' );
}

my $upload = Monoidea::HTTP::Action::Upload->new(url => 'http://localhost:3000/upload/put_cam',
						 filename => 'cam-001.mp4',
						 creation_time => 1554431634,
						 duration => 60,
						 media_file => dirname (__FILE__) . '/cam-001.mp4');


# now test it works as advertised
cmp_ok(ref($upload), 'eq', 'Monoidea::HTTP::Action::Upload', "is a Monoidea::HTTP::Action::Upload");
cmp_ok($upload->url, 'eq', 'http://localhost:3000/upload/put_cam', 'correct URL');
cmp_ok($upload->filename, 'eq', 'cam-001.mp4', 'correct filename');
cmp_ok($upload->creation_time, '==', 1554431634, 'correct creation time');
cmp_ok($upload->duration, '==', 60, 'correct duration');
cmp_ok($upload->media_file, 'eq', dirname (__FILE__) . '/cam-001.mp4', 'correct media file');

my $user_agent = LWP::UserAgent->new();
$user_agent->cookie_jar( {} );

my $login = Monoidea::HTTP::Action::Login->new(url => 'http://localhost:3000/people/login',
	  				       username => 'admin',
					       password => 'secret');

$login->do_login($user_agent);
my $response = $upload->do_upload($user_agent);

printf $response->content;
