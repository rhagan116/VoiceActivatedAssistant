/*!
 * @file uart.ino
 * @brief   Control the voice recognition module via UART
 * @n  Get the recognized command ID and play the corresponding reply audio according to the ID;
 * @n  Set the wake-up state duration, set mute mode, set volume, enter the wake-up state, and reset the module
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-04-02
 * @url  https://github.com/DFRobot/DFRobot_DF2301Q
 */
#include "DFRobot_DF2301Q.h"

//I2C Communication
DFRobot_DF2301Q_I2C asr;

//Initialize servo's
#include <Servo.h>
Servo servoComp;
Servo servoLight;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servoComp.attach(3);
  servoLight.attach(5);

  // Check sensor connects succesfully 
  while (!(asr.begin())) {
    Serial.println("Thalia communication failed");
    delay(3000);
  }
  Serial.println("Begin ok!");

  //set the voice volume (0-7)
  asr.setVolume(11);

  //set the wake time duration (0-255)
  asr.setWakeTime(10);  


}

void loop() {
  // put your main code here, to run repeatedly:
  //receive the current command id (CMDID)
  uint8_t CMDID = asr.getCMDID();
  Serial.println(CMDID);
  switch(CMDID){
    
    // Command for "Computer Off"
    case 5:
      servoComp.write(50);
      delay(800);
      servoComp.write(90);
      break;

    // Command for "Computer On"
    case 6:
      servoComp.write(50);
      delay(800);
      servoComp.write(90);
      break;

    //Command for "Light Off"
    case 8:
      servoLight.write(90);
      delay(800);
      
      break;
      
    //Command for "Light On"
    case 7:
      servoLight.write(50);
      delay(800);
      
      break;

    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");
        Serial.println(CMDID);
      }
    
  }
  delay(300);
}