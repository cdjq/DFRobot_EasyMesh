# DFRobot_EasyMesh

- [中文版](./README_CN.md)
产品xxx是一款集成了蓝牙5.2通讯模组的Arduino Leonardo开发板，蓝牙模组上集成了蓝牙mesh透传协议,可轻松的组网进行数据传输

![效果图](resources/images/DFR0889.jpg)

## Product Link(https://www.dfrobot.com/product-2546.html)

    SKU:DFR0889

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary


## Installation
There are two methods for using this library:<br>
1. Open Arduino IDE, search for "DFRobot_EasyMesh" on the status bar in Tools ->Manager Libraries and install the library.<br>
2. Download the library file before use, paste it into \Arduino\libraries directory, then open the examples folder and run the demo in the folder.<br>

## Methods

```C++
  /**
   * @fn setDivceName
   * @brief 设置设备名字
   * @param name 0x0000 ~ 0xFFFF
   * @return NULL
   */
  void setDivceName(uint16_t name);

  /**
   * @fn setGroup
   * @brief 设置要订阅的组
   * @param group 参数可以组合 如 GROUP_1 | GROUP_2
   * @n NO_GROUP
   * @n GROUP_1
   * @n GROUP_2
   * @n GROUP_3
   * @n GROUP_4
   * @n GROUP_5
   * @n GROUP_6
   * @n GROUP_7
   * @n GROUP_8
   * @n GROUP_9
   * @n GROUP_10
   * @n GROUP_11
   * @n GROUP_12
   * @n GROUP_13
   * @n GROUP_14
   * @n GROUP_15
   * @n GROUP_16
   * @return NULL
   */
  void setGroup(uint16_t group);

  /**
   * @fn getData
   * @brief 获取mesh透传数据
   * @return 结构体类型
   * @retval sMeshData_t.sourceAddr  收到谁发的数据
   * @retval sMeshData_t.data 数据
   * @retval sMeshData_t.datalen 数据长度
   */
  sMeshData_t getData(void);

  /**
   * @fn sendName
   * @brief 单播，给指定的名字发数据
   * @param name 0x0000 ~ 0xFFFF
   * @param data 发送的数据
   * @return NULL
   */
  void sendName(uint16_t name, const char *data);

  /**
   * @fn sendGroup
   * @brief 组播，给指定的组发数据
   * @param GROUP_1 - GROUP_16
   * @param data 发送的数据
   * @return NULL
   */
  void sendGroup(uint16_t group, const char *data);

  /**
   * @fn getVersion
   * @brief 获取版本
   * @return 版本名称 字符串
   */
  char *getVersion(void);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Leonardo   |      √       |              |             |


## History

- 2022/05/16 - V1.0.0 Version

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))
