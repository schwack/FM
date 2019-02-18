// Nano-based control for tool changer project.

// Simple two-button interrupt based open/close 
// servo control with rgb LED indicator.

// 2018.02.18   Initial implementation by Schwackmaster
// 2019.02.08   Add A4988 stepper driver with pot speed control


//#include <Servo.h>

//Servo tool_changer_Servo;
const int servoPin = 9;
//common anode led
const int redPin = 6;
const int greenPin = 4;
const int bluePin = 5;
//servo interrupts
const int holdPin = 2;
const int releasePin = 3;

volatile bool open_pressed = false;
volatile bool close_pressed = false;

int pos = 128; 
int stp = 64;
int least = 0;
int most = 256;

//stepper
int potPin = A1;

//buttons
 int fwdPin = 7;
 int revPin = 10;

// A4988 driver
 int stepPin = 11;
 int dirPin = 12;

const int dly = 150;
 int spd = 0;
 int ledPin = 13;
 bool fwd = false;
 bool rev = true;
const int factor = 1024;  // pot range control
int minimum = 300;  // stall prevention 
 
void setup() {
  Serial.begin(9600);
  
//servo
   pinMode(releasePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(releasePin), unMountTool, FALLING);
  
   pinMode(holdPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(holdPin), mountTool, FALLING);
  
pinMode(servoPin, OUTPUT);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);

//tool_changer_Servo.attach(servoPin);
//tool_changer_Servo.write(pos);
digitalWrite(servoPin, pos * 4);
//stepper
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(fwdPin,INPUT_PULLUP);
  pinMode(revPin,INPUT_PULLUP);

};


void loop(){
  
  bool t =  (close_pressed) ? grabbing() : (open_pressed) ? openingUp() : false;

  if(t){
    delay(dly);
    };

      if(digitalRead(fwdPin) == LOW){
    digitalWrite(dirPin,fwd);
    step();
    }
  else if(digitalRead(revPin) == LOW){
    digitalWrite(dirPin,rev);
    step();
  }
  else digitalWrite(ledPin,LOW);
};

// interrupt routines take no arguments, return no value
// and should execute as quickly as possible.

void unMountTool() {
  digitalWrite(greenPin, HIGH);
 open_pressed = true;
};

void mountTool() {
  digitalWrite(redPin, HIGH);
 close_pressed = true;
};    


bool openingUp() {  
  digitalWrite(bluePin, HIGH);
 delay(dly); 
  open_pressed = false;
  if (pos < most) pos += stp;
//  tool_changer_Servo.attach(servoPin
rotate(pos);
  //tool_changer_Servo.detach();
  return true; 
};   
    

bool grabbing() {
  digitalWrite(bluePin, HIGH);
 delay(dly); 

  close_pressed = false;
  if (pos > least) pos -= stp;
 // tool_changer_Servo.attach(servoPin);
rotate(pos);
  return true; 
};   

void rotate(int angle){
   Serial.println(angle);
    Serial.println(pos);
    if(pos == most)angle -= 1;
digitalWrite(servoPin, angle*4);
 delay(dly); 
digitalWrite(servoPin, angle * 4);
 delay(dly); 
 digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(greenPin, LOW);
  //tool_changer_Servo.detach();
}


// stepper routines
void step() {
  digitalWrite(ledPin,HIGH);
  digitalWrite(stepPin,HIGH);  
    delayMicroseconds(80); 
  digitalWrite(stepPin,LOW);
    delayMicroseconds(getSpeed());
   return;   
}

int getSpeed(){
  return (minimum + (factor - analogRead(potPin)));
}

