package Monoidea::WWW::Model::MONOSERVICE;

use strict;
use base 'Catalyst::Model::DBIC::Schema';

__PACKAGE__->config(
    schema_class => 'Monoidea::Schema',
    
    connect_info => {
        dsn => 'dbi:mysql:MONOSERVICE',
        user => 'monothek',
        password => 'letmein',
    }
);

=head1 NAME

Monoidea::WWW::Model::MONOSERVICE - Catalyst DBIC Schema Model

=head1 SYNOPSIS

See L<Monoidea::WWW>

=head1 DESCRIPTION

L<Catalyst::Model::DBIC::Schema> Model using schema L<Monoidea::Schema>

=head1 GENERATED BY

Catalyst::Helper::Model::DBIC::Schema - 0.65

=head1 AUTHOR

Joël Krähemann

=head1 LICENSE

This library is free software, you can redistribute it and/or modify
it under the same terms as Perl itself.

=cut

1;