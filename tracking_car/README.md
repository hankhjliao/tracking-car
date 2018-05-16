# Tracking Car

## Material

1. mbed K64F * 1
2. BOE BOT Car * 1
3. IR sensor * 2
4. uLCD * 1
5. Xbee * 2
6. PC * 1
7. microUSB to USB converter * 1
8. Wire several

## Preparation

1. Connect the device.
	1. Assemble the BOE BOT Car. [*Instruction*](http://www1.ee.nthu.edu.tw/ee240500/mbed-lab-12-boe-bot-car.html#assemble-your-propeller-boe-bot)
	2. Put the uLCD onto the circuit board of the BOE BOT Car.
	3. Assemble the uLCD. [*Instruction*](http://www1.ee.nthu.edu.tw/ee240500/mbed-lab-4-liquid-crystal-displays.html#color-lcd-display-ulcd-144g2-ar)
	4. Connect other device according to below instruction.  
         uLCD:  

         Pin|I/O  
         :---:|:---:  
         VCC|Xbee VCC, both IR sensor VCC (Red)  
         GND|Xbee GND, both IR sensor GND (Black)  
         D7|Xbee Rx  
         D8|Left IR sensor signal (White)  
         D9|Xbee Tx  
         D10|Right IR sensor signal (White)  
         D11|Left continuous servos signal (White)  
         D12|Right continuous servos signal (White)  
         
2. Connect two Xbee. [*Instruction*](http://www1.ee.nthu.edu.tw/ee240500/mbed-lab-9-wireless-communication-xbee.html#test-and-configure-xbee-with-screen)

3. Create new mbed project.  
`$ mbed new TrackingCar`

4. Go to the directory.  
`$ cd TrackingCar`

5. Copy the all the source codes of this project into the directory.  

6. Before adding "4DGL-uLCD-SE" library, we need to install an required package mercurial.  
`$ sudo apt install mercurial`

7. Add "4DGL-uLCD-SE" library.  
`$ mbed add https://os.mbed.com/users/4180_1/code/4DGL-uLCD-SE/`

8. Add "parallax" library.  
`$ mbed add http://gitlab.larc-nthu.net/embedded_lab/parallax`

9. Add "bbcar_control" library.  
`$ mbed add http://gitlab.larc-nthu.net/embedded_lab/bbcar_control`

10. Add "bbcar_control_rpc" library.  
`$ mbed add http://gitlab.larc-nthu.net/embedded_lab/bbcar_control_rpc`

11. Add the RPC library into the project.  
`$ cd mbed-os/drivers`  
`$ cp ../features/unsupported/rpc/* .`

12. Install GNU Compiler Suit for Ubuntu.  
`$sudo apt install build-essencitial -y`

13. Install pip3.  
`$sudo apt install python3-pip -y`

14. Install PyQt5.  
`$sudo -H pip3 install pyqt5`

15. Compile and flash the program.  
`$ sudo mbed compile -m K64F -t GCC_ARM -f`

## Execution

`$ sudo python3 main.py`
