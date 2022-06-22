/*!
 * @file node3.ino
 * @brief node3.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2021-05-20
 * @url https://github.com/DFRobot/DFRobot_EasyMesh
 */
#include "DFRobot_EasyMesh.h"

#define I2C_ADDRESS  MESH_I2C_ADDR
DFRobot_EasyMesh_I2C mesh(&Wire, I2C_ADDRESS);

#define NAME_ID1  0x0011
#define NAME_ID2  0x0022
#define NAME_ID3  0x0033

#define BUTTON1  4
#define BUTTON2  5
#define BUTTON3  6


void setup()
{
  Serial.begin(115200);
  while(!mesh.begin()){
    Serial.println("begin failed!");
    delay(1000);
  }
  Serial.println("begin success!");
  mesh.setDivceName(NAME_ID3);
  mesh.setGroup(GROUP_1);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
}

void loop()
{
  if(digitalRead(BUTTON1)){
    while(digitalRead(BUTTON1));
    mesh.sendName(NAME_ID1, "led-turn");
  }
  if(digitalRead(BUTTON2)){
    while(digitalRead(BUTTON2));
    mesh.sendName(NAME_ID2, "led-turn");
  }
  if(digitalRead(BUTTON3)){
    while(digitalRead(BUTTON3));
    mesh.sendGroup(GROUP_1, "led-off");
  }
  delay(20);
}
