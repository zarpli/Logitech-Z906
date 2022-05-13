# Logitech-Z906
Logitech Z906 Control Library

This 5.1 speaker system comes with a 1000 Watts Peak/500 Watts RMS power for a rich THX Certified surround sound. With the ability to decode Dolby Digital and DTS encoded soundtracks. 

<p align="center"><img src=/images/logitech_z906.png></p>

The [Logitech Z906](datasheet/Z906_User_Manual.pdf) is who has six class D amplifiers included, but you cannot use them if you do not have the console connected.

<p align="center"><img src=/images/z906-console.png></p>

# DE-15 Console Connector

The main component is a Renesas [D2-71583](datasheet/D2-71583.pdf) intelligent digital amplifier and sound processor.

The communication between the Digital Audio Processor and the console is done through TTL serial communication at 3.3V.

The following table illustrates the pinout.

|Pin|Description|Pin|Description|
|---|---|---|---|
|6|GND|12|TX|
|13|RX|15|Console Enable|

D2-71583 **NO** is 5V tolerant.

|Serial settings||
|---|---|
|Baud rate|57600|
|Data|8 bit|
|Parity|Odd|
|Stop|1 bit|

Here is the DE-15 male as viewed from the front of the Main Board.

<img src=/images/DE-15-M.jpg width="200">

# Enable Console

Connect pin 15 to GND.

# Basic Usage

Instantiate a Z906 object and attach to Serial1, you may create multiple Z906 objects.
```C++
Z906 LOGI(Serial1)
```
**cmd** method uses single or double argument, check this list for single and this for double.
```C++
LOGI.cmd(arg_a)
LOGI.cmd(arg_a, arg_b)
```
Examples : 
```C++
LOGI.cmd(MUTE_ON)         // Enable Mute
LOGI.cmd(MAIN_LEVEL, 15)  // Set Main Level to 15
```
# Commands of single argument

|function|cmd|description|
|---|---|---|
|SELECT_INPUT_1|0x02|Enable TRS 5.1 input|
|SELECT_INPUT_2|0x05|Enable RCA 2.0 input|
|SELECT_INPUT_3|0x03|Enable Optical 1 input|
|SELECT_INPUT_4|0x04|Enable Optical 2 input|
|SELECT_INPUT_5|0x06|Enable Coaxial input|
|SELECT_INPUT_AUX|0x07|Enable TRS 2.0 (console) input|
|||
|LEVEL_MAIN_UP|0x08|Increase Main Level by one unit|
|LEVEL_MAIN_DOWN|0x09|Decrease Main Level by one unit|
|LEVEL_SUB_UP|0x0A|Increase Subwoofer Level by one unit|
|LEVEL_SUB_DOWN|0x0B|Decrease Subwoofer Level by one unit|
|LEVEL_CENTER_UP|0x0C|Increase Center Level by one unit|
|LEVEL_CENTER_DOWN|0x0D|Decrease Subwoofer Level by one unit|
|LEVEL_REAR_UP|0x0E|Increase Rear Level by one unit|
|LEVEL_DOWN_UP|0x0F|Decrease Rear Level by one unit|
|||
|PWM_OFF|0x10|PWM Generator OFF|
|PWM_ON|0x11|PWM Generator ON|
|||
|SELECT_EFFECT_3D|0x14|Enable 3D Effect|
|SELECT_EFFECT_41|0x15|Enable 4.1 Effect|
|SELECT_EFFECT_21|0x16|Enable 2.1 Effect|
|SELECT_EFFECT_NO|0x35|Disable all Effects|
|||
|BLOCK_INPUTS|0x22|Disable signal input|
|NO_BLOCK_INPUTS|0x33|Enable signal input|
|||
|RESET_PWR_UP_TIME|0x30|Reset Power-Up Timer|
|EEPROM_SAVE|0x36|Save current settings to EEPROM|
|||
|MUTE_ON|0x38|Enable Mute|
|MUTE_OFF|0x39|Disable Mute|

# Commands of single argument

|Argument a|Argument b|
|---|---|
|MAIN_LEVEL|0-255|
|READ_LEVEL|0-255|
|CENTER_LEVEL|0-255|
|SUB_LEVEL|0-255|

