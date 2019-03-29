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

package Monoidea::Service;
use Moose;

with 'MooseX::SimpleConfig';

has 'cam_upload_dir' => (is => 'ro', isa => 'Str', required => 1);
has 'audio_upload_dir' => (is => 'ro', isa => 'Str', required => 1);
has 'export_dir' => (is => 'ro', isa => 'Str', required => 1);
has 'ffmpeg_bin' => (is => 'ro', isa => 'Str', required => 1);

1;
__END__
=head1 NAME

Monoidea::Service

=head1 SYNOPSIS

The monoidea's monothek service library routines.
