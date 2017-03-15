#include "Firebase.h"


Firebase::Firebase(const char* host){
  firebaseHost = host;
}

void Firebase::connectedToWifi(const char* ssid,const char* password){   
    
    if (WiFi.status() != WL_CONNECTED){
      this -> ssid = ssid;
      this -> password  = password;
      WiFi.begin(ssid,password);
      while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
      }
      Serial.println("WiFi connected");
      Serial.println("IP address:");
      Serial.println(WiFi.localIP());  
    }  
 }

 void Firebase::connectedToFirebase(){
    if(WiFi.status() == WL_CONNECTED){      
      if(!client.connect(firebaseHost,httpsPort)){
        Serial.println("connection failed");
        return;
      }
      Serial.print("connecting to ");
      Serial.println(firebaseHost);
          
    }else{
      return;
    }
 }

 JsonObject* Firebase::getJSONData(String url){
    connectedToFirebase();
    
    if(WiFi.status() == WL_CONNECTED && client.connected()){
      Serial.print("requesting URL:");
      String urlRequest = "GET " + url + " HTTP/1.1\r\n" +
                          "Host: " + firebaseHost + "\r\n" +                    
                           "Connection: close\r\n\r\n";
      Serial.println(urlRequest);
      client.print(urlRequest);
      
      unsigned long timeout = millis();
      while(client.available() == 0){
        if(millis() - timeout > 5000){
          Serial.println(">>>>Client Timeout!");
          client.stop();
          return nullptr;
        }
      }

      Serial.println("----------------data-------------");
      String section = "header";
      
      while(client.available()){
        String line = client.readStringUntil('\r');
        if(section == "header"){
          Serial.print(".");
          //Serial.print(line);
          if(line=="\n"){
            section = "json";
          }
          continue;                  
        }
       Serial.print("line:");
       Serial.println(line);
       String result = line.substring(1);//前面有一個換行字元
       Serial.print("result:");
       Serial.println(result);
       int size = result.length() + 1;//c字串內最後要加一個"/0"
       char json[size];
       result.toCharArray(json,size);
       StaticJsonBuffer<200> jsonBuffer;
       JsonObject& json_parsed = jsonBuffer.parseObject(json);
       if(!json_parsed.success()){
        Serial.println();
        Serial.println("parseObject() failed");
        return nullptr;
       }else{
        Serial.println("closing connection");
        //const char* d2State = json_parsed["D2"];        
        return &json_parsed;        
       }
        
      }
      Serial.println("closing connection");
     
    }else{
      return nullptr;
    }
 }

