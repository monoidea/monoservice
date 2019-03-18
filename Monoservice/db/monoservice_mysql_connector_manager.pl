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

package Monoservice::DB::ConnectorManager;

use Modern::Perl '2015';
use autodie;

use List::Util qw(first);

my $mysql_connector_manager;

sub add_connector {
    my $self = shift;

    my $connector = $_[0];

    push $self->{connector}, $connector;
}

sub remove_connector {
    my $self = shift;

    my $connector = $_[0];

    delete $self->{connector}[first { $self->{connector}[$_] eq $connector }];
}

sub get_connector_by_hostname {
    my $self = shift;

    my $hostname = $_[0];

    return $self->{connector}[first { $self->{connector}[$_]->{hostname} eq $hostname }];
}

sub get_instance {
    if(!(defined $mysql_connector_manager)){
	$mysql_connector_manager = new({});
    }

    return($mysql_connector_manager);
}

sub new {
    my ($class, $args) = @_;

    my $self = bless {
	connector => $args->{connector}
    }, $class;
}
