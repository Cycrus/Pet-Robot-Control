// 5 Volt VCC

#include <Adafruit_NeoPixel.h>

#define LEDPIN 3
#define NUMPIXELS 12

int loop_num = 0;
Adafruit_NeoPixel ring(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  ring.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Fill LED Ring: ");
  ring.clear();

  uint32_t c = ring.Color(0, 0, 0);

  if(loop_num % 4 == 0)
  {
    c = ring.Color(10, 0, 10);
    Serial.println("Violet");
  }
  else if(loop_num % 3 == 0)
  {
    c = ring.Color(20, 0, 0);
    Serial.println("Red");
  }
  else if(loop_num % 2 == 0)
  {
    c = ring.Color(0, 20, 0);
    Serial.println("Green");
  }
  else
  {
    c = ring.Color(0, 0, 20);
    Serial.println("Blue");
  }

  for(int i = 0; i < NUMPIXELS; i++)
  {
    ring.setPixelColor(i, c);
    ring.show();
    delay(100);
  }

  loop_num++;
}
