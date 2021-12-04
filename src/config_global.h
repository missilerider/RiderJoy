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
#define MOMENTARY_MS    50;
#define IDLE_MS         0;

/** Milisegundos a esperar para cancelar la aceleración de un rotary axis
 */
#define ROTARY_IDLE_TIMEOUT     20;


/** Se puede conectar un multiplexor ("MUX") de puertos analógicos (74HC4067) para 
 * utilizar 16 entradas analógicas en un solo pin analógico del Arduino (MUX_PIN_IN).
 * El posible conectar múltiples
 * 
 * Conexión:
 * MUX      Arduino
 * S0       MUX_ADDR_PIN0
 * S1       MUX_ADDR_PIN1
 * S2       MUX_ADDR_PIN2
 * S3       MUX_ADDR_PIN3
 * SIG      Pin analógico
 * VCC      VCC
 * GND      GND
 * 
 * El pin analógico puede ser único
 */
#define MUX_ADDR_PIN0   15
#define MUX_ADDR_PIN1   14
#define MUX_ADDR_PIN2   16
#define MUX_ADDR_PIN3   10
