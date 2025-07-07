#include <BleCombo.h>

int PB = 14;   // Change
int JOY_X = 33, JOY_Y = 4, JOY_SW = 25;  // Change
int x_value, y_value;                     // Change

// VCC laser, pb, joystick
// GND laser, joystick
// data pb

int JOY_SW_State = LOW;
int last_JOY_SW_State = LOW;
unsigned long lastJOYDebounceTime = 0;
int PB_State = LOW;
int last_PB_State = LOW;
unsigned long lastPBDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50 ms debounce delay
// "Klickr 9000."

void setup() {
  pinMode(PB, INPUT_PULLDOWN);

  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SW, INPUT_PULLUP);

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
  // Serial.print("Pushbutton status - ");
  // Serial.println(digitalRead(PB));
  pushbutton(); // comment out if using wasd
  joystick();               
}

void pushbutton() {
  int reading = digitalRead(PB);

  if (reading != last_PB_State) {
    lastPBDebounceTime = millis();  // reset the timer
  }

  if ((millis() - lastPBDebounceTime) > debounceDelay) {
    if (reading != PB_State) {
      PB_State = reading;

      if (PB_State == HIGH) {
        Keyboard.write(KEY_ESC);
      }
    }
  }

  last_PB_State = reading;
}

void joystick() {
  y_value = analogRead(JOY_X);
  x_value = analogRead(JOY_Y);
  // Serial.println("X Value: " + String(x_value) + " | Y Value: " + String(y_value));

  // Mouse or WASD - Choose ONE
  mouse(x_value, y_value);
  //wasd(x_value, y_value);
}

int top_trigger = 3800, bottom_trigger = 300; // Joystick trigger boundaries

void mouse(int x, int y) {
  bool btn = digitalRead(PB) == HIGH;

  int dx = 0, dy = 0;

  if (x < bottom_trigger) dx = -1; // move left
  if (x > top_trigger) dx = 1; // move right
  if (y > top_trigger) dy = -1; //move up
  if (y < bottom_trigger) dy = 1; // move down

  if (dx != 0 || dy != 0) {
    Mouse.move(dx, dy, 0);  // move mouse
  }

  int reading = digitalRead(JOY_SW);

  if (reading != last_JOY_SW_State) {
    lastJOYDebounceTime = millis();  // reset the timer
  }

  if ((millis() - lastJOYDebounceTime) > debounceDelay) {
    if (reading != JOY_SW_State) {
      JOY_SW_State = reading;

      if (JOY_SW_State == HIGH) {
        Mouse.click(MOUSE_LEFT);
      }
    }
  }

  last_JOY_SW_State = reading;
}

bool wPressed = false;
bool aPressed = false;
bool sPressed = false;
bool dPressed = false;
bool spacePressed = false;

void wasd(int x, int y) {
  bool btn = digitalRead(PB) == HIGH;

  // --- Handle W (UP) ---
  if (y < top_trigger) {
    if (!wPressed) { Keyboard.press('w'); wPressed = true; }
  } else if (wPressed) {
    Keyboard.release('w'); wPressed = false;
  }

  // --- Handle S (DOWN) ---
  if (y > bottom_trigger) {
    if (!sPressed) { Keyboard.press('s'); sPressed = true; }
  } else if (sPressed) {
    Keyboard.release('s'); sPressed = false;
  }

  // --- Handle A (LEFT) ---
  if (x < bottom_trigger) {
    if (!aPressed) { Keyboard.press('a'); aPressed = true; }
  } else if (aPressed) {
    Keyboard.release('a'); aPressed = false;
  }

  // --- Handle D (RIGHT) ---
  if (x > top_trigger) {
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