- # DFRobot_EasyMesh
- [English Version](./README.md)

产品xxx是一款集成了蓝牙5.2通讯模组的Arduino Leonardo开发板，蓝牙模组上集成了蓝牙mesh透传协议,可轻松的组网进行数据传输

![正反面svg效果图](resources/images/DFR0889.jpg)

## 产品链接(https://www.dfrobot.com.cn/goods-3475.html)

    SKU:DFR0889

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述


## 库安装
这里提供两种使用本库的方法:<br>
1.打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_EasyMesh"并安装本库.<br>
2.首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.<br>

## 方法

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

## 兼容性

| 主板        | 通过 | 未通过 | 未测试 | 备注 |
| ----------- | :--: | :----: | :----: | ---- |
| Leonardo    |  √   |        |        |      |


## 历史

- 2022/05/16 - V0.0.1 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))
