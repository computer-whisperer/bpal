#include "gpio.hpp"

using namespace hal;

GPIOPeripheral led_gpio;

int main(void)
{
  gpio_init();
  //led_gpio = GPIOPeripheral::get_from_port_signal(0, 5); // A5
  led_gpio = GPIOPeripheral::get_from_port_signal(1, 5); // B5
  //led_gpio = GPIOPeripheral::get_from_port_signal(0, 3); // rpi 22
  led_gpio.mode_set(GPIOPeripheral::Mode::OUTPUT);

  long i = 0;

	/* Blink the LED (PC8) on the board. */
	while (1) {
    led_gpio.set();
    wait(10);
     
    led_gpio.clear();
    wait(1000);

	}

	return 0;
}
