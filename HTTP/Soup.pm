package HTTP::Soup;

use Glib::Object::Introspection;

sub import {
  Glib::Object::Introspection->setup(basename => $BASENAME,
                                     version => $VERSION,
                                     package => $PACKAGE);
}

$BASENAME = 'Soup'; $VERSION = '2.4'; $PACKAGE = 'HTTP::Soup';
