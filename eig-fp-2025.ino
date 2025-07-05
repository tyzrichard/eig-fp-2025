// #include <BleConnectionStatus.h>
// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEScan.h>
// #include <BLEAdvertisedDevice.h>

#include <BleCombo.h>

int PB = 14;   // Change
int JOY_X = 4, JOY_Y = 0, JOY_SW = 34;  // Change
int x_value, y_value;                     // Change

// "Klickr 9000."

void setup() {
  pinMode(PB, INPUT_PULLDOWN);

  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SW, INPUT_PULLDOWN);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(921600);

  Keyboard.end();
  Mouse.end();
  Serial.println("Starting device...");
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  Serial.print("Pushbutton status - ");
  Serial.println(digitalRead(PB));
  pushbutton(); // comment out if using wasd
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

  // Mouse or WASD - Choose ONE
  mouse();
  // wasd();
}


void mouse() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
  bool btn = digitalRead(PB) == HIGH;

  int dx = 0, dy = 0;

  if (x < 1600) dx = -5; // move left
  if (x > 2400) dx = 5; // move right
  if (y < 3000) dy = -5; //move up
  if (y > 3600) dy = 5; // move down

  if (dx != 0 || dy != 0) {
    Mouse.move(dx, dy, 0);  // move mouse
    // delay(20);
  }

  if (digitalRead(JOY_SW) == 1) {
    Mouse.click(); // clicks left button
  }
}

bool wPressed = false;
bool aPressed = false;
bool sPressed = false;
bool dPressed = false;
bool spacePressed = false;

void wasd() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
  bool btn = digitalRead(PB) == HIGH;

  // --- Handle W (UP) ---
  if (y < 1600) {
    if (!wPressed) { Keyboard.press('w'); wPressed = true; }
  } else if (wPressed) {
    Keyboard.release('w'); wPressed = false;
  }

  // --- Handle S (DOWN) ---
  if (y > 2400) {
    if (!sPressed) { Keyboard.press('s'); sPressed = true; }
  } else if (sPressed) {
    Keyboard.release('s'); sPressed = false;
  }

  // --- Handle A (LEFT) ---
  if (x < 1600) {
    if (!aPressed) { Keyboard.press('a'); aPressed = true; }
  } else if (aPressed) {
    Keyboard.release('a'); aPressed = false;
  }

  // --- Handle D (RIGHT) ---
  if (x > 2400) {
    if (!dPressed) { Keyboard.press('d'); dPressed = true; }
  } else if (dPressed) {
    Keyboard.release('d'); dPressed = false;
  }

  // --- Handle SPACEBAR button ---
  if (btn && !spacePressed) {
    Keyboard.press(' ');
    spacePressed = true;
  } else if (!btn && spacePressed) {
    Keyboard.release(' ');
    spacePressed = false;
  }

  delay(10); // debounce/polling delay
}
