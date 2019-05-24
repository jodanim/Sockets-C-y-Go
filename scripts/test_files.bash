#!/usr/bin/env bash

ruby -e 'a=STDIN.readlines;100000.times do;b=[];16.times do; b << a[rand(a.size)].chomp end; puts b.join(" "); end' < /usr/share/dict/words > file.txt
