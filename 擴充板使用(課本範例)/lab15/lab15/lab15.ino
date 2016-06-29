#include<OneWire.h>
#include<DallasTemperature.h>
#define DS18B20_pin 7

OneWire ds(DS18B20_pin);
DallasTemperature DS18B20(&ds);

void setup() {
  Serial.begin(115200);
  DS18B20.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  DS18B20.requestTemperatures();
  float val = DS18B20.getTempCByIndex(0);
  Serial.println(val,2);
  delay(1000);
}
