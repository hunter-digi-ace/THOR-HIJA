[← Volver al índice](index.md)

# 03, Sensores

THOR-HIJA usa dos tipos de sensor:

1. **QTR-1A (×2)**, detectan el **borde blanco del dohyō** (median la reflexión).
2. **Sharp GP2Y0A21YK**, detectan al **oponente** (distancia por IR).

## Sensores de línea (QTR-1A)

- Modelo: Pololu QTR-1A (reflectancia, salida **analógica**).
- En el esquema se rotulan como `QTR-8` (conjunto de sensores QTR de Pololu);
  el conjunto real montado aquí es un par de QTR-1A frontales.
- Conectados a `A1` y `A2`.

### Lectura

```cpp
QTRSensors qtr;
qtr.setTypeAnalog();
qtr.setSensorPins((const uint8_t[]){ A1, A2 }, 2);
qtr.setEmitterPin(255);        // emisor sin control (siempre encendido)

uint16_t sensorValues[2];
qtr.read(sensorValues);
```

Los valores van de **0** (máxima reflexión → superficie clara) a **2500**
(mínima reflexión → superficie oscura). El borde del dohyō es una línea blanca,
así que al cruzarla el valor **cae por debajo de 200**: ese es el umbral usado
en el firmware para detectar que estamos en el borde.

### Calibración

Para microsumo de competición conviene sustituir el umbral fijo por una
**calibración automática** (barrido girando sobre el dohyō, guardando mínimos y
máximos) usando el `emitterPin` para evitar el umbral "falso" del IR ambiente.

## Sensor de oponente (Sharp GP2Y0A21)

- Salida **analógica**: el voltaje **sube cuando el objeto se acerca**.
- Rango de medición típico: **10–80 cm**.
- Conectado a `A0`.

### Lectura filtrada

La función `ADC0_promedio(n)` promedia `n` lecturas de `A0` para reducir el ruido:

```cpp
int ADC0_promedio(int n) {
  long suma = 0;
  for (int i = 0; i < n; i++)
    suma += analogRead(A0);
  return suma / n;
}
```

Uso con `n = 20` (prueba de filtrado) o `n = 200` (detección estable):

```cpp
int ADC_SHARP = ADC0_promedio(20);
Serial.println(ADC_SHARP);
```

### Umbral de oponente: 350

En los tests se considera que hay **objeto delante** cuando `ADC_SHARP > 350`
(`sharp_led.ino` enciende el pin 9 y marca `"Objeto Detectado"`). El mismo umbral
se usa en el firmware principal para decidir `back(...)`.

> Nota: 350 ADC ≈ 1.71 V (con referencia de 5 V). El valor exacto depende de la
> posición de montaje, la luz ambiente y la obscuridad del oponente; es un buen
> punto de partida pero conviene ajustarlo en pista.

## Tests disponibles

| Archivo | Sensor | Descripción |
|---|---|---|
| `tests/sharp_filtro.ino` | Sharp (A0) | Promedio de 20 lecturas por serie |
| `tests/sharp_led.ino` | Sharp (A0) | Promedio de 200, umbral 350 → LED en pin 9 |

---

[← 02 - Firmware](02-firmware.md)  |  [04 - Mando IR →](04-comunicacion-ir.md)