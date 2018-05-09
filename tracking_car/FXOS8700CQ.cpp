#include "mbed.h"
#define UINT14_MAX        16383
// FXOS8700CQ I2C address

#define FXOS8700CQ_SLAVE_ADDR0 (0x1E<<1) // with pins SA0=0, SA1=0
#define FXOS8700CQ_SLAVE_ADDR1 (0x1D<<1) // with pins SA0=1, SA1=0
#define FXOS8700CQ_SLAVE_ADDR2 (0x1C<<1) // with pins SA0=0, SA1=1
#define FXOS8700CQ_SLAVE_ADDR3 (0x1F<<1) // with pins SA0=1, SA1=1
// FXOS8700CQ internal register addresses
#define FXOS8700Q_STATUS 0x00
#define FXOS8700Q_OUT_X_MSB 0x01
#define FXOS8700Q_OUT_Y_MSB 0x03
#define FXOS8700Q_OUT_Z_MSB 0x05
#define FXOS8700Q_M_OUT_X_MSB 0x33
#define FXOS8700Q_M_OUT_Y_MSB 0x35
#define FXOS8700Q_M_OUT_Z_MSB 0x37
#define FXOS8700Q_WHOAMI 0x0D
#define FXOS8700Q_XYZ_DATA_CFG 0x0E
#define FXOS8700Q_CTRL_REG1 0x2A
#define FXOS8700Q_M_CTRL_REG1 0x5B
// #define FXOS8700Q_M_CTRL_REG2 0x5C
#define FXOS8700Q_M_CTRL_REG1_M_ACAL (1 << 7)
// #define FXOS8700Q_M_CTRL_REG1_M_RST (1 << 6)
// #define FXOS8700Q_M_CTRL_REG1_M_OST (1 << 5)
#define FXOS8700Q_M_CTRL_REG1_MO_OS3(x) (x << 2) // x is 3-bit
#define FXOS8700Q_M_CTRL_REG1_M_HMS2(x) (x << 0) // x is 2-bit
#define FXOS8700Q_WHOAMI_VAL 0xC7

extern I2C i2c;
int m_addr = FXOS8700CQ_SLAVE_ADDR1;
void FXOS8700CQ_readRegs(int addr, uint8_t * data, int len);
void FXOS8700CQ_writeRegs(uint8_t * data, int len);

void FXOS8700CQ_enable(){
    uint8_t data[2];
    FXOS8700CQ_readRegs( FXOS8700Q_CTRL_REG1, &data[1], 1);
    data[1] |= 0x01;
    data[0] = FXOS8700Q_CTRL_REG1;
    FXOS8700CQ_writeRegs(data, 2);

    FXOS8700CQ_readRegs( FXOS8700Q_M_CTRL_REG1, &data[1], 1);
    // Setup for write-through for M_CTRL_REG series
    data[0] = FXOS8700Q_M_CTRL_REG1;
    data[1] =
        FXOS8700Q_M_CTRL_REG1_M_ACAL | // set automatic calibration
        FXOS8700Q_M_CTRL_REG1_MO_OS3(7) | // use maximum magnetic oversampling
        FXOS8700Q_M_CTRL_REG1_M_HMS2(3); // enable hybrid sampling (both sensors)
     FXOS8700CQ_writeRegs(data, 2);
}

float FXOS8700CQ_read_X(){
    uint8_t res[2];
    FXOS8700CQ_readRegs(FXOS8700Q_OUT_X_MSB, res, 2);
    int16_t acc16 = (res[0] << 6) | (res[1] >> 2);

    if (acc16 > UINT14_MAX / 2) acc16 -= UINT14_MAX;
    return ((float)acc16) / 4096.0f;
}

float FXOS8700CQ_read_Y(){
    uint8_t res[2];
    FXOS8700CQ_readRegs(FXOS8700Q_OUT_Y_MSB, res, 2);
    int16_t acc16 = (res[0] << 6) | (res[1] >> 2);

    if (acc16 > UINT14_MAX / 2) acc16 -= UINT14_MAX;
    return ((float)acc16) / 4096.0f;
}

float FXOS8700CQ_read_Z(){
    uint8_t res[2];
    FXOS8700CQ_readRegs(FXOS8700Q_OUT_Z_MSB, res, 2);
    int16_t acc16 = (res[0] << 6) | (res[1] >> 2);

    if (acc16 > UINT14_MAX / 2) acc16 -= UINT14_MAX;
    return ((float)acc16) / 4096.0f;
}

float FXOS8700CQ_read_M_X(){
    uint8_t res[2];
    FXOS8700CQ_readRegs(FXOS8700Q_M_OUT_X_MSB, res, 2);
    int16_t mag16 = (res[0] << 8) | (res[1]);
    return ((float)mag16)*0.1f;
}

float FXOS8700CQ_read_M_Y(){
    uint8_t res[2];
    FXOS8700CQ_readRegs(FXOS8700Q_M_OUT_Y_MSB, res, 2);
    int16_t mag16 = (res[0] << 8) | (res[1]);
    return ((float)mag16)*0.1f;
}

float FXOS8700CQ_read_M_Z(){
    uint8_t res[2];
    FXOS8700CQ_readRegs(FXOS8700Q_M_OUT_Z_MSB, res, 2);
    int16_t mag16 = (res[0] << 8) | (res[1]);
    return ((float)mag16)*0.1f;
}

void FXOS8700CQ_readRegs(int addr, uint8_t * data, int len) {
    char t = addr;
    i2c.write(m_addr, &t, 1, true);
    i2c.read(m_addr, (char *)data, len);
}

void FXOS8700CQ_writeRegs(uint8_t * data, int len) {
    i2c.write(m_addr, (char *)data, len);
}
