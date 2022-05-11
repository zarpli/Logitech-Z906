# WIP

# Logitech-Z906
Logitech Z906 Arduino Control Library

This 5.1 speaker system comes with a 1000 Watts Peak/500 Watts RMS power for a rich THX Certified surround sound. With the ability to decode Dolby Digital and DTS encoded soundtracks. 

<p align="center"><img src=/images/logitech_z906.png></p>

The [Z906](datasheet/Z906_User_Manual.pdf) is who has six class D amplifiers included, but you cannot use them if you do not have the console connected.

<p align="center"><img src=/images/z906-console.png></p>

# DE-15 Console Connector

The main component is a Renesas [D2-71583](datasheet/D2-71583.pdf) intelligent digital amplifier and sound processor.

The communication between the Digital Audio Processor and the console is done through TTL serial communication at 3.3V.

The following table illustrates the pinout.

|Pin|Description|Pin|Description|
|---|---|---|---|
|1||2||
|3||4||
|5||6|GND|
|7||8||
|9||10||
|11||12|TX|
|13|RX|14||
|15|Console Enable|||

D2-71583 **NO** is 5V tolerant.

|Serial settings||
|---|---|
|Baud rate|57600|
|Data|8 bit|
|Parity|Odd|
|Stop|1 bit|

Here is the DE-15 male as viewed from the front of the Main Board.

<img src=https://raw.githubusercontent.com/zarpli/Logitech-Z906/main/images/DE-15-M.jpg width="300">
