package Monoidea::WWW::Controller::Upload;
use Moose;
use namespace::autoclean;

BEGIN { extends 'Catalyst::Controller'; }

=head1 NAME

Monoidea::WWW::Controller::Upload - Catalyst Controller

=head1 DESCRIPTION

Catalyst Controller.

=head1 METHODS

=cut


=head2 index

=cut

sub index :Path :Args(0) {
    my ( $self, $c ) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_upload / )){
#TODO:JK: implement me
    }else{
	$c->detach("access_denied");
    }
}

sub access_denied :Local :Args(0) {
    my ( $self, $c ) = @_;

    $c->stash->{'template'} = 'accessdenied.tt';
}

sub put_cam_record :Local {
    my ($self, $c) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_upload / )){
#TODO:JK: implement me

	$c->response->body('success');
	$c->response->status(200);
    }else{
	$c->detach("access_denied");
    }
}

sub put_screen_capture :Local {
    my ($self, $c) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_upload / )){
#TODO:JK: implement me

	$c->response->body('success');
	$c->response->status(200);
    }else{
	$c->detach("access_denied");
    }
}

sub put_mic_capture :Local {
    my ($self, $c) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_upload / )){
#TODO:JK: implement me

	$c->response->body('success');
	$c->response->status(200);
    }else{
	$c->detach("access_denied");
    }
}

sub put_audio_export :Local {
    my ($self, $c) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_upload / )){
#TODO:JK: implement me

	$c->response->body('success');
	$c->response->status(200);
    }else{
	$c->detach("access_denied");
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
