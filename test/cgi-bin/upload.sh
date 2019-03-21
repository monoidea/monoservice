#!/bin/bash

echo -e -n "abs\r\nContent-Disposition: form-data; name=\"username\"\r\n\r\nmonothek\r\nabs\r\nContent-Disposition: form-data; name=\"token\"\r\n\r\nmonothek\r\n" | PERL5LIB=/home/joelkraehemann/github/monoservice:/home/joelkraehemann/perl5/lib/perl5/x86_64-linux-gnu-thread-multi CONTENT_TYPE="Content-Type: multipart/form-data; boundary=abs" CONTENT_LENGTH="0" ./Monoservice/cgi-bin/monoservice_upload.pl
    
