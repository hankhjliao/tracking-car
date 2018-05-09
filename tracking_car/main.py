
import time
import math
from serial import Serial
import sys,tty,termios
from PyQt5.QtWidgets import (QApplication, QWidget, QLabel, QHBoxLayout, QVBoxLayout, QPushButton, QLineEdit, QGridLayout, QMessageBox)
from PyQt5.QtGui import (QPainter, QPen)
from PyQt5.QtCore import Qt, QThread, QMutexLocker, QMutex, pyqtSignal, QRect

serdev = '/dev/ttyUSB0'
s = Serial(serdev, 9600)

class Example(QWidget):

    def __init__(self):
        super(Example, self).__init__()
        self.initUI()
        self.setMouseTracking(False)
        self.pos_xy = []
        self.work = Worker()
        self.work.pos_xyW.connect(self.updateM)
        self.mode = 1

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)
        pen = QPen(Qt.black, 2, Qt.SolidLine)
        painter.setPen(pen)
        if len(self.pos_xy) > 1:
            point_start = self.pos_xy[0]
            for pos_tmp in self.pos_xy:
                point_end = pos_tmp
                if point_end == (-1, -1):
                    point_start = (-1, -1)
                    continue
                if point_start == (-1, -1):
                    point_start = point_end
                    continue
                painter.drawLine(point_start[0], point_start[1], point_end[0], point_end[1])
                point_start = point_end
        painter.end()
    
    def initUI(self):
        self.modeButton = QPushButton("Mode 1")
        self.modeButton.setGeometry(QRect(20, 10, 85, 26))
        horizontalLayout = QHBoxLayout()
        self.recordButton = QPushButton("Record")
        horizontalLayout.addWidget(self.recordButton)
        self.stopButton = QPushButton("Stop")
        horizontalLayout.addWidget(self.stopButton)
        self.playButton = QPushButton("Play")
        horizontalLayout.addWidget(self.playButton)
        self.clearButton = QPushButton("Clear")
        horizontalLayout.addWidget(self.clearButton)
        
        self.modeButton.clicked.connect(self.changeMode)
        self.recordButton.clicked.connect(self.recordTrace)
        self.stopButton.clicked.connect(self.stopTrace)
        self.playButton.clicked.connect(self.playTrace)
        self.clearButton.clicked.connect(self.clearTrace)

        mainLayout = QVBoxLayout()
        mainLayout.addWidget(self.modeButton)
        mainLayout.addStretch()
        mainLayout.addLayout(horizontalLayout)

        self.modeButton.setEnabled(False)
        self.recordButton.setEnabled(True)
        self.stopButton.setEnabled(False)
        self.playButton.setEnabled(False)
        self.clearButton.setEnabled(False)

        self.setLayout(mainLayout)
        self.resize(800, 600)
        self.move(100, 100)
        self.setWindowTitle("Tracking Car")
        self.show()

    def changeMode(self):
        s.write(b'm')
        if(self.mode == 1):
            self.modeButton.setText("Mode 2")
            self.recordButton.setEnabled(False)
            self.clearButton.setEnabled(False)
            self.mode = 2
        elif(self.mode == 2):
            self.modeButton.setText("Mode 1")
            self.recordButton.setEnabled(True)
            self.clearButton.setEnabled(True)
            self.mode = 1
        self.stopButton.setEnabled(False)
        self.playButton.setEnabled(False)

    def recordTrace(self):
        s.write(b'g')
        s.write(b'\r')
        s.write(b'\n')
        self.pos_xy=[]
        self.work.start()
        self.modeButton.setEnabled(False)
        self.recordButton.setEnabled(False)
        self.stopButton.setEnabled(True)
        self.playButton.setEnabled(False)
        self.clearButton.setEnabled(False)

    def stopTrace(self):
        s.write(b's')
        s.write(b'\r')
        s.write(b'\n')
        pos_test = (-1, -1)
        self.pos_xy.append(pos_test)
        self.work.stop()
        # self.modeButton.setEnabled(True)
        self.recordButton.setEnabled(True)
        self.stopButton.setEnabled(False)
        self.playButton.setEnabled(True)
        self.clearButton.setEnabled(True)
        self.update()

    def playTrace(self):
        print(self.pos_xy)
        # self.modeButton.setEnabled(False)
        # self.recordButton.setEnabled(True)
        # self.stopButton.setEnabled(True)
        # self.playButton.setEnabled(False)

    def clearTrace(self):
        # self.modeButton.setEnabled(True)
        self.recordButton.setEnabled(True)
        self.stopButton.setEnabled(False)
        self.playButton.setEnabled(False)
        self.clearButton.setEnabled(False)
        self.pos_xy=[]
        self.update()
    
    def updateM(self,pos):
        self.pos_xy.append(pos)
        self.update()

