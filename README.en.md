# 2024 Intelligent Vehicle Motorcycle Group - Wanling Bifang

#### Introduction

This project is designed for the 19th motorcycle group, indoor track, with the K2 vehicle model.

#### Software Architecture

```
-[.setting]
  -[...] Project configuration files
-[Debug] 
  -[...] System debug generated files
-[code] Personal code folder
  -[Fusion] Gyroscope attitude calculation library, see detailed reference at the end of the document
  -[camera] Camera image processing code
  -[controller] 
    -[ano] Wireless serial port transmission module
    -[balance] Balance control module, called by timer
    -[menu] Menu module
    -[pid] PID module
    -[user_key] Key scanning module
-[libraries]
  -[...] Feifei open source libraries, omitted
-[user]
  -[...] Core task scheduling, omitted
```

#### Hardware Architecture

Omitted

#### References

1. [Attitude Calculation Open Source Library](https://github.com/xioTechnologies/Fusion)
2. [Feifei Motorcycle Group Analysis](https://mp.weixin.qq.com/s/qAG4r8Nu76s_rK_FdMEDYA)

#### Contributors

- Javen
- Dai