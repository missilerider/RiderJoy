#pragma once

#include <Arduino.h>

class FnNumpad {
public:
    static uint16_t status;
    static uint8_t p0, p1, p2, p3, p4, p5, p6;

    static void begin();
    static void setup(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6);

    static void process();
    static void process(void (*doPoll)());
};

