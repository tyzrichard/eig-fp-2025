
#include <BleCombo.h>

const int PB = 14;
const int JOY_X = 4, JOY_Y = 0, JOY_SW = 34;


const int x_left_trigger = 1750,
          x_right_trigger = 2100,
          y_top_trigger = 3100,
          y_bottom_trigger = 3500;  // Joystick trigger boundaries
int JOY_SW_State = LOW;
int last_JOY_SW_State = LOW;
unsigned long lastJOYDebounceTime = 0;
int PB_State = LOW;
int last_PB_State = LOW;
unsigned long lastPBDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50 ms debounce delay

String deviceName = "Klickr 9000 Pro";
String manufacturer = "richard";

void setup() {
  pinMode(PB, INPUT_PULLDOWN);
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SW, INPUT_PULLDOWN);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);


  initDevice(deviceName, manufacturer);
  Serial.begin(921600);
}

void loop() {
  if (Keyboard.isConnected()) {
    pushbutton();
    joystick();
  } else {
    Serial.println("Disconnected");
    delay(1000);
  initDevice(deviceName, manufacturer);
  }
}

void pushbutton() {
  int reading = digitalRead(PB);

  if (reading != last_PB_State) {
    lastJOYDebounceTime = millis();  // reset the timer
  }

  if ((millis() - lastPBDebounceTime) > debounceDelay) {
    if (reading != PB_State) {
      PB_State = reading;

      if (PB_State == HIGH) {
        Keyboard.print("Hello world!");  // Assignable macro
      }
    }
  }

  last_PB_State = reading;
}

void joystick() {
  joystickRead();
  // Mouse or WASD - Choose ONE
  mouse();
  // wasd();
}

int x_value, y_value;

void joystickRead() {
  x_value = analogRead(JOY_X);
  y_value = analogRead(JOY_Y);
  Serial.println("X Value: " + String(x_value) + " | Y Value: " + String(y_value));
}


void mouse() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
  bool btn = digitalRead(PB) == HIGH;

  int dx = 0, dy = 0;

  if (x < x_left_trigger) dx = -1;   // move left
  if (x > x_right_trigger) dx = 1;   // move right
  if (y < y_top_trigger) dy = -1;    //move up
  if (y > y_bottom_trigger) dy = 1;  // move down

  if (dx != 0 || dy != 0) {
    Mouse.move(dx, dy, 0);  // move mouse
    // delay(20);
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


void wasd() {

  bool wPressed = false;
  bool aPressed = false;
  bool sPressed = false;
  bool dPressed = false;
  bool spacePressed = false;
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
  bool btn = digitalRead(PB) == HIGH;

  // --- Handle W (UP) ---
  if (y < y_top_trigger) {
    if (!wPressed) {
      Keyboard.press('w');
      wPressed = true;
    }
  } else if (wPressed) {
    Keyboard.release('w');
    wPressed = false;
  }

  // --- Handle S (DOWN) ---
  if (y > y_bottom_trigger) {
    if (!sPressed) {
      Keyboard.press('s');
      sPressed = true;
    }
  } else if (sPressed) {
    Keyboard.release('s');
    sPressed = false;
  }

  // --- Handle A (LEFT) ---
  if (x < x_left_trigger) {
    if (!aPressed) {
      Keyboard.press('a');
      aPressed = true;
    }
  } else if (aPressed) {
    Keyboard.release('a');
    aPressed = false;
  }

  // --- Handle D (RIGHT) ---
  if (x > x_right_trigger) {
    if (!dPressed) {
      Keyboard.press('d');
      dPressed = true;
    }
  } else if (dPressed) {
    Keyboard.release('d');
    dPressed = false;
  }

  // --- Handle SPACEBAR button ---
  if (btn && !spacePressed) {
    Keyboard.press(' ');
    spacePressed = true;
  } else if (!btn && spacePressed) {
    Keyboard.release(' ');
    spacePressed = false;
  }
  delay(1000 / x);  // debounce/polling delay
}

void initDevice(String deviceName, String deviceManufacturer) {
  Keyboard.end();
  Mouse.end();
  Keyboard.setDeviceName(deviceName);
  Keyboard.setDeviceManufacturer(deviceManufacturer);
  Serial.println("Starting device...");
  Keyboard.begin();
  Mouse.begin();
  if (Keyboard.isConnected())
    Serial.println("Connected");
}
