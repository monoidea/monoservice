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

package Monoservice::DB::MySQLConnectorManager;

use Modern::Perl '2015';
use autodie;

use List::Util qw(first);

use Monoservice::DB::MySQLConnector;

my $mysql_connector_manager;

sub add_connector {
    my $self = shift;

    my $connector = $_[0];

    $self->{connector}[++$#$self->{connector}] = $connector;
}

sub remove_connector {
    my $self = shift;

    my $connector = $_[0];

    delete $self->{connector}[first { $self->{connector}[$_] eq $connector } $self->{connector}];
}

sub get_connector_by_hostname {
    my $self = shift;

    my $hostname = $_[0];

    my @connector_arr = @{$self->{connector}};

    my $retval = first { $_->{hostname} eq $hostname } @connector_arr;
    
    return($retval);
}

sub get_instance {
    if(!(defined $mysql_connector_manager)){
	my $local_connector = Monoservice::DB::MySQLConnector->new({ hostname => "localhost",
								     user => "monothek",
								     password => "monothek",
								     db_name => "MONOSERVICE",
								     port => 3306});

	my @connector_arr;
	
	$connector_arr[0] = $local_connector;

	$mysql_connector_manager = Monoservice::DB::MySQLConnectorManager->new({connector => \@connector_arr });
    }

    return($mysql_connector_manager);
}

sub new {
    my ($class, $args) = @_;

    my $self = bless {
	connector => \@{$args->{connector}}
    }, $class;
}

1;
