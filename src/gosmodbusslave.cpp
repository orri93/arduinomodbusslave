#include <gosmodbusslave.h>

#ifndef MODBUS_FRAME_SIZE
#define MODBUS_FRAME_SIZE 4
#endif

#ifndef MODBUS_CRC_LENGTH
#define MODBUS_CRC_LENGTH 2
#endif

#ifndef MODBUS_ADDRESS_INDEX
#define MODBUS_ADDRESS_INDEX 0
#endif
#ifndef MODBUS_FUNCTION_CODE_INDEX
#define MODBUS_FUNCTION_CODE_INDEX 1
#endif
#ifndef MODBUS_DATA_INDEX
#define MODBUS_DATA_INDEX 2
#endif

#ifndef MODBUS_BROADCAST_ADDRESS
#define MODBUS_BROADCAST_ADDRESS 0
#endif
#ifndef MODBUS_ADDRESS_MIN
#define MODBUS_ADDRESS_MIN 1
#endif
#ifndef MODBUS_ADDRESS_MAX
#define MODBUS_ADDRESS_MAX 247
#endif

#ifndef MODBUS_HALF_SILENCE_MULTIPLIER
#define MODBUS_HALF_SILENCE_MULTIPLIER 3
#endif
#ifndef MODBUS_FULL_SILENCE_MULTIPLIER
#define MODBUS_FULL_SILENCE_MULTIPLIER 7
#endif

#define readUInt16(arr, index) word(arr[index], arr[index + 1])
#define readCRC(arr, length) word(\
  arr[(length - MODBUS_CRC_LENGTH) + 1], \
  arr[length  - MODBUS_CRC_LENGTH])

namespace gos {
namespace modbus {

Slave::Slave(const uint8_t& id, const int& pin) :
  stream_(Serial),
  id_(id),
  pin_(pin) {
}

Slave::Slave(Stream &stream, const uint8_t& id, const int& pin) :
  stream_(stream),
  id_(id),
  pin_(pin) {
}

void Slave::begin(const unsigned long& baud) {
  if (pin_ != MODBUS_CONTROL_PIN_NONE) {
    pinMode(pin_, OUTPUT);
    digitalWrite(pin_, LOW);
  }
  // disable serial stream timeout and cleans the buffer
  stream_.setTimeout(0);
  stream_.flush();
  stream_buffer_length_ = stream_.availableForWrite();

  // calculate half char time time from the serial's baudrate
  if (baud > 19200)
  {
    half_char_time_ = 250; // 0.5T
  }
  else
  {
    half_char_time_ = 5000000 / baud; // 0.5T
  }
  // set the last received time to 3.5T on the future to ignore
  // request currently in the middle of transmission
  last_time_ = micros() + (half_char_time_ * MODBUS_FULL_SILENCE_MULTIPLIER);

  // sets the request buffer length to zero
  request_length_ = 0;
}

}
}
