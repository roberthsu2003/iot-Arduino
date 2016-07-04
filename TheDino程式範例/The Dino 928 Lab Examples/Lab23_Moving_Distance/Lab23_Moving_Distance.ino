const int M1_encoder = 2;  //　代表 pin2
const float DistancePerPulse = 1.02101761242 ;// 碼盤旋轉一格行走的距離
volatile int M1_pos = 0;
int pos, oldpos;
float  TravelDistance ; // 計算行走距離

void setup() {
  // put your setup code here, to run once:
  pinMode(M1_encoder, INPUT);
  attachInterrupt(0, EncoderEvent, FALLING);  //　指定 pin2 對應中斷
  Serial.begin(9600);
}

void loop() {
  //暫時停止中斷
  uint8_t oldSREG = SREG;
  cli();
  pos = M1_pos;  //　取得位置計數值
  SREG = oldSREG;

  //　若位置有變化，則顯示
  if (pos != oldpos)
  {
    Serial.println(pos);
    oldpos = pos;
    Serial.print(“ -- Distance : “);
    Serial.println(TravelDistance,3) ; // 顯示行走距離至小數點第三位
  }
  delay(1000);
}

void EncoderEvent()
{
  M1_pos++;
TravelDistance  +=  DistancePerPulse ; // increase one pulse range 1/20 wheel
}
