#include <Servo.h>

#define R_PWM 5
#define L_PWM 6
#define LS_BOTTOM 9
#define LS_TOP 10

Servo L_gripper;
Servo R_gripper;

int LS_TOP_VALUE;
int LS_BOTTOM_VALUE;
int crc;

bool isUp = true;



int speed = 80;
int m, s;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(LS_BOTTOM, INPUT_PULLUP);
  pinMode(LS_TOP, INPUT_PULLUP);
  L_gripper.attach(A0);
  R_gripper.attach(A1);

  L_gripper.write(0);
  R_gripper.write(0);




}


void loop() {
  if (Serial.available() > 0) {
    if (Serial.read() == 'E') {
      m = Serial.parseInt();
      s = Serial.parseInt();
      // Serial.print("M : ");
      Serial.print(m);
      Serial.print(" ");
      // Serial.print("S : ");
      Serial.println(s);

      // // Motor
      if (m > 0) {
        analogWrite(L_PWM, m);
        analogWrite(R_PWM, 0);
      } else {
        analogWrite(L_PWM, 0);
        analogWrite(R_PWM, -m);
      }
    }
  }
}



