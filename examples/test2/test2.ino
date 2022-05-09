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
  mesh.setDivceName(NAME_ID2);
  mesh.setGroup(GROUP_1|GROUP_2);
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
    mesh.sendGroup(GROUP_1, "2-G1");
    mesh.sendGroup(GROUP_2, "2-G2");
    mesh.sendName(NAME_ID1, "2-n1");
    mesh.sendName(NAME_ID3, "2-n3");
  }
  delay(10); 
}