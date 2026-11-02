int redPin = 12;
int greenPin = 13;
int yellowPin = 14;
int buttonPin = 27;
int baudRate = 115200;
bool isButtonPressed = false;
int buttonState;
int timesPressed = 0;
int previousTime = millis();
int interval = 500;

void setup()
{
  Serial.begin(baudRate);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(buttonPin, INPUT);
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

  Serial.println(String("Button State: ") + buttonState + String(" ") + timesPressed);

  if (buttonState)
  {
    if (millis() - interval > previousTime)
    {
      if (timesPressed >= 3)
      {
        timesPressed = 0;
      }
      else
      {
        timesPressed++;
      }
      previousTime = millis();

      switch (timesPressed)
      {
      case 1:
        lightGreen();
        break;
      case 2:
        lightYellow();
        break;
      case 3:
        lightRed();
        break;
      default:
        hideGreen();
        hideYellow();
        hideRed();
      }
    }
  }
}
