

/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <Dynamixel2Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

  #define DXL_SERIAL   Serial3 //OpenCM9.04 EXP Board's DXL port Serial. (Serial1 for the DXL port on the OpenCM 9.04 board)
  #define DEBUG_SERIAL Serial
  const int DXL_DIR_PIN = 22;


const uint8_t DXL_ID1 = 3;
const uint8_t DXL_ID2 = 4;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

//This namespace is required to use Control table item names
using namespace ControlTableItem;

int maxMotorSpeed = 0; //0 = max speed, larger number = slower

StaticJsonDocument<200> doc;
float maxVal = 15340;
float targetPosition1 = 0.0;
float targetPosition2 = 0.0;

float prev1;
float prev2;

void setup() {
  // put your setup code here, to run once:
  
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  while(!DEBUG_SERIAL);

  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID1);
 // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID1);
  dxl.setOperatingMode(DXL_ID1, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID1);

  // Limit the maximum velocity in Position Control Mode. Use 0 for Max speed
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID1, maxMotorSpeed);
 
  dxl.ping(DXL_ID2);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID2);
  dxl.setOperatingMode(DXL_ID2, OP_EXTENDED_POSITION);
  dxl.torqueOn(DXL_ID2);

  // Limit the maximum velocity in Position Control Mode. Use 0 for Max speed
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID2, maxMotorSpeed);


}

void loop() {
  
  DeserializationError error = deserializeJson(doc, Serial);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
else
  
{
targetPosition1 = doc["motor1"];
maxVal = doc["maxVal"];

//float flippedTarget1=maxVal-targetPosition1;

targetPosition2= doc["motor2"];

if(prev1!=targetPosition1)
{
  dxl.setGoalPosition(DXL_ID1, targetPosition1, UNIT_DEGREE);

}
if(prev2!=targetPosition2)
{
  dxl.setGoalPosition(DXL_ID2, targetPosition2, UNIT_DEGREE);
}
  
 prev1=targetPosition1; 
 prev2=targetPosition2;
}

}
