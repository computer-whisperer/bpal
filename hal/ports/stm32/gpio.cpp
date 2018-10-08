#include "gpio.hpp"

namespace libopencm3 {
  extern "C" {
    #include <libopencm3/stm32/gpio.h>
    #include <libopencm3/stm32/rcc.h>
  }
}

namespace hal {

  void gpio_init() {
    libopencm3::rcc_periph_clock_enable(libopencm3::RCC_GPIOA);
  }

  GPIOPeripheral GPIOPeripheral::get_from_port_signal(uint32_t port, uint32_t signal) {
    const uint32_t stm32_port_map[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK};
    
    // Use lookup table
    uint32_t stm32_port = stm32_port_map[port];
    // STM32 opencm3: signal corresponds to bit enabled (out of 16)
    uint32_t stm32_signal = 1 << signal;
    
    GPIOPeripheral output;
    output.port = stm32_port;
    output.signal = stm32_signal;
    return output;
  }
  
  void GPIOPeripheral::mode_set(Mode mode) {
    switch (mode) {
      case Mode::INPUT_NOPULL:
        libopencm3::gpio_mode_setup(port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, signal);
        break;
      case Mode::INPUT_PULLUP:
        libopencm3::gpio_mode_setup(port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, signal);
        break;
      case Mode::INPUT_PULLDOWN:
        libopencm3::gpio_mode_setup(port, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, signal);
        break;
      case Mode::OUTPUT:
        libopencm3::gpio_mode_setup(port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, signal);
        break;
    }
  }

  void GPIOPeripheral::set(){
    libopencm3::gpio_set(port, signal);
  }
  
  void GPIOPeripheral::clear(){
    libopencm3::gpio_clear(port, signal);
  }
  
  void wait(uint32_t time) {
    for (int j = 0; j < time; j++)
      for (int i = 0; i < 5000; i++)
        __asm__("nop"); 
  }
  
}
