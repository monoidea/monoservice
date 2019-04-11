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

my ($purchase_filename, $product_name, $position_id, $recipe_id, $invoice_amount, $session_id, $token, $media_account_id) = @ARGV;

if(!$purchase_filename ||
   !$product_name ||
   !$position_id ||
   !$recipe_id ||
   !$invoice_amount){
    printf "prepare_purchase.pl PURCHASE_FILENAME PRODCUT_NAME POSITION_ID RECIPE_ID INVOICE_AMOUNT <SESSION_ID TOKEN MEDIA_ACCOUNT_ID>\n";

    exit(0);
}

if(!$session_id){
    $session_id = '';
    $token = '';
    $media_account_id = '';
}

my $host = $cfg->param('host');
my $username = $cfg->param('username');
my $password = $cfg->param('password');

my $user_agent = LWP::UserAgent->new();
$user_agent->cookie_jar( {} );

my $login_url = 'http://' . $host . '/people/login';
my $logout_url = 'http://' . $host . '/people/logout';
my $prepare_purchase_url = 'http://' . $host . '/purchase/prepare';

my $purchase_doc;
my $root_node;

my $pp = XML::LibXML::PrettyPrint->new(indent_string => "  ");

if(-e $purchase_filename){
    $purchase_doc = XML::LibXML->load_xml(location => $purchase_filename);
    $root_node = $purchase_doc->documentElement;
}

if(!$purchase_doc ||
   !$root_node){
    $purchase_doc = XML::LibXML->createDocument();

    $root_node = XML::LibXML::Element->new('monoidea-purchase');
    $purchase_doc->setDocumentElement($root_node);

    $pp->pretty_print($purchase_doc);

    $purchase_doc->toFile($purchase_filename, 2);
}

my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime(time);
$year += 1900;
$mon += 1;

my $purchase_node = XML::LibXML::Element->new('purchase');
$purchase_node->setAttribute(timestamp => sprintf("%04d-%02d-%02d %02d:%02d:%02d", $year, $mon, $mday, $hour, $min, $sec));
$root_node->appendChild($purchase_node);

my $success = 0;
my $i = 0;

while(!$success && $i < 5){
    DEBUG "login: ****";

    my $login = Monoidea::HTTP::Action::Login->new(url => $login_url,
						   username => $username,
						   password => $password);
    $login->do_login($user_agent);

    DEBUG "prepare purchase - product name: " . $product_name;

    my $purchase = Monoidea::HTTP::Action::Purchase->new(url => $prepare_purchase_url,
							 session_id => $session_id,
							 token => $token,
							 media_account_id => $media_account_id,
							 product_name => $product_name,
							 position_id => $position_id,
							 recipe_id => $recipe_id,
							 invoice_amount => $invoice_amount);
    my $response = $purchase->prepare_purchase($user_agent);

    if($response->is_success){
	$success = 1;

	DEBUG "prepare purchase - success ";

	my $node;

	$node = XML::LibXML::Element->new('product-name');
	$node->appendText($product_name);
	$purchase_node->appendChild($node);

	$node = XML::LibXML::Element->new('position-id');
	$node->appendText($position_id);
	$purchase_node->appendChild($node);

	$node = XML::LibXML::Element->new('recipe-id');
	$node->appendText($recipe_id);
	$purchase_node->appendChild($node);

	$node = XML::LibXML::Element->new('invoice-amount');
	$node->appendText($invoice_amount);
	$purchase_node->appendChild($node);

	my $response_doc = XML::LibXML->load_xml(string => $response->decoded_content);

	my $order_node = $response_doc->documentElement->cloneNode(1);
	$order_node->setNodeName('order');

	$purchase_node->appendChild($order_node);
    }

    HTTP::Request::Common::GET($logout_url);

    if(!$success){
	DEBUG "prepare purchase failed - attempt " . ($i + 1) . "/5 retrying in 1 seconds";

	sleep(1);
    }

    $i++;
}

if(!$success){
	my $node;

	DEBUG "prepare purchase failed - giving up";

	$node = XML::LibXML::Element->new('status');
	$node->setAttribute(value => 'failed');
	$purchase_node->appendChild($node);
}

$pp->pretty_print($purchase_doc);

$purchase_doc->toFile($purchase_filename, 2);
