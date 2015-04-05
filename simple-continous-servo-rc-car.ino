/**
 * Simple Spark core enabled RC car that uses two continuous servos with wheels 
 * attached on end, with an optional bearing in lieu of a second set of wheels. 
 * The car is controlled via HTTP POST requests to spark cores REST resource.
 * 
 * Basic car componnent layout (top view)
 * 
 *                FRONT
 * 
 * (wheel)-[L servo]  [R servo]-(wheel)
 *         [                  ]
 *         [ circuit board w/ ]
 *         [ sparkcore and    ]
 *         [ connections to   ]
 *         [ some external    ]
 *         [ or additional    ]
 *         [ power source for ]
 *         [ servos           ]
 *         [                  ]
 *         [     bearing      ]
 * 
 *                REAR
 * 
 * See repo for circuit layout.
 * 
 * @author Kevin Dela Rosa
 * 
 */

// Constants and variables
int SHORT_DELAY              = 10;
int COMMAND_SUCCES_EXECUTION = 1;
int COMMAND_FAILED_EXECUTION = -1;

// Pulse widths for continuous servos in micro seconds, adjust for your hardware
int LEFT_FULL_FOWARD         = 1700; // where left wheel spins towards front of car
int RIGHT_FULL_FORWARD       = 1300; // where right wheel spins towards front of car
int LEFT_FULL_REVERSE        = 1300;
int RIGHT_FULL_REVERSE       = 1700;
int LEFT_FULL_STOP           = 1525;
int RIGHT_FULL_STOP          = 1525;
int LEFT_SLOW_REVERSE        = 1475; // slow reverse used instead of stopping to make turn faster
int RIGHT_SLOW_REVERSE       = 1575;

// Servos
Servo leftServo;
Servo rightServo;


/**
 * Sets up servos and registers command
 */
void setup() {
  leftServo.attach(A0);
  rightServo.attach(A1);
  Spark.function("command", executeCommand);
}


/**
 * Loop forever 
 */
void loop() {
  // Do nothing, loop not used
}


/**
 * Handles commands to the car
 * 
 * This function automagically gets called upon a matching POST request
 * 
 * example request:
 * curl https://api.spark.io/v1/devices/<DEVICE-ID-FOR-SPARK-CORE>/command -d access_token=<ACCESS-TOKEN-FOR-SPARK-CORE> -d "args=left"
 * 
 */
int executeCommand(String command) {
  if(command == "forward") {
    returnforward();
  } else if (command == "backward"){
    return backward();
  } else if (command == "left"){
    return left();
  } else if (command == "right"){
    return right();
  } else if (command =="stop") {
    return stop();
  }
  else return COMMAND_FAILED_EXECUTION;
}


/**
 * Move car forward
 */
int forward() { 
    leftServo.writeMicroseconds(LEFT_FULL_FOWARD);
    rightServo.writeMicroseconds(RIGHT_FULL_FORWARD);
    delay(SHORT_DELAY);
    return COMMAND_SUCCES_EXECUTION;
}


/**
 * Move car backward
 */
int backward() {
    leftServo.writeMicroseconds(LEFT_FULL_REVERSE);
    rightServo.writeMicroseconds(RIGHT_FULL_REVERSE);
    delay(SHORT_DELAY);
    return COMMAND_SUCCES_EXECUTION;
}


/**
 * Move car right
 */
int right() {
    leftServo.writeMicroseconds(LEFT_FULL_FOWARD);
    rightServo.writeMicroseconds(RIGHT_SLOW_REVERSE);
    delay(SHORT_DELAY);
    return COMMAND_SUCCES_EXECUTION;
}


/**
 * Move car left
 */
int left() {
    leftServo.writeMicroseconds(LEFT_SLOW_REVERSE);
    rightServo.writeMicroseconds(RIGHT_FULL_FORWARD);
    delay(SHORT_DELAY);
    return COMMAND_SUCCES_EXECUTION;
}


/**
 * Bring car to full sop
 */
int stop() {
    leftServo.writeMicroseconds(LEFT_FULL_STOP);
    rightServo.writeMicroseconds(RIGHT_FULL_STOP);
    delay(SHORT_DELAY);
    return COMMAND_SUCCES_EXECUTION;
}
