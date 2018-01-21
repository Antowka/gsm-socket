#!/usr/bin/env bash
cmake .
make
avrdude -p m328p -c usbasp -b 115200 -U flash:w:bin/gsm_module.hex