/*
  RGB STRIP LIGHT EFFECTS DEMO
  Runs different effects on RGB strip light (NOT the Pixel LED with Data pins).

  Connect pin 9, 10, 11 of Arduino to RGB pins of the LED strip light via
  a driving circuit like IRFZ44N MOSFET or any appropriate transistor.

  This program is designed and tested on Arduino UNO R3 board.

  Created 9 Sep 2025
  by Rishik Tiwari (MAKING by Auriva Technologies)
  https://making.auriva.tech
*/

int i = 0; // used in loops
int idx = 0; // active pin index

int pins[] = {9, 10, 11}; // using pwm pins
uint8_t num_of_pins = 3; // num of pins (colour channels)

void setup() {
  for(int i = 0; i < num_of_pins; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
}

void loop() {
  blink();
  blink();
  blink();
  chase(2, 300);
  chaseFade(1, 250);
  strobe(20);
  chase(1, 100);
  delay(500);
  chaseRubberBand(10, 200);
}

void blink() {
  for(i = 0; i < num_of_pins; i++) {
    digitalWrite(pins[i], HIGH);
  }
  delay(1500);
  for(i = 0; i < num_of_pins; i++) {
    digitalWrite(pins[i], LOW);
  }
  delay(250);
}

void chase(uint8_t repeat, int holdMs) {
  repeat *= num_of_pins;
  for(i = 0; i < repeat; i++) {
    digitalWrite(pins[idx], HIGH);
    delay(holdMs);
    digitalWrite(pins[idx], LOW);
    
    idx += 1;
    if(idx >= num_of_pins) { // loops to pin range
      idx = 0;
    }
  }
}

void chaseRubberBand(uint8_t repeat, int holdMs) {
  repeat *= num_of_pins;
  int direction = 1;
  for(i = 0; i < repeat; i++) {
    digitalWrite(pins[idx], HIGH);
    delay(holdMs);
    digitalWrite(pins[idx], LOW);
    
    idx += direction;
    if(idx >= num_of_pins) { // change chase direction to decrement
      idx -= 2;
      direction = -1;
    }
    else if (idx <= 0) { // change chase direction to increment
      direction = 1;
    }
  }
  idx = 0; // reset idx
}

void chaseFade(uint8_t repeat, int holdMs) {
  repeat *= num_of_pins;
  int j = 0;
  for(i = 0; i < repeat; i++) { // iterations = repeat * num_of_pins
    for(j = 0; j < 256; j++) { // fade in
      analogWrite(pins[idx], j);
      delay(2);
    }
    delay(holdMs);
    for(j = 255; j >= 0; j--) { // fade out
      analogWrite(pins[idx], j);
      delay(2);
    }
    idx += 1;
    if(idx >= num_of_pins) { // loops to pin range
      idx = 0;
    }
  }
}

void strobe(uint16_t times) {
  for(i = 0; i < times; i++) {
    PORTB &= B11110001;
    delay(90);
    PORTB |= B00001110;
    delay(30);
  }
  PORTB &= B11110001;
}