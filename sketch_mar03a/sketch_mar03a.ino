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
// It'a maximum range is 180 degrees.
const short MAX_ROTATION_RIGHT = 0;
const short MAX_ROTATION_LEFT = 180;

// 5 Servos atm, one for each finger.
const short SERVO_COUNT = 5;

const int MS_DELAY = 5*100; // How long to wait between iterations in milliseconds.

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
};
std::vector<servo_struct> servo_list;

int val;  // variable to read the value from the analog pin

bool revsere_direction = false;

void setup()
{
  Serial
  // Create a new servo object and populat the list.
  // Assuming sequential pin ids, and none are skipped.
  // If any non-sequential method is used, hardcoding the attchments will
  // be required. Starting at 2, as that's the first PWM pin.
  for (short pin_id=2; pin_id < (SERVO_COUNT+pin_id); pin_id++)
  {
    Serial.begin(9600); // Set up the serial port with it's baud rate.
    Servo servo;
    servo.attach(pin_id);  // Attach/Assign the servo to a pin.
    servo_struct tmp_struct;
    tmp_struct.servo_obj = servo;
    servo_list.push_back(tmp_struct); // Add it to the list.
  }
}

void loop()
{
  // Wait until it's avaialable.
  if (Serial.available() > 0)
  { // read the incoming byte:
    int incomingByte = Serial.parseInt();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  for (short iter = 0; iter < SERVO_COUNT; iter++)
  {
    servo_struct tmp_struct = servo_list[iter];

    // Make sure we don't overextend.
    if (val > MAX_ROTATION_RIGHT)
      val = MAX_ROTATION_RIGHT;
    else if (val > MAX_ROTATION_LEFT)
      val = MAX_ROTATION_LEFT;
    
    tmp_struct.servo_obj.write(val);  // Sets the servo position according to the scaled value (as an angle)

    delay(100);
  }
  // Flip the direction for the next iteration.
  if (revsere_direction == true)
    revsere_direction = false;
  else
    revsere_direction = true;
  
  delay(MS_DELAY);  // Waits for the servo to get there, and delays until the next iteration.
}

