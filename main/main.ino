int  redPin=12;
int  greenPin=13;
int  yellowPin=14;
int buttonPin=27;
int baudRate=115200;
bool isButtonPressed=false;
int newTimer;

void setup(){
    Serial.begin(baudRate);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(buttonPin, INPUT);
}

void turnOn(int pin){
  digitalWrite(pin,HIGH);
}

void turnOff(int pin){
  digitalWrite(pin,LOW);
}

void lightRed(){
  turnOn(redPin);
}

void lightGreen(){
  turnOn(greenPin);
}

void lightYellow(){
  turnOn(yellowPin);
}

void hideRed(){
  turnOff(redPin);
}

void hideGreen(){
  turnOff(greenPin);
}

void hideYellow(){
  turnOff(yellowPin);
}

int getInput(){
  int timer;

 Serial.println("Choose timer amount (seconds): ");

  while (Serial.available() == 0) {
    // Do nothing, just wait
  }

  timer= Serial.parseInt();
  Serial.println(timer);

  return timer;
}

int splitTimer(int timerValue){
  int splitValue=timerValue/3;
  return splitValue;
}

int calculateChunk(int splitValue,int chunk){
  return  splitValue*chunk;
}
  int firstChunk=0;
  int secondChunk=0;
  int thirdChunk=0;

void loop(){
  int input;
  int splitInput;

  isButtonPressed=digitalRead(buttonPin);

  if(isButtonPressed){
      newTimer=millis();
      input=getInput()*1000;
      splitInput=splitTimer(input);
       firstChunk=calculateChunk(splitInput, 1);
       secondChunk=calculateChunk(splitInput, 2);
       thirdChunk=calculateChunk(splitInput, 3);
      isButtonPressed=false;
  }

unsigned long elapsedTime = millis() - newTimer;
  Serial.print(elapsedTime);

  if(elapsedTime>=thirdChunk){
    lightRed();
    lightGreen();
    lightYellow();

    delay(500);

    hideGreen();
    hideYellow();
    hideRed();
  } else if (elapsedTime>=secondChunk){
    hideGreen();
    hideYellow();
    lightRed();
  } else if(elapsedTime>=firstChunk){
    hideGreen();
    lightYellow();
  } else{
    hideYellow();
    hideRed();
    lightGreen();
  }

  
}


