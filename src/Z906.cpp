#include "Z906.h"

Z906::Z906(HardwareSerial &serial) {
    dev_serial = &serial;
	dev_serial->begin(BAUD_RATE,SERIAL_CONFIG);
}

// Longitudinal Redundancy Check {-1,-1}

uint8_t Z906::LRC(uint8_t* pData, uint8_t length){

	uint8_t LRC = 0;

    for (int i = 1; i < length-1; i++) LRC -= pData[i];

	return LRC;
}


int Z906::update(){
	
	dev_serial->write(GET_STATUS);
	
	unsigned long currentMillis = millis();
	
	while(dev_serial->available() < STATUS_TOTAL_LENGTH)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

	for(int i = 0; i < STATUS_TOTAL_LENGTH; i++) status[i] = dev_serial->read();
	
    if (status[STATUS_STX] != EXP_STX) return 0;
    if (status[STATUS_MODEL] != EXP_MODEL_STATUS) return 0;
	if (status[STATUS_CHECKSUM] == LRC(status, STATUS_TOTAL_LENGTH)) return 1;
	
	return 0;
	
}

int Z906::request(uint8_t cmd){
	
	if(update())
	{
	if(cmd == VERSION) return status[STATUS_VER_C] + 10 * status[STATUS_VER_B] + 100 * status[STATUS_VER_A];
	if(cmd == CURRENT_INPUT) return status[STATUS_CURRENT_INPUT] + 1;
	
	return status[cmd];
	}
	return 0;
}

int Z906::cmd(uint8_t cmd){
	
	dev_serial->write(cmd);

	unsigned long currentMillis = millis();
	
	while(dev_serial->available() == 0)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

	return dev_serial->read();
}

int Z906::cmd(uint8_t cmd_a, uint8_t cmd_b){
	
	update();
	
	status[cmd_a] = cmd_b;
	
	status[STATUS_CHECKSUM] = LRC(status, STATUS_TOTAL_LENGTH);
	
	for(int i = 0; i <STATUS_TOTAL_LENGTH; i++)
	dev_serial->write(status[i]);

	unsigned long currentMillis = millis();
	
	while(dev_serial->available() < ACK_TOTAL_LENGTH)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

	for(int i = 0; i < ACK_TOTAL_LENGTH; i++) dev_serial->read();

}

void Z906::print_status(){
	
	update();
	
	for(int i = 0; i <STATUS_TOTAL_LENGTH; i++)
	{
		Serial.print(status[i],HEX);
		Serial.print(" ");
	}
	Serial.print("\n");
}

uint8_t Z906::main_sensor(){
	
	dev_serial->write(GET_TEMP);
	
	unsigned long currentMillis = millis();
	
	while(dev_serial->available() < TEMP_TOTAL_LENGTH)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

	uint8_t temp[TEMP_TOTAL_LENGTH];
	
	for(int i = 0; i < TEMP_TOTAL_LENGTH; i++) temp[i] = dev_serial->read();
	
	if(temp[2] != EXP_MODEL_TEMP) return 0;
	
	return temp[7];
}