/*!
 * @file node1.ino
 * @brief node1.
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
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  sMeshData_t mdata = mesh.getData();
  if(mdata.datalen != 0){
    Serial.print("name  = ");
    Serial.println(mdata.sourceAddr, HEX);
    Serial.print("data  = ");
    Serial.println(mdata.data);

    if(mdata.sourceAddr == NAME_ID3)
    {
      if(!strcmp(mdata.data,"led-turn")) digitalWrite(LED_BUILTIN, 1 ^ digitalRead(LED_BUILTIN));  //翻转输出电平
      if(!strcmp(mdata.data,"led-off")) digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
