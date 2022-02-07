#pragma once

// 0000 0000 0000 0000 
// TTTT DDDD DDXX XXXX 
// 0000 0000 00XX XXXX PIN[X]
// 0001 00DD DDXX XXXX MCP[D][X]
// 0010 DDDD DDXX XXXX MUX...

//#define ControlData         uint64_t
/*
union ControlData {
    // 3B: buttons
    // 1B: specs
    // 2B: pins
    // 1B: timeout (ms)
    uint8_t _data[3 + 1 + 2 + 1];

    struct {
        uint8_t button[3];
        uint8_t specs;
        uint8_t pin[2];
        uint8_t timeout;
    } part;
};*/

// bits 0-2
#define CTRLMASK_TYPE               0b111
#define CONTROL_TYPE_BUTTON         0b000
#define CONTROL_TYPE_SWITCH3        0b001
#define CONTROL_TYPE_SWITCH2        0b010
#define CONTROL_TYPE_POT            0b011
#define CONTROL_TYPE_ROTARY_B       0b100
#define CONTROL_TYPE_ROTARY_AXIS    0b101

// bits 3-4
#define CTRLMASK_MOMENTARY          0b11000
#define CONTROL_MOMENTARY_NO        0b00000
#define CONTROL_MOMENTARY_SIMPLE    0b01000
#define CONTROL_MOMENTARY_FULL      0b10000

// bit 5-6
#define CTRL_MOMENTARY_STAGE0   0b00000000
#define CTRL_MOMENTARY_STAGE1   0b00100000
#define CTRL_MOMENTARY_STAGE2   0b01000000
#define CTRL_MOMENTARY_STAGE3   0b01100000
#define CTRL_MOMENTARY_STAGE4   0b10000000
#define CTRL_MOMENTARY_STAGE5   0b10100000
#define CTRL_MOMENTARY_STAGE6   0b11000000
#define CTRL_MOMENTARY_STAGE7   0b11100000
#define CTRL_MOMENTARY_STAGEMASK    0b00011111

class ControlData {
public:
    uint8_t button[3];
    uint8_t specs;
    uint8_t pin[2];
    uint8_t timeout;

public:
    ControlData() {
        this->button[0] = this->button[1] = this->button[2] = 0;
        this->specs = 0;
        this->pin[0] = this->pin[1] = 0;
        this->timeout = 0;
    }

    ControlData *setup(uint8_t type, uint8_t i1, uint8_t b1) {
        this->button[0] = b1;
        this->button[1] = this->button[2] = 0;
        this->specs = 0;
        this->pin[0] = i1;
        this->pin[1] = 0;
        this->timeout = 0;

        this->setType(type);

        return this;
    }

    ControlData *setup(uint8_t type, uint8_t i1, uint8_t b1, uint8_t b2) {
        this->button[0] = b1;
        this->button[1] = b2;
        this->button[2] = 0;
        this->specs = 0;
        this->pin[0] = i1;
        this->pin[1] = 0;
        this->timeout = 0;

        this->setType(type);

        return this;
    }

    ControlData *setup(uint8_t type, uint8_t i1, uint8_t i2, uint8_t b1, uint8_t b2, uint8_t b3) {
        this->button[0] = b1;
        this->button[1] = b2;
        this->button[2] = b3;
        this->specs = 0;
        this->pin[0] = i1;
        this->pin[1] = i2;
        this->timeout = 0;

        this->setType(type);
     
        return this;
    }

    ControlData *momentary() {
        this->setMomentary(CONTROL_MOMENTARY_SIMPLE);
        return this;
    }

    ControlData *momentaryFull() {
        this->setMomentary(CONTROL_MOMENTARY_FULL);
        return this;
    }

    void setMomentary(uint8_t mtry) {
        this->specs |= mtry;
    }

    void setType(uint8_t type) {
        this->specs |= type;
    }

    uint8_t getType() {
        return this->specs & CTRLMASK_TYPE;
    }

    uint8_t getMomentary() {
        return this->specs & CTRLMASK_MOMENTARY;
    }

    uint8_t getStage() {
        return this->specs & CTRL_MOMENTARY_STAGE7;
    }

    void setStage0() {
        this->specs = (this->specs & CTRL_MOMENTARY_STAGEMASK);
    }

    void setStage1() {
        this->specs = (this->specs & CTRL_MOMENTARY_STAGEMASK) | CTRL_MOMENTARY_STAGE1;
    }

    void setStage2() {
        this->specs = (this->specs & CTRL_MOMENTARY_STAGEMASK) | CTRL_MOMENTARY_STAGE2;
    }

