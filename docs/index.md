# Documentación, THOR-HIJA

Repositorio del robot **THOR-HIJA**, microsumo 5×5×5 cm: el kit de LEM ROBOTICS (Esdrufao, 2020). El nombre es un chiste del grupo: *"hija de Thor, torrija"*.

## Índice

1. [Hardware y pinout](01-hardware.md), componentes, alimentación y conexionado completo
2. [Firmware](02-firmware.md), estructura del código, librerías, cómo flashear
3. [Sensores](03-sensores.md), QTR de borde del dohyō y SHARP de detección de oponente
4. [Mando IR](04-comunicacion-ir.md), receptor, protocolo y códigos del mando blanco
5. [PCB](05-pcb.md), diseño en Proteus, gerbers y configuración de alimentación

## Resumen

| | |
|---|---|
| Categoría | Microsumo (máx. 5×5×5 cm; < 100 g) |
| MCU | ATmega328P (Arduino Pro Mini, 5 V / 16 MHz) |
| Motorización | 2× N20 (3 V / 6 V) + TB6612FNG |
| Sensores | 2× QTR-1A (línea), 1× Sharp GP2Y0A21 (oponente) |
| Control remoto | Receptor IR (pin 11) + mando blanco |
| Año de diseño | 2020 (Esdrufao / LEM ROBOTICS) |

## Enlaces de interés

- Vídeo de montaje: <https://www.youtube.com/watch?v=JZTX_83l-D0>
- Chasis 3D (origen): <https://cults3d.com/es/modelo-3d/juegos/robot-microsumo>

---

[Siguiente: 01 - Hardware y pinout →](01-hardware.md)
