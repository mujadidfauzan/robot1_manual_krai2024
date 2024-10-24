#define R_PWM 6
#define L_PWM 5
#define pinCom 4

const int encoderPinA = 2;
const int encoderPinB = 3;

int velocity = 0;

volatile long pulseCount = 0;
unsigned long previousTime = 0;

void handleInterrupt() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(pinCom, OUTPUT);
  digitalWrite(pinCom, LOW);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), handleInterrupt, RISING);
}


int m = 0;
int s = 0;
float Err = 0, dErr = 0, LastErr = 0;
float Hasil = 0;
void loop() {
  Serial.println(velocity);
  if (Serial.available() > 0) {
    if (Serial.read() == 'B') {
      m = Serial.parseInt();
      Serial.print("M : ");
      Serial.println(m);

      // Motor
      if (m > 0) {
        rpwm(m);
      } else if (m < 0) {
        m *= -1;
        lpwm(m);
      } else {
        analogWrite(R_PWM, 0);
        analogWrite(L_PWM, 0);
      }
    }
  }
}

void rpwm(int target) {
  unsigned long currentTime = millis();
  float elapsedTime = currentTime - previousTime;
  double pulsePerTick;
  if (elapsedTime >= 79) {
    pulsePerTick = (double)pulseCount;
    pulseCount = 0;
    previousTime = currentTime;
  }

  Err = target - pulsePerTick;
  dErr = Err - LastErr;
  LastErr = Err;

  Hasil += (Err * 0.2 + dErr * 0.2);

  velocity = constrain((int)Hasil, 0, 255);

  analogWrite(R_PWM, velocity);
  analogWrite(L_PWM, 0);
  // Serial.print(Err);
  // Serial.print('\t');
  // Serial.print(target);
  // Serial.print('\t');
  // Serial.print(Hasil);
  // Serial.print('\t');
  // Serial.print(velocity);
  // Serial.print('\t');
  // Serial.println(pulsePerTick);
}

void lpwm(int target) {
  unsigned long currentTime = millis();
  float elapsedTime = currentTime - previousTime;
  double pulsePerTick;
  if (elapsedTime >= 79) {
    pulsePerTick = (double)pulseCount;
    pulseCount = 0;
    previousTime = currentTime;
  }

  Err = target - pulsePerTick;
  dErr = Err - LastErr;
  LastErr = Err;

  Hasil += (Err * 0.2 + dErr * 0.2);

  velocity = constrain((int)Hasil, 0, 255);

  analogWrite(L_PWM, velocity);
  analogWrite(R_PWM, 0);
  // Serial.print(Err);
  // Serial.print('\t');
  // Serial.print(target);
  // Serial.print('\t');
  // Serial.print(Hasil);
  // Serial.print('\t');
  // Serial.print(velocity);
  // Serial.print('\t');
  // Serial.println(pulsePerTick);
}
