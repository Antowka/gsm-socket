cmake_minimum_required(VERSION 3.5)

project(gsm_module)

set(DEVICE atmega328p)
set(FREQ "14745600")

include_directories("/usr/avr/sys-root/include")
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(CMAKE_C_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -std=c11 -Wl,--gc-sections")
set(CMAKE_CXX_FLAGS "-Os -mmcu=${DEVICE} -DF_CPU=${FREQ}UL -Wl,--gc-sections")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES
        main.c
        components/system/mydefs.h
        components/system/helperavr.h
        components/system/initializer.c components/system/initializer.h components/uart/uart.h components/uart/uart.c components/modem/control.h components/modem/control.c components/modem/dtmf/dtmf.h components/modem/dtmf/dtmf.h components/modem/dtmf/dtmf.c components/modem/sms/sms.h components/modem/sms/sms.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -R.eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.eep)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} --mcu=${DEVICE} --format=avr)
