#include "commands.h"
#include "subbus.h"
#include "spi.h"

void commands_init(void) {
  gpio_set_pin_direction(ADR0, GPIO_DIRECTION_IN);
  gpio_set_pin_pull_mode(ADR0, GPIO_PULL_OFF);
  gpio_set_pin_function(ADR0, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(ADR1, GPIO_DIRECTION_IN);
  gpio_set_pin_pull_mode(ADR1, GPIO_PULL_OFF);
  gpio_set_pin_function(ADR1, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(ADR2, GPIO_DIRECTION_IN);
  gpio_set_pin_pull_mode(ADR2, GPIO_PULL_OFF);
  gpio_set_pin_function(ADR2, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(CLOSE0, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(CLOSE0, false);
  gpio_set_pin_function(CLOSE0, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(OPEN0, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(OPEN0, false);
  gpio_set_pin_function(OPEN0, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(CLOSE1, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(CLOSE1, false);
  gpio_set_pin_function(CLOSE1, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(OPEN1, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(OPEN1, false);
  gpio_set_pin_function(OPEN1, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(CLOSE2, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(CLOSE2, false);
  gpio_set_pin_function(CLOSE2, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(OPEN2, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(OPEN2, false);
  gpio_set_pin_function(OPEN2, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(CLOSE3, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(CLOSE3, false);
  gpio_set_pin_function(CLOSE3, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(OPEN3, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(OPEN3, false);
  gpio_set_pin_function(OPEN3, GPIO_PIN_FUNCTION_OFF);

  gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);
  gpio_set_pin_level(LED, true);
  gpio_set_pin_function(LED, GPIO_PIN_FUNCTION_OFF);
  
  subbus_cache_config(SUBBUS_ADDR_CMDS, true);
}

typedef struct {
  int open;
  int close;
} channel_command_pins;

channel_command_pins channel_pins[4] = {
  { OPEN0, CLOSE0 },
  { OPEN1, CLOSE1 },
  { OPEN2, CLOSE2 },
  { OPEN3, CLOSE3 }
};

static void issue_command(int channel, int mode) {
  bool open_cmd = (mode & 2) != 0;
  bool close_cmd = (mode & 1) != 0;
  gpio_set_pin_level(channel_pins[channel].open, open_cmd);
  gpio_set_pin_level(channel_pins[channel].close, close_cmd);
}
void poll_commands(void) {
  uint16_t cmd;
  if (subbus_cache_iswritten(SUBBUS_ADDR_CMDS, &cmd)) {
    switch (cmd) {
      case 32: spi_enable(true); break;
      case 33: spi_enable(false); break;
      case 34: spi_single_ended(true); break;
      case 35: spi_single_ended(false); break;
      case 36: spi_measure_pos(true); break;
      case 37: spi_measure_pos(false); break;
      default:
        if (cmd < 32) {
          int channel = (cmd & 0x1C) >> 2;
          int mode = cmd & 0x03;
          if (mode == 3 && channel != 3) return;
          if (channel <= 3) {
            issue_command(channel, mode);
          } else {
            for (channel = 0; channel <= 3; ++channel) {
              issue_command(channel, mode);
            }
          }
        }
       break;
    }
  }
}