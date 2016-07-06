//手機使用變數begin
  unsigned char mobileData[10];
  int index = 0;
  char mobileMode = -1; // 0 is iphone,1 is android
//手機使用變數end

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
char buttonState = 0;         // variable for reading the pushbutton status
char currentButtonState = 0;

void setup() {
  Serial.begin(115200);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  
  
    if(currentButtonState != buttonState){
        currentButtonState = buttonState;
        digitalWrite(ledPin,currentButtonState);
        mobileAction(currentButtonState); //mobile
    }
   
}



void mobileAction(char index){
  
  
  Serial.write(index);
       
}



