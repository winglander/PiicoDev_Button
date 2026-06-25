/*
  PiicoDev_Button.h - Minimal Arduino library for the Core Electronics PiicoDev Button
  Tested on Arduino UNO R4 with a button at default address 0x42.

  Register map (confirmed on hardware):
    0x11  live state, ACTIVE-LOW   (1 = released, 0 = pressed)
    0x12  "was pressed" latch       (1 if pressed since last read, auto-clears on read)
*/

#ifndef PIICODEV_BUTTON_H
#define PIICODEV_BUTTON_H

#include <Arduino.h>
#include <Wire.h>

#define PIICODEV_BUTTON_DEFAULT_ADDR 0x42

class PiicoDev_Button {
  public:
    // Pass a custom address if you've changed the ID switches, and/or a
    // different TwoWire bus (e.g. Wire1).
    PiicoDev_Button(uint8_t address = PIICODEV_BUTTON_DEFAULT_ADDR, TwoWire &wire = Wire);

    // Call once in setup(). Does NOT call Wire.begin() for you, so you stay
    // in control of bus init. Returns true if the device acknowledges.
    bool begin();

    // True if the button is being held down right now.
    bool isPressed();

    // True if the button was pressed since the last call. Auto-clears, so
    // each physical press is reported exactly once. Ideal for counting.
    bool wasPressed();

    // True if the device responds on the bus.
    bool isConnected();

  private:
    uint8_t  _addr;
    TwoWire *_wire;
    int      _readReg(uint8_t reg);   // returns 0-255, or -1 on error
};

#endif
