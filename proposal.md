# 循跡車

## Introduction

* 自製無人自走車引導系統
* 增加記憶能力
* 增加遠端更改路線的功能


## Design specification
* Input
  * IR Sensor
  * Magnetometer
* Output
  * BOE BOT Car movement
  * Computer Application



## Implementation details
* Component list (software and hardware).
  1. BOE BOT Car  
  2. Xbee  
  3. 紅外線循跡模組  
  4. Python  
  5. Qt5  

* Hardware schematic.  
![](http://gitlab.larc-nthu.net/106061209/midterm/raw/master/Schematic.png)  

* Expected issues and challenges for the implementation.  
  1. 紅外線循跡模組無法使用
  2. BOE BOT Car 不依照軌跡行走
  3. GUI 無法顯示 BOE BOT Car 行走路線
  4. 無法儲存行走路線並回放行走的路線
  5. 畫在電腦端的軌跡無法傳給BOE BOT Car

## Score components
1. 紅外線循跡模組可以讀到正確的訊號
2. BOE BOT Car 可以依據地面的軌跡行走
3. BOE BOT Car 可以將行走時地磁計的數據顯示到電腦上
4. BOE BOT Car 可以將行走路線顯示到電腦上
5. BOE BOT Car 可以儲存行走路線並回放行走的路線
6. BOE BOT Car 可以照著畫在電腦中的軌跡行走出相同的路線

## References
https://tutorials.webduino.io/zh-tw/docs/useful/example/toycar-line-following.html  
http://epaper.gotop.com.tw/pdf/AEH003200.pdf  
https://sites.google.com/site/studyarduino/04mblock/03mblock-xun-ji-che  
http://sinocgtchen.blogspot.tw/2013/05/motoduinoarduino-l293d-ir-tracker-sensor.html  
https://www.cnblogs.com/PyLearn/p/7689170.html  
https://blog.digilentinc.com/how-to-convert-magnetometer-data-into-compass-heading/