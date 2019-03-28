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
use Test::More tests => 8;

BEGIN {
    use_ok( 'Monoidea::DB::MySQLConnectorManager' );
}

# create a Monoidea::DB::MySQLConnector object
my $connector_manager = Monoidea::DB::MySQLConnectorManager->get_instance();

# now test it works as advertised
cmp_ok(ref($connector_manager), 'eq', 'Monoidea::DB::MySQLConnectorManager', "is a Monoidea::DB::MySQLConnectorManager");
cmp_ok(ref(@{$connector_manager->connector()}[0]), 'eq', 'Monoidea::DB::MySQLConnector', "is a Monoidea::DB::MySQLConnector");

# add connector
my $connector = Monoidea::DB::MySQLConnector->new(hostname => 'localhost',
						  user => 'monothek',
						  password => 'secret',
						  db_name => 'MONOSERVICE',
						  port => 3306,
						  dsn => 'DBI:mysql:MONOSERVICE@localhost:3306');

$connector_manager->add_connector($connector);

# now test last element
cmp_ok(ref(@{$connector_manager->connector()}[$#{$connector_manager->connector()}]), 'eq', 'Monoidea::DB::MySQLConnector', "is a Monoidea::DB::MySQLConnector");
cmp_ok((grep { $_ eq $connector } @{$connector_manager->connector()}), '==', 1, "connector manager contains connector");

cmp_ok(scalar @{$connector_manager->connector()}, '==', 2, "array element count == 2");

# remove connector
$connector_manager->remove_connector($connector);

# now test last element
cmp_ok((grep { $_ eq $connector } @{$connector_manager->connector()}), '==', 0, "connector manager doesn't contain connector");

cmp_ok(scalar @{$connector_manager->connector()}, '==', 1, "array element count == 1");
