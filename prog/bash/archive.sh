#! /bin/bash

# archive.sh - archive home

echo 'Mounting USB'

sudo mount /dev/sdb1 /mnt/

echo 'Preparing home'

sudo rm -rf /mnt/sawuare/
sudo mkdir /mnt/sawuare/

echo 'Copying home'

sudo cp -a /home/sawuare/data   /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/docs   /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/prog   /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/.bash* /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/.nano* /mnt/sawuare/ 2> /dev/null
sudo cp -a /home/sawuare/.vim*  /mnt/sawuare/ 2> /dev/null

echo 'Unmounting USB'

sudo umount /mnt/
