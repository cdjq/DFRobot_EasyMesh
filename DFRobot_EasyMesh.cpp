/*!
 * @file DFRobot_EasyMesh.cpp
 * @brief Define the basic structure of class DFRobot_EasyMesh
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V0.1
 * @date 2022-04-24
 * @url https://github.com/DFRobot/DFRobot_EasyMesh
 */
#include "DFRobot_EasyMesh.h"
/*
DFRobot_EasyMesh::DFRobot_EasyMesh(){}
DFRobot_EasyMesh::~DFRobot_EasyMesh(){}
*/

void DFRobot_EasyMesh::setDivceName(uint16_t name)
{
  uint8_t temp[7] = {PACKET_HEAD, SET_NAME, 0x02, 0x00, 0x00, PACKET_TAIL};
  temp[3] = name>>8;
  temp[4] = name;
  writeData(temp, 6);
}

void DFRobot_EasyMesh::setGroup(uint16_t group)
{
  uint8_t temp[10] = {PACKET_HEAD, SET_GROUP, 0x02, 0x00, 0x00, PACKET_TAIL};
  temp[3] = group>>8;
  temp[4] = group;
  writeData(temp, 6);
}

uint8_t DFRobot_EasyMesh::getdataLen(void)
{
  uint8_t len = 0;
  uint8_t temp[4] = {PACKET_HEAD, GET_DATA_LEN, PACKET_TAIL};
  writeData(temp, (uint8_t)3);
  delay(100);
  readData(&len, 1);
  return len;
}

sMeshData_t DFRobot_EasyMesh::getData(void)
{
  uint8_t len;
  uint8_t temp[4] = {PACKET_HEAD, GET_DATA, PACKET_TAIL};
  uint8_t data[40] = {0};
  sMeshData_t meshData;
  len = getdataLen();
  if(len != 0){
    writeData(temp, (uint8_t)3);
    delay(20);
    readData(data, len); 
    memset(meshData.data, 0, 32);
    meshData.sourceAddr = (uint16_t(data[0])<<8 | data[1]);
    memcpy(meshData.data, &data[2], len-2);
    meshData.datalen = len-2;
  }else{
    meshData.datalen = 0;
  }
  return meshData;
}

void DFRobot_EasyMesh::sendName(uint16_t name, const char *data)
{

  uint8_t templen = 0;
  uint8_t len = strlen(data);
  uint8_t temp[len+10] = {PACKET_HEAD, SEND_NAME, len};
  temp[3] = name>>8;
  temp[4] = name;
  memcpy(&temp[5] ,data, len);
  temp[5+len] = PACKET_TAIL;
  templen = 6 + len;
  writeData(temp, templen);
}

void DFRobot_EasyMesh::sendGroup(uint16_t group, const char *data)
{
  uint8_t templen = 0;
  uint8_t len = strlen(data);
  uint8_t temp[len+10] = {PACKET_HEAD, SEND_GROUP, len};
  temp[3] = (group+0xc000)>>8;
  temp[4] = group+0xc000;
  memcpy(&temp[5] ,data, len);
  temp[5+len] = PACKET_TAIL;
  templen = 6 + len;
  writeData(temp, templen);
}


DFRobot_EasyMesh_I2C::DFRobot_EasyMesh_I2C(TwoWire *pWire, uint8_t addr)
{
  _pWire = pWire;
  _I2C_addr = addr;
}

DFRobot_EasyMesh_I2C::~DFRobot_EasyMesh_I2C()
{
}

bool DFRobot_EasyMesh_I2C::begin(void)
{
  delay(300);
  _pWire->begin();
  _pWire->beginTransmission(_I2C_addr);
  
  if(_pWire->endTransmission() == 0){
      return true;
  }else{
    DBG("I2C connect error");
    return false;
  }
}

void DFRobot_EasyMesh_I2C::writeData(uint8_t *data ,uint8_t len)
{
  _pWire->beginTransmission(this->_I2C_addr);
  for(uint8_t i = 0; i < len; i++)
    _pWire->write(data[i]);
  _pWire->endTransmission();
  return;
}

void DFRobot_EasyMesh_I2C::readData(uint8_t *data ,uint8_t len)
{
  uint8_t i = 0;
  _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)len);
  while (_pWire->available()){
    data[i++]=_pWire->read();
  }
  return;
}