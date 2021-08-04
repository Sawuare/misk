#! /bin/bash

# ctif.sh - count tabs in files

if [ "$#" -eq 0 ]
then
  exit 1
fi

for f in "$@"
do
  if [ -f "$f" ] && [ -r "$f" ]
  then
    ((c += $(tr -cd "\t" < "$f" | wc -c)))
  else
    exit 2
  fi
done

echo "$c"
exit 0
