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
  //Testing this part first - Darius 
  Keyboard.deviceName = "name" //you can set any name you want for your device here
  Keyboard.deviceManufacturer = "Manufactuer" //you can set any name
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
        // Keyboard.write(' ');
      }
    }
  }

  last_PB_State = reading;
}

void joystick() {
  y_value = analogRead(JOY_X);
  x_value = analogRead(JOY_Y);
  Serial.println("X Value: " + String(x_value) + " | Y Value: " + String(y_value));

  // Mouse or WASD - Choose ONE
  mouse(x_value, y_value);
  // wasd(x_value, y_value);
}

// Joystick boundaries
int top_trigger = 3800;
int bottom_trigger = 300; 
const int x_center = 1770; // tweak accordingly
const int y_center = 1700; // tweak accordingly
const int deadZone = 500;
const float scale = 0.001; // tweak accordingly

void mouse(int x, int y) {
  int deflectionX = x - x_center;
  int deflectionY = y_center - y;

  int dx = deflectionX * scale;
  int dy = deflectionY * scale;

  if (abs(deflectionX) < deadZone) dx = 0;
  if (abs(deflectionY) < deadZone) dy = 0;
  if (dx != 0 || dy != 0) {
    Mouse.move(dx, dy, 0);
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

void wasd(int x, int y) {
  bool btn = digitalRead(PB) == HIGH;

  // --- Handle UP ARROW ---
  if (y > top_trigger) {
    if (!wPressed) { 
      Keyboard.press(KEY_UP_ARROW); 
      wPressed = true; }
  } else if (wPressed) {
    Keyboard.release(KEY_UP_ARROW); 
    wPressed = false;
  }

  // --- Handle DOWN ARROW ---
  if (y < bottom_trigger) {
    if (!sPressed) { 
      Keyboard.press(KEY_DOWN_ARROW); 
      sPressed = true; 
    }
  } else if (sPressed) {
    Keyboard.release(KEY_DOWN_ARROW); 
    sPressed = false;
  }

  // --- Handle LEFT ARROW ---
  if (x < bottom_trigger) {
    if (!aPressed) { 
      Keyboard.press(KEY_LEFT_ARROW); 
      aPressed = true; 
    }
  } else if (aPressed) {
    Keyboard.release(KEY_LEFT_ARROW); 
    aPressed = false;
  }

  // --- Handle RIGHT ARROW ---
  if (x > top_trigger) {
    if (!dPressed) { 
      Keyboard.press(KEY_RIGHT_ARROW); 
      dPressed = true; 
    }
  } else if (dPressed) {
    Keyboard.release(KEY_RIGHT_ARROW); 
    dPressed = false;
  }

  // --- Handle Joystick button ---
  int reading = digitalRead(JOY_SW);

  if (reading != last_JOY_SW_State) {
    lastJOYDebounceTime = millis();  // reset the timer
  }

  if ((millis() - lastJOYDebounceTime) > debounceDelay) {
    if (reading != JOY_SW_State) {
      JOY_SW_State = reading;

      if (JOY_SW_State == HIGH) {
        Keyboard.write('c');
        delay(10);
      }
    }
  }
  last_JOY_SW_State = reading;

  delay(20); // debounce/polling delay
}
