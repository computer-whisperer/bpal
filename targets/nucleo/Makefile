PROJECT = main
BUILD_DIR = bin

CFILES = main.cpp
CFILES += gpio.cpp

# TODO - you will need to edit these two lines!
DEVICE=stm32f446ret6u

# OOCD values
OOCD		?= openocd
OOCD_INTERFACE	?= stlink-v2
OOCD_TARGET	?= stm32f4x

# You shouldn't have to edit anything below here.
VPATH += ../../ ../../hal/ports/stm32
INCLUDES += -I../../hal/include
OPENCM3_DIR=../../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk

include rules.mk

include $(OPENCM3_DIR)/mk/genlink-rules.mk


