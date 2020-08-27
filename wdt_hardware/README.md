# Watchdog Timer ATtiny13

----

С помощью команды lsusb вы можете узнать идентификатор шины и устройства вашего устройства USBasp:
By using the command lsusb you can find out the bus and device id of your USBasp device:

`$ lsusb`

Bus 003 Device 018: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb

`$ ls -al /dev/bus/usb/003/018`

crw-rw-r-- 1 root root 189, 273 23. Aug 11:23 /dev/bus/usb/003/018

`$ sudo chmod 666 /dev/bus/usb/003/018`

----

<img alt="attiny13pin" src="attiny13_pin.png?raw=true" />

<img alt="attiny13cmt" src="attiny13_cmt.png?raw=true" />
