#pragma once

// 0000 0000 0000 0000 
// TTTT DDDD DDXX XXXX 
// 0000 0000 00XX XXXX PIN[X]
// 0001 00DD DDXX XXXX MCP[D][X]
// 0010 DDDD DDXX XXXX MUX...

#define Input    uint8_t

// PIN: 00 XXXXXX
// x: [0,63]
#define PIN(x) ((uint8_t)x)

// MCP: 1Y YY XXXX
// x:[0,15]
#define MCP0(x) (0b10000000 | x)
#define MCP1(x) (0b10010000 | x)
#define MCP2(x) (0b10100000 | x)
#define MCP3(x) (0b10110000 | x)
#define MCP4(x) (0b11000000 | x)
#define MCP5(x) (0b11010000 | x)
#define MCP6(x) (0b11100000 | x)
#define MCP7(x) (0b11110000 | x)

// AMUX: 01 YY XXXX
// x:[0,15]
#define AMUX0(x) (0b01000000 | x)
#define AMUX1(x) (0b01010000 | x)
#define AMUX2(x) (0b01100000 | x)
#define AMUX3(x) (0b01110000 | x)

#define GET_PIN_TYPE(x) (x & 0b11000000)

#define TYPE_PIN    0b00000000
#define TYPE_MCPa   0b10000000
#define TYPE_MCPb   0b11000000
#define TYPE_AMUX   0b01000000

//#define IS_PIN(x) (GET_PIN_TYPE(x) == TYPE_PIN)
//#define IS_MCP(x) (GET_PIN_TYPE(x) == TYPE_MCP)
//#define IS_AMUX(x) (GET_PIN_TYPE(x) == TYPE_AMUX)

#define MCP_ID(x) ((x & 0b01110000) >> 4)
#define MCP_PIN(x) (x & 0b1111)

#define AMUX_ID(x) ((x & 0b00110000) >> 6)
#define AMUX_PIN(x) (x & 0b1111)
