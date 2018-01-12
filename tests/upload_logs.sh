#!/bin/bash
TOKEN=$(curl --silent https://paste.ee/ |egrep 'token' | awk '{print $NF }' | cut -f2 -d'"')
data=$(python3 -c "from urllib.parse import urlencode; print(urlencode({'_token':'$TOKEN','expiration':86400,'expiration_views':'','description':'lithtech build-log ubuntu 14.04 ($TRAVIS - $CI)','paste[section1][name]':'','paste[section1][syntax]':'text','paste[section1][contents]':open('make.build.log','r').read(),'fixlines':'true','jscheck':'validate'}))")
curl --silent 'https://paste.ee/paste' -H 'Host: paste.ee' -H 'Referer: https://paste.ee/' --data "$data" | grep title
