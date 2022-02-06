#! /bin/sh

ifconfig eth0 10.42.0.215 netmask 255.255.255.0

#------- insert kernel modules for the button and the tranceiver
insmod /etc/my_nrf24.ko
insmod /etc/button.ko

rm -rf /dev/mqueue
mkdir /dev/mqueue
mount -t mqueue none /dev/mqueue

#-------- start daemon ---------
/etc/sender

#------- start program ---------
/etc/smartFitness -platform linuxfb
