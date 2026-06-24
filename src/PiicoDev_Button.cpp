#include "PiicoDev_Button.h"

#define REG_IS_PRESSED  0x11   // active-low: 1 = released, 0 = pressed
#define REG_WAS_PRESSED 0x12   // latch: 1 if pressed since last read, clears on read

PiicoDev_Button::PiicoDev_Button(uint8_t address, TwoWire *bus) {
  _addr = address;
  _wire = bus;
}

bool PiicoDev_Button::begin() {
  return isConnected();
}

bool PiicoDev_Button::isConnected() {
  _wire->beginTransmission(_addr);
  return (_wire->endTransmission() == 0);
}

int PiicoDev_Button::_readReg(uint8_t reg) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  if (_wire->endTransmission(false) != 0) return -1;

  _wire->requestFrom((int)_addr, 1);
  if (_wire->available() < 1) return -1;
  return _wire->read();
}

bool PiicoDev_Button::isPressed() {
  int v = _readReg(REG_IS_PRESSED);
  if (v < 0) return false;       // bus error -> report not pressed
  return (v == 0);               // active-low
}

bool PiicoDev_Button::wasPressed() {
  int v = _readReg(REG_WAS_PRESSED);
  if (v < 0) return false;
  return (v != 0);
}
