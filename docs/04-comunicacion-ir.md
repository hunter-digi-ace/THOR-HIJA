[← Volver al índice](index.md)

# 04, Mando IR (comunicación)

THOR-HIJA puede recibir órdenes por **infrarrojos** con el típico **mando blanco**
(decodificador de reproductores MP3 chinos). La idea es arrancar la cuenta atrás
y armar el robot desde el mando, sin tocar la placa.

## Receptor

- Módulo receptor **TSOP (38 kHz)** conectado externamente a la PCB (la placa V1
  no trae footprint de receptor).
- Pin de datos: **D11** (definido en el test `REMOTO.ino`).
- Alimentación: 5V / GND del Pro Mini.

> El soporte IR en el firmware principal está **comentado** (`IRremote` y
> `irrecv` desactivados en `THOR-HIJA.ino`). La integración está **prevista como mejora**.

## Librería

- [IRremote](https://github.com/z3t0/Arduino-IRremote)

## Prueba de recepción (`tests/IR/REMOTO.ino`)

```cpp
#include <IRremote.h>
int receptor = 11;
IRrecv irrecv(receptor);
decode_results codigo;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&codigo)) {
    Serial.println(codigo.value, DEC);
    irrecv.resume();
  }
}
```

Apunta el mando al receptor y el monitor serie (9600 baud) imprime el código
**decimal** de 32 bits de cada tecla.

### Ejemplo del propio test

| Tecla del mando de prueba | Código | Decimal | Acción |
|---|---|---|---|
| "0" | `0xFF6897` | `16720095` | Enciende el LED del pin 13 |
| "1" | `0xFF30CF` | `16736415` | Apaga el LED del pin 13 |

## Códigos del mando blanco

Tabla extraída de `source_code/tests/IR/codigos_mando_blanco.txt`
(valores de 32 bits tal y como los imprime `IRrecv`):

| Tecla | Código (hex) |
|---|---|
| POWER | `FA3F159F` |
| MENU | `12209C7B` |
| UP | `51E43D1B` |
| ENTER | `AB91951F` |
| DOWN | `FF9186B7` |
| REPEAT | `8C22657B` |
| MUTE | `E5CFBD7F` |
| SHUFFLE | `2A89195F` |
| VOL+ | `F0C41643` |
| REWIND | `45473C1B` |
| PLAY/PAUSE | `9EF4941F` |
| FORWARD | `F377C5B7` |
| VOL- | `FFA857` |

> Nota: este mando usa un protocolo propio de MP3-chino (dirección + complemento
> en 32 bits), no NEC estándar. Para usarlo en el firmware basta comparar
> `codigo.value` con estos valores, p. ej. `0xFA3F159F` para POWER.

---

[← 03 - Sensores](03-sensores.md)  |  [05 - PCB →](05-pcb.md)