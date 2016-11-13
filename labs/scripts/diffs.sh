#!/bin/bash -x
act_outputs="testdata_students/*.actual"
regex="([a-z0-9]+).actual"
for f in $act_outputs; do
	if [[ $f =~ $regex ]]
	then
		test_case="${BASH_REMATCH[1]}"
	fi
	out_name="testdata_students/$test_case.out"
	diff $f $out_name
done
