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

package Monoidea::Media::Exporter;

use Moose;
use namespace::clean -except => 'meta';

has 'session_id' => (is => 'rw', isa => 'Str', required => 1);
has 'token' => (is => 'rw', isa => 'Str', required => 1);
has 'start_time_usec' => (is => 'rw', isa => 'Num', required => 1);
has 'end_time_usec' => (is => 'rw', isa => 'Num', required => 1);
has 'renderer' => (is => 'rw', isa => 'Monoidea::Media::Renderer', lazy_build => 1);

sub query {
}

sub persist {
}

sub export {
}

__PACKAGE__->meta->make_immutable;

1;
