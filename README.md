# Logitech-Z906
Logitech Z906 Control Library

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

# Commands

The following commands are single byte:

**Inputs**

|function|cmd|description|
|---|---|---|
|SET_INPUT_1|0x02|Enable TRS 5.1 input|
|SET_INPUT_2|0x05|Enable RCA 2.0 input|
|SET_INPUT_3|0x03|Enable Optical 1 input|
|SET_INPUT_4|0x04|Enable Optical 2 input|
|SET_INPUT_5|0x06|Enable Coaxial input|
|SET_INPUT_AUX|0x07|Enable TRS 2.0 (console) input|
|||
|GAIN_MAIN_UP|0x08|Increase Main Gain|
|GAIN_MAIN_DOWN|0x09|Decrease Main Gain|
|GAIN_SUB_UP|0x0A|Increase Subwoofer Gain|
|GAIN_SUB_DOWN|0x0B|Decrease Subwoofer Gain|
|GAIN_CENTER_UP|0x0C|Increase Center Gain|
|GAIN_CENTER_DOWN|0x0D|Decrease Subwoofer Gain|
|GAIN_REAR_UP|0x0E|Increase Rear Gain|
|GAIN_DOWN_UP|0x0F|Decrease Rear Gain|
|||
|PWM_OFF|0x10|PWM Generator OFF|
|PWM_ON|0x11|PWM Generator ON|
|||
|SET_EFFECT_3D|0x14|Enable 3D Effect|
|SET_EFFECT_41|0x15|Enable 4.1 Effect|
|SET_EFFECT_21|0x16|Enable 2.1 Effect|
|SET_EFFECT_NO|0x35|Disable all Effects|
|||
|BLOCK_INPUTS|0x22|Disable signal input|
|GET_TEMP|0x25|Get Temperature sensors|
|GET_INPUT_GAIN|0x2F|Get gain of input signal|
|NO_BLOCK_INPUTS|0x33|Enable signal input|
|||
|RESET_PU_TIMER|0x30|Reset Power-Up Timer|
|GET_PU_TIMER|0x31|Get Power-Up Timer|
|GET_STATUS|0x34|Get General Status|
|EEPROM_SAVE|0x36|Save current settings to EEPROM|
|||
|MUTE_ON|0x38|Enable Mute|
|MUTE_OFF|0x39|Disable Mute|
