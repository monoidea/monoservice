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
use Test::More tests => 5;

use LWP::UserAgent;

BEGIN {
    use_ok( 'Monoidea::HTTP::Action::Login' );
}

my $login = Monoidea::HTTP::Action::Login->new(url => 'http://localhost:3000/people/login',
					       username => 'admin',
					       password => 'secret');

# now test it works as advertised
cmp_ok(ref($login), 'eq', 'Monoidea::HTTP::Action::Login', "is a Monoidea::HTTP::Action::Login");
cmp_ok($login->url, 'eq', 'http://localhost:3000/people/login', 'correct URL');
cmp_ok($login->username, 'eq', 'admin', 'correct username');
cmp_ok($login->password, 'eq', 'secret', 'correct password');

my $response = $login->do_login(LWP::UserAgent->new());
