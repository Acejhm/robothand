#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>

/*
 * Resources:
 * http://www.instructables.com/id/Arduino-Multiple-Servo-Control-With-Arduino/
 * https://www.arduino.cc/en/Tutorial/PWM
 * https://www.arduino.cc/en/Tutorial/Knob
 * 
 * Servo Spec sheet:  https://servodatabase.com/servo/futaba/s3003
 * 
 * IMPORTANT:  To use C/C++ STL's, you should follow this guide:  https://github.com/maniacbug/StandardCplusplus
 */

#include <StandardCplusplus.h>
#include <vector>
#include <Servo.h>

// In degrees, with it's resting position being 0 degrees.
// TODO: Verify these values, as these are rough approximations.
// These are correct according to the spec sheet, but it needs actual testing.
// These values should be within the operating range, as anything over
// these gets set to this angle.
const short MAX_ROTATION_RIGHT = 60;
const short MAX_ROTATION_LEFT = 60;

// 5 Servos atm, one for each finger.
const short SERVO_COUNT = 5;

const int MS_DELAY = 5*100 // How long to wait between iterations in milliseconds.

// List of all servos and pin ids.
// Only the digital input needs to be attached, which is just one pin.
// PWM (Pulse Width Modulation) Pins should be used.
// Pin ids 2-13
// Index 0 is index fingers.  Pins ???
// Index 1 is middle finger. Pins ???
// Index 2 is ring finger. Pins ???
// Index 3 is pinky finger. Pins ???
// Index 4 is thumb. Pins ???

struct servo_struct
{
  Servo servo_obj;
  int meter_val;  // Analog pin used to connect the potentiometer.
                  // TODO: Need to map these as well.
}
std::vector<struct> servo_list;

int val;  // variable to read the value from the analog pin

bool revsere = false;

void setup()
{
  // Create a new servo object and populat the list.
  // Assuming sequential pin ids, and none are skipped.
  // If any non-sequential method is used, hardcoding the attchments will
  // be required. Starting at 2, as that's the first PWM pin.
  for (short pin_id=2; pin_id < (SERVO_COUNT+pin_id); pin_id++)
  {
    Servo servo;
    servo.attach(pin_id);  // Attach/Assign the servo to a pin.
    tmp_struct = new servo_struct;
    tmp_struct.servo_obj = servo;
    //tmp_struct.meter_val = ????? // TODO: Figure out what the mappings should be for these pins.
    
    servo_list.push_back(&tmp_struct); // Add it to the list.
  }
}

void loop()
{
  for (short iter = 0; iter < SERVO_COUNT; iter++;)
  {
    tmp_struct = servo_list[iter]
    int val = analogRead(tmp_struct.meter_val);  // Reads the value of the potentiometer (value between 0 and 1023)

    // Scale it to use it with the servo (value between 0 and 180)
    // Syntax: value, fromLow, fromHigh, toLow, toHigh
    // So this function maps value that's within a range to a new range.
    // Flipping the high and low effectively gives the "reverse" direction.
    if reverse
      val = map(val, 0, 1023, 180, 0);
    else
      val = map(val, 0, 1023, 0, 180);

    // Make sure we don't overextend.
    if val > MAX_ROTATION_RIGHT
      val = MAX_ROTATION_RIGHT;
    else if val > MAX_ROTATION_LEFT
      val = MAX_ROTATION_LEFT;
    
    tmp_struct.servo_obj.write(val);  // Sets the servo position according to the scaled value (as an angle)
  }
  // Flip the direction for the next iteration.
  if reverse
    reverse = false;
  else
    reverse = true;
  
  delay(MS_DELAY);  // Waits for the servo to get there, and delays until the next iteration.
}

