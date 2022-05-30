#include "Arduino.h"

// Serial Settings

#define BAUD_RATE     		57600
#define SERIAL_CONFIG		SERIAL_8O1
#define	SERIAL_TIME_OUT		1000

#define	STATUS_TOTAL_LENGTH	0x17
#define	ACK_TOTAL_LENGTH	0x05
#define	TEMP_TOTAL_LENGTH	0x0A

// Single Commands

#define SELECT_INPUT_1		0x02
#define SELECT_INPUT_2		0x05
#define SELECT_INPUT_3		0x03
#define SELECT_INPUT_4		0x04
#define SELECT_INPUT_5		0x06
#define SELECT_INPUT_AUX	0x07

#define LEVEL_MAIN_UP     0x08
#define LEVEL_MAIN_DOWN   0x09
#define LEVEL_SUB_UP      0x0A
#define LEVEL_SUB_DOWN    0x0B
#define LEVEL_CENTER_UP   0x0C
#define LEVEL_CENTER_DOWN 0x0D
#define LEVEL_REAR_UP     0x0E
#define LEVEL_REAR_DOWN   0x0F

#define	PWM_OFF           0x10
#define	PWM_ON            0x11

#define SELECT_EFFECT_3D  0x14			
#define SELECT_EFFECT_41  0x15			
#define SELECT_EFFECT_21  0x16			
#define SELECT_EFFECT_NO  0x35			

#define	EEPROM_SAVE       0x36

#define	MUTE_ON           0x38
#define	MUTE_OFF          0x39

#define BLOCK_INPUTS      0x22
#define RESET_PWR_UP_TIME 0x30
#define NO_BLOCK_INPUTS   0x33

// Double commmands

#define MAIN_LEVEL        0x03
#define READ_LEVEL        0x04
#define CENTER_LEVEL      0x05
#define SUB_LEVEL         0x06

// Requests

#define VERSION           0xF0
#define CURRENT_INPUT     0xF1
#define GET_INPUT_GAIN    0x2F
#define GET_TEMP          0x25
#define GET_PWR_UP_TIME   0x31
#define GET_STATUS        0x34

// MASK

#define EFFECT_3D         0x00			
#define EFFECT_21         0x01			
#define EFFECT_41         0x02			
#define EFFECT_NO         0x03			

#define SPK_NONE          0x00			
#define SPK_ALL           0xFF
#define SPK_FR            0x01
#define SPK_FL            0x10
#define SPK_RR            0x02
#define SPK_RL            0x08
#define SPK_CENTER        0x04
#define	SPK_SUB           0x20

class Z906
{
public:

Z906(HardwareSerial &serial);

int 	cmd(uint8_t);
int 	cmd(uint8_t, uint8_t);
int		request(uint8_t);
void 	print_status();

uint8_t main_sensor();

private:

const uint8_t EXP_STX               = 0xAA;
const uint8_t EXP_MODEL_STATUS      = 0x0A;
const uint8_t EXP_MODEL_TEMP        = 0x0C;

const uint8_t STATUS_STX            = 0x00;
const uint8_t STATUS_MODEL          = 0x01;
const uint8_t STATUS_LENGTH         = 0x02;
const uint8_t STATUS_MAIN_LEVEL     = 0x03;
const uint8_t STATUS_READ_LEVEL     = 0x04;
const uint8_t STATUS_CENTER_LEVEL   = 0x05;
const uint8_t STATUS_SUB_LEVEL      = 0x06;
const uint8_t STATUS_CURRENT_INPUT  = 0x07;
const uint8_t STATUS_UNKNOWN        = 0x08;
const uint8_t STATUS_FX_INPUT_4     = 0x09;
const uint8_t STATUS_FX_INPUT_5     = 0x0A;
const uint8_t STATUS_FX_INPUT_2     = 0x0B;
const uint8_t STATUS_FX_INPUT_AUX   = 0x0C;
const uint8_t STATUS_FX_INPUT_1     = 0x0D;
const uint8_t STATUS_FX_INPUT_3     = 0x0E;
const uint8_t STATUS_SPDIF_STATUS   = 0x0F;
const uint8_t STATUS_SIGNAL_STATUS  = 0x10;
const uint8_t STATUS_VER_A          = 0x11;
const uint8_t STATUS_VER_B          = 0x12;
const uint8_t STATUS_VER_C          = 0x13;
const uint8_t STATUS_STBY           = 0x14;
const uint8_t STATUS_AUTO_STBY      = 0x15;
const uint8_t STATUS_CHECKSUM       = 0x16;

HardwareSerial* dev_serial;

int 	update();
uint8_t LRC(uint8_t*, uint8_t);
uint8_t status[STATUS_TOTAL_LENGTH];
};


