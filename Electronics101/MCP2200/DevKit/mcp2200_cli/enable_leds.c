#include "common.h"

/*
  enable the Tx/Rx pins, while keeping all other configurations constant
 */
void enable_leds(hid_device *device_handle) {
  unsigned char report_buffer[REPORT_SIZE];
  int result;

  printf("Turning on the Tx and Rx LEDs..\n");

  report_buffer[0] = READ_ALL_OPCODE;
  result = hid_write(device_handle, report_buffer, REPORT_SIZE);
  result = hid_read(device_handle, report_buffer, REPORT_SIZE);

  report_buffer[0] = CONFIGURE_OPCODE;
  report_buffer[Config_Alt_Pins] |= RxLED | TxLED;              // enabled the LEDs
  report_buffer[Config_Alt_Options] &= !(RxTGL | TxTGL);        // set to blink slow
  report_buffer[Config_Alt_Options] |= LEDX;                    // set to blink slow
  result = hid_write(device_handle, report_buffer, REPORT_SIZE);
}

/*
  main program - find the first MCP2200 and turn on the Tx/Rx LEDS
 */
int main(int argc, char* argv[]) {
  hid_device *device_handle;  // pointer to the selected MCP2200 device

  hid_init();

  device_handle = open_first_device();
  if(!device_handle) {
    printf("No MCP2200 devices found, sorry!\n");
    return 1;
  }
  enable_leds(device_handle);

  close_device(device_handle);

  hid_exit();

  return 0;
}
