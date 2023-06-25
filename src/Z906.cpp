#include "Z906.h"

Z906::Z906(HardwareSerial &serial) {
    dev_serial = &serial;
	dev_serial->begin(BAUD_RATE,SERIAL_CONFIG);
}

// Longitudinal Redundancy Check {-1,-1}
uint8_t Z906::LRC(uint8_t* pData, size_t length){

	uint8_t LRC = 0;

    for(size_t i = 1; i < length-1; i++) LRC -= pData[i];

	return LRC;

}

void Z906::on(){
    write(PWM_ON);
}

void Z906::off(){
    write(PWM_OFF);

    uint8_t cmd[] = { RESET_PWR_UP_TIME, 0x37, EEPROM_SAVE };
    write(cmd, sizeof(cmd));
    flush();    // Discard ACK
}

void Z906::input(uint8_t input, uint8_t effect){
    // If no effect is select, use default (same as console default)
    if(effect = 0xFF){
        if(input == SELECT_INPUT_2 || input == SELECT_INPUT_AUX){
            effect = SELECT_EFFECT_3D;
        } else {
            effect = SELECT_EFFECT_NO;
        }
    }

    uint8_t cmd[] = { MUTE_ON, input, effect, MUTE_OFF };
    write(cmd, sizeof(cmd));
    flush();    // Discard ACK
}

void Z906::flush(){
    delay(SERIAL_DEADTIME);         //Avoid UART TX collisions
    dev_serial->flush(false);       //Clear RX buffer
}

void Z906::write(uint8_t cmd){
	flush();
	dev_serial->write(cmd);
	dev_serial->flush();            //Flush TX buffer to device
}

void Z906::write(uint8_t* pCmd, size_t cmd_len){
    flush();

	for(size_t i = 0; i < cmd_len; i++)
	    dev_serial->write(pCmd[i]);

    dev_serial->flush();            //Flush TX buffer to device
}

int Z906::update(){

	write(GET_STATUS);

	unsigned long currentMillis = millis();
	
    // Determine payload size and total required buffer size
	while(dev_serial->available() < STATUS_LENGTH + 1)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;
    
	for(int i = 0; i <= STATUS_LENGTH; i++) status[i] = dev_serial->read();

    size_t payload_len = status[STATUS_LENGTH];     //Size of the payload
    status_len = payload_len + 4;                   //Size of full status buffer in RAM

	while(dev_serial->available() < payload_len + 1)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

    //Read payload + checksum
    for(int i = 0; i <= payload_len; i++) status[i + STATUS_LENGTH + 1] = dev_serial->read();
    STATUS_CHECKSUM = status_len - 1;

    if (status[STATUS_STX] != EXP_STX) return 0;
    if (status[STATUS_MODEL] != EXP_MODEL_STATUS) return 0;
	if (status[STATUS_CHECKSUM] == LRC(status, status_len)) return 1;
	
	return 0;
	
}

int Z906::request(uint8_t cmd){
    
	if(update()){
        if(cmd == VERSION) return status[STATUS_VER_C] + 10 * status[STATUS_VER_B] + 100 * status[STATUS_VER_A];
        if(cmd == CURRENT_INPUT) return status[STATUS_CURRENT_INPUT] + 1;
        if(cmd == MAIN_LEVEL || cmd == REAR_LEVEL || cmd == CENTER_LEVEL || cmd == SUB_LEVEL) return (uint8_t) (((uint16_t) status[cmd])*255/MAX_VOL);

        return status[cmd];
	}
	return 0;
}

int Z906::cmd(uint8_t cmd){

    write(cmd);

	unsigned long currentMillis = millis();
	
	while(dev_serial->available() == 0)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

	return dev_serial->read();
}

int Z906::cmd(uint8_t cmd_a, uint8_t cmd_b){

	update();
	
    //Normalize volume to 0...255
    if(cmd_a == MAIN_LEVEL || cmd_a == REAR_LEVEL || cmd_a == CENTER_LEVEL || cmd_a == SUB_LEVEL)
        cmd_b = (uint8_t) (((uint16_t) cmd_b)*MAX_VOL/255);

	status[cmd_a] = cmd_b;
	status[STATUS_CHECKSUM] = LRC(status, status_len);
	
    write(status, status_len);

    flush(); // Discard ACK message
}

void Z906::print_status(){

	update();
	
	for(int i = 0; i < status_len; i++)
	{
		Serial.print(status[i],HEX);
		Serial.print(" ");
	}
	Serial.print("\n");
}

uint8_t Z906::main_sensor(){

	write(GET_TEMP);
	
	unsigned long currentMillis = millis();
	
	while(dev_serial->available() < TEMP_TOTAL_LENGTH)
	if (millis() - currentMillis > SERIAL_TIME_OUT) return 0;

	uint8_t temp[TEMP_TOTAL_LENGTH];
	
	for(int i = 0; i < TEMP_TOTAL_LENGTH; i++) temp[i] = dev_serial->read();
	
	if(temp[2] != EXP_MODEL_TEMP) return 0;
	
	return temp[7];
}