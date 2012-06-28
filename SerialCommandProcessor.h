#ifndef SerialCommandProcessor_h
#define SerialCommandProcessor_h

#include <stdint.h>

template <typename Handler>
class SerialCommandProcessor {
  static const uint8_t buffer_len = 128;

  typedef uint8_t idx_t; // TODO: auto scale to buffer_len

  char mBuffer[buffer_len];
  idx_t mBufferHead;
public:
  bool echo;

  template <typename SerialType>
  void step(SerialType& serial) {
    if (!serial.available())
      return;

    uint8_t byte = serial.read();
    if (byte == '\r' || byte == '\n') {
      if (echo)
	serial.println();
      mBuffer[mBufferHead] = 0;
      Handler::handleCommand(mBuffer, mBufferHead);
      mBufferHead = 0;
    }
    else {
      idx_t newBufferHead = mBufferHead + 1;
      if (newBufferHead < buffer_len) {
	if (echo)
	  serial.write(byte);
      
	mBuffer[mBufferHead] = byte;
	mBufferHead = newBufferHead;
      }
    }
  }
};

#endif
