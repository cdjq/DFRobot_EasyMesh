/*!
 * @file sendData.ino
 * @brief Simple Mesh networking Demo.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V0.2
 * @date 2022-05-07
 * @url https://github.com/DFRobot/DFRobot_EasyMesh
 */
#include "DFRobot_EasyMesh.h"

#define I2C_ADDRESS  MESH_I2C_ADDR
DFRobot_EasyMesh_I2C mesh(&Wire, I2C_ADDRESS);

#define NAME_ID1  0x0011
#define NAME_ID2  0x0022
#define NAME_ID3  0x0033
#define NAME_ID4  0x0044

uint32_t timer;
void setup()
{
  Serial.begin(115200);
  while(!mesh.begin()){
    Serial.println("begin failed!");
    delay(1000);
  }
  Serial.println("begin success!");
  mesh.setDivceName(NAME_ID1);
  mesh.setGroup(GROUP_1);
  Serial.print("Version : ");
  Serial.println(mesh.getVersion());
  timer = millis();
}

void loop()
{  
  sMeshData_t mdata = mesh.getData();
  if(mdata.datalen != 0){
    Serial.print("name : ");
    Serial.print(mdata.sourceAddr, HEX);
    Serial.print(" -  ");
    Serial.print("data : ");
    Serial.println(mdata.data);
  }
  if(millis() - timer >= 5000){
    timer = millis();
    mesh.sendGroup(GROUP_1, "1-send-Group1");
    mesh.sendGroup(GROUP_2, "1-send-Group2");
    mesh.sendName(NAME_ID2, "1-send-name2");
    mesh.sendName(NAME_ID3, "1-send-name3");
  }
  delay(20); 
}