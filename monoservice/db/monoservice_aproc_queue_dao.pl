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

package Monothek::DB;

use Modern::Perl '2015';
use autodie;

use DBI;

sub monoservice_aproc_queue_dao_create {
    my $mysql_connector = $_[0];

    my $query = "INSERT INTO APROC_QUEUE DEFAULT VALUES";

    $mysql_connector->query($query);

    return($mysql_connector->{dbh}->{mysql_insertid});
}

sub monoservice_aproc_queue_dao_delete {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];

    my $query = "DELETE FROM APROC_QUEUE WHERE APROC_QUEUE_ID = '" . $aproc_queue_id . "'";

    $mysql_connector->query($query);
}

sub monoservice_aproc_queue_dao_select {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];

    my $query = "SELECT * FROM APROC_QUEUE WHERE APROC_QUEUE_ID = '" . $aproc_queue_id . "'";

    $mysql_connector->query($query);
}

sub monoservice_aproc_queue_dao_set_video_file {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];
    my $video_file = $_[2];

    my $query = "UPDATE APROC_QUEUE SET VIDEO_FILE = '" . $video_file . "' WHERE APROC_QUEUE_ID = '" . $aproc_queue_id . "'";

    $mysql_connector->query($query);
}

sub monoservice_aproc_queue_dao_set_raw_audio_file {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];
    my $raw_audio_file = $_[2];

    my $query = "UPDATE APROC_QUEUE SET RAW_AUDIO_FILE = '" . $raw_audio_file.  "' WHERE APROC_QUEUE_ID = '" . $aproc_queue_id .  "'";

    $mysql_connector->query($query);
}

sub monoservice_aproc_queue_dao_set_title_strip_audio_file {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];
    my $title_strip_audio_file = $_[2];

    my $query = "UPDATE APROC_QUEUE SET TITLE_STRIP_AUDIO_FILE = '" . $title_strip_audio_file . "' WHERE APROC_QUEUE_ID = '" . $aproc_queue_id . "'";

    $mysql_connector->query($query);
}

sub monoservice_aproc_queue_dao_set_end_credits_audio_file {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];
    my $end_credits_audio_file = $_[2];

    my $query = "UPDATE APROC_QUEUE SET END_CREDITS_AUDIO_FILE = '" . $end_credits_audio_file . "' WHERE APROC_QUEUE_ID = '" . $aproc_queue_id . "'";

    $mysql_connector->query($query);
}

sub monoservice_aproc_queue_dao_set_started {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];
    my $is_started = $_[2];

    my $query = "UPDATE APROC_QUEUE SET STARTED = " . ($is_started ? "true": "false") . " WHERE APROC_QUEUE_ID = '" . $aproc_queue_id . "'";

    $mysql_connector->query($query);
}

sub monoservice_aproc_queue_dao_set_completed {
    my $mysql_connector = $_[0];
    my $aproc_queue_id = $_[1];
    my $is_completed = $_[2];

    my $query = "UPDATE APROC_QUEUE SET COMPLETED = " . ($is_completed ? "true": "false") . " WHERE APROC_QUEUE_ID = '" . $aproc_queue_id . "'";

    $mysql_connector->query($query);    
}
