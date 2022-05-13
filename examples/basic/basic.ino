/*
Zarpli - Tecnología Interactiva
30042022 Alejandro Zárate
https://github.com/zarpli/LOGItech-Z906/

DESCRIPTION
====================
  
Basic example of the Logitech-Z906 library.
*/

#include <Z906.h>

// Instantiate a Z906 object and Attach to Serial1
Z906 LOGI(Serial1);

void setup(){

Serial.begin(9600);
while(!Serial);

while(LOGI.cmd(VERSION) == 0)
{
  Serial.println("Waiting Z906 Power-Up");
  delay(1000);
}

Serial.println("Z906 Version : " + (String) LOGI.request(VERSION));

// Power ON PWM Generator
LOGI.cmd(PWM_ON);

// Select RCA 2.0 Input
LOGI.cmd(SELECT_INPUT_2);

// Disable Mute
LOGI.cmd(MUTE_OFF);

// Set Main Level to 15;
LOGI.cmd(MAIN_LEVEL, 15);
}

void loop(){

Serial.println("Temperature main sensor: " + (String) LOGI.main_sensor());

delay(1000);

}
