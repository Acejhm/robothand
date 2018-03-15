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

#include <Servo.h>

/******************************************************************************
********************     Defines/ Macros    ***********************************
******************************************************************************/
//max rotation in degrees, resing being 0, maximum being 180
#define MAX_ROTATION_RIGHT  0
#define MAX_ROTATION_LEFT 180

#define SERVO_COUNT 5

//How long to wait between iterations in milliseconds.
#define MS_DELAY (5*100) 

//the hand is expected to be conected to sequential pins starting at this value
#define STARTING_PIN 2

/******************************************************************************
********************       Globals          ***********************************
******************************************************************************/
typedef struct 
{
  Servo servo_obj;
  int meter_val;  // Analog pin used to connect the potentiometer.
  char pin_id;
} servo_struct;

// List of all servos and pin ids.
// Only the digital input needs to be attached, which is just one pin.
// PWM (Pulse Width Modulation) Pins should be used.
// Pin ids 2-13
// Index 0 is index fingers.  Pins ???
// Index 1 is middle finger. Pins ???
// Index 2 is ring finger. Pins ???
// Index 3 is pinky finger. Pins ???
// Index 4 is thumb. Pins ???
servo_struct servos [SERVO_COUNT];

//we might be able to make this an unsigned char if all of the values will be
//between 0 and 180
int val;  // variable to read the value from the analog pin

/******************************************************************************
********************       Functions Declarations     *************************
******************************************************************************/
/* Reads in a byte from serial and writes it back.
 */
void read_byte();

/* Sets the rotation of the supplied servo to the specified value
 */ 
void set_servo_rotation(servo_struct servo, int val);

/* Sets all of the servos rotation to the specified value
 */
void set_all_servos(int val);

/* Sets the servos first to the maximum, then to the minimum rotation
 */
void fully_extend_and_retract_servos();


/******************************************************************************
********************       Setup and Main Loop        *************************
******************************************************************************/
void setup()
{
  Serial.begin(9600); // Set up the serial port with it's baud rate.

  // Create a new servo object and populat the list.
  // Assuming sequential pin ids, and none are skipped.
  // If any non-sequential method is used, hardcoding the attchments will
  // be required. Starting at 2, as that's the first PWM pin.
  for (char pin_id=STARTING_PIN; pin_id < (SERVO_COUNT+pin_id); pin_id++)
  {
    Servo servo;
    servo.attach(pin_id);  // Attach/Assign the servo to a pin.
    servo_struct tmp_struct = {
        .servo_obj = servo,
        .pin_id = pin_id
    };
    servos[pin_id - STARTING_PIN] = tmp_struct;
  }
  val = MAX_ROTATION_RIGHT;
}

void loop()
{
  //waits for the user to send a character from serial then fully extends and 
  //fully retracts all of the fingers (servos)
  read_byte();

  fully_extend_and_retract_servos();
}

/******************************************************************************
********************       Functions Definitions      *************************
******************************************************************************/
/* Reads in a byte from serial and writes it back.
 *  This eventually needs to be modified to grab the byte and return it as a 
 *  char for cli functionality.
 */
void read_byte()
{
  // Wait until it's avaialable.
  if (Serial.available() > 0)
  { // read the incoming byte:
    int incomingByte = Serial.parseInt();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}

/* Sets the rotation of the supplied servo to the specified value
 */ 
void set_servo_rotation(servo_struct servo, int val)
{
    servo.servo_obj.write(val);
}

/* Sets all of the servos rotation to the specified value
 */
void set_all_servos(int val)
{
  for (char iter = 0; iter < SERVO_COUNT; iter++)
  {
    set_servo_rotation(servos[iter], val);
    delay(100);
  }
}

/* Sets the servos first to the maximum, then to the minimum rotation
 */
void fully_extend_and_retract_servos()
{
  set_all_servos(MAX_ROTATION_RIGHT);
  delay(MS_DELAY);  
  set_all_servos(MAX_ROTATION_LEFT);
  delay(MS_DELAY);  
}
