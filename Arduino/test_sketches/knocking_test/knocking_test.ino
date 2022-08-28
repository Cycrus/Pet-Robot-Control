int knock_pin = 3;

int knock_signal = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(knock_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  knock_signal = !digitalRead(knock_pin);
  Serial.println(knock_signal);
}
