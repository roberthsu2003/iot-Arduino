
unsigned char iphoneData[10];
int index = 0;
char mobileMode = -1; // 0 is iphone,1 is android

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
        }

        if(incomingByte == 100){ 
            if (mobileMode == 0){          
              iphoneControl(iphoneData,index);
               memset(iphoneData,255,10);
            }
            //set default          
            index = 0;    
        }else{
            iphoneData[index++] = incomingByte;
        }
        
    }
}

void iphoneControl(unsigned char data[],int index){
  
    for(int i=0;i<index;i++){
        Serial.write(data[i]);
         delay(100);
       }
}


