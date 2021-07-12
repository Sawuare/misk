#! /bin/bash

# ftc.sh - File Tab Count

for f in "$@"
do
	if [ -f "$f" ] && [ -r "$f" ]
	then
		((c += $(tr -cd '\t' < "$f" | wc -c)))
	fi
done

echo "$c"
