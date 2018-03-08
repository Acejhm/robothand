/*
 * Resources:
 * http://www.instructables.com/id/Arduino-Multiple-Servo-Control-With-Arduino/
 * https://www.arduino.cc/en/Tutorial/PWM
 * https://www.arduino.cc/en/Tutorial/Knob
 * 
 * IMPORTANT:  To use C/C++ STL's, you should follow this guide:  https://github.com/maniacbug/StandardCplusplus
 */

#include <StandardCplusplus.h>
#include <vector>
#include <Servo.h>

// In degrees, with it's resting position being 0 degrees.
// TODO: Verify these values, as these are rough approximations.
const short MAX_ROTATION_RIGHT = 90;
const short MAX_ROTATION_LEFT = 90;

// 5 Servos atm, one for each finger.
const short SERVO_COUNT = 5;

// List of all servos and pin ids.
// Only the digital input needs to be attached, which is just one pin.
// PWM (Pulse Width Modulation) Pins should be used.
// Pin ids 2-13
// Index 0 is index fingers.  Pins ???
// Index 1 is middle finger. Pins ???
// Index 2 is ring finger. Pins ???
// Index 3 is pinky finger. Pins ???
// Index 4 is thumb. Pins ???
std::vector<Server> servo_list;

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup()
{
  // Create a new servo object and populat the list.
  // Assuming sequential pin ids, and none are skipped.
  // If any non-sequential method is used, hardcoding the attchments will
  // be required. Starting at 2, as that's the first PWM pin.
  for (short pin_id=2; pin_id < (SERVO_COUNT+pin_id); pin_id++)
  {
    Servo servo_obj;
    servo_obj.attach(pin_id);  // Attach/Assign the servo to a pin.
    servo_list.push_back(&servo_obj); // Add it to the list.
  }
}

void loop()
{
//  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
//  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
//  myservo.write(val);                  // sets the servo position according to the scaled value
//  delay(15);                           // waits for the servo to get there
}
