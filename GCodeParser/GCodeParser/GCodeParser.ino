#include <Servo.h> //using B
int servoCount = 1;
int durationServo = 1000;
Servo reelservo;
// define the parameters of our machine.

float X_STEPS_PER_INCH = 48;
float X_STEPS_PER_MM = 40;
int X_MOTOR_STEPS   = 100;

float Y_STEPS_PER_INCH = 48;
float Y_STEPS_PER_MM  = 40;
int Y_MOTOR_STEPS   = 100;

float Z_STEPS_PER_INCH = 48;
float Z_STEPS_PER_MM   = 40;
int Z_MOTOR_STEPS    = 100;

float B_STEPS_PER_INCH = 48;
float B_STEPS_PER_MM   = 40;
int B_MOTOR_STEPS    = 100;

//our maximum feedrates
long FAST_XY_FEEDRATE = 2000;
long FAST_Z_FEEDRATE = 2000;
long FAST_B_FEEDRATE = 4000;

// Units in curve section
#define CURVE_SECTION_INCHES 0.019685
#define CURVE_SECTION_MM 0.5


// Set to one if sensor outputs inverting (ie: 1 means open, 0 means closed)
// RepRap opto endstops are *not* inverting.
int SENSORS_INVERTING = 1;

// How many temperature samples to take.  each sample takes about 100 usecs.


/****************************************************************************************
* digital i/o pin assignment
*
* this uses the undocumented feature of Arduino - pins 14-19 correspond to analog 0-5
****************************************************************************************/
/// port1
int X_STEP_PIN = 10;    //pwm 10
int X_DIR_PIN = 11;     // pwm 11
int X_ENABLE_PIN = -1;
/// port 7 used to be port 6
int X_MIN_PIN = 13;    // old 17
int X_MAX_PIN = -1; // old 16
/// port2
int Y_STEP_PIN = 12; //pwm 9 
int Y_DIR_PIN = 9; //pwm 3
int Y_ENABLE_PIN = -1;
/// port 3 used to be port 3
int Y_MIN_PIN = 8; // old 13
int Y_MAX_PIN = 13; // old 12
//PORT 10 USED TO BE PORT 7
int Z_STEP_PIN = 7;
int Z_DIR_PIN = 6; //pwm
int Z_ENABLE_PIN = -1;
int Z_MIN_PIN = -1;
int Z_MAX_PIN = 3;
//PORT 9
int B_STEP_PIN = 4; 
int B_DIR_PIN = 5;  //pwm
int B_ENABLE_PIN = -1;
int B_MIN_PIN = -1;
int B_MAX_PIN = -1;
//Port 7
int SERVO_1 = 16;         //S1
int SERVO_2 = 17;         //S2
//Port 8
int SERVO_3 = 15;          //S2
int SERVO_4 = 14;         //S1
#define COMMAND_SIZE 128

char commands[COMMAND_SIZE];
byte serial_count;
int no_data = 0;

//Servo servo;

//int currentPosServo = 90;
//int targetPosServo = 90;
bool comment = false;
void setup()
{
	
	//Do startup stuff here
	Serial.begin(115200);
 pinMode (2,OUTPUT);
//        if(Z_ENABLE_SERVO==1){
//          servo.attach(Z_STEP_PIN);
//        }
	//other initialization.

	init_process_string();
	init_steppers();
	process_string("G90",3);//Absolute Position
        Serial.println("start");
}

void loop()
{
  
	char c;
	//read in characters if we got them.
	if (Serial.available() > 0)
	{
		c = Serial.read();
		no_data = 0;
		//newlines are ends of commands.
		if (c != '\n')
		{
			if(c==0x18){
				Serial.println("Grbl 1.0");
			}else{
                          if (c == '('){
                            comment = true;
                          }
                          // If we're not in comment mode, add it to our array.
                          if (!comment)
                          {
                            commands[serial_count] = c;
                    				serial_count++;
                          }
                          if (c == ')'){
                            comment = false; // End of comment - start listening again
                          }
                        }
				
		}
	}else
	{
		no_data++;
		delayMicroseconds(100);

	//if theres a pause or we got a real command, do it
	if (serial_count && (c == '\n' || no_data > 100))
	{
		//process our command!
		process_string(commands, serial_count);
		//clear command.
		init_process_string();
	}

	//no data?  turn off steppers
	if (no_data > 1000){
		disable_steppers();
	}
        }
//        return;
//                delay(5);
//                int dPos = abs(currentPosServo-targetPosServo);
//                if(currentPosServo<targetPosServo){
//                   currentPosServo += dPos>8?6:1;
//                }else if(currentPosServo>targetPosServo){
//                   currentPosServo -= dPos>8?6:1;
//                }

                
        
}
