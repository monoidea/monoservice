package Monoidea::WWW::Controller::Purchase;
use Moose;
use XML::LibXML;
use namespace::autoclean;

BEGIN { extends 'Catalyst::Controller'; }

=head1 NAME

Monoidea::WWW::Controller::Purchase - Catalyst Controller

=head1 DESCRIPTION

Catalyst Controller.

=head1 METHODS

=cut


=head2 index

=cut

sub index :Path :Args(0) {
    my ( $self, $c ) = @_;

    $c->response->body('Matched Monoidea::WWW::Controller::Purchase in Purchase.');
}

sub prepare :Local {
    my ( $self, $c ) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_transaction / )){
	my $session_id = $c->req->params->{'session_id'};
	my $token = $c->req->params->{'token'};
	my $media_account_id = $c->req->params->{'media_account_id'};

	my $product_name = $c->req->params->{'product_name'};
	my $position_id = $c->req->params->{'position_id'};
	my $recipe_id = $c->req->params->{'recipe_id'};
	my $invoice_amount = $c->req->params->{'invoice_amount'};

	# get some record sets
	my $session_store_rs = $c->model('MONOSERVICE::SessionStore');
	my $media_account_rs = $c->model('MONOSERVICE::MediaAccount');
	my $billing_address_rs = $c->model('MONOSERVICE::BillingAddress');

	my $product_rs = $c->model('MONOSERVICE::Product');
	my $payment_rs = $c->model('MONOSERVICE::Payment');
	my $purchase_rs = $c->model('MONOSERVICE::Purchase');

	# prepare
	my $current_time = time();

	my $product = $product_rs->find({ product_name => $product_name});

	my $payment = $payment_rs->create({ recipe_id => $recipe_id,
					    invoice_amount => $invoice_amount,
					    due_date => $current_time});

	my $purchase = $purchase_rs->create({ position_id => $position_id,
					      payment => $payment->payment_id,
					      product => $product->product_id,
					      billing_time => $current_time });

	# find billing address, media account and session
	my $session_store;
	my $media_account;
	my $billing_address;

	if($session_id &&
	   $media_account_id){
	    $media_account = $media_account_rs->find({ media_account_id => $media_account_id });

	    $billing_address = $billing_address_rs->find({ billing_address_id => $media_account->billing_address });

	    $session_store = $session_store_rs->find({ media_account => $media_account_id });
	}

	# create billing address, media account and session
	if(!$session_store ||
	   !$media_account ||
	   !$billing_address ||
	   !$session_store->session_id ||
	   !$session_store->token ||
	    $session_store->session_id != $session_id ||
	    $session_store->token != $token){
	    $billing_address = $billing_address_rs->create({ });

	    $media_account = $media_account_rs->create({ billing_address => $billing_address->billing_address_id });

	    my $session_id_guid = Data::GUID->new;
	    my $token_guid = Data::GUID->new;

	    $session_id = $session_id_guid->as_string;
	    $token = $token_guid->as_string;

	    $session_store = $session_store_rs->create({ media_account => $media_account->media_account_id,
							 session_id => $session_id,
							 token => $token });
	}else{
	    $session_id = $session_store->session_id;
	    $token = $session_store->token;
	}

	# create response
	my $dom = XML::LibXML::Document->new('1.0', 'UTF-8');

	my $root_node = $dom->createElement('monoidea-order');
	$dom->setDocumentElement($root_node);

	my $node;

	$node = $dom->createElement('session-id');
	$node->appendText($session_id);
	$root_node->appendChild($node);

	$node = $dom->createElement('token');
	$node->appendText($token);
	$root_node->appendChild($node);

	$node = $dom->createElement('media-account');
	$node->appendText($media_account_id);
	$root_node->appendChild($node);

	$node = $dom->createElement('payment');
	$node->appendText($payment->payment_id);
	$root_node->appendChild($node);

	# write response
	my $response_body = $dom.toString();

	$c->response->headers->content_type('text/xml');
	$c->response->headers->content_length(length($response_body));
	$c->response->headers->last_modified($current_time);

	$c->response->body($response_body);
    }else{
	$c->detach("access_denied");
    }
}

sub cancel :Local {
    my ( $self, $c ) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_transaction / )){
	my $payment_id = $c->req->params->{'payment_id'};

	my $payment_rs = $c->model('MONOSERVICE::Payment');

	my $payment = $payment_rs->find({ payment_id => $payment_id });

	$payment->update({ due_date => undef });
    }else{
	$c->detach("access_denied");
    }
}

sub completed :Local {
    my ( $self, $c ) = @_;

    if($c->user_exists() && $c->check_user_roles( qw / can_transaction / )){
	my $payment_id = $c->req->params->{'payment_id'};

	my $payment_rs = $c->model('MONOSERVICE::Payment');

	my $payment = $payment_rs->find({ payment_id => $payment_id });

	$payment->update({ completed => 1 });
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
