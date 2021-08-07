
// Declaring pins used for I/O components
const int BUTTON = 1;
const int MOTION = 2;
const int TILT = 3;
const int W_LED_PIN = 4;
const int G_LED_PIN = 5;
const int R_LED_PIN = 6;
const int Y_LED_PIN = 7;

// Variables for setting states
volatile int buttonPressed = 0;
volatile int motionDetected = 0;
volatile int tiltDetected = 0;
int whiteState = LOW;
int greenState = LOW;
int redState = LOW;
int yellowState = LOW;

// Variables for the timer
const uint16_t t1_load = 0;
const uint16_t t1_comp = 46875;

// Setting up pin modes and interrupts
void setup()
{
  // Setting modes for pins used for I/O components
  pinMode(BUTTON, INPUT);
  pinMode(MOTION, INPUT_PULLUP);
  pinMode(TILT, INPUT_PULLUP);
  pinMode(W_LED_PIN, OUTPUT);
  pinMode(G_LED_PIN, OUTPUT);
  pinMode(R_LED_PIN, OUTPUT);
  pinMode(Y_LED_PIN, OUTPUT);
  
  // Enable pin change for group 2
  PCICR |= B00000100;
  // Trigger set to pin D1 from group 2
  PCMSK2 |= B00000010;
  
  // Set Timer 1 control register A to 0 by default
  TCCR1A = 0;
  // Set to prescalar of 1024 for 46875 cycles to reach 6 seconds
  TCCR1B |= _BV(CS12);
  TCCR1B &= ~_BV(CS11);
  TCCR1B |= _BV(CS10);
  // Load the timer with 0
  TCNT1 = t1_load;
  // Store the match value to the compare register
  OCR1A = t1_comp;
  // Set the bit to cause the interrupt
  TIMSK1 = _BV(OCIE1A);
  
  // Enable global interrupts
  sei();
  
  // Setting interrupt detection
  attachInterrupt(digitalPinToInterrupt(2), motion_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), tilt_ISR, CHANGE);
  
  // Setting the baud rate
  Serial.begin(9600);
}

void loop()
{
}

// Function for motion interrupt when called (red LED)
void motion_ISR()
{
  // Detects motion and changes red LED state
  motionDetected = digitalRead(MOTION);
  redState = !redState;
  digitalWrite(R_LED_PIN, redState);
  
  //Printing data to serial monitor
  Serial.print("Motion: ");
  Serial.print(motionDetected);
  Serial.print(" Red LED State: ");
  Serial.println(redState);
}


// Function for button push interrupt when called (green LED)
void tilt_ISR()
{  
  // Detects motion and changes red LED state
  tiltDetected = digitalRead(TILT);
  greenState = !greenState;
  digitalWrite(G_LED_PIN, greenState);
  
  //Printing data to serial monitor
  Serial.print("Tilt: ");
  Serial.print(tiltDetected);
  Serial.print(" Green LED State: ");
  Serial.println(greenState);
}

ISR(PCINT2_vect)
{
  buttonPressed = digitalRead(BUTTON);
  
  if(buttonPressed == HIGH)
  {
    digitalWrite(W_LED_PIN, LOW);
  }
  else
  {
    digitalWrite(W_LED_PIN, HIGH);
  }
}

ISR(TIMER1_COMPA_vect)
{
  yellowState = !yellowState;
  TCNT1 = t1_load;
  digitalWrite(Y_LED_PIN, yellowState);
  
  Serial.print("Timer LED ");
  Serial.println(yellowState);
}
