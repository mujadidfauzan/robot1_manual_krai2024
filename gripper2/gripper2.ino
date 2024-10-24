#include <Servo.h>
#define R_PWM 5
#define L_PWM 6
#define enPin 4
#define LS_TOP 10
#define LS_BOTTOM 9
#define enPin 4



Servo L_gripper;
Servo R_gripper;

int LS_BOTTOM_VALUE, LS_TOP_VALUE;
int m = 0;
int s = 0;

bool isArmMove = true;
bool gripperOnTop = true;

void setup() {
  Serial.begin(115200);
  pinMode(enPin, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  digitalWrite(enPin, LOW);

  pinMode(LS_BOTTOM, INPUT_PULLUP);
  pinMode(LS_TOP, INPUT_PULLUP);
  L_gripper.attach(A0);
  R_gripper.attach(A1);

  L_gripper.write(0);
  R_gripper.write(10);


}



// int degree = 0;
// int deg = constrain(degree, 0, 100);
void loop() {

  LS_BOTTOM_VALUE = digitalRead(LS_BOTTOM);
  LS_TOP_VALUE = digitalRead(LS_TOP);


  if (Serial.available() > 0) {
    if (Serial.read() == 'E') {
      m = Serial.parseInt();
      s = Serial.parseInt();
      // Serial.print("M : ");
      Serial.print(m);
      Serial.print(" ");
      // Serial.print("S : ");
      Serial.println(s);

      if(m == 11){
        isArmMove = !isArmMove;
      }
   
    }
  }
  
  gripSystem();

  delay(150);

}



void naik(){
  grip();
  analogWrite(R_PWM, 55);
  analogWrite(L_PWM, 0);
  if(LS_TOP_VALUE == 0 ){
    isArmMove = !isArmMove;
  }
}

void turun(){
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 55);
  if(LS_BOTTOM_VALUE == 0 ){
    isArmMove = !isArmMove;
    ungrip();
  }else{
    grip();
  }
}

void diam(){
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 0);
}

void arm(){
  if(isArmMove){
    if(gripperOnTop){
      naik();
    }else{
      turun();
    }
  }else{
    diam();
  }
}

void gripSystem(){
  if(isArmMove){
    if(gripperOnTop){
      turun();
    }else{
      naik();
    }
  }else{
    diam();
  }
}

void grip(){
  L_gripper.write(90);
  R_gripper.write(110);
}

void ungrip(){
  L_gripper.write(0);
  R_gripper.write(0); 
}

void bacaLS(int TOP, int BOT, int m, int isArmMove){
  Serial.print(" IS ARM MOVE : ");
  Serial.print(isArmMove);
  Serial.print(" LS TOP : ");
  Serial.print(TOP);
  Serial.print(" LS BOT : ");
  Serial.print(BOT);
  Serial.print(" m : ");
  Serial.println(m);
}




