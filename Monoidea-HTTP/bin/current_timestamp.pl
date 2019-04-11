#!/usr/bin/env perl

$ENV{"TZ"} = "UTC";

my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);

$year += 1900;

printf $year . " " .  $yday . " " . $hour . ":" . $min . ":" . $sec . "\n";
