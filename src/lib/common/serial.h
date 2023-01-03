#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "io.h"
#include "queue.h"
#include "stream_buffer.h"
#include "trace.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t *buffer;
  size_t idx;
  size_t len;
  void (*lineCallback)(void *serialHandle, uint8_t *line, size_t len);
} SerialLineBuffer_t;

typedef struct SerialHandle {
  // Pointer to hardware struct
  void * device;

  // Name of peripheral (for debug)
  const char *name;

  //
  // TODO - have separate struct for buffers, callbacks, etc.
  //        and use functions to register/allocate them when needed
  //

  // Pin references for low power enable/disable
  IOPinHandle_t *txPin;
  IOPinHandle_t *rxPin;

  // Tx stream buffer to feed ISR
  StreamBufferHandle_t txStreamBuffer;

  // Rx stream buffer to receive from ISR
  StreamBufferHandle_t rxStreamBuffer;

  // Size of Tx stream buffer
  uint32_t txBufferSize;

  // Size of Rx stream buffer
  uint32_t rxBufferSize;

  // ISR rx byte processing function
  BaseType_t (*rxBytesFromISR)(struct SerialHandle *handle, uint8_t *buffer, size_t len);

  // ISR tx byte processing function
  size_t (*getTxBytesFromISR)(struct SerialHandle *handle, uint8_t *buffer, size_t len);

  // Function to process received bytes
  void (*processByte)(void *serialHandle, uint8_t byte);

  // Pointer for additonal arguments/data to link to this handle
  void *data;

  // Interface enabled
  volatile bool enabled;

  // Misc flags
  volatile uint32_t flags;

} SerialHandle_t;

// Dropped rx characters
#define SERIAL_FLAG_RXDROP (1 << 0)

// Dropped tx characters
#define SERIAL_FLAG_TXDROP (1 << 1)

typedef struct {
  uint8_t *buff;
  uint16_t len;
  void *destination;
} SerialMessage_t;

BaseType_t serialGenericRxBytesFromISR(SerialHandle_t *handle, uint8_t *buffer, size_t len);
size_t serialGenericGetTxBytes(SerialHandle_t *handle, uint8_t *buffer, size_t len);
size_t serialGenericGetTxBytesFromISR(SerialHandle_t *handle, uint8_t *buffer, size_t len);
void serialGenericUartIRQHandler(SerialHandle_t *handle);
void serialPutcharUnbuffered(SerialHandle_t *handle, char character);

void serialEnable(SerialHandle_t *handle);
void serialDisable(SerialHandle_t *handle);
void serialGenericRxTask(void *parameters);
void serialTxTask(void *parameters);
void startSerial();

void serialWrite(SerialHandle_t *handle, uint8_t *buff, size_t len);
void serialWriteNocopy(SerialHandle_t *handle, uint8_t *buff, size_t len);

xQueueHandle serialGetTxQueue();

#ifdef TRACE_SERIAL
inline void traceAddSerial(SerialHandle_t *handle, uint8_t byte, bool tx, bool isr) {
  uint32_t arg = 0;
  arg = (uint32_t)handle & 0xFFFF;
  if(tx) {
    // Tx Flag
    arg |= 1 << 16;
  }

  if(isr) {
    // ISR Flag
    arg |= 1 << 17;
  }
  arg |= (uint32_t)byte << 24;

  traceAdd(kTraceEventSerialByte, (void *)arg);
}

#endif

#ifdef __cplusplus
}
#endif
