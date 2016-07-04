const int M1_enable = 5;
const int M2_enable = 6;
const int M1_in1 = 12;
const int M1_in2 = 11;
const int M2_in3 = 10;
const int M2_in4 =  9;
int speed =0;

void setup()
{
  speed = 0;
  Serial.begin(9600);
  pinMode(M1_in1, OUTPUT);
  pinMode(M1_in2, OUTPUT);
  pinMode(M2_in3, OUTPUT);
  pinMode(M2_in4, OUTPUT);
  Serial.println("'+':speed up   '-':speed down   'F':forward,   'B'backward,   otherwise break");
}


void loop()
{
int _speed;

   if(Serial.available()) {
    char ch = Serial.read();
    if (ch=='+') {
      //speed = speed+1>10 ? 10 : speed+1;
      speed++;
      if (speed>10) speed=10;
      _speed = map(speed, 1, 10, 100, 255);
      
      Serial.print("speed , _speed => "); Serial.print(speed); Serial.print(" , "); Serial.println(_speed);
      analogWrite(M1_enable, _speed);  //右輪
      analogWrite(M2_enable, _speed);  //左輪
    } else if (ch=='-') { 
      speed--;
      if (speed<=0) {
        speed=0;
        _speed=0;

      } else {
        _speed = map(speed, 1, 10, 100, 255);
      }
      Serial.print("speed , _speed => "); 
      Serial.print(speed); 
      Serial.print(" , ");
      Serial.println(_speed);
      analogWrite(M1_enable, _speed);  //右輪
      analogWrite(M2_enable, _speed);  //左輪
    } else if (ch=='F') { 
      //　前進
      Serial.println("forward");
      digitalWrite(M1_in1, HIGH);  //右輪前進
      digitalWrite(M1_in2, LOW);
      digitalWrite(M2_in3, HIGH);  //左輪前進
      digitalWrite(M2_in4, LOW);
    } else if (ch=='B') { 

      //　倒車
      Serial.println("backward");

      digitalWrite(M1_in1, LOW);  //右輪倒轉
      digitalWrite(M1_in2, HIGH);  
      digitalWrite(M2_in3, LOW);  //左輪倒轉
      digitalWrite(M2_in4, HIGH);
    } else {
      //　停止
      Serial.println("stop");
      speed = 0;
      analogWrite(M1_enable, speed);  //右輪停止
      analogWrite(M2_enable, speed);  //左輪停止
    }
  }
}

