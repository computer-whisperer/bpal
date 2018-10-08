#include "stdint.h"

#ifndef __HAL_GPIO_HPP__
#define __HAL_GPIO_HPP__

namespace hal {
  
  class GPIOPeripheral {
    uint32_t port;
    uint32_t signal;
    void* lowlevel_reference_a;
    void* lowlevel_reference_b;
    void* lowlevel_reference_c;
    
    public:
      enum Mode {
        INPUT_NOPULL,
        INPUT_PULLUP,
        INPUT_PULLDOWN,
        OUTPUT
      };
    
      static GPIOPeripheral get_from_port_signal(uint32_t port, uint32_t signal);
      void mode_set(Mode mode);
      void set();
      void clear();
  };
  
  void gpio_init();
  
  void wait(uint32_t time);

}

#endif
