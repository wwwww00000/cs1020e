#!/bin/bash -x
inputs="input/*.in"
regex="input/([a-z0-9_]+).in"
for f in $inputs; do
	if [[ $f =~ $regex ]]
	then
		test_case="${BASH_REMATCH[1]}"
		out_name="output/${test_case}.out"
		./a.out < $f | diff $out_name -
	fi
done
