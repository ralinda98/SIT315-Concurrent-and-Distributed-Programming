
// Declaring pins used for I/O components
const int MOTION = 2;
const int TILT = 3;
const int G_LED_PIN = 6;
const int R_LED_PIN = 7;

// Variables for setting states
volatile int motionDetected = 0;
volatile int tiltDetected = 0;
int redState = LOW;
int greenState = LOW;

//Setting up pin modes and interrupts
void setup()
{
  // Setting motion sensor pin as input with
  // pullup resistor enabled.
  DDRD &= ~_BV(MOTION);
  PORTD |= _BV(MOTION);
  
  // Setting tilt sensor pin as input with
  // pullup resistor enabled.
  DDRD &= ~_BV(TILT);
  PORTD |= _BV(TILT);
  
  // Setting LED pins as output.
  DDRD |= _BV(G_LED_PIN);
  DDRD |= _BV(R_LED_PIN);
  
  //Setting interrupt detection
  attachInterrupt(digitalPinToInterrupt(MOTION), motion_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(TILT), tilt_ISR, CHANGE);
  
  //Setting the baud rate
  Serial.begin(9600);
}

void loop()
{
}

void motion_ISR()
{
  motionDetected = digitalRead(MOTION);
  redState = !redState;
  
  // Flip bit to turn on LED when interrupted
  PORTD ^= _BV(R_LED_PIN);
  
  //Printing data to serial monitor
  Serial.print("Motion: ");
  Serial.print(motionDetected);
  Serial.print(" Tilt: ");
  Serial.print(tiltDetected);
  Serial.print(" Red LED State: ");
  Serial.print(redState);
  Serial.print(" Green LED State: ");
  Serial.println(greenState);
}

void tilt_ISR()
{
  tiltDetected = digitalRead(TILT);
  greenState = !greenState;
  
  // Flip bit to turn on LED when interrupted
  PORTD ^= _BV(G_LED_PIN);
  
  //Printing data to serial monitor
  Serial.print("Motion: ");
  Serial.print(motionDetected);
  Serial.print(" Tilt: ");
  Serial.print(tiltDetected);
  Serial.print(" Red LED State: ");
  Serial.print(redState);
  Serial.print(" Green LED State: ");
  Serial.println(greenState);
}
