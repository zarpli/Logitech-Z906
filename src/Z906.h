#include "Arduino.h"

#define BAUD_RATE     		57600
#define SERIAL_CONFIG		SERIAL_8O1
#define	SERIAL_TIME_OUT		1000

#define SET_INPUT_1			0x02
#define SET_INPUT_2			0x05
#define SET_INPUT_3			0x03
#define SET_INPUT_4			0x04
#define SET_INPUT_5			0x06
#define SET_INPUT_AUX		0x07

#define GAIN_MAIN_UP		0x08
#define GAIN_MAIN_DOWN		0x09
#define GAIN_SUB_UP			0x0A
#define GAIN_SUB_DOWN		0x0B
#define GAIN_CENTER_UP		0x0C
#define GAIN_CENTER_DOWN	0x0D
#define GAIN_REAR_UP		0x0E
#define GAIN_DOWN_UP		0x0F

#define	PWM_OFF				0x10
#define	PWM_ON				0x11

#define SET_EFFECT_3D		0x14			
#define SET_EFFECT_41		0x15			
#define SET_EFFECT_21		0x16			
#define SET_EFFECT_NO		0x35			

#define BLOCK_INPUTS		0x22
#define GET_TEMP			0x25
#define GET_INPUT_GAIN		0x2F
#define NO_BLOCK_INPUTS		0x33

#define RESET_IDLE_TIME		0x30
#define GET_IDLE_TIME		0x31
#define GET_STATUS			0x34
#define	EEPROM_SAVE			0x36

#define	MUTE_ON				0x38
#define	MUTE_OFF			0x39

#define SPK_NONE			0x00			// speaker mask
#define SPK_ALL				0xFF
#define SPK_FR				0x01
#define SPK_FL				0x10
#define SPK_RR				0x02
#define SPK_RL				0x08
#define SPK_CENTER			0x04
#define	SPK_SUB				0x20

#define EFFECT_3D			0x00			
#define EFFECT_21			0x01			
#define EFFECT_41			0x02			
#define EFFECT_NO			0x03			

#define	ON_LINE				0x3F

#define CMD_STX				0xAA
#define CMD_NOISE			0x07
#define CMD_STATUS			0x0A

#define CMD_LENGTH			0x13
#define CMD_TOTAL_LENGTH	0x17

#define MAIN_GAIN			0x01
#define READ_GAIN			0x02
#define CENTER_GAIN			0x03
#define SUB_GAIN			0x04
#define CURRENT_INPUT		0x05
#define EFFECT_INPUT_1		0x06
#define EFFECT_INPUT_2		0x07
#define EFFECT_INPUT_3		0x08
#define EFFECT_INPUT_4		0x09
#define EFFECT_INPUT_5		0x0A
#define EFFECT_INPUT_AUX	0xA1
#define SPDIF_STATUS		0xA2
#define SIGNAL_INPUT_STATUS	0xA3
#define VERSION				0xA4
#define STANDBY				0xA5
#define AUTO_STANDBY		0xA6
#define CHECKSUM			0xA7

class Z906
{
public:

Z906(HardwareSerial &serial);

int command(unsigned char);
int request(unsigned char);

private:

HardwareSerial* dev_serial;

};
