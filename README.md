# 2024智能车摩托组--宛陵毕方

#### 介绍

本项目适用于第十九届摩托组，室内赛道，K2车模

#### 软件架构====

```
-[.settting]
  -[...] 项目配置文件
-[Debug] 
  -[...] 系统debug生成文件
-[code] 个人代码文件夹
  -[Algorithm] 算法库,包含常用的数学函数
  -[Fusion] 陀螺仪姿态结算库,详细参考文末链接
  -[camera] 相机图像处理代码
  -[controller] 
    -[ano] 无线串口发送模块
    -[balance] 平衡控制模块,定时器调用
    -[menu] 菜单模块
    -[pid] pid模块
    -[user_key] 按键扫描模块
  -[tld7002] 灯光秀驱动
-[libraries]
  -[...] 逐飞开源库,略
-[user]
  -[...] 核心任务调度,略
```

#### 硬件架构

逐飞主板

#### 参考资料

1. [姿态解算开源库](https://github.com/xioTechnologies/Fusion)
2. [逐飞摩托组解析](https://mp.weixin.qq.com/s/qAG4r8Nu76s_rK_FdMEDYA)
3. [逐飞TC264开源驱动库](https://gitee.com/seekfree/TC264_Library)

#### 贡献者

- Javen 
  -QQ:2452731211

#### 开源不易，如果对你有帮助，请给我们的项目点一个star,感谢您的关注与支持！