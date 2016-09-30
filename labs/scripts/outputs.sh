#!/bin/bash -xe
inputs="testdata_students/*.in"
regex="([a-z0-9]+).in"
for f in $inputs; do
	if [[ $f =~ $regex ]]
	then
		test_case="${BASH_REMATCH[1]}"
	fi
	out_name="testdata_students/${test_case}.actual"
	./a.out < $f > $out_name
done
