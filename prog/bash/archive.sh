#! /bin/bash

# archive.sh - archive home

function is_ok {
	if [ $? ]
	then
		echo "OK"
	else
		echo "NOT OK"
	fi
}

echo -n "Mounting USB...   "

sudo mount /dev/sdb1 /mnt/

is_ok

echo -n "Preparing home... "

sudo rm -rf /mnt/sawuare/

sudo mkdir /mnt/sawuare/

is_ok

echo -n "Copying home...   "

sudo cp -a /home/sawuare/data   /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/prog   /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/.bash* /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/.nano* /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/.vim*  /mnt/sawuare/ 2> /dev/null

is_ok

echo -n "Unmounting USB... "

sudo umount /mnt/

is_ok
