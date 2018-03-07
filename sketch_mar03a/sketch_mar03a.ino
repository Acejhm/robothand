/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <vector>

// 5 Servos atm, one for each finger.
const short SERVO_COUNT = 5;

// Each servo takes three pins.
const short SERVO_PIN_SIZE = 3;

// List of all servos and pin ids.
// Pin ids are inclusive.
// Index 0 is index fingers.  Pins 0-2
// Index 1 is middle finger. Pins 3-5
// Index 2 is ring finger. Pins 6-8
// Index 3 is pinky finger. Pins 9-11
// Index 4 is thumb. Pins 12-14
std::vector<Server> servo_list;

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup()
{
  for (short iter=0; iter < SERVO_COUNT; i++)
  {
    // Create a new servo object and populat the list.
    Servo servo_obj;
    for (int pin_id=(iter*SERVO_PIN_SIZE); pin_id < SERVO_PIN_SIZE; pin_id++)
        servo_obj.attach(pin_id)  // Attach/Assign the servo to a set of pins.
    servo_list.push_back(&servo_obj);
  }
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
