//手機使用變數begin
  unsigned char mobileData[10];
  int index = 0;
  char mobileMode = -1; // 0 is iphone,1 is android
//手機使用變數end

void setup() {
    Serial.begin(115200);               //initial the Serial
    pinMode(13,OUTPUT);
}

void loop()
{
   mobileControl(); 
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

void mobileAction(unsigned char data[],int index){
  /*
    for(int i=0;i<index;i++){
        Serial.write(data[i]);
         delay(100);
       }
       */
       
       //get feature
       unsigned char feature = data[1];
       if(feature == 0x02){
          switchLight(data[2]);
       }
}



void switchLight(unsigned char action){
    if(action == 1){
        digitalWrite(13,HIGH);
        
    }else if(action == 0){
        digitalWrite(13,LOW);
        
    }

    Serial.write(action);
}


