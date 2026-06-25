# PiicoDev_Button (Arduino)

Minimal Arduino library for the [Core Electronics PiicoDev® Button](https://core-electronics.com.au/piicodev-button.html), communicating over I2C.

It exposes the live press state and a clear-on-read "was pressed" latch, so each physical press can be counted exactly once.

Tested on an Arduino UNO R4 with the button at its default address `0x42`.

## Installation

**Arduino IDE — Library Manager** (once accepted into the index): *Tools → Manage Libraries…*, search for `PiicoDev_Button`.

**Manual / .ZIP:** download this repo as a ZIP and use *Sketch → Include Library → Add .ZIP Library…*, or clone it into your `Arduino/libraries` folder.

## Wiring

Connect the PiicoDev Button to your board's I2C bus (SDA/SCL) and power. The library does **not** call `Wire.begin()` for you — call it yourself in `setup()`.

## Usage

```cpp
#include <Wire.h>
#include <PiicoDev_Button.h>

PiicoDev_Button button;   // default address 0x42, on Wire

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (!button.begin()) {
    Serial.println("PiicoDev Button not found - check wiring/address.");
  }
}

void loop() {
  if (button.wasPressed()) {   // counted once per physical press
    Serial.println("pressed!");
  }
  delay(20);
}
```

See [`examples/PressCounter`](examples/PressCounter/PressCounter.ino) for a complete sketch.

## API

| Method | Description |
| --- | --- |
| `PiicoDev_Button(address = 0x42, wire = Wire)` | Construct with an optional I2C address and `TwoWire` bus (e.g. `Wire1`). |
| `bool begin()` | Returns `true` if the device acknowledges on the bus. Call once in `setup()`. |
| `bool isPressed()` | `true` while the button is held down right now. |
| `bool wasPressed()` | `true` if pressed since the last call. Auto-clears, so each press is reported once. |
| `bool isConnected()` | `true` if the device responds on the bus. |

## Register map

Confirmed on hardware:

| Register | Meaning |
| --- | --- |
| `0x11` | Live state, **active-low** (`1` = released, `0` = pressed). |
| `0x12` | "Was pressed" latch (`1` if pressed since last read; auto-clears on read). |

## License

[MIT](LICENSE)
