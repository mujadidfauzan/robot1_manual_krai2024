#include <Ps3Controller.h>
#define enPin 4

// CLASS SLAVE
class Slave {
public:
  Slave(char address, int data1) {
    Serial.println(address);
    Serial.println(data1);
    delay(15);
  }

  Slave(char address, int data1, int data2) {
    Serial.println(address);
    Serial.println(data1);
    Serial.println(data2);
    delay(15);
  }

  Slave(char address, int data1, int data2, int data3) {
    Serial.println(address);
    Serial.println(data1);
    Serial.println(data2);
    Serial.println(data3);
    delay(15);
  }
};


void onConnect() {
  Serial.println("Connected.");
}

// Analog
int spd = 150;
int lX,
  lY, rX, rY;
float arah;
void analog() {
  lX = map(Ps3.data.analog.stick.lx, -128, 127, -spd, spd);
  lY = map(Ps3.data.analog.stick.ly, -128, 127, spd, -spd);
  rX = map(Ps3.data.analog.stick.rx, -128, 127, spd, -spd);
  rY = map(Ps3.data.analog.stick.ry, -128, 127, spd, -spd);
  arah = atan2(rX, rY);
}

// Tombol
int circleBtn, squareBtn, r1Btn, l1Btn, r2Btn, gripOn;
void tombol() {
  // Grip
  if (Ps3.data.button.r1) {
    circleBtn = 11;
  } else if(Ps3.data.button.r2) {
    circleBtn = 10;
  } else if(Ps3.data.button.cross) {
    circleBtn = 9;
  }
  else{
    circleBtn = 0;
  }

  if(Ps3.data.button.square){
    squareBtn = 20;
  }else{
    squareBtn = 0;
  }

  // R1
  // if (Ps3.data.button.r1) {
  //   gripOn = 12;
  // }

  // // L1
  if (Ps3.data.button.l1) {
    spd -= 7;
    if (spd <= 0) {
      spd = 0;
    }
  }else if(Ps3.data.button.l2){
    spd += 7;
    if (spd >= 250) {
      spd = 250;
    }    
  }else if(Ps3.data.button.triangle){
    spd = 50;
  }

  // Serial.print("Speed : "); Serial.println(spd);
}

// Rumus Mecanum
int m1, m2, m3, m4;
void gerak(float radius, float sudut, int w) {
  //rumus baru, sudut dalam radian
  m1 = radius * sin(sudut + 0.785) - w * 0.7;  //depankanan
  m2 = radius * sin(sudut + 2.356) + w * 0.7;  //depankiri
  m3 = radius * sin(sudut + 2.356) - w * 0.7;  //belakangkanan
  m4 = radius * sin(sudut + 0.785) + w * 0.7;  //belakangkiri
  // Serial.print("M1 : "); Serial.println(m1);
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(250);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, HIGH);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("e8:6b:ea:c3:e4:3a");
}

// Slave Address
char addresSlave1 = 'A';
char addresSlave2 = 'B';
char addresSlave3 = 'C';
char addresSlave4 = 'D';
char addresSlave5 = 'E';
char addresSlave6 = 'F';



void loop() {
  analog();
  tombol();
  gerak(lY, arah, lX);


  Slave slave1(addresSlave1, m1);
  Slave slave2(addresSlave2, m2);
  Slave slave3(addresSlave3, m3);
  Slave slave4(addresSlave4, m4);
  Slave slave5(addresSlave5, circleBtn);
  Slave slave6(addresSlave6, squareBtn);


}
