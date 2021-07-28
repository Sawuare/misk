#! /bin/bash

# ctif.sh - count tabs in files

for f in "$@"
do
	if [ -f "$f" ] && [ -r "$f" ]
	then
		((c += $(tr -cd '\t' < "$f" | wc -c)))
	fi
done

echo "$c"
