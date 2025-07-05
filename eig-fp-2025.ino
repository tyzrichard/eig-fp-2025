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

BleKeyboard bleKeyboard;
BleMouse bleMouse;

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

  bleKeyboard.begin();
  Serial.println("BLE Keyboard Started!");
  bleMouse.begin();
  Serial.println("BLE Mouse Started!");
}

void loop() {
  // Serial.print("PB1 status - ");
  // Serial.println(digitalRead(PB1));
  pushbutton();
  // laser();
  joystick();               
}

void pushbutton() {
  if (digitalRead(PB)) {
    bleKeyboard.write(KEY_MEDIA_LOCAL_MACHINE_BROWSER);
  }
}

// void laser() {
//   static unsigned long lastPressTime = 0;
//   static bool ledState = false;                  // Persistent laser state
//   static bool buttonPreviouslyPressed = false;
//   static bool waitingForSecondClick = false;
//   static bool holdActive = false;

//   bool buttonPressed = digitalRead(PB1) == HIGH;
//   unsigned long currentTime = millis();

//   // Detect rising edge (button just pressed)
//   if (buttonPressed && !buttonPreviouslyPressed) {
//     if (waitingForSecondClick && (currentTime - lastPressTime <= 400)) {
//       // Double click detected
//       ledState = !ledState;
//       waitingForSecondClick = false;
//     } else {
//       // First click
//       waitingForSecondClick = true;
//       lastPressTime = currentTime;
//     }
//   }

//   // If button is held down (press-and-hold), and laser is not toggled on
//   if (buttonPressed && !ledState) {
//     holdActive = true;
//   }

//   // If button is released, disable temporary hold
//   if (!buttonPressed && buttonPreviouslyPressed) {
//     holdActive = false;
//   }

//   // Cancel waiting for double-click if timeout exceeded
//   if (waitingForSecondClick && (currentTime - lastPressTime > 400)) {
//     waitingForSecondClick = false;
//   }

//   // Decide whether to turn on laser
//   if (ledState || holdActive) {
//     digitalWrite(LED1, HIGH);
//   } else {
//     digitalWrite(LED1, LOW);
//   }

//   // Update previous state
//   buttonPreviouslyPressed = buttonPressed;

//   // Debug output
//   Serial.print("ledState (toggled): ");
//   Serial.println(ledState);
//   Serial.print("holdActive (temporary): ");
//   Serial.println(holdActive);
// }


void joystick() {
  x_value = analogRead(JOY_X);
  y_value = analogRead(JOY_Y);
  Serial.println("X Value: " + String(x_value) + " | Y Value: " + String(y_value));
  tetris();
}

void tetris() {
  if (x_value < 1400) {
    bleKeyboard.write('a');
  } else if (x_value > 2000) {
    bleMouse.move();
  } else {
    bleMouse.stop();
  }

  if (y_value < 1400) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
  } else if (y_value > 2000) {
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
  } else {
    bleKeyboard.releaseAll();
  }         

  if (digitalRead(JOY_SW) == 1) {
    bleKeyboard.write(' ');
  }
}

void mouse() {
  // No this doesn't work yet
}
