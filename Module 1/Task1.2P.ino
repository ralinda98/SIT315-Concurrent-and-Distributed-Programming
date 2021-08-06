
// Declaring pins used for I/O components
const int SENSOR = 2;
const int LED_PIN = 13;

//Variables for setting states
volatile int motionDetected = 0;
int ledState = LOW;

//Setting up pin modes and interrupts
void setup()
{
  //Setting modes for pins used for I/O components
  pinMode(SENSOR, INPUT);
  pinMode(LED_PIN, OUTPUT);
  //Setting interrupt detection
  attachInterrupt(digitalPinToInterrupt(2), pin_ISR, CHANGE);
  //Setting the baud rate
  Serial.begin(9600);
}

void loop()
{
}

void pin_ISR()
{
  //Detects motion and changes LED state
  motionDetected = digitalRead(SENSOR);
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  
  //Printing data to serial monitor
  Serial.print("Motion: ");
  Serial.print(motionDetected);
  Serial.print(" LED State: ");
  Serial.println(ledState);
}