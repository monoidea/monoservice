use 5.006;
use strict;
use warnings;
use inc::Module::Install;

name     'Monoidea-Service';
all_from 'lib/Monoidea/Service.pm';
author   q{Joël Krähemann <jkraehemann@gmail.com>};
license  'artistic2';

perl_version '5.006';

tests_recursive('t');

resources (
   #homepage   => 'http://yourwebsitehere.com',
   #IRC        => 'irc://irc.perl.org/#Monoidea-Service',
   license    => 'http://www.perlfoundation.org/artistic_license_2_0',
   #repository => 'git://github.com/Joël Krähemann/Monoidea-Service.git',
   #repository => 'https://bitbucket.org/Joël Krähemann/Monoidea-Service',
   bugtracker => 'https://rt.cpan.org/NoAuth/Bugs.html?Dist=Monoidea-Service',
);

configure_requires (
   'Module::Install' => '0',
);

test_requires (
   'Test::More' => '0',
);

requires (
   #'ABC'              => '1.6',
   #'Foo::Bar::Module' => '5.0401',
    'Moose',
    'DBI',
);

install_as_cpan;
auto_install;
WriteAll;
