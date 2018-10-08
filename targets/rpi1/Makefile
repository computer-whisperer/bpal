TOOLCHAIN = arm-unknown-linux-gnueabi
CC = $(TOOLCHAIN)-gcc
CXX = $(TOOLCHAIN)-g++
LD = $(TOOLCHAIN)-ld

EXTRAINCDIRS = ../../hal/include

VPATH += ../../ ../../hal/ports/wiringpi

CFLAGS = $(patsubst %,-I%,$(EXTRAINCDIRS))
CXXFLAGS = $(patsubst %,-I%,$(EXTRAINCDIRS))

all: main

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ 

main: main.o gpio.o
	$(CXX) -lwiringPi main.o gpio.o -o $@
