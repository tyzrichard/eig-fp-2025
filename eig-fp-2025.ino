#include <BleConnectionStatus.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// #include <BleKeyboard.h>
// #include <BleMouse.h>
#include <BleCombo.h>

int PB = 14, LED1 = 27;        // Change
int JOY_X = 4, JOY_Y = 0, JOY_SW = 34;  // Change
int x_value, y_value;                     // Change
int LED_status = 0;

// BleKeyboard bleKeyboard("Klickr 9000", "eig", 100);
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
  Keyboard.begin();
  Mouse.begin();
  // bleKeyboard.end();
  // bleKeyboard.begin();
  // Serial.println("BLE Keyboard Started!");
  // // bleMouse.begin();
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
    Keyboard.print("Hello world!");
  }
}

void joystick() {
  x_value = analogRead(JOY_X);
  y_value = analogRead(JOY_Y);
  Serial.println("X Value: " + String(x_value) + " | Y Value: " + String(y_value));
  mouse();
  // wasd();
}

void wasd() {
  //havent figured out the release portion, i might rework this part ngl
  if (x < 1400) Keyboard.press("a"); // move left
  if (x > 2700) Keyboard.press("d"); // move right
  if (y < 1400) Keyboard.press("w"); //move up
  if (y > 2700) Keyboard.press("s"); // move down

  if (digitalRead(JOY_SW) == 1) {
    Keyboard.press(KEY_SPACEBAR);
  }
}

void mouse() {
  int dx = 0, dy = 0;

  if (x < 1400) dx = -5; // move left
  if (x > 2700) dx = 5; // move right
  if (y < 1400) dy = -5; //move up
  if (y > 2700) dy = 5; // move down

  if (dx != 0 || dy != 0) {
    bleCombo.move(dx, dy, 0);  // move mouse
    delay(20);
  }

  if (digitalRead(JOY_SW) == 1) {
    Mouse.click(); //clicks left button
  }

  // if (x_value < 1400) {
  //   Mouse.move(-5, 0); // move left
  // } else if (x_value > 2000) {
  //   Mouse.move(5, 0); // move right
  // }

  // if (y_value < 1400) {
  //   Mouse.move(0, -5); // move up
  // } else if (y_value > 2000) {
  //   Mouse.move(0, 5); // move down
  // }    
}
