#!/bin/bash -xe
inputs="testdata_students/*.in"
regex="([a-z0-9]+).in"
for f in $inputs; do
	if [[ $f =~ $regex ]]
	then
		test_case="${BASH_REMATCH[1]}"
		out_name="testdata_students/${test_case}.out"
		./a.out < $f | diff $out_name -
	fi
done
