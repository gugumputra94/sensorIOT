const int pushBtn = 3;
boolean hasilBaca;
const int led = 4;

void setup() {
  Serial.begin(9600);
  pinMode(pushBtn, INPUT);
  pinMode(led, OUTPUT);

}

void loop() {
  Serial.println(digitalRead=(pushBtn));
  if (hasilBaca == 1) {
    digitalWrite(led, HIGH);
    Serial.println ("LED menyala");
  }else {
    digitalWrite(led, LOW);
    Serial.println ("LED mati");
  }


}
