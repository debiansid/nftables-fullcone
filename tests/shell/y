#!/bin/bash

rm -f leak.txt

cat x | while read line
do
	echo "running $line..."
	sh -c 'echo clear > /sys/kernel/debug/kmemleak'
	./run-tests.sh $line
	echo "... checking for leaks"
	sh -c 'echo scan > /sys/kernel/debug/kmemleak'
	LINES=`cat /sys/kernel/debug/kmemleak | grep nfnetlink | wc -l | cut -d' ' -f 1`
	echo $LINES
	if [ $LINES -ne 0 ]
	then
		echo "POSSIBLE LEAK!!!!!!!!!"
		echo "$line" >> leak.txt
	fi
done
