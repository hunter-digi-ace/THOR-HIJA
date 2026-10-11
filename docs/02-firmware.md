[← Volver al índice](index.md)

# 02, Firmware

El firmware está escrito en **Arduino (C++)** y se compila con el IDE de Arduino.

## Carpeta de código

| Archivo | Descripción |
|---|---|
| `source_code/THOR-HIJA/THOR-HIJA.ino` | Firmware principal del microsumo |
| `source_code/tests/REMOTO.ino` | Lectura de códigos del mando IR |
| `source_code/tests/sharp_filtro.ino` | Lectura filtrada (promedio) del Sharp |
| `source_code/tests/sharp_led.ino` | Detección de oponente + LED de prueba |

> Los sketches de prueba originales se llamaban `REMOTO.ino`, `sketch_mar03b.ino`
> y `sketch_mar03c.ino`; se han renombrado aquí para mayor claridad.

## Librerías

| Librería | Autor | Uso |
|---|---|---|
| [QTRSensors](https://github.com/pololu/qtr-sensors-arduino) | Pololu | Lectura de sensores de reflectancia QTR-1A |
| [SparkFun_TB6612](https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library) | SparkFun | Driver de motores TB6612FNG |
| [IRremote](https://github.com/z3t0/Arduino-IRremote) | z3t0 | Receptor IR (usada en los tests, no en el firmware principal) |

Instalar las tres desde el **Gestor de librerías** del IDE de Arduino antes de compilar.

## Firmware principal (`THOR-HIJA.ino`)

```cpp
#include <QTRSensors.h>
#include <SparkFun_TB6612.h>

QTRSensors qtr;                       // 2 sensores analógicos en A1, A2
uint16_t sensorValues[2];

#define AIN1 2      #define BIN1 7
#define AIN2 4      #define BIN2 8
#define PWMA 5      #define PWMB 6
#define STBY 9

#define ADC_SHARP A0                 // sensor de oponente

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA = 1, STBY);   // canal A
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB = 1, STBY);   // canal B
```

### `setup()`
- `Serial.begin(9600)`
- Configura los **QTR como analógicos** en `A1`/`A2`.
- `qtr.setEmitterPin(255)` → el control del emisor IR queda desactivado
  (los QTR-1A no tienen patilla de emisor controlada).
- La recepción IR (`IRremote`) está desactivada.

### `loop()`, lógica de control
1. **Lectura del borde del dohyō**: `qtr.read(sensorValues)` devuelve 2 valores
   de 0 (máxima reflexión / superficie blanca) a 2500 (mínima reflexión / negra).
2. Si un sensor lee `< 200` → activa `digitalWrite(10, HIGH)` (indicador) y llama
   a `forward(motor1, motor2, 255)`.
3. **Sensor de oponente** (Sharp en `A0`): si la media analógica supera `350`
   → `back(motor1, motor2, 255)`.
4. En caso contrario, oscila `right(...)` / `left(...)` a 180 con `delay(100)`.

La función auxiliar `ADC0_promedio(n)` devuelve la media de `n` lecturas de `A0`.

> Este bucle es una **versión de trabajo en curso**, en evolución.

## Cómo flashear

1. Abrir `source_code/THOR-HIJA/THOR-HIJA.ino` con el IDE de Arduino.
2. Placa: **Arduino Pro Mini**; procesador **ATmega328P (5 V, 16 MHz)**.
3. Conectar un **USB-TTL** a los pines RX/TX del Pro Mini
   (desconectando el plug de la batería mientras se programa).
4. Subir el código y abrir el monitor serie a 9600 baudios.

## Tests de sensores

| Test | Qué hace | Salida |
|---|---|---|
| `REMOTO.ino` | Imprime `codigo.value` por serie cada vez que recibe un código IR | Decimal 32-bit |
| `sharp_filtro.ino` | Promedio de 20 lecturas de `A0` y lo imprime | Valor analógico |
| `sharp_led.ino` | Promedio de 200 lecturas; si es `> 350` enciende el pin 9 y marca "Objeto Detectado" | HIGH/LOW en pin 9 + serie |

Ver [04-comunicacion-ir.md](04-comunicacion-ir.md) y
[03-sensores.md](03-sensores.md) para los detalles de cada sensor.

---

[← 01 - Hardware y pinout](01-hardware.md)  |  [03 - Sensores →](03-sensores.md)