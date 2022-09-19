int RECEIVER_GPIO = 32;
int infrared_state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RECEIVER_GPIO, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  infrared_state = digitalRead(RECEIVER_GPIO);
  
  if(infrared_state == HIGH)
  {
    Serial.println("OFF");
  }
  else
  {
    Serial.println("ON");
  }
  delay(10);
}
