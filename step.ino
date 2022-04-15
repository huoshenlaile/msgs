
#include <Stepper.h>
#include aiducam


const int stepsPerRevolution = 200;  

Stepper st(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;         // number of steps the motor has taken
int steps;
String command;

void idle() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void takephoto() {
//take a photo


}




//SETUP
void setup() {
  Serial.begin(9600);
  st.setSpeed(15);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}



//LOOP

void loop() {
  while(Serial.available()){
    delay(5);  
    char c = Serial.read();
    command += c;
  }  
  
  if (command.length()>0) {
    Serial.println();
    Serial.println(command);
    if(command=="stop") steps = 0; //stop
    if(command=="set 1") steps = stepsPerRevolution/200; //1.8 deg turns
    if(command=="set 2") steps = stepsPerRevolution/40; //9 deg turns    
    if(command=="set 3") steps = stepsPerRevolution/20; //18 deg turns
    if(command=="set 2") steps = stepsPerRevolution/10; //36 deg turns
    if(command=="180") {
      stepCount+=180;
      st.step(100);
    }
    
    if(command=="360") {
      stepCount+=360;
      st.step(200);
    }
    
    if(command=="info") {
      Serial.print("Setting: ");
      Serial.print(steps);
      Serial.print(", Angle: ");
      Serial.println((stepCount % 200)*1.8f);
    }
    command = "";
   
  }

  
  st.step(steps);
  stepCount += steps;
  delay(500);  
  idle();
}
