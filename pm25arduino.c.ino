#include <SoftwareSerial.h>
uint16_t pmcf10 = 0;
uint16_t pmcf25 = 0;
uint16_t pmcf100 = 0;
uint16_t pmat10 = 0;
uint16_t pmat25 = 0;
uint16_t pmat100 = 0;
char buf[50];
int count = 0;
SoftwareSerial BT(9, 10);
SoftwareSerial sensor(2, 3);
char getter, last, high;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Loli is good!\n");
  BT.begin(9600);
  sensor.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:

  if (BT.available()) {
    getter = BT.read();
    if (getter != -1) Serial.print(getter);
  }
  if (sensor.available()) {
    last = getter;
    getter = sensor.read();
    if (last == 0x42 && getter == 0x4d) {
      count = 0;
    }
    count++;
    if (count == 4 || count == 6 || count == 8 || count == 10 || count == 12 || count == 14 || count == 16) {
      high = getter;
    }
    else if (count == 7) {
      pmcf25 = 256 * high + getter;
      Serial.print("CF=1, PM2.5= : ");
      Serial.print(pmcf25);
      Serial.print(" ug/m3");
      Serial.print("\t\t");
      BT.print(pmcf25);
      BT.print("\n");
    }
    else if (count == 9) {
      pmcf10 = 256 * high + getter;
      Serial.print("CF=1, PM10= : ");
      Serial.print(pmcf10);
      Serial.print(" ug/m3");
      Serial.print("\t\t");
    } 
    else if (count == 11) {} 
    else if (count == 13) {
      pmat25 = 256 * high + getter;
      Serial.print("atmosphere, PM2.5= : ");
      Serial.print(pmat25);
      Serial.println(" ug/m3");
    }
  }
}
