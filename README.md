# Real-Time Sensor Telemetry & State Logger

A lightweight, zero-allocation circular buffer and sensor node processing pipeline written in standard C for low-level embedded systems.

## Features
- **Circular History Buffer (`O(1)` complexity):** Uses index-wrapping pointer math instead of expensive shift loops.
- **Data Bundling (`struct`):** Packages raw ADC readings, scaled physical units (Volts), and status flags into a single structured node.
- **Bitwise Status Flagging:** Packs real-time warning states into a single `uint16_t` register using bitwise masking (`|=`, `&= ~`).
