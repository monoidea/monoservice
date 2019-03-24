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

package Monoservice::Log::Logger;

use Modern::Perl '2015';
use autodie;

use Log::Log4perl qw(get_logger);

sub new {
    my ($class, $args) = @_;

    Log::Log4perl::init(\$args->{conf});
    my $log = get_logger("Monoservice::Log::Logger");
    
    my $self = bless {
	conf => $args->{conf},
	log => $log,
    }, $class;
}

1;
