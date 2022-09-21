#include <Servo.h>
Servo myservo;


int pos = 0;  // variable to read the value from the analog pin

#define echoPin 9 //Echo Pin
#define trigPin 10 //Trigger Pin
#define LEDPin 13 //Led default dari Arduino uno

int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 0; //kebutuhan akan minimal range
long duration, distance; //waktu untuk kalkulasi jarak

void setup() {
  Serial.begin (9600); //inisialiasasi komunikasi serial
  //deklarasi pin
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  //pinMode(6, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  /* Berikut siklus trigPin atau echo pin yang digunakan
    untuk menentukan jarak objek terdekat dengan memantulkan
    gelombang suara dari itu. */

  long duration, inches, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(pos);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  digitalWrite(LEDPin, LOW);

  if (cm < 20) {
    //for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    pos = 180;
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
    //}
  }

  //}
  else if (cm > 20) {
    //for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    pos = 0;
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15ms for the servo to reach the position
    //}
  }


}

long microsecondsToInches(long microseconds) {
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
}
