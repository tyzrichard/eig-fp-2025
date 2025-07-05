#include <BleConnectionStatus.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include <BleKeyboard.h>
#include <BleMouse.h>

int PB = 14, LED1 = 27;        // Change
int JOY_X = 4, JOY_Y = 0, JOY_SW = 34;  // Change
int x_value, y_value;                     // Change
int LED_status = 0;

BleKeyboard bleKeyboard("Klickr 9000", "eig", 100);
// BleMouse bleMouse;

void setup() {

  pinMode(PB, INPUT_PULLDOWN);

  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SW, INPUT);

  pinMode(LED1, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(921600);
  Serial.println("Starting device...");
  bleKeyboard.end();
  bleKeyboard.begin();
  Serial.println("BLE Keyboard Started!");
  // bleMouse.begin();
  // Serial.println("BLE Mouse Started!");
}

void loop() {
  Serial.print("Pushbutton status - ");
  Serial.println(digitalRead(PB));
  pushbutton();
  joystick();               
}

void pushbutton() {
  if (digitalRead(PB)) {
    bleKeyboard.print("Hello world!");
  }
}

void joystick() {
  x_value = analogRead(JOY_X);
  y_value = analogRead(JOY_Y);
  Serial.println("X Value: " + String(x_value) + " | Y Value: " + String(y_value));
  tetris();
}

void car() {
  if (x_value < 1400) {
  } else if (x_value > 2000) {
  } else {
  }

  if (y_value < 1400) {
  } else if (y_value > 2000) {
  } else {
  }         

  if (digitalRead(JOY_SW) == 1) {
  }
}

void mouse() {
  if (x_value < 1400) {
    bleMouse.move(-5, 0); // move left
  } else if (x_value > 2000) {
    bleMouse.move(5, 0); // move right
  } else {
    bleMouse.end();
  }

  if (y_value < 1400) {
    bleMouse.move(0, 5); // move up
  } else if (y_value > 2000) {
    bleMouse.move(0, -5); // move down
  } else {
    bleMouse.end();
  }         

  if (digitalRead(JOY_SW) == 1) {
    bleMouse.click(); //clicks left button
  }
}
