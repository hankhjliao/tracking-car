#include "mbed.h"
#include "parallax.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "uLCD_4DGL.h"

//sudo mbed compile -m K64F -t GCC_ARM -f
Ticker IRSensor;
uLCD_4DGL uLCD(D1, D0, D2);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalIn pin8(D8);
DigitalIn pin10(D10);
PwmOut pin12(D12), pin11(D11), buzzer(D3);
Serial xbee(D9,D7);
I2C i2c( D14, D15 );
// Serial pc( USBTX, USBRX);

parallax_servo *servo0_ptr, *servo1_ptr;

void FXOS8700CQ_enable();
float FXOS8700CQ_read_M_X();
float FXOS8700CQ_read_M_Y();

char strings[256];
char buf[256], outbuf[256], xbuf[256];
int state = 0;

void IR() {
    if(pin8 && !pin10) 
    {
        led1 = 0;
        led2 = 1;
        state = 0;
        sprintf(strings, "/ServoTurn/run 25 -0.1");
    }
    else if(!pin8 && pin10) 
    {
        led1 = 1;
        led2 = 0;
        state = 0;
        sprintf(strings, "/ServoTurn/run 25 0.1");
    }
    else 
    {
        led1 = 1;
        led2 = 1;
        if (state == 0)
        {
            sprintf(strings, "/ServoStop/run");
            state = 1;
        }
        else if (state == 1)
        {
            sprintf(strings, "/ServoTurn/run 25");
            state = 2;
        }
        else
        {
            sprintf(strings, "/ServoTurn/run 25");
        }
    }
}

int main() {
    int s = 0;
    bbcar_init(pin11, pin12);
    FXOS8700CQ_enable();
    uLCD.color(BLUE);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.printf("\n106061209\n");
    uLCD.circle(65,80,30,WHITE);
    uLCD.line(65,80,65,50,WHITE);
    uLCD.line(65,80,39,95,WHITE);
    uLCD.line(65,80,91,95,WHITE);
    IRSensor.attach(&IR, 0.1);
    while (1) {
        while(xbee.readable()) {
            for( int i=0; i < 10;i++ ) {
                xbuf[i] = xbee.getc();
                if(xbuf[i] == '\n') break;
            }
        }
        if (xbuf[0]=='g')
        {
            s = 1;
            xbee.printf("o");
            // IRSensor.attach(&IR, 0.1);
        }
        else if (xbuf[0]=='s')
        {
            // IRSensor.detach();
            sprintf(strings, "/ServoStop/run");
            strcpy(buf, strings);
            RPC::call(buf, outbuf);
            led1 = 1;
            led2 = 1;
            s = 0;
            state = 2;
            xbee.printf("k");
        }
        if (s==1) 
            strcpy(buf, strings);
        if (s==1) 
            RPC::call(buf, outbuf);
        xbee.printf("x%4.1f,z%4.1f,",FXOS8700CQ_read_M_X(), FXOS8700CQ_read_M_Y());
    }
}