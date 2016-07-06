#include<OneWire.h>
#include<DallasTemperature.h>
#define DS18B20_pin 7

//手機使用變數begin
  unsigned char mobileData[10];
  int index = 0;
  char mobileMode = -1; // 0 is iphone,1 is android
//手機使用變數end


OneWire ds(DS18B20_pin);
DallasTemperature DS18B20(&ds);

unsigned long firstTime = millis();

void setup() {
  Serial.begin(115200);
  DS18B20.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  mobileControl();
  DS18B20.requestTemperatures();
  float val = DS18B20.getTempCByIndex(0);
  
  if(mobileMode == 0){
    //send to iphone
    unsigned long currentTime = millis();
    if((currentTime-firstTime)>1000){
      Serial.print(val);
      firstTime = millis();
    }
    
    
    
  }else if (mobileMode == 1){
    Serial.print(val);
    delay(1000);
    
   
  }
  
  
 
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
              iphoneAction(mobileData,index);              
            }else if(mobileMode == 1){
              androidAction(mobileData,index);             
            }
             memset(mobileData,255,10);
            //set default          
            index = 0; 
             
        }else{
            mobileData[index++] = incomingByte;
           
        }
        
    }
}

void iphoneAction(unsigned char data[],int index){
  
       
       //get feature
       unsigned char feature = data[1];
       
       if(feature == 0x02){
          unsigned char value = data[2];         
          if(value == 0x02){
            
            mobileMode = -1;
          }
       }
}

void androidAction(unsigned char data[],int index){
  
       
       //get feature
       unsigned char feature = data[1];
       if(feature == 0x02){
          unsigned char value = data[2];
          if(value == 0x02){
            mobileMode = -1;
          }
       }
}




