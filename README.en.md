# 2024 Intelligent Car Motorcycle Group - Wanling Bifang

#### Introduction

This project is for the 19th Motorcycle Group, indoor track, K2 model car.

#### Software Architecture

```
-[.setting]
  -[...] Project configuration files
-[Debug] 
  -[...] System debug generated files
-[code] Personal code folder
  -[Algorithm] Algorithm library, containing commonly used mathematical functions
  -[Fusion] Gyroscope attitude calculation library, detailed reference at the link below
  -[camera] Camera image processing code
  -[controller] 
    -[ano] Wireless serial port sending module
    -[balance] Balance control module, called by timer
    -[menu] Menu module
    -[pid] PID module
    -[user_key] Button scanning module
  -[tld7002] Light show driver
-[libraries]
  -[...] ZOFly open-source library, omitted
-[user]
  -[...] Core task scheduling, omitted
```

#### Hardware Architecture

ZF mainPCB

#### References

1. [Attitude Calculation Open Source Library](https://github.com/xioTechnologies/Fusion)
2. [ZOFly Motorcycle Group Analysis](https://mp.weixin.qq.com/s/qAG4r8Nu76s_rK_FdMEDYA)
3. [ZOFly TC264 Open Source Driver Library](https://gitee.com/seekfree/TC264_Library)

#### Contributors

- Javen 
  - QQ: 2452731211

#### Open-source projects are not easy. If this project has helped you, please give our project a star. Thank you for your attention and support!