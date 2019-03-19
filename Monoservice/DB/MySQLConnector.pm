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

package Monoservice::DB::MySQLConnector;

use Modern::Perl '2015';
use autodie;

use lib '/home/joelkraehemann/perl5/lib/perl5/x86_64-linux-gnu-thread-multi/';
use DBI;

sub do_connect {
    my $self = shift;

    $self->{dbh} = DBI->connect($self->{dsn}, $self->{username}, $self->{password});
}

sub do_query {
    my $self = shift;

    my @row;
    my $query = $_[0];

    my $sth = $self->{dbh}->prepare($query);
    $sth->execute();

    @row = $sth->fetchrow_array();

    $sth->finish();

    return(@row);
}

sub do_close {
    my $self = shift;

    $self->{dbh}->disconnect();
}


sub new {
    my ($class, $args) = @_;

    my $self = bless {
	hostname => $args->{hostname},
	user => $args->{user},
	password => $args->{password},
	db_name => $args->{db_name},
	port => $args->{port},
	dsn => "DBI:mysql:" . $args->{db_name} . "@" . $args->{hostname} . ":" . $args->{port}
    }, $class;
}

1;
