use utf8;
package Monoidea::Schema::Result::Payment;

# Created by DBIx::Class::Schema::Loader
# DO NOT MODIFY THE FIRST PART OF THIS FILE

=head1 NAME

Monoidea::Schema::Result::Payment

=cut

use strict;
use warnings;

use Moose;
use MooseX::NonMoose;
use MooseX::MarkAsMethods autoclean => 1;
extends 'DBIx::Class::Core';

=head1 COMPONENTS LOADED

=over 4

=item * L<DBIx::Class::InflateColumn::DateTime>

=back

=cut

__PACKAGE__->load_components("InflateColumn::DateTime");

=head1 TABLE: C<PAYMENT>

=cut

__PACKAGE__->table("PAYMENT");

=head1 ACCESSORS

=head2 payment_id

  data_type: 'integer'
  is_auto_increment: 1
  is_nullable: 0

=head2 billing_address

  data_type: 'integer'
  is_foreign_key: 1
  is_nullable: 1

=head2 invoice_amount

  data_type: 'decimal'
  is_nullable: 1
  size: [15,2]

=head2 due_date

  data_type: 'timestamp'
  datetime_undef_if_invalid: 1
  default_value: '0000-00-00 00:00:00'
  is_nullable: 0

=head2 completed

  data_type: 'tinyint'
  is_nullable: 1

=cut

__PACKAGE__->add_columns(
  "payment_id",
  { data_type => "integer", is_auto_increment => 1, is_nullable => 0 },
  "billing_address",
  { data_type => "integer", is_foreign_key => 1, is_nullable => 1 },
  "invoice_amount",
  { data_type => "decimal", is_nullable => 1, size => [15, 2] },
  "due_date",
  {
    data_type => "timestamp",
    datetime_undef_if_invalid => 1,
    default_value => "0000-00-00 00:00:00",
    is_nullable => 0,
  },
  "completed",
  { data_type => "tinyint", is_nullable => 1 },
);

=head1 PRIMARY KEY

=over 4

=item * L</payment_id>

=back

=cut

__PACKAGE__->set_primary_key("payment_id");

=head1 RELATIONS

=head2 billing_address

Type: belongs_to

Related object: L<Monoidea::Schema::Result::BillingAddress>

=cut

__PACKAGE__->belongs_to(
  "billing_address",
  "Monoidea::Schema::Result::BillingAddress",
  { billing_address_id => "billing_address" },
  {
    is_deferrable => 1,
    join_type     => "LEFT",
    on_delete     => "RESTRICT",
    on_update     => "RESTRICT",
  },
);

=head2 purchases

Type: has_many

Related object: L<Monoidea::Schema::Result::Purchase>

=cut

__PACKAGE__->has_many(
  "purchases",
  "Monoidea::Schema::Result::Purchase",
  { "foreign.payment" => "self.payment_id" },
  { cascade_copy => 0, cascade_delete => 0 },
);


# Created by DBIx::Class::Schema::Loader v0.07049 @ 2019-04-01 07:33:52
# DO NOT MODIFY THIS OR ANYTHING ABOVE! md5sum:rDt8+JjbL/76DnwKY9cS4g


# You can replace this text with custom code or comments, and it will be preserved on regeneration
__PACKAGE__->meta->make_immutable;
1;
