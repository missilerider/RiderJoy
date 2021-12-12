#pragma once

// Tiempo de pulsación para las configuraciones momentáneas, en milisegundos
/** Descripción:
 * Si un botón momentáneo se mantiene pulsado, el botón del joystick permanecerá 
 * pulsado MOMENTARY_MS milisegundos y luego se apagará hasta que se pulse de 
 * nuevo el botón.
 * 
 * En caso de un botón rotatorio que se apague solo (con "IDLE_MS"), se apagará 
 * durante "idle" milisegundos y se volverá a encender MOMENTARY_MS milisegundos 
 * si se sigue girando.
 */
#define MOMENTARY_MS    1000;
#define IDLE_MS         50;

/** Milisegundos a esperar para cancelar la aceleración de un rotary axis
 */
#define ROTARY_IDLE_TIMEOUT     20;


/** Se puede conectar un multiplexor de puertos analógicos ("AMUX") (74HC4067) para 
 * utilizar 16 entradas analógicas en un solo pin analógico del Arduino (AMUX_PIN_INx).
 * El posible conectar múltiples multiplexores, con todos los S0 a AMUX_ADDR_PIN0 y 
 * demás, y cada SIG a un AMUX_PIN_IN diferente
 * 
 * Los pines se referencian como AMUX0(3) para leer el puerto 3 del multiplexor
 * conectado a AMUX_PIN_IN0
 * 
 * Conexión:
 * MUX      Arduino
 * S0       AMUX_ADDR_PIN0
 * S1       AMUX_ADDR_PIN1
 * S2       AMUX_ADDR_PIN2
 * S3       AMUX_ADDR_PIN3
 * SIG      Pin analógico
 * VCC      VCC
 * GND      GND
 * 
 */
#define AMUX_ADDR_PIN0   15
#define AMUX_ADDR_PIN1   14
#define AMUX_ADDR_PIN2   16
#define AMUX_ADDR_PIN3   10

#define AMUX_PIN_IN0    A0
#define AMUX_PIN_IN1    A1
#define AMUX_PIN_IN2    A2
#define AMUX_PIN_IN3    A3
