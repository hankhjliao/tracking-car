# Tracking Car

## Before Execution

1. Before adding a library, we need to install an required package mercurial.  
`$ sudo apt install mercurial`

2. Add "4DGL-uLCD-SE" library.  
`$ mbed add https://os.mbed.com/users/4180_1/code/4DGL-uLCD-SE/`

3. Add "parallax" library.  
`$ mbed add http://gitlab.larc-nthu.net/embedded_lab/parallax`

4. Add "bbcar_control" library.  
`$ mbed add http://gitlab.larc-nthu.net/embedded_lab/bbcar_control`

5. Add "bbcar_control_rpc" library.  
`$ mbed add http://gitlab.larc-nthu.net/embedded_lab/bbcar_control_rpc`

6. Add the RPC library into the project.  
`$ cd mbed-os/drivers`  
`$ cp ../features/unsupported/rpc/* .`

7. Install PyQt5.  
`$ pip3 install pyqt5`


## Execution

`$ sudo python3 main.py`
