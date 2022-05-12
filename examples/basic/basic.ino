/*
Zarpli - Tecnología Interactiva
30042022 Alejandro Zárate
https://github.com/zarpli/Logitech-Z906/

DESCRIPTION
====================
  
Simple example of the Logitech-Z906 library.
*/

#include <Z906.h>

// Instantiate a Z906 object and Attach to Serial1
Z906 AMP(Serial1);

void setup(){

Serial.begin(9600);
while(!Serial);

while(AMP.command(VERSION) == 0)
{
  Serial.println("Waiting Z906 Power-Up");
  delay(1000);
}

Serial.println("Z906 Version : " + (String) AMP.command(VERSION));

// Power ON PWM Generator
AMP.command(PWM_ON);

// Enable RCA 2.0 Input
AMP.command(SET_INPUT_2);

// Disable Mute
AMP.command(MUTE_OFF);
}

void loop(){

Serial.println("Current Main Gain : " + (String) AMP.request(MAIN_GAIN));
Serial.println("Current Input : " + (String) AMP.request(CURRENT_INPUT));
delay(1000);

}
