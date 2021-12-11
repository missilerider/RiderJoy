#pragma once

// 0000 0000 0000 0000 
// TTTT DDDD DDXX XXXX 
// 0000 0000 00XX XXXX PIN[X]
// 0001 00DD DDXX XXXX MCP[D][X]
// 0010 DDDD DDXX XXXX MUX...

#define Input    uint16_t

#define PIN(x) ((uint16_t)x)

#define MCP0(x) (0b0001000000000000 | x)
#define MCP1(x) (0b0001000001000000 | x)
#define MCP2(x) (0b0001000010000000 | x)
#define MCP3(x) (0b0001000011000000 | x)
#define MCP4(x) (0b0001000100000000 | x)
#define MCP5(x) (0b0001000101000000 | x)
#define MCP6(x) (0b0001000110000000 | x)
#define MCP7(x) (0b0001000111000000 | x)

#define AMUX0(x) (0b0010000000000000 | x)
#define AMUX1(x) (0b0010000001000000 | x)
#define AMUX2(x) (0b0010000010000000 | x)
#define AMUX3(x) (0b0010000011000000 | x)

#define GET_PIN_TYPE(x) (x & 0b1111000000000000)

#define TYPE_PIN 0b0000000000000000
#define TYPE_MCP 0b0001000000000000
#define TYPE_AMUX 0b0010000000000000

#define IS_PIN(x) (GET_PIN_TYPE(x) == TYPE_PIN)
#define IS_MCP(x) (GET_PIN_TYPE(x) == TYPE_MCP)
#define IS_AMUX(x) (GET_PIN_TYPE(x) == TYPE_AMUX)

#define MCP_ID(x) ((x & 0b111000000) >> 6)
#define MCP_PIN(x) (x & 0b1111)

#define AMUX_ID(x) ((x & 0b11000000) >> 6)
#define AMUX_PIN(x) (x & 0b1111)