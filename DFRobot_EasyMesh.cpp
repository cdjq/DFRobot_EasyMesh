/*!
 * @file DFRobot_EasyMesh.cpp
 * @brief Define the basic structure of class DFRobot_EasyMesh
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V0.2
 * @date 2022-05-20
 * @url https://github.com/DFRobot/DFRobot_EasyMesh
 */
#include "DFRobot_EasyMesh.h"
/*
DFRobot_EasyMesh::DFRobot_EasyMesh(){}
DFRobot_EasyMesh::~DFRobot_EasyMesh(){}
*/

void DFRobot_EasyMesh::setDivceName(uint16_t name)
{
  uint8_t temp[7] = {0};
  temp[0] = name>>8;
  temp[1] = name;
  writeData(R_NAME_H, temp, (uint8_t)2);
}

void DFRobot_EasyMesh::setGroup(uint16_t group)
{
  uint8_t temp[7] = {0};
  temp[0] = group>>8;
  temp[1] = group;
  writeData(R_GROUP_H, temp, (uint8_t)2);
}

uint8_t DFRobot_EasyMesh::getdataLen(void)
{
  uint8_t temp[4] = {0};
  i2c_flush();
  readData(R_DATALEN, temp, (uint8_t)1);
  return temp[0];
}

void DFRobot_EasyMesh::i2c_flush(void)
{
  uint8_t temp[7] = {0};
  temp[0] = FLUSH_DATA;
  writeData(R_FLUSH, temp, (uint8_t)1);
  delay(20);  // 避免未刷新，简单处理
}

sMeshData_t DFRobot_EasyMesh::getData(void)
{
  uint8_t len;
  uint8_t temp[40] = {0};
  sMeshData_t meshData;
  len = getdataLen();
  if(len != 0){
    readData(R_ADDR_H, temp, len);
    memset(meshData.data, 0, 32);
    meshData.sourceAddr = (uint16_t(temp[0])<<8 | temp[1]);
    memcpy(meshData.data, temp+2, len-2);
    meshData.datalen = len-2;
  }else{
    meshData.datalen = 0;
  }
  return meshData;
}

void DFRobot_EasyMesh::sendName(uint16_t name, const char *data)
{
  uint8_t temp[40] = {0};
  temp[0] = SEND_NAME;
  temp[1] = name>>8;
  temp[2] = name;
  memcpy(temp+3 ,data, strlen(data));
  writeData(R_TYPE, temp, strlen(data)+3);
}

void DFRobot_EasyMesh::sendGroup(uint16_t group, const char *data)
{
  uint8_t temp[40] = {0};
  temp[0] = SEND_GROUP;
  temp[1] = (group+0xc000)>>8;
  temp[2] = group+0xc000;
  memcpy(temp+3 ,data, strlen(data));
  writeData(R_TYPE, temp, strlen(data)+3);
}

char *DFRobot_EasyMesh::getVersion(void)
{
  uint8_t temp[15] = {0};
  memset(_version, 0, 10);
  readData(R_VERSION, (uint8_t *)_version, strlen("V0.0.0"));
  return _version;
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

void DFRobot_EasyMesh_I2C::writeData(uint8_t reg, uint8_t *data, uint8_t len)
{
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(reg);
  for(uint8_t i = 0; i < len; i++)
    _pWire->write(data[i]);
  _pWire->endTransmission();
  return;
}

void DFRobot_EasyMesh_I2C::readData(uint8_t reg, uint8_t *data ,uint8_t len)
{
  uint8_t i = 0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(reg);
  _pWire->endTransmission();
  _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)len);
  while (_pWire->available()){
    data[i++]=_pWire->read();
  }
  return;
}