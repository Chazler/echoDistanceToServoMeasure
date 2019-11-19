//Sonar
#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 250

//Servo
#include <Servo.h>
Servo servo;

void setup() {
  servo.attach(5);
  Serial.begin(9600);
}

void loop() {
  moveServo(getEchoDistance());
  delay(50);
}

int calcAngle(int sonarDistance){
  if(sonarDistance <= 1000){
    int angle = (sonarDistance*0.01) * 180;
    return angle;
  }
  return 180;
}

int getEchoDistance(){
  long echoDistance = measure();
  Serial.print("Distance: ");
  Serial.print(echoDistance);
  Serial.println(" mm");
  return echoDistance;
}

long measure()
{
  long measureSum = 0;
  for (int i = 0; i < MEASURE_SAMPLES; i++)
  {
    delay(MEASURE_SAMPLE_DELAY);
    measureSum += singleMeasurement();
  }
  return measureSum / MEASURE_SAMPLES;
}

long singleMeasurement()
{
  long duration = 0;
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(11);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  return (long) (((float) duration / USONIC_DIV) * 10.0);
}

void moveServo(int echoDistance){
  int angle = calcAngle(echoDistance);
  if(angle <= 180){
    servo.write(angle);
  }
}
