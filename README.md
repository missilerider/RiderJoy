# RiderJoy
Simplest Arduino joystick project, for people with a simpit in mind but no idea about programming



# Configuración
Toda la configuración de controles se realiza en el fichero `config_controls.h` y se realiza con macros para hacer la vida más fácil.

Estas macros se pueden usar manualmente o con el configurador Excel incluido, `Configurator.xlsx` (si no tienes Excel siempre puedes importarlo en Google Sheets, por ejemplo).

## Configurador Excel
```Insertar cómo se usa```

# Controles

*Nota:* Los pines de conexión se identifican como `PIN` o `MCPx`, donde `x` es la dirección del MCP asignado. Así, el pin 8 del Arduino será `PIN(8)`, y el pin 8 de la placa MCP 4 será `MCP4(8)`.

*Nota2:* Los botones del joystick se indican en base 0; es decir, para asignar el primer botón del joystick se usará el número **0**, y aparecerá en el panel de control de Windows como "botón 1".

## Botón
Pulsador simple. Lee la electricidad de un pin y escribe el resultado en un botón del joystick.

### Conexión eléctrica:

| Control | Conexión |
|-|-|
| Pin 1 | Gnd |
| Pin 2 | Pin libre del Arduino o MCP |

### Código
**ADD_BUTTON** 

| Argumento | Descripción
| - | - |
| 1 | Pin (`PIN` o `MCP`) donde está conectado el botón |
| 2 | Botón del joystick asignado (en base 0) |
