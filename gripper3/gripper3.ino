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

bool isArmMove = false;
bool gripperOnTop = true;
bool isGrip = false;

void setup() {
  Serial.begin(115200);
  pinMode(enPin, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(LS_TOP, INPUT_PULLUP);
  pinMode(LS_BOTTOM, INPUT_PULLUP);

  L_gripper.attach(A0);
  R_gripper.attach(A1);

  R_gripper.write(0);
  L_gripper.write(0);



  digitalWrite(enPin, LOW);
}


// int degree = 0;
// int deg = constrain(degree, 0, 100);
void loop() {

  LS_TOP_VALUE = digitalRead(LS_TOP);
  LS_BOTTOM_VALUE = digitalRead(LS_BOTTOM);

  // gripSystem();

  if (Serial.available() > 0) {
    if (Serial.read() == 'E') {
      m = Serial.parseInt();
      s = Serial.parseInt();
      // Serial.print("M : ");
      if(m == 11){
        // isArmMove = !isArmMove;
        pressNaik();
      }else if(m == 10){
        pressTurun();
      }else if(m == 9){
        isGrip = !isGrip;
        if(isGrip){
          ungrip();
        }else{
          grip();
        }
      }else{
        diam();
      }

      Serial.print(" M : ");
      Serial.print(m);
      Serial.print(" ");
      Serial.print(" S : ");
      Serial.println(s);

      // Serial.print("is Arm Move : ");
      // Serial.print(isArmMove);
      // Serial.print(" onTop : ");
      // Serial.print(gripperOnTop);
      // Serial.print(" Gripper on top : ");
      // Serial.print(gripperOnTop);
      // Serial.print(" LS TOP : ");
      // Serial.print(LS_TOP_VALUE);
      // Serial.print(" LS BOTTOM : ");
      // Serial.print(LS_BOTTOM_VALUE);
      // Serial.print(" ");

    }
  }
}

void naik(){
  grip();
  analogWrite(R_PWM, 40);
  analogWrite(L_PWM, 0);
  // Serial.print("naik");
  if(LS_TOP_VALUE == 0){
    diam();
    gripperOnTop = true;
    isArmMove = false;
  }

}

void turun(){
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 40);
  // Serial.print("turun");
  if(LS_BOTTOM_VALUE == 0 ){
    diam();
    isArmMove = false;
    gripperOnTop = false;
    ungrip();
  }
}

void diam(){
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 0);
}


void gripSystem(){
  if(!isArmMove){
    diam();
  }else{
    if(gripperOnTop){
      turun();
    }else{
      naik();
    }
  }
}

void grip(){
  L_gripper.write(70);
  R_gripper.write(70);
  delay(400);
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

void pressNaik(){
  grip();
  analogWrite(R_PWM, 255);
  analogWrite(L_PWM, 0);
  // Serial.print("turun");
  if(LS_TOP_VALUE == 0 ){
    diam();
    isArmMove = false;
    gripperOnTop = true;
  }
}

void pressTurun(){
  analogWrite(R_PWM, 0);
  analogWrite(L_PWM, 40);
  // Serial.print("turun");
  if(LS_BOTTOM_VALUE == 0 ){
    diam();
    isArmMove = false;
    gripperOnTop = false;
    ungrip();
  }
}


