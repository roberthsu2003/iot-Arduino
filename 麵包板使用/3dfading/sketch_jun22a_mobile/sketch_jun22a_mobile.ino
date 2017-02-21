//手機使用變數begin
  unsigned char mobileData[10];
  int index = 0;
  char mobileMode = -1; // 0 is iphone,1 is android

//手機使用變數end

#define led 3
#define potentiometer A3

void setup() {
  Serial.begin(115200);
  pinMode(potentiometer,INPUT);
  pinMode(led,OUTPUT);  
}

void loop() {
  mobileControl(); 
  breadbordAction();
  
}

void mobileControl(){
  if(Serial.available())
    {
        
        unsigned char incomingByte = Serial.read();
        // set iphone mode or android mode  

        if(incomingByte == 99){
          mobileMode = 0;
        }else if(incomingByte == 98){          
          mobileMode = 1;
        }
        
        

        if(incomingByte == 100){           
            if (mobileMode == 0){          
              mobileAction(mobileData,index);              
            }else if(mobileMode == 1){
              mobileAction(mobileData,index);             
            }
             memset(mobileData,255,10);
            //set default          
            index = 0; 
             
        }else{
            mobileData[index++] = incomingByte;
           
        }
        
    }
}

//mobilState connected,disconnected
bool mobileState = false;

void mobileAction(unsigned char data[],int index){
  /*
    for(int i=0;i<index;i++){
        Serial.write(data[i]);
         delay(100);
       }
       */
       
       //get feature
       unsigned char feature = data[1];
       
       //0x02 mobileConnected, 0x03 mobileDisConnected
       if(feature == 0x02){
          mobileState = true;
       }else if (feature == 0x03){
          mobileState = false;
       }
}



void breadbordAction(){
  
  int inputValue = analogRead(potentiometer);
  //unsigned char outputValue = (float)inputValue / 1023 * 255;
  int outputValue = (float)inputValue / 1023 * 255;  
  analogWrite(led,outputValue);
  delay(100);
  
  if (mobileMode == 0){
    if (mobileState) {
        Serial.write(outputValue);
    }
  }else if(mobileMode == 1){
    if (mobileState) {
        char s[64];
        sprintf(s,"%d",outputValue);
        Serial.write(s);
        
    }
  }
}


