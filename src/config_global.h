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
