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

package Monoidea::DB::MySQLConnector;
use Moose;

use DBI;

has 'hostname' => (is => 'rw', isa => 'Str', required => 1);
has 'user' => (is => 'rw', isa => 'Str', required => 1);
has 'password' => (is => 'rw', isa => 'Str', required => 1);
has 'db_name' => (is => 'rw', isa => 'Str', required => 1);
has 'port' => (is => 'rw', isa => 'Num', required => 1);
has 'dsn' => (is => 'rw', isa => 'Str', lazy_build => 1);

has 'dbh' => (is => 'rw', isa => 'ScalarRef', required => 0);

sub create_dsn {
    my ($self, $db_name, $hostname, $port) = @_;

    my $dsn = "DBI:mysql:" . $db_name . "@" . $hostname . ":" . $port;

    return($dsn);
}

sub connect {
    my ($self) = @_;

    $self->dbh(DBI->connect($self->dsn, $self->username, $self->password));
}

sub query {
    my ($self, $query) = @_;

    my @row;

    my $sth = $self->dbh->prepare($query);
    $sth->execute();

    @row = $sth->fetchrow_array();

    $sth->finish();

    return(@row);
}

sub close {
    my ($self) = @_;

    $self->dbh->disconnect();
}

1;
__END__
=head1 NAME

Monoidea::DB::MySQLConnector

=head1 SYNOPSIS

The monoidea's MySQL database connector.

my $connector = Monoidea::DB::MySQLConnector->new(hostname => 'localhost',
						  user => 'monothek',
						  password => 'secret',
						  db_name => 'MONOSERVICE',
						  port => 3306,
						  dsn => 'DBI:mysql:MONOSERVICE@localhost:3306');

=head1 METHODS

=head2 create_dsn

Create DSN by db_name, hostname and port.

=head2 connect

Connect to DSN using $connector->username and $connector->password and assign $connector->dbh

=head2 query

Exexute $query and return @row array.

=head2 close

Closes $connector->dbh.
