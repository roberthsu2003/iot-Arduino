const int Vpin=0;
void setup() {
  Serial.begin(9600); 
}
void loop() {
  int raw_data = analogRead(Vpin);  // 依據電壓傳回介於 0~1023 的值
  Serial.print("raw data : ");  Serial.print(raw_data);
  float map_data = raw_data / 1024.0 * 5.0;
  Serial.print("    voltage data : ");  Serial.println(map_data);
  delay(1000);
}
