// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 6
#define GREENPIN 5
#define BLUEPIN 3
//#define BUTTONPIN 2

#define FADESPEED 5     // make this higher to slow down

const int buttonInterrupt = 0;

volatile int mode = 0;
volatile int buttonState = LOW;
volatile long lastDebounceTime = 0;   // the last time the interrupt was triggered
long debounceDelay = 200;    // the debounce time; decrease if quick button presses are ignored
 
void setup() {
  Serial.begin(57600);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  //pinMode(BUTTONPIN, INPUT);
  attachInterrupt(buttonInterrupt, modeButton, FALLING);

}
 

// main loop 
void loop() {
  
  if (mode == 0) {
    //Serial.print("mode: ");
    //Serial.println(mode);
    brightWhiteLight();
  }
  
  else if (mode == 1) {
    //Serial.print("mode: ");
    //Serial.println(mode);
    sunLight();
  }
  
  else {
    //Serial.print("mode: ");
    //Serial.println(mode);
    colorFade();
  }  
  Serial.print("mode: ");
  Serial.println(mode);
}

//
void modeButton() {
 long currentTime = millis();
  
 if ((currentTime - lastDebounceTime) > debounceDelay)
 {
   lastDebounceTime = currentTime;
  
    // there are 2 modes
    if (mode < 2) {
      mode++;
    }
    else
    {
      mode = 0;
    }
  
    //Serial.print("mode: ");
    //Serial.println(mode);   
 }  
}

void brightWhiteLight()  {
// super bright white
  //Serial.print("mode: ");
  //Serial.println(mode);
  analogWrite(REDPIN, 255);
  analogWrite(GREENPIN, 255);
  analogWrite(BLUEPIN, 255);
}

void sunLight()  {
// dim white
  //Serial.print("mode: ");
  //Serial.println(mode);
  analogWrite(REDPIN, 192);
  analogWrite(GREENPIN, 191);
  analogWrite(BLUEPIN, 173);
}

void dimWhiteLight()  {
// dim white
  //Serial.print("mode: ");
  //Serial.println(mode);
  analogWrite(REDPIN, 127);
  analogWrite(GREENPIN, 127);
  analogWrite(BLUEPIN, 127);
}

void colorFade() {
// fade between colors
  int r, g, b;

  //Serial.print("mode: ");
  //Serial.println(mode);

  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  }  
}
