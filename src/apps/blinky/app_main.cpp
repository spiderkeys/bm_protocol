
// Includes from CubeMX Generated files
#include "main.h"

// Peripheral
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "icache.h"
#include "iwdg.h"
#include "ucpd.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

// Includes for FreeRTOS
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"
#include "cli.h"
#include "debug_memfault.h"
#include "debug_sys.h"
#include "gpioISR.h"
#include "io.h"
#include "serial.h"
#include "serial_console.h"
#include "memfault_platform_core.h"
#include "watchdog.h"
#include "mcuboot_cli.h"

#include <stdio.h>

static void defaultTask(void *parameters);

// static void defaultTask( void *parameters );

SerialHandle_t usart1 = {
  .device = USART1,
  .name = "usart1",
  .txPin = NULL,
  .rxPin = NULL,
  .txStreamBuffer = NULL,
  .rxStreamBuffer = NULL,
  .txBufferSize = 4096,
  .rxBufferSize = 512,
  .rxBytesFromISR = serialGenericRxBytesFromISR,
  .getTxBytesFromISR = serialGenericGetTxBytesFromISR,
  .processByte = NULL,
  .data = NULL,
  .enabled = false,
  .flags = 0,
};

extern "C" void USART1_IRQHandler(void) {
  serialGenericUartIRQHandler(&usart1);
}

extern "C" int main(void) {

  // Before doing anything, check if we should enter ROM bootloader
  // enterBootloaderIfNeeded();

  HAL_Init();

  SystemClock_Config();

  SystemPower_Config_ext();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_UCPD1_Init();
  MX_USART1_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_ICACHE_Init();
  MX_RTC_Init();
  MX_IWDG_Init();

  // usbMspInit();

  // rtcInit();

  // Enable hardfault on divide-by-zero
  SCB->CCR |= 0x10;

  // Initialize low power manager
  lpmInit();

  // Inhibit low power mode during boot process
  lpmPeripheralActive(LPM_BOOT);

  BaseType_t rval = xTaskCreate(
              defaultTask,
              "Default",
              // TODO - verify stack size
              128 * 4,
              NULL,
              // Start with very high priority during boot then downgrade
              // once done initializing everything
              2,
              NULL);
  configASSERT(rval == pdTRUE);

  // Start FreeRTOS scheduler
  vTaskStartScheduler();

  /* We should never get here as control is now taken by the scheduler */

  while (1){};
}

bool buttonPress(const void *pinHandle, uint8_t value, void *args) {
  (void)pinHandle;
  (void)args;

  printf("Button press! %d\n", value);
  return false;
}


static void defaultTask( void *parameters ) {

  (void)parameters;

  startIWDGTask();
  startSerial();
  startSerialConsole(&usart1);
  startCLI();
  serialEnable(&usart1);
  gpioISRStartTask();

  memfault_platform_boot();
  memfault_platform_start();

  bspInit();

  debugSysInit();
  debugMemfaultInit(&usart1);
  mcubootCliInit();

  // Commenting out while we test usart1
  // lpmPeripheralInactive(LPM_BOOT);

  gpioISRRegisterCallback(&USER_BUTTON, buttonPress);

  // uint32_t count = 0;
  while(1) {
    IOWrite(&LED_BLUE, 1);
    vTaskDelay(2);
    IOWrite(&LED_BLUE, 0);
    vTaskDelay(998);
  }

}