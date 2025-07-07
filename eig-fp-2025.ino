
#include <BleCombo.h>

int PB = 14;   // Change
int JOY_X = 15, JOY_Y = 4, JOY_SW = 34;  // Change
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
  //wasd();
}

int x_left_trigger = 300, x_right_trigger = 3800, y_top_trigger = 300, y_bottom_trigger = 3800; // Joystick trigger boundaries

void mouse() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
  bool btn = digitalRead(PB) == HIGH;

  int dx = 0, dy = 0;

  if (x < x_left_trigger) dx = -1; // move left
  if (x > x_right_trigger) dx = 1; // move right
  if (y < y_top_trigger) dy = -1; //move up
  if (y > y_bottom_trigger) dy = 1; // move down

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
  if (y < y_top_trigger) {
    if (!wPressed) { Keyboard.press('w'); wPressed = true; }
  } else if (wPressed) {
    Keyboard.release('w'); wPressed = false;
  }

  // --- Handle S (DOWN) ---
  if (y > y_bottom_trigger) {
    if (!sPressed) { Keyboard.press('s'); sPressed = true; }
  } else if (sPressed) {
    Keyboard.release('s'); sPressed = false;
  }

  // --- Handle A (LEFT) ---
  if (x < x_left_trigger) {
    if (!aPressed) { Keyboard.press('a'); aPressed = true; }
  } else if (aPressed) {
    Keyboard.release('a'); aPressed = false;
  }

  // --- Handle D (RIGHT) ---
  if (x > x_right_trigger) {
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
