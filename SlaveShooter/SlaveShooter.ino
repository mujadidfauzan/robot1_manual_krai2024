#include <Servo.h>
#define R_PWM 6
#define L_PWM 5
#define enPin 4

Servo myservo;

bool isShoot = false;

void setup() {
  Serial.begin(115200);
  pinMode(enPin, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  digitalWrite(enPin, LOW);
}


int m = 0;
int s = 0;
// int degree = 0;
// int deg = constrain(degree, 0, 100);


void loop() {

  shoot();

  
  if (Serial.available() > 0) {
    if (Serial.read() == 'F') {
      m = Serial.parseInt();
      s = Serial.parseInt();
      // Serial.print("M : ");
      Serial.print(m);
      Serial.print(" ");
      // Serial.print("S : ");
      Serial.print(s);

      Serial.print(" isShoot : ");
      Serial.println(isShoot);

      if(m == 20){
        isShoot = !isShoot;
      }
    }
  }
}

void shoot(){
  if(isShoot){
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, 0);
  }else{
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, 0);
  }
}

