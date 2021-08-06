
// Declaring pins used for I/O components
const int SENSOR = 2;
const int LED_PIN = 13;

// Declaring variables for I/O states
int motionPrevState = LOW;
int ledState = LOW;

void setup()
{
  //Setting modes for pins used for I/O components
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR, INPUT);
  // Setting the baud rate
  Serial.begin(9600);
}

void loop()
{
  //Variable to get motion data
  int motionDetected = digitalRead(SENSOR);
  
  //Printing data to serial monitor
  Serial.print("Motion: ");
  Serial.print(motionDetected);
  Serial.print(" LED State: ");
  Serial.println(ledState);
  
  // Check if motion is detected
  // If so, turn on LED. Else no outcome
  if(motionDetected != motionPrevState)
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  
  //Saves last motion state
  motionPrevState = motionDetected;
    
  //Pause for 500ms before re-entering the loop
  delay(500);
}