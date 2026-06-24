/*
  PressCounter - counts PiicoDev Button presses and prints the total.
  Each physical press is counted exactly once via wasPressed().
*/

#include <Wire.h>
#include <PiicoDev_Button.h>

PiicoDev_Button button;   // default address 0x42, on Wire

uint16_t pressCount = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!button.begin()) {
    Serial.println("PiicoDev Button not found - check wiring/address.");
  }
}

void loop() {
  if (button.wasPressed()) {
    pressCount++;
    Serial.println(pressCount);
  }
  delay(20);
}
