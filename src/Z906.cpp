#include "Z906.h"

Z906::Z906(HardwareSerial &serial) {
    dev_serial = &serial;
	dev_serial->begin(BAUD_RATE,SERIAL_CONFIG);
}

int Z906::request(unsigned char cmd){
	
	dev_serial->write(GET_STATUS);
	
	unsigned long currentMillis = millis();
	
	while(dev_serial->available() < CMD_TOTAL_LENGTH)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

    if (dev_serial->read() != CMD_STX) return 0;
    if (dev_serial->read() != CMD_STATUS) return 0;
	if (dev_serial->read() != CMD_LENGTH) return 0;
	
	unsigned char main_gain 			= dev_serial->read();
	unsigned char read_gain 			= dev_serial->read();
	unsigned char center_gain 			= dev_serial->read();
	unsigned char sub_gain 				= dev_serial->read();
	unsigned char current_input 		= dev_serial->read();
										  dev_serial->read();
	unsigned char effect_input_4 		= dev_serial->read();
	unsigned char effect_input_5 		= dev_serial->read();
	unsigned char effect_input_2 		= dev_serial->read();
	unsigned char effect_input_AUX 		= dev_serial->read();
	unsigned char effect_input_1 		= dev_serial->read();
	unsigned char effect_input_3 		= dev_serial->read();
	unsigned char spdif_status 			= dev_serial->read();
	unsigned char signal_input_status 	= dev_serial->read();
	unsigned char version_a 			= dev_serial->read();
	unsigned char version_b 			= dev_serial->read();
	unsigned char version_c 			= dev_serial->read();
	unsigned char standby 				= dev_serial->read();
	unsigned char auto_standby 			= dev_serial->read();
	unsigned char checksum 				= dev_serial->read();
	
	switch (cmd)
	{
	case MAIN_GAIN: 			return main_gain;
	case READ_GAIN: 			return read_gain;
	case CENTER_GAIN: 			return center_gain;
	case SUB_GAIN: 				return sub_gain;
	case CURRENT_INPUT:			return current_input + 1;
	case EFFECT_INPUT_1:		return effect_input_1;
	case EFFECT_INPUT_2:		return effect_input_2;
	case EFFECT_INPUT_3: 		return effect_input_3;
	case EFFECT_INPUT_4: 		return effect_input_4;
	case EFFECT_INPUT_5: 	  	return effect_input_5;
	case EFFECT_INPUT_AUX:		return effect_input_AUX;
	case SPDIF_STATUS:			return spdif_status;
	case SIGNAL_INPUT_STATUS:	return signal_input_status;
	case VERSION: 				return version_c + 10 * version_b + 100 * version_a;
	case STANDBY: 				return standby;
	case AUTO_STANDBY: 			return auto_standby;
	case CHECKSUM: 				return checksum;
	}
}

int Z906::command(unsigned char cmd){
	
	if(cmd == GET_STATUS || cmd == GET_TEMP || cmd == GET_INPUT_GAIN) return 0;
	
	dev_serial->write(cmd);

	unsigned long currentMillis = millis();
	
	while(dev_serial->available() == 0)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

	return dev_serial->read();
}