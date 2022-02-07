#pragma once

#define DEBUG

#define MAX_CONTROLS  128
#define MAX_ROTARIES  4

// Tiempo de pulsación para las configuraciones momentáneas, en milisegundos
/** Descripción:
 * Si un botón momentáneo se mantiene pulsado, el botón del joystick permanecerá 
 * pulsado MOMENTARY_MS milisegundos y luego se apagará hasta que se pulse de 
 * nuevo el botón.
 * 
 * En caso de un botón rotatorio que se apague solo (con "IDLE_MS"), se apagará 
 * durante "idle" milisegundos y se volverá a encender MOMENTARY_MS milisegundos 
 * si se sigue girando.
 * 
 * MOMENTARY_MS para rotatorios y otros con cambio rápido, como rotary encoders
 * MOMENTARY_LONG_MS para pulsaciones lentas, como botones o switches
 */
//#define MOMENTARY_MS    50
#define MOMENTARY_MS    20
//#define IDLE_MS         20
#define IDLE_MS         20

#define MOMENTARY_LONG_MS   250
//#define MOMENTARY_LONG_MS   200
#define IDLE_LONG_MS        250
//#define IDLE_LONG_MS        80

/** Milisegundos a esperar para cancelar la aceleración de un rotary axis
 */
#define ROTARY_IDLE_TIMEOUT     20


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
#define AMUX_ADDR_PIN0   6
#define AMUX_ADDR_PIN1   7
#define AMUX_ADDR_PIN2   8
#define AMUX_ADDR_PIN3   9

#define AMUX_PIN_IN0    A0
#define AMUX_PIN_IN1    A1
#define AMUX_PIN_IN2    A2
#define AMUX_PIN_IN3    A3



/** Umbral que es necesario rebasar para que un potenciómetro cambie de valor (y no baile entre dos cifras)
 * Si se indica el valor 1 no se registrarán cambios de 1 unidad en las lecturas, que es un valor típico para un potenciómetro normalito
 * Si se deja a 0, todos los cambios de lectura se registrarán como movimientos del eje
 */
#define POT_ERROR       1


