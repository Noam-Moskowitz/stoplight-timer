int redPin = 13;
int greenPin = 14;
int yellowPin = 12;
int buttonPin = 27;
int baudRate = 115200;
bool isButtonPressed = false;
int newTimer;
int previousTime = millis();
int interval = 500;
boolean redLit = false;
boolean yellowLit = false;
boolean greenLit = false;

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
  if (redLit)
    return;
  turnOn(redPin);
  redLit = true;
}

void lightGreen()
{
  if (greenLit)
    return;
  turnOn(greenPin);
  greenLit = true;
}

void lightYellow()
{
  if (yellowLit)
    return;
  turnOn(yellowPin);
  yellowLit = true;
}

void hideRed()
{
  if (!redLit)
    return;
  turnOff(redPin);
  redLit = false;
}

void hideGreen()
{
  if (!greenLit)
    return;
  turnOff(greenPin);
  greenLit = false;
}

void hideYellow()
{
  if (!yellowLit)
    return;
  turnOff(yellowPin);
  yellowLit = false;
}

int getInput()
{
  int timer;

  Serial.println("\n Choose timer amount (seconds): ");

  while (Serial.available() == 0)
  {
    // Do nothing, just wait
  }

  String input = Serial.readStringUntil('\n');
  input.trim(); // R

  timer = input.toInt();
  Serial.println(String('\n You entered: ' + timer));

  return timer;
}

boolean acceptPress()
{
  return millis() - interval > previousTime;
}

int splitTimer(int timerValue)
{
  int splitValue = timerValue / 3;
  return splitValue;
}

int calculateChunk(int splitValue, int chunk)
{
  return splitValue * chunk;
}
int firstChunk = 0;
int secondChunk = 0;
int thirdChunk = 0;

int buttonState;
int timesPressed = 0;
int elapsedTime = 0;

void loop()
{

  int input;
  int splitInput;

  isButtonPressed = digitalRead(buttonPin);

  if (isButtonPressed)
  {
    if (acceptPress())
    {
      input = getInput();
      splitInput = splitTimer(input);
      firstChunk = calculateChunk(splitInput, 1);
      secondChunk = calculateChunk(splitInput, 2);
      thirdChunk = calculateChunk(splitInput, 3);
      isButtonPressed = false;
      elapsedTime = 0;
    }
  }
  elapsedTime++;

  Serial.print("\n Input: ");
  Serial.print(input);
  Serial.print("\n Split input: ");
  Serial.print(splitInput);
  Serial.print("\n First Chunk: ");
  Serial.print(firstChunk);
  Serial.print("\n Second Chunk: ");
  Serial.print(secondChunk);
  Serial.print("\n Third Chunk: ");
  Serial.print(thirdChunk);
  Serial.print("\n Elapsed time: ");
  Serial.print(elapsedTime);
  Serial.printf(
      "\n Green Status: %s Yellow Status: %s Red Status: %s",
      greenLit ? " ON " : " OFF ",
      yellowLit ? " ON " : " OFF ",
      redLit ? " ON " : " OFF ");

  if (elapsedTime <= firstChunk)
  {
    lightRed();
    lightGreen();
    lightYellow();
  }
  else if (elapsedTime <= secondChunk)
  {
    hideGreen();
  }
  else if (elapsedTime <= thirdChunk)
  {
    hideYellow();
  }
  else
  {
    // blink
    if (!greenLit)
    {
      lightRed();
      lightGreen();
      lightYellow();
    }
    else
    {
      hideRed();
      hideGreen();
      hideYellow();
    }
  }

  delay(1000);
}