    void setStage3() {
        this->specs = (this->specs & CTRL_MOMENTARY_STAGEMASK) | CTRL_MOMENTARY_STAGE3;
    }

    void setStage4() {
        this->specs = (this->specs & CTRL_MOMENTARY_STAGEMASK) | CTRL_MOMENTARY_STAGE4;
    }

    void setStage5() {
        this->specs = (this->specs & CTRL_MOMENTARY_STAGEMASK) | CTRL_MOMENTARY_STAGE5;
    }

    void setStage6() {
        this->specs = (this->specs & CTRL_MOMENTARY_STAGEMASK) | CTRL_MOMENTARY_STAGE6;
    }

    void setStage7() {
        this->specs |= CTRL_MOMENTARY_STAGE7;
    }

    ControlData *i() {
        this->setStage1();
        return this;
    }

    ControlData *minIdle(uint8_t idle) {
        this->button[2] = idle;
    }

    /** Actualiza el temporizador
     * @return: -1: No ha saltado el timeout. 0: Timeout expirado
     **/
    uint8_t loop(uint8_t elapsed) {
        if(this->timeout == 0) return 0; // Timeout ya finalizado

        if(elapsed >= this->timeout) {
            this->timeout = 0;
            return -1; // Ultimo timeout
        }

        this->timeout -= elapsed;
        return -1; // Timeout suficiente todavía
    }
};


/*

// BOTONES: 7 bits * 3, 
#define CTRLMASK_BUTTON     0b1111111
#define CTRLSHFT_BUTTON     7

#define CONTROL_SETBUTTON(data, button_num, button)     (data |= (((uint8_t)button & CTRLMASK_BUTTON) << (CTRLSHFT_BUTTON * ((uint8_t)button_num))))
#define CONTROL_GETBUTTON(data, button_num)             (data & (CTRLMASK_BUTTON << (CTRLSHFT_BUTTON * ((uint8_t)button_num))))


// MOMENTARY: 2 bits
#define CTRLDISP_MOMENTARY  (CTRLSHFT_BUTTON*3)
#define CTRLMASK_MOMENTARY  (0b11 << CTRLDISP_MOMENTARY)

#define CTRL_MOMENTARY_NO       (0b00 << CTRLDISP_MOMENTARY)
#define CTRL_MOMENTARY_SIMPLE   (0b01 << CTRLDISP_MOMENTARY)
#define CTRL_MOMENTARY_FULL     (0b10 << CTRLDISP_MOMENTARY)


// PIN: 8 bits * 2
#define CTRLDISP_INPUT  (CTRLDISP_MOMENTARY + 2)
#define CTRLSHFT_INPUT  8
#define CTRLMASK_INPUT  0xFF

#define CONTROL_SETINPUT(data, input_num, pin)          (data |= (static_cast<ControlData>((uint8_t)pin & CTRLMASK_INPUT) << (CTRLDISP_INPUT + (CTRLSHFT_INPUT * (uint8_t)input_num))))
#define CONTROL_GETINPUT(data, input_num)              (uint8_t)((data >> (CTRLDISP_INPUT + (CTRLSHFT_INPUT * (uint8_t)input_num))) & CTRLMASK_INPUT)


// TYPE: 3 bits
#define CTRLDISP_TYPE       (CTRLDISP_INPUT + CTRLSHFT_INPUT * 2)
#define CTRLMASK_TYPE       static_cast<ControlData>(0b111 << CTRLDISP_TYPE)

#define CONTROL_TYPE_BUTTON     static_cast<ControlData>(static_cast<ControlData>(0b000) << CTRLDISP_TYPE)
#define CONTROL_TYPE_SWITCH3    static_cast<ControlData>(static_cast<ControlData>(0b001) << CTRLDISP_TYPE)
#define CONTROL_TYPE_SWITCH2    static_cast<ControlData>(static_cast<ControlData>(0b010) << CTRLDISP_TYPE)
#define CONTROL_TYPE_POT        static_cast<ControlData>(static_cast<ControlData>(0b011) << CTRLDISP_TYPE)
#define CONTROL_TYPE_ROTARY_B   static_cast<ControlData>(static_cast<ControlData>(0b100) << CTRLDISP_TYPE)
#define CONTROL_TYPE_TEST   static_cast<ControlData>(static_cast<ControlData>(0b111) << CTRLDISP_TYPE)

#define CONTROL_SETTYPE(data, type)                     (data |= type)
#define CONTROL_GETTYPE(data)                           static_cast<ControlData>(data & CTRLMASK_TYPE)
*/