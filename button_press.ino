/* Button StateMachine Example
 *  by: Jay Wilhelm (jwilhelm@ohio.edu)
 *  Purpose: Demonstrates a button up/down state machine
 *  where actions can be triggered at the press/release states
 */

//button states
#define ButtonState_Up      1
#define ButtonState_Pressed 2 
#define ButtonState_Down    3
#define ButtonState_Released 4
//map button high/low to up/down
#define ButtonRead_Up 1
#define ButtonRead_Down 2

#define sensor1 8
#define sensor2 7
#define buzzer 2

void setup() {
  // initialize the LED pin as an output:
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(buzzer, OUTPUT);
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  Serial.println("Welcome to the touch button press example");
}


void loop() {
  static int sensor1 = 0;
  static int sensor2 = 0;
  //button1 check
  sensor1p = buttonfunc(sensor1);

  Serial.println("Button 1 finished");

  sensor2p = buttonfunc(sensor2);

  Serial.println("Button 2 finished");

  if (sensor1p == 1 && sensor2p ==1)
  {
    Serial.println("3");
  }
  else if (sensor1p == 1)
  {
    Serial.println("1");
  }
  else if (sensor2p == 1)
  {
    Serial.println("2");
  }
  

}

int buttonfunc(int pin)
{
  //init value of state machine
  static int button1State = ButtonState_Up;
  //keep track of the times a press occurs
  static int pressed = 0;
  /*Serial.print("Current State: ");//debug prints
  Serial.print(button1State);
  Serial.print(" Button Read: ");
  Serial.println(checkButton(buttonPin));*/
  button1State = UpdateButtonState(button1State,
                        checkButton(pin));  
  /*Serial.print("New State: ");//debug prints
  Serial.println(button1State);*/

  //check the states
  if (button1State == ButtonState_Pressed) {
    pressed = 1;
    Serial.println("Button Pressed");
    
    
  } 
  else if(button1State == ButtonState_Released) {
    pressed = 0;
  }
  return(pressed);
}

int UpdateButtonState(int iButtonState, int iNewButtonRead)
{
  if(iButtonState == ButtonState_Up && iNewButtonRead == ButtonRead_Down)
    return ButtonState_Pressed;
  else if(iButtonState == ButtonState_Pressed)
    return ButtonState_Down;
  else if(iButtonState == ButtonState_Down && iNewButtonRead == ButtonRead_Up)
    return ButtonState_Released;
  else if(iButtonState == ButtonState_Released)
    return ButtonState_Up;
  return iButtonState;
}

int checkButton(int iButtonPin)
{
  int newButtonRead = digitalRead(iButtonPin);
  delay(10);
  int debounceButtonRead = digitalRead(iButtonPin);
  if(newButtonRead != debounceButtonRead)
    return -1;//button is not stable

  if(newButtonRead == LOW) //Button is active low, ie using pullup
    return ButtonRead_Down;
  return ButtonRead_Up;
}
