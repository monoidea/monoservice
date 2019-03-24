#!/bin/bash

echo -e -n "POST / HTTP/1.1\r\nHost: localhost:8080\r\nContent-Type: multipart/form-data; boundary=abs\r\nContent-Length: 332\r\n\r\nabs\r\nContent-Disposition: form-data; name=\"username\"\r\n\r\nmonothek\r\nabs\r\nContent-Disposition: form-data; name=\"token\"\r\n\r\nmonothek\r\nabs\r\nContent-Disposition: form-data; name=\"media_timestamp\"\r\n\r\n1553204231\r\n" | PERL5LIB=/home/joelkraehemann/github/monoservice:/home/joelkraehemann/perl5/lib/perl5/x86_64-linux-gnu-thread-multi CONTENT_TYPE="Content-Type: multipart/form-data; boundary=abs" CONTENT_LENGTH="332" ./Monoservice/cgi-bin/monoservice_upload.pl
    