class Worker(QThread):
    pos_xyW = pyqtSignal(tuple)    
    def __init__(self, parent=None):
        super(Worker, self).__init__(parent)
        self.stoped = False
        self.mutex = QMutex()
        self.xvalue = 0
        self.yvalue = 0
        self.assign = 1
    
    def run(self):
        pos_init=(400.0,300.0)
        with QMutexLocker(self.mutex):
            self.stoped = False
        while(True):
            for i in range(5):
                char = s.read()
                if(char==b'x'):
                    self.xvalue = 0
                    self.assign = 1
                    while char != b'.':
                        char = s.read()
                        if (char == b'-'):
                            self.assign = -1
                        elif (char == b'0'):
                            self.xvalue *= 10
                        elif (char == b'1'):
                            self.xvalue *= 10
                            self.xvalue += 1
                        elif (char == b'2'):
                            self.xvalue *= 10
                            self.xvalue += 2
                        elif (char == b'3'):
                            self.xvalue *= 10
                            self.xvalue += 3
                        elif (char == b'4'):
                            self.xvalue *= 10
                            self.xvalue += 4
                        elif (char == b'5'):
                            self.xvalue *= 10
                            self.xvalue += 5
                        elif (char == b'6'):
                            self.xvalue *= 10
                            self.xvalue += 6
                        elif (char == b'7'):
                            self.xvalue *= 10
                            self.xvalue += 7
                        elif (char == b'8'):
                            self.xvalue *= 10
                            self.xvalue += 8
                        elif (char == b'9'):
                            self.xvalue *= 10
                            self.xvalue += 9
                    self.xvalue *= self.assign
                if(char==b'z'):
                    self.yvalue = 0
                    self.assign = 1
                    while char != b'.':
                        char = s.read()
                        if (char == b'-'):
                            self.assign = -1
                        elif (char == b'0'):
                            self.yvalue *= 10
                        elif (char == b'1'):
                            self.yvalue *= 10
                            self.yvalue += 1
                        elif (char == b'2'):
                            self.yvalue *= 10
                            self.yvalue += 2
                        elif (char == b'3'):
                            self.yvalue *= 10
                            self.yvalue += 3
                        elif (char == b'4'):
                            self.yvalue *= 10
                            self.yvalue += 4
                        elif (char == b'5'):
                            self.yvalue *= 10
                            self.yvalue += 5
                        elif (char == b'6'):
                            self.yvalue *= 10
                            self.yvalue += 6
                        elif (char == b'7'):
                            self.yvalue *= 10
                            self.yvalue += 7
                        elif (char == b'8'):
                            self.yvalue *= 10
                            self.yvalue += 8
                        elif (char == b'9'):
                            self.yvalue *= 10
                            self.yvalue += 9
                    self.yvalue *= self.assign
            if(self.yvalue==0 and self.xvalue>=0):
                tmp=0.0
            elif(self.yvalue==0 and self.xvalue<0):
                tmp=180.0
            elif(self.yvalue>0):
                tmp=math.pi/2-math.atan(self.xvalue/self.yvalue)
            else:
                tmp=math.pi*3/2-math.atan(self.xvalue/self.yvalue)
            pos_init=pos_tmp
            self.pos_xyW.emit(pos_tmp)
            if self.stoped:
                return 
            
    def stop(self):
        with QMutexLocker(self.mutex):
            self.stoped = True
    
    def isStop(self):
        with QMutexLocker(self.mutex):
            return self.stoped

if __name__ == "__main__":
    app = QApplication(sys.argv)
    pyqt_learn = Example()
    pyqt_learn.show()
    app.exec_()
