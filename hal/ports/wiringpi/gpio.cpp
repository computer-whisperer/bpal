#include "gpio.hpp"

namespace wiringpi {
  extern "C" {
    #include <wiringPi.h>
  }
}

namespace hal {

  void gpio_init() {
    wiringpi::wiringPiSetup();
  }

  GPIOPeripheral GPIOPeripheral::get_from_port_signal(uint32_t port, uint32_t signal) {

    GPIOPeripheral output;
    output.port = port;
    output.signal = signal;
    return output;
  }
  
  void GPIOPeripheral::mode_set(Mode mode) {
    switch (mode) {
      case (Mode::INPUT_NOPULL):
        wiringpi::pinMode(signal, INPUT);
        wiringpi::pullUpDnControl(signal, PUD_OFF);
        break;
      case (Mode::INPUT_PULLUP):
        wiringpi::pinMode(signal, INPUT);
        wiringpi::pullUpDnControl(signal, PUD_UP);
        break;
      case (Mode::INPUT_PULLDOWN):
        wiringpi::pinMode(signal, INPUT);
        wiringpi::pullUpDnControl(signal, PUD_DOWN);
        break;
      case (3):
        wiringpi::pinMode(signal, OUTPUT);
        break;
    }
  }

  void GPIOPeripheral::set(){
    wiringpi::digitalWrite(signal, HIGH);
  }
  
  void GPIOPeripheral::clear(){
    wiringpi::digitalWrite(signal, LOW);
  }
  
  void wait(uint32_t time) {
    for (int j = 0; j < time; j++)
      wiringpi::delay(1);
  }
  
}
