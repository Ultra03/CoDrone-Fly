#include <CoDrone.h>

void setup() {
  // put your setup code here, to run once:

  CoDrone.begin(115200);

  CoDrone.AutoConnect(NearbyDrone);
  CoDrone.DroneModeChange(Flight);

  CoDrone.LedColor(EyeFlicker, Aqua, 100);
  delay(100);
  CoDrone.LedColor(ArmFlow, Cornsilk, 10);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte bt1 = digitalRead(11);       // reads the far left button and saves it to btn1
  byte bt4 = digitalRead(14);       // reads the middle button and saves it to btn4
  byte bt8 = digitalRead(18);       // reads the far right button and saves it to btn8

  // Stop when the left butotn is pressed, but none of the others are
  if (bt1 && !bt4 && !bt8)
  {
    CoDrone.FlightEvent(Stop);      // This command stops the drone (it turns off the motors)
  }

  // try to land when the right button is pressed and no others are
  if (!bt1 && !bt4 && bt8)
  {
     CoDrone.FlightEvent(Landing);  // Tells the drone to land (slowly lowers until it hits the ground and then turns off)
  }

  if(digitalRead(14) == 1) {
    CoDrone.LedColor(EyeHold, Yellow, 100);
    delay(100);
    CoDrone.LedColor(ArmHold, Yellow, 100);
    delay(100);
  }

  if(digitalRead(16) == 1) {
    CoDrone.LedColor(EyeFlicker, Aqua, 100);
    delay(100);
    CoDrone.LedColor(ArmFlow, Cornsilk, 10);
    delay(100);
  }

  // PAIRING is set to true in AutoConnect if they connect together
  if (PAIRING == true)  // Check to see that we are paired before trying to fly               
  {
    // reads the joystick (analogRead(A#)) and then converts it into a value that the drone can use (AnalogScaleChange())
    // if any of the joysticks move backwards compared to the drone (up is down or left is right), add -1 * at the start
    // it will change the direction the drone moves when you move the joystick
    YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));   // YAW (turn left or right), port A3, reversed
    THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));  // THROTTLE (height), port A4, not reversed
    ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));  // ROLL (tilt left or right), port A5, reversed
    PITCH = CoDrone.AnalogScaleChange(analogRead(A6));      // PITCH (tilt front or back), port A6, not reversed
    
    CoDrone.Control(SEND_INTERVAL); // sends the values to the codrone, it will make sure that SEND_INTERVAL (~50ms) time has passed before it sends again 
  }





}

