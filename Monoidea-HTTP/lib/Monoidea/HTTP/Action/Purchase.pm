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

package Monoidea::HTTP::Action::Purchase;

use LWP::UserAgent;
use HTTP::Request;
use HTTP::Request::Common;
use XML::LibXML;

use Moose;
use namespace::clean -except => 'meta';

has 'url' => (is => 'rw', isa => 'Str', required => 1);
has 'session_id' => (is => 'rw', isa => 'Str', lazy_build => 1);
has 'token' => (is => 'rw', isa => 'Str', lazy_build => 1);
has 'media_account_id' => (is => 'rw', isa => 'Str', lazy_build => 1);
has 'payment_id' => (is => 'rw', isa => 'Str', lazy_build => 1);
has 'product_name' => (is => 'rw', isa => 'Str', lazy_build => 1);
has 'position_id' => (is => 'rw', isa => 'Str', lazy_build => 1);
has 'recipe_id' => (is => 'rw', isa => 'Str', lazy_build => 1);
has 'invoice_amount' => (is => 'rw', isa => 'Str', lazy_build => 1);

sub prepare_purchase {
    my ( $self, $user_agent) = @_;

    my $request = HTTP::Request::Common::POST($self->url,
					      Content_Type  => 'form-data',
					      Content       => [ 'session_id' => $self->session_id,
								 'token' => $self->token,
								 'media_account_id' => $self->media_account_id,
								 'product_name' => $self->product_name,
								 'position_id' => $self->position_id,
								 'recipe_id' => $self->recipe_id,
								 'invoice_amount' => $self->invoice_amount,]);

    my $response = $user_agent->request($request);

    if($response->is_success){
	my $doc = XML::LibXML->load_xml(string => $response->decoded_content);

	my $root_node = $doc->documentElement;

	foreach my $child ($root_node->childNodes){
	    if($child->nodeName eq 'session-id'){
		$self->session_id($child->to_literal());
	    }elsif($child->nodeName eq 'token'){
		$self->token($child->to_literal());
	    }elsif($child->nodeName eq 'media-account'){
		$self->media_account_id($child->to_literal());
	    }elsif($child->nodeName eq 'payment'){
		$self->payment_id($child->to_literal());
	    }
	}
    }

    return($response);
}

sub cancel_purchase {
    my ( $self, $user_agent) = @_;

    my $request = HTTP::Request::Common::POST($self->url,
					      Content_Type  => 'form-data',
					      Content       => [ 'payment_id' => $self->payment_id,
]);

    my $response = $user_agent->request($request);

    return($response);
}

sub completed_purchase {
    my ( $self, $user_agent) = @_;

    my $request = HTTP::Request::Common::POST($self->url,
					      Content_Type  => 'form-data',
					      Content       => [ 'payment_id' => $self->payment_id,
]);

    my $response = $user_agent->request($request);

    return($response);
}

__PACKAGE__->meta->make_immutable;

1;
