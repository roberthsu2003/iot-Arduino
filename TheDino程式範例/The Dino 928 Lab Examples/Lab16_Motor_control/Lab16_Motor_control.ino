const int M1_in1 = 12;
const int M1_in2 = 11;
const int M2_in3 = 10;
const int M2_in4 =  9;

void setup()
{
  Serial.begin(9600);
  pinMode(M1_in1, OUTPUT);
  pinMode(M1_in2, OUTPUT);
  pinMode(M2_in3, OUTPUT);
  pinMode(M2_in4, OUTPUT);
  Serial.println("輸入字元'+'代表前進, 字元'-'代表後退, 任意鍵代表停車");
}

void loop()
{

  if(Serial.available()) {
    char ch = Serial.read();
    if (ch=='+') {
      //　前進
      Serial.println("前進");
      digitalWrite(M1_in1, HIGH);  //右輪前進
      digitalWrite(M1_in2, LOW);
      digitalWrite(M2_in3, HIGH);  //左輪前進
      digitalWrite(M2_in4, LOW);

    } else if (ch=='-') { 
      //　倒車
      Serial.println("倒車");
      digitalWrite(M1_in1, LOW);  //右輪倒轉
      digitalWrite(M1_in2, HIGH);  
      digitalWrite(M2_in3, LOW);  //左輪倒轉
      digitalWrite(M2_in4, HIGH);

    } else {
      //　停止
      Serial.println("停止");
      digitalWrite(M1_in1, LOW);  //右輪停止
      digitalWrite(M1_in2, LOW);
      digitalWrite(M2_in3, LOW);  //左輪停止
      digitalWrite(M2_in4, LOW);
    }
  }
}

