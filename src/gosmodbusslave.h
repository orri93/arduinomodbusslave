#ifndef _GOS_ARDUINO_LIBRARY_MODBUS_SLAVE_H_
#define _GOS_ARDUINO_LIBRARY_MODBUS_SLAVE_H_

#include <Arduino.h>

#ifndef MODBUS_MAX_BUFFER
#define MODBUS_MAX_BUFFER 256
#endif

#ifndef MODBUS_INVALID_UNIT_ADDRESS
#define MODBUS_INVALID_UNIT_ADDRESS 255
#endif

#ifndef MODBUS_DEFAULT_UNIT_ADDRESS
#define MODBUS_DEFAULT_UNIT_ADDRESS 1
#endif

#ifndef MODBUS_CONTROL_PIN_NONE
#define MODBUS_CONTROL_PIN_NONE -1
#endif

namespace gos {
namespace modbus {

enum class Function {
  Invalid = 0,
  ReadCoils = 1,
  ReadDiscreteInput = 2,
  ReadHoldingRegisters = 3,
  ReadInputRegisters = 4,
  WriteCoil = 5,
  WriteRegister = 6,
  ReadExceptionStatus = 7,
  WriteMultipleCoils = 15,
  WriteMultipleRegisters = 16
};

class Slave {
public:
  Slave(
    const uint8_t& id = MODBUS_DEFAULT_UNIT_ADDRESS,
    const int& pin = MODBUS_CONTROL_PIN_NONE);
  Slave(
    Stream &stream,
    const uint8_t& id = MODBUS_DEFAULT_UNIT_ADDRESS,
    const int& pin = MODBUS_CONTROL_PIN_NONE);
  void begin(const unsigned long& baud);
private:
  Stream& stream_;
  uint8_t id_;
  uint8_t pin_;
  int stream_buffer_length_;
  uint16_t half_char_time_;
  unsigned long last_time_;
  uint16_t request_length_;
};

}
}

#endif /* _GOS_ARDUINO_LIBRARY_MODBUS_SLAVE_H_ */
