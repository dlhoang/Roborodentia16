#include <Servo.h>
#include <AFMotor.h>

AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);

// 2 for distance, 3 for line reading?
// 0, 1, 2 for line reading
// 3, 4 for distance
int sensors[5] = {27, 26, 23, 13, 15};
int onBoardPin = 13;
double irVals[5];
long timeCnt;

// probably will need to declare/initialize servos

// initialize direction
int dir = FORWARD;
int left = 0;
int right = 1;
int threshold = 500;

unsigned long readIR(int sensor) {
  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, HIGH);
  pinMode(sensor, INPUT);
  unsigned long timer = micros();
  while (digitalRead(sensor) == HIGH) {
    if ((micros() - timer) > threshold)
      break;
  }
  return micros() - timer;
}

void readSensors() {
  for (int i = 0; i < 5; i++) {
    // line sensors
    if (i < 4)
      irVals[i] = readIR(sensors[i]);
    // distance sensors
    else
      irVals[i] = (4800/(analogRead(sensors[i]) - 20))*0.2;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(onBoardPin, OUTPUT);
  
  leftMotor.setSpeed();
  rightMotor.setSpeed();
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
  
  // need to delay or using switch to trigger robot?
}

void loop() {
   // write function to read sensors
   readSensors();
   
   
}
