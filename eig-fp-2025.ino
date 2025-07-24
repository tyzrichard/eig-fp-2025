#include <BleCombo.h>

#define PB 14
#define JOY_X 33
#define JOY_Y 4
#define JOY_SW 25 
int x_value, y_value;                  

// General debounce timing
unsigned long debounceDelay = 50;  

// Debouncing variables used for the joystick (JOYSW) and black pushbutton (PB)
int JOY_SW_State = LOW;
int last_JOY_SW_State = LOW;
unsigned long lastJOYDebounceTime = 0;
int PB_State = LOW;
int last_PB_State = LOW;
unsigned long lastPBDebounceTime = 0;


void setup() { // everything here is called when the esp32 boots up
  // setting GPIO pins as input for the switch and black pushbutton
  pinMode(PB, INPUT_PULLDOWN);
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_SW, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // to indicate that the esp32 has started up

  Serial.begin(921600); 
  
  Serial.println("Starting device...");
  
  // Set the name you want for your device here!
  Keyboard.deviceName = "name"; 
  Keyboard.deviceManufacturer = "Engineering Interest Group"; 
  
  Keyboard.begin(); // Begins Keyboard, which can be called for any keyboard-related functions
  Mouse.begin(); // Begins Mouse, which can be called for any mouse-related functions
}

void loop() {
  // Serial.print("Pushbutton status - ");
  // Serial.println(digitalRead(PB));

  // Calls the two functions from below
  pushbutton();
  joystick();               
}

void pushbutton() {
  int reading = digitalRead(PB); // reads whether the pushbutton is pressed (True/1) or not (False/0)

  if (reading != last_PB_State) {
    lastPBDebounceTime = millis();  // millis() gives the number of microseconds since program start, basically a measurement of current time
  }

  if ((millis() - lastPBDebounceTime) > debounceDelay) { // checks if button press is more than 50 milliseconds after last button press
    if (reading != PB_State) {
      PB_State = reading; 
      if (PB_State == HIGH) { // checks if button is pressed
        // use only ONE of the lines below, comment out the other!
        Keyboard.write(KEY_ESC); // the original code, press escape key
        // Keyboard.write(' '); // FP3 addon code, presses the spacebar instead
      }
    }
  }

  last_PB_State = reading; // updates last_PB_state with reading
}

void joystick() {
  // swaps x and y values due to the orientation of the joystick
  y_value = analogRead(JOY_X);
  x_value = analogRead(JOY_Y);
  Serial.println("X Value: " + String(x_value) + " | Y Value: " + String(y_value));

  mouse(x_value, y_value);
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

  // Debouncing code for Joystick Button
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
