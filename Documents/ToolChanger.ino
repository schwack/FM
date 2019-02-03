#include <U8glib.h>

// Nano-based control for tool changer project.

// 2018.02.18   Initial implementation by Schwackmaster

// Simple two-button interrupt based open/close 
// servo control with rgb LED indicator.

#include <Servo.h>

Servo tool_changer_Servo;
const int servoPin = 8;
const int redPin = 6;
const int greenPin = 4;
const int bluePin = 5;
const int holdPin = 2;  
const int releasePin = 3;
volatile bool open_pressed = false;
volatile bool close_pressed = false;
int x = 0;

 
void setup() {
	// set up the buttons to be interrupts 
   pinMode(releasePin, INPUT_PULLUP);    // start high
   // when the pin goes low (Falling) --> unMountTool()
  attachInterrupt(digitalPinToInterrupt(releasePin), unMountTool, FALLING);  
  
   pinMode(holdPin, INPUT_PULLUP);   
  attachInterrupt(digitalPinToInterrupt(holdPin), mountTool, FALLING);
  
pinMode(servoPin, OUTPUT);
// common cathode RGB LED
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
// init servo to center
tool_changer_Servo.attach(servoPin);
tool_changer_Servo.write(90);
};


void loop(){
  // the interrupts set the flags, the functions reset them
  // light will be on if t == true
  bool t =  (close_pressed) ? grabbing() : (open_pressed) ? openingUp() : false;

  if(t){
    delay(2000);
    };
};

// interrupt routines take no arguments, return no value
// and should execute as quickly as possible.
// so turn on a light, set a flag, & go.

void unMountTool() {
  digitalWrite(greenPin, HIGH);
 open_pressed = true;
};

void mountTool() {
  digitalWrite(redPin, HIGH);
 close_pressed = true;
};    


bool openingUp() {  
  digitalWrite(bluePin, HIGH); // change colors
  open_pressed = false;  // reset flag
 tool_changer_Servo.write(180); // move
 delay(2500);
   digitalWrite(bluePin, LOW); // kill lights
  digitalWrite(greenPin, LOW);
  return true; // go home
};   
    

bool grabbing() {
  digitalWrite(bluePin, HIGH);

  close_pressed = false;
 tool_changer_Servo.write(0);
 delay(2500); 
 digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
  return true; 
};   
    

