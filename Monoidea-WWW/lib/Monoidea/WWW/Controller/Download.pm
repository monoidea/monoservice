package Monoidea::WWW::Controller::Download;
use Moose;
use namespace::autoclean;

BEGIN { extends 'Catalyst::Controller'; }

=head1 NAME

Monoidea::WWW::Controller::Download - Catalyst Controller

=head1 DESCRIPTION

Catalyst Controller.

=head1 METHODS

=cut


=head2 index

=cut

sub index :Path :Args(0) {
    my ( $self, $c ) = @_;

    my $session_id = $c->req->params->{'session_id'};
    my $token = $c->req->params->{'token'};

    my $session_store_rs = $c->model('MONOSERVICE::SessionStore');

    if($session_store_rs->find({session_id => $session_id},
			       {toke => $token})){
	$c->stash(
	    session_id => $session_id,
	    token => $token,
	    current_view => 'Download',
	    );
    }else{
	$c->detach("access_denied");
    }
}

sub access_denied :Local :Args(0) {
    my ( $self, $c ) = @_;

    $c->stash->{'template'} = 'accessdenied.tt';
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
