#include "gpio.hpp"

namespace avr {
  #include <avr/io.h>
}

namespace hal {

  void gpio_init() {
    // Nothing needed
  }

  GPIOPeripheral GPIOPeripheral::get_from_port_signal(uint32_t port, uint32_t signal) {
    volatile uint8_t* avr_port_map[] = {0, &PORTB, &PORTC, &PORTD};
    volatile uint8_t* avr_pin_map[] = {0, &PINB, &PINC, &PIND};
    volatile uint8_t* avr_ddr_map[] = {0, &DDRB, &DDRC, &DDRD};
    
    // signal corresponds to bit enabled (out of 8)
    uint8_t avr_signal = 1 << signal;
        
    GPIOPeripheral output;
    output.port = port;
    output.signal = avr_signal;
    output.lowlevel_reference_a = (void*) avr_port_map[port];
    output.lowlevel_reference_b = (void*) avr_pin_map[port];
    output.lowlevel_reference_c = (void*) avr_ddr_map[port];
    
    return output;
  }
  
  void GPIOPeripheral::mode_set(Mode mode) {
    
    switch (mode) {
      case Mode::OUTPUT:
        *((volatile uint8_t*)lowlevel_reference_c) |= signal; // DDR
        *((volatile uint8_t*)lowlevel_reference_a) |= signal; // Default low
        break;
      case Mode::INPUT_NOPULL:
        *((volatile uint8_t*)lowlevel_reference_c) &= ~signal; // DDR
        *((volatile uint8_t*)lowlevel_reference_a) &= ~signal; // No pull
        break;
      case Mode::INPUT_PULLUP:
        *((volatile uint8_t*)lowlevel_reference_c) &= ~signal; // DDR
        *((volatile uint8_t*)lowlevel_reference_a) |= signal; // Pullup
        break;
      case Mode::INPUT_PULLDOWN:
        // Unsupported
        break;

    }
  }

  void GPIOPeripheral::set(){
    *((volatile uint8_t*)lowlevel_reference_a) |= signal;
  }
  
  void GPIOPeripheral::clear(){
    *((volatile uint8_t*)lowlevel_reference_a) &= ~signal;
  }
  
  void wait(uint32_t time) {
    for (int j = 0; j < time; j++)
      for (int i = 0; i < 5000; i++)
        __asm__("nop"); 
  }
  
}
