#include <arduino.h>

#ifndef _GPIO_EXPANDER_
#define _GPIO_EXPANDER_

#ifndef INPUT_PULLDOWN
#define INPUT_PULLDOWN 0x3
#endif
//INPUT_PULLDOWN

#ifndef DEFAULT_GPIOEXP_ADDR
#define DEFAULT_GPIOEXP_ADDR 42
#endif
// DEFAULT_GPIOEXP_ADDR

enum IOcommand {
      WHO_AM_I //Отдали UID
    , RESET // сброс
    , CHANGE_I2C_ADDR // сменить I2C-адрес вручную
    , SAVE_I2C_ADDR // Сохранить текущий адрес во флэш, чтобы стартовать при последующих включениях с него
    , PORT_MODE_INPUT // настроили пины на вход
    , PORT_MODE_PULLUP // .. вход с поддтяжкой вверх
    , PORT_MODE_PULLDOWN // .. вниз
    , PORT_MODE_OUTPUT // .. на выход
    , DIGITAL_READ    // считали состояние виртуального порта
    , DIGITAL_WRITE_HIGH // Выставили пины виртуального порта в высокий уровень
    , DIGITAL_WRITE_LOW // .. в низкий уровень
    , ANALOG_WRITE // Запустить ШИМ
    , ANALOG_READ // Считать значениие с АЦП
    , PWM_FREQ // установка частоты ШИМ (общая для всех PWM-пинов)
    , ADC_SPEED
    , SEND_MASTER_READED_UID
    , CHANGE_I2C_ADDR_IF_UID_OK
};

class GpioExpander 
{
public:
    GpioExpander(uint8_t i2caddress);
    void digitalWrite(int pin, bool value);
    void pinMode(int pin, uint8_t mode);
    void analogWrite(int pin, uint8_t pulseWidth);
    void analogWrite_16(int pin, uint16_t pulseWidth);
    void pwmFreq(uint16_t freq);
    void changeAddr(uint8_t newAddr);
    void changeAddrWithUID(uint8_t newAddr);
    void saveAddr();
    void reset();
    int  digitalRead(int pin);
    int  analogRead(int pin);//, uint8_t avgCount = 2);
    uint32_t getUID();
    int digitalReadPort();
    void digitalWritePort(uint16_t value);
    void pinModePort(uint16_t value, uint8_t mode);
    void adcSpeed(uint8_t speed);

private:
    uint8_t _i2caddress;
    void writeCmdPin(IOcommand command, uint8_t pin, bool sendStop = true);
    void writeCmdPin16Val(IOcommand command, uint8_t pin, uint16_t value, bool sendStop = true);
    void writeCmd16BitData(IOcommand command, uint16_t data);
    void writeCmd8BitData(IOcommand command, uint8_t data);
    void writeCmd(IOcommand command, bool sendStop = true);
    int  read16Bit();
    uint32_t read32bit();
};

#endif //_GPIO_EXPANDER_
