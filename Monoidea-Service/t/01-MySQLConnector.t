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
use Test::More tests => 9;

BEGIN {
    use_ok( 'Monoidea::DB::MySQLConnector' );
}

# create a Monoidea::DB::MySQLConnector object
my $connector = Monoidea::DB::MySQLConnector->new(hostname => 'localhost',
						  user => 'monothek',
						  password => 'secret',
						  db_name => 'MONOSERVICE',
						  port => 3306,
						  dsn => 'DBI:mysql:MONOSERVICE@localhost:3306');

# now test it works as advertised
cmp_ok(ref($connector), 'eq', 'Monoidea::DB::MySQLConnector', "is a Monoidea::DB::MySQLConnector");
cmp_ok($connector->hostname, 'eq', 'localhost', 'correct hostname');
cmp_ok($connector->user, 'eq', 'monothek', 'correct user');
cmp_ok($connector->password, 'eq', 'secret', 'correct password');
cmp_ok($connector->db_name, 'eq', 'MONOSERVICE', 'correct db_name');
cmp_ok($connector->port, 'eq', 3306, 'correct port');
cmp_ok($connector->dsn, 'eq', 'DBI:mysql:MONOSERVICE@localhost:3306', 'correct DSN');

# create DSN
my $dsn = Monoidea::DB::MySQLConnector->create_dsn('MONOSERVICE', 'localhost', 3306);

# now test it works as advertised
cmp_ok($dsn, 'eq', 'DBI:mysql:MONOSERVICE@localhost:3306', 'correct DSN created');
