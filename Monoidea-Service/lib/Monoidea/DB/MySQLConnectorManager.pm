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

package Monoidea::DB::MySQLConnectorManager;

use Moose;

use List::Util qw(first);

use Monoidea::DB::MySQLConnector;

my $mysql_connector_manager;

has 'connector' => (is => 'rw', isa => 'ArrayRef[Monoidea::DB::MySQLConnector]', required => 1);

sub add_connector {
    my ($self, $connector) = @_;

    push(@{$self->connector()}, $connector);
}

sub remove_connector {
    my ($self, $connector) = @_;

    my $success = 0;

    for(my $i = 0; $i < scalar @{$self->connector()} && !$success; $i += 1){
	if(${$self->connector()}[$i] == $connector){
	    splice(@{$self->connector()}, $i, 1);

	    $success = 1;
	}
    }
}

sub get_connector_by_hostname {
    my ($self, $hostname) = @_;

    my @connector_arr = @{$self->connector()};

    my $retval = first { $_->hostname() eq $hostname } @connector_arr;
    
    return($retval);
}

sub get_instance {
    if(!(defined $mysql_connector_manager)){
	my $local_connector = Monoidea::DB::MySQLConnector->new(hostname => 'localhost',
								user => 'monothek',
								password => 'monothek',
								db_name => 'MONOSERVICE',
								port => 3306,
								dsn => Monoidea::DB::MySQLConnector->create_dsn('MONOSERVICE', 'localhost', 3306));

	my @connector_arr;
	
	$connector_arr[0] = $local_connector;

	$mysql_connector_manager = Monoidea::DB::MySQLConnectorManager->new(connector => \@connector_arr);
    }

    return($mysql_connector_manager);
}

1;
__END__
=head1 NAME

Monoidea::DB::MySQLConnectorManager

=head1 SYNOPSIS

The monoidea's MySQL database connector manager.

my $connector_manager = Monoservice::DB::MySQLConnectorManager->get_instance();

=head1 METHODS

=head2 add_connector

Add $connector to $connector_manager.

=head2 remove_connector

Remove $connector from $connector_manager.

=head2 get_by_hostname

Find @connector by specifying $hostname.

=head2 get_instance

Get Monoservice::DB::MySQLConnectorManager singleton.
