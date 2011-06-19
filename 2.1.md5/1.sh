#!/bin/bash

if [[ !(-r $1 && -r $2)  ]]; then 
	echo "files aren’t readable" ;
	exit
fi

declare -A Array

exec < $1
while read md5 siz;
do
	while read fil && [[ -n $fil ]];
	do
		Array[$fil]="$md5|$siz"
	done;
done;

exec < $2
while read md5 siz fil;
do
	if [[ ${Array[$fil]} != "$md5|$siz" ]];
	then
		echo "changed file: $fil.before: ${Array[$fil]}.after: $md5|$siz"
	fi;
done;
