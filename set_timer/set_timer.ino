int redPin = 12;
int greenPin = 13;
int yellowPin = 14;
int buttonPin = 27;
int baudRate = 115200;
bool isButtonPressed = false;
int buttonState;
int butttonPressed = 0;
int previousTime = millis();
int interval = 500;
int timer=30;

void setup()
{
  Serial.begin(baudRate);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void turnOn(int pin)
{
  digitalWrite(pin, HIGH);
}

void turnOff(int pin)
{
  digitalWrite(pin, LOW);
}

void lightRed()
{
  turnOn(redPin);
}

void lightGreen()
{
  turnOn(greenPin);
}

void lightYellow()
{
  turnOn(yellowPin);
}

void hideRed()
{
  turnOff(redPin);
}

void hideGreen()
{
  turnOff(greenPin);
}

void hideYellow()
{
  turnOff(yellowPin);
}

void loop()
{

  buttonState = digitalRead(buttonPin);

  Serial.println(String("Timer: ") + timer + String(" isButtonPressed ") + isButtonPressed);

  if (buttonState)
  {
    if (millis() - interval > previousTime)
    {

      isButtonPressed=!isButtonPressed;

     if (!isButtonPressed){ timer=30;}
  }


  
  }
  if(isButtonPressed){
    timer--;

      

      if (timer >= 20) {
        lightGreen();
      } else if (timer >= 11 && timer < 20) {
        lightYellow();
      } else if (timer >= 0 && timer <= 10) {
        lightRed();
      } else {
        hideGreen();
        hideYellow();
        hideRed();
      }

      delay(1000);
    }
}
