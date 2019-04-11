#!/usr/bin/env perl

use strict;
use warnings;

use Log::Log4perl qw(:easy);
Log::Log4perl->easy_init($DEBUG);

use Config::Simple;
use LWP::UserAgent;
use XML::LibXML;
use XML::LibXML::PrettyPrint;
use Monoidea::HTTP::Action::Login;
use Monoidea::HTTP::Action::Purchase;

$ENV{"TZ"} = "UTC";

my $cfg = new Config::Simple('monoidea_http.conf');

my ($purchase_filename, $payment_id) = @ARGV;

if(!$purchase_filename ||
   !$payment_id){
    printf "completed_purchase.pl PURCHASE_FILENAME PAYMENT_ID\n";

    exit(0);
}

my $host = $cfg->param('host');
my $username = $cfg->param('username');
my $password = $cfg->param('password');

my $user_agent = LWP::UserAgent->new();
$user_agent->cookie_jar( {} );

my $login_url = 'http://' . $host . '/people/login';
my $logout_url = 'http://' . $host . '/people/logout';
my $completed_purchase_url = 'http://' . $host . '/purchase/completed';

my $purchase_doc;
my $root_node;

if(-e $purchase_filename){
    $purchase_doc = XML::LibXML->load_xml(location => $purchase_filename);
    $root_node = $purchase_doc->documentElement;
}else{
    ERROR "file doesn't exist: " . $purchase_filename;

    exit(-1);
}

my $pp = XML::LibXML::PrettyPrint->new(indent_string => "  ");

my ($purchase_node) = $root_node->findnodes('/monoidea-purchase/purchase/order/payment[text()=' . $payment_id . ']/ancestor::*[self::purchase][1]');

if(!$purchase_node){
    ERROR "no such payment id: " . $payment_id;

    exit(-1);
}

my $success = 0;
my $i = 0;

while(!$success && $i < 5){
    DEBUG "login: ****";

    my $login = Monoidea::HTTP::Action::Login->new(url => $login_url,
						   username => $username,
						   password => $password);
    $login->do_login($user_agent);

    DEBUG "completed purchase - payment id: " . $payment_id;

    my $purchase = Monoidea::HTTP::Action::Purchase->new(url => $completed_purchase_url,
							 payment_id => $payment_id);
    my $response = $purchase->completed_purchase($user_agent);

    if($response->is_success){
	$success = 1;

	my $node;

	DEBUG "completed purchase - success ";

	$node = XML::LibXML::Element->new('status');
	$node->setAttribute(value => 'completed');
	$purchase_node->appendChild($node);
    }

    HTTP::Request::Common::GET($logout_url);

    if(!$success){
	DEBUG "completed purchase failed - attempt " . ($i + 1) . "/5 retrying in 1 seconds";

	sleep(1);
    }

    $i++;
}

if(!$success){
	my $node;

	ERROR "completed purchase failed - giving up";

	$node = XML::LibXML::Element->new('status');
	$node->setAttribute(value => 'error: failed to set completed');
	$purchase_node->appendChild($node);
}

$pp->pretty_print($purchase_doc);

$purchase_doc->toFile($purchase_filename, 2);
