package Monoidea::WWW::Controller::MediaQueue;
use Moose;
use namespace::autoclean;
use File::Path;

BEGIN { extends 'Catalyst::Controller'; }

=head1 NAME

Monoidea::WWW::Controller::MediaQueue - Catalyst Controller

=head1 DESCRIPTION

Catalyst Controller.

=head1 METHODS

=cut


=head2 index

=cut

sub index :Path :Args(0) {
    my ( $self, $c ) = @_;

    $c->response->body('Matched Monoidea::WWW::Controller::MediaQueue in MediaQueue.');
}

sub export :Local {
    my ( $self, $c ) = @_;
    
    if($c->user_exists() && $c->check_user_roles( qw / can_export / )){
	my $media_account_id = $c->req->params->{'media_account_id'};
	my $creation_time = $c->req->params->{'creation_time'};
	my $duration = $c->req->params->{'duration'};

	my $video_file_rs = $c->model('MONOSERVICE::VideoFile');
	my $media_account_rs = $c->model('MONOSERVICE::MediaAccount');

	File::Path->make_path($c->config->{download_dir} . '/media/video/' . $creation_time . '/');

	my $video_file = $video_file_rs->create({ filename => $c->config->{download_dir} . '/media/video/' . $creation_time . '/monothek_download.mp4' });


	
    }
}

=encoding utf8

=head1 AUTHOR

Joël Krähemann

=head1 LICENSE

This library is free software. You can redistribute it and/or modify
it under the same terms as Perl itself.

=cut

__PACKAGE__->meta->make_immutable;

1;
