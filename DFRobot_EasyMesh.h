/*!
 * @file DFRobot_EasyMesh.h
 * @brief Define the basic structure of class DFRobot_EasyMesh
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V0.2
 * @date 2022-05-20
 * @url https://github.com/DFRobot/DFRobot_EasyMesh
 */
#ifndef __DFROBOT_EASY_MESH__
#define __DFROBOT_EASY_MESH__
#include <Arduino.h>
#include <Wire.h>

//#define ENABLE_DBG
//#define NORMAL_ENABLE

#ifdef ENABLE_DBG
  #ifdef NORMAL_ENABLE
    #define DBG(...) {Serial.println(__VA_ARGS__);}
  #else
    #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
  #endif
#else
  #define DBG(...)
#endif


#define MESH_I2C_ADDR 0x3A     ///< Chip I2C address, no change address function.

#define R_NAME_H 0x01
#define R_NAME_L 0x02
#define R_GROUP_H 0x03
#define R_GROUP_L 0x04
#define R_FLUSH 0x05
#define R_DATALEN 0x06
#define R_TYPE 0x07
#define R_ADDR_H 0x08
#define R_ADDR_L 0x09
#define R_VERSION 0xF1

#define SEND_NAME 0x03
#define SEND_GROUP 0x04
#define FLUSH_DATA 0x01
#define FLUSH_DATA_EXIST 0x03
#define FLUSH_DATA_NOEXIST 0x00
#define NO_GROUP  0
#define GROUP_1   1<<0
#define GROUP_2   1<<1
#define GROUP_3   1<<2
#define GROUP_4   1<<3
#define GROUP_5   1<<4
#define GROUP_6   1<<5
#define GROUP_7   1<<6
#define GROUP_8   1<<7
#define GROUP_9   1<<8
#define GROUP_10  1<<9
#define GROUP_11  1<<10
#define GROUP_12  1<<11
#define GROUP_13  1<<12
#define GROUP_14  1<<13
#define GROUP_15  1<<14
#define GROUP_16  1<<15



typedef struct
{
  uint16_t sourceAddr;
  char data[32];
  uint8_t datalen;
}sMeshData_t;


class DFRobot_EasyMesh{
public:
  DFRobot_EasyMesh(){};
  ~DFRobot_EasyMesh(){};
  
  void setDivceName(uint16_t name);

  void setGroup(uint16_t group);

  sMeshData_t getData(void);

  void sendName(uint16_t name, const char *data);

  void sendGroup(uint16_t group, const char *data);

  char *getVersion(void);

protected:
  virtual void readData(uint8_t reg, uint8_t *data ,uint8_t len)=0;
  virtual void writeData(uint8_t reg, uint8_t *data, uint8_t len)=0;
private:
  uint8_t getdataLen(void);
  void i2c_flush(void);
  char _version[10];
};

class DFRobot_EasyMesh_I2C:public DFRobot_EasyMesh{
public:
  DFRobot_EasyMesh_I2C(TwoWire *pWire=&Wire ,uint8_t addr=0x3A);
  ~DFRobot_EasyMesh_I2C();
  void writeData(uint8_t reg, uint8_t *data, uint8_t len);
  void readData(uint8_t reg, uint8_t *data ,uint8_t len);
  bool begin(void);
private:
  TwoWire *_pWire;
  uint8_t _I2C_addr;
  
};
#endif
