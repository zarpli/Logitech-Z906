/*
Zarpli - Tecnología Interactiva
12112021 Alejandro Zárate
https://github.com/zarpli/BrightSign/

DESCRIPTION
====================
  
Simple example of the BrightSign library that play a media file 
and wait for it to finish to run again.
  
The BSuControl Script must be installed in the BrightSign unit 
memory unit and must be connected to the Serial1 port.  

https://github.com/zarpli/BSuControl/

Media Files for Testing
https://github.com/zarpli/Media/
*/

#include <BrightSign.h>

// Instantiate a BrightSign object and Attach to Serial1
BrightSign BS(Serial1);   

void setup(){

// Enable debug msg over Serial
BS.debug();               

Serial.begin(9600);
while(!Serial);

Serial.println("Waiting BrightSign Power-Up");
while(!BS.online())BS.update(); 

//Set Volume to 20%
BS.volume(20);            
}

void loop(){
// Update the BrightSign instance
BS.update();
if(BS.media_ended()) BS.play("AUDIO.M4A");
}
