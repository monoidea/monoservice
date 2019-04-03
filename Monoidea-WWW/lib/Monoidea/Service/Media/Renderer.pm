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

package Monoidea::Media::Renderer;

use Moose;
use namespace::clean -except => 'meta';

has 'audio_source' => (is => 'rw', isa => 'ArrayRef[Monoidea::Media::Resource]', required => 1);
has 'video_source' => (is => 'rw', isa => 'ArrayRef[Monoidea::Media::Resource]', required => 1);
has 'destination_filename' => (is => 'rw', isa => 'Str', required => 1);
has 'start_timestamp_sec' => (is => 'rw', isa => 'Num', required => 1);
has 'end_timestamp_sec' => (is => 'rw', isa => 'Num', required => 1);

sub concat {
}

__PACKAGE__->meta->make_immutable;

1;
