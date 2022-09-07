#define TRIGGER_PIN 8
#define ECHO_PIN 9

int duration = 0;
int distance = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIGGER_PIN, LOW);
  delay(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) * 0.03432;
  
  if(distance >= 500 || distance <= 0)
  {
    Serial.println("No measurement possible");
  }
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  delay(500);
}
