#!/bin/bash

#echo "Hello World"

#echo -e "First line\nSecond line\nThird line"

#printf "%.3e\n" 23342.6789076

a=10
b="Hello"


echo $a
echo $b
echo Argument from user $1
echo 4th Argument $4

echo 'As it is $a'

temp=`ls`

for f in $temp
do
	echo $f
done


#While loop

count=5

while [ $count -gt 0 ]
do
	echo $count
	let count=count-1
done
