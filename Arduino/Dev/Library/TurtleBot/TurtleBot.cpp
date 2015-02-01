/*
 * TurtleBot.cpp - Library for easy control of an Arduino Uno powered
 * Parallax BoE (Board of Education) robot.
 *
 * License:  Released into the public domain.
 * Authors:
 *   AD:  Andrew C. Dassing
 *   BL:  Brad Lane
 * Change Log:
 *   2014-03-06 AD:  Conceptualized and initiated.
 *	 2014-09-07 BL:  Modified to add IR control. 
 *	 2014-11-23 BL:  added Turtlebot.playtune function. 
 */
#include "TurtleBot.h"
#include "TurtleBotTune.h"
#include <Arduino.h>

#define PI 3.141592


TurtleBot::TurtleBot() {
	init();
}

TurtleBot::~TurtleBot() {
	if (left.attached()) {
		left.writeMicroseconds(LeftStopPWM);
		left.detach();
	}
	if (right.attached()) {
		right.writeMicroseconds(RightStopPWM);
		right.detach();
	}
}

TurtleBot::TurtleBot(const int leftMotorPin, const int rightMotorPin,
	const float wheelDiameter, const float axleTrack) {
	init();
	this->leftMotorPin = leftMotorPin;
	this->rightMotorPin = rightMotorPin;
	this->wheelDiameter = wheelDiameter;
	this->axleTrack = axleTrack;
	this->speed = wheelDiameter * PI;
}

void TurtleBot::init() {
	revPerMs = 0.00075;
	//= 0.00081; // = 0.81 revs/sec
	steering = SteerFORWARD;

	leftMotorPin = 13;
	leftPwm = LeftStopPWM;

	rightMotorPin = 12;
	rightPwm = RightStopPWM;

	wheelDiameter = 6.7; //cm
	axleTrack = 11.0;  //cm
	speed = wheelDiameter * PI;  // rotations/sec
	steer(0);

	/* init for IR remote functions - BL */ 
	#ifdef IRINPUTPIN
		irrecv.attach(IRINPUTPIN);   	// init IR receive structure to pin 3 input- BL
		irrecv.enableIRIn();   		// Start the IR receiver - BL
	#endif
	/* Set up GPIO controlled by remote */
	#ifdef button_0_GPIO
		pinMode(button_0_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_1_GPIO
		pinMode(button_1_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_2_GPIO
		pinMode(button_2_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_3_GPIO
		pinMode(button_3_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_4_GPIO
		pinMode(button_4_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_5_GPIO
		pinMode(button_5_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_6_GPIO
		pinMode(button_6_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_7_GPIO
		pinMode(button_7_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_8_GPIO
		pinMode(button_8_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif
	#ifdef button_9_GPIO
		pinMode(button_9_GPIO, OUTPUT);    // setting GPIO PIN Mode Per TurtleBotmyIRcodes.h
	#endif

}

void TurtleBot::setRevolutionsPerSecond(const float revPerSec) {
	revPerMs = revPerSec / 1000.0;
}

TurtleBot& TurtleBot::forward(const float revolutions) {	
    steer(0);	engage(revolutions);
	return *this;
}

TurtleBot& TurtleBot::backward(const float revolutions) {
	steer(0);
	engage(-revolutions);
	return *this;
}

TurtleBot& TurtleBot::turnLeft() {	// 90 degrees
	turnLeft(90);
	return *this;
}

TurtleBot& TurtleBot::turnLeft(const float degrees) {
	steer(degrees < 0.0? SteerTurnRIGHT : SteerTurnLEFT);
	engage(getTurnRevsForDegrees(degrees));
	return *this;
}

TurtleBot& TurtleBot::spinLeft() {  // 90 degrees
	spinLeft(90);
	return *this;
}

TurtleBot& TurtleBot::spinLeft(const float degrees) {
	steer(degrees < 0.0? SteerSpinRIGHT : SteerSpinLEFT);
	engage(getSpinRevsForDegrees(degrees));
	return *this;
}

TurtleBot& TurtleBot::turnRight() {   // 90 degrees
	turnRight(90);
	return *this;
}

/*
 * turnRight() - spins in place clockwise approximately the number of degrees specified.
 */
TurtleBot& TurtleBot::turnRight(const float degrees) {
	steer(degrees < 0.0? SteerTurnLEFT : SteerTurnRIGHT);
	engage(getTurnRevsForDegrees(degrees));
	return *this;
}

/*
 * spinRight() - spins in place clockwise approximately 90 degrees.
 */
TurtleBot& TurtleBot::spinRight() { // 90 degrees
	spinRight(90);
	return *this;
}

TurtleBot& TurtleBot::spinRight(const float degrees) {
	steer(degrees < 0.0? SteerSpinLEFT : SteerSpinRIGHT);
	engage(getSpinRevsForDegrees(degrees));
	return *this;
}


/*
 * -200 .. -100 .. 0 .. +100 .. +200
 * spin    turn   fwd   turn    spin
 * left    left         right   right
 */
void TurtleBot::steer(const float steering) {

	leftPwm = LeftFullFwdPWM;
	rightPwm = RightFullFwdPWM;	
	if (steering == 0.0) {
		//go straight
	} else if (steering < 0.0) { // left turn
		leftPwm = LeftFullFwdPWM + int(2.0 * steering);
	} else { //right turn
		rightPwm = RightFullFwdPWM + int(2.0 * steering);
	}
	
}

long TurtleBot::getMsForRevolutions(const float revolutions) {
	return long(abs(revolutions) / revPerMs);
}

float TurtleBot::getTurnRevsForDegrees(const float degrees) {
	return (axleTrack * degrees) / (wheelDiameter * 180.0);
}

float TurtleBot::getSpinRevsForDegrees(const float degrees) {
	return getTurnRevsForDegrees(degrees) / 2.0f;
}

void TurtleBot::engage(const float revolutions) {
	boolean reversed = revolutions < 0.0;
	int finalLeftPwm = reversed? rightPwm : leftPwm;
	int finalRightPwm = reversed? leftPwm : rightPwm;
	int IRoverride = 1;
	int IRcontrolmode = 0;
	/* attaching Servos  */ 
	if (!left.attached())
		left.attach(leftMotorPin);
	if (!right.attached())
		right.attach(rightMotorPin); 		
	/* Adding IR override trap - BL */
	TCCR2A = 2; // make sure timer 2 is correct (?) - timer2 being step on somewhere else in turtlebot.init and here - can't find.
    TCCR2B = 2; // make sure timer 2 is correct (?)  
	while (IRoverride) {
		if (irrecv.decode(&results)) 
		{ 
		     /* if LED connected to output pin 6 - flash LED when IR code received */
			#ifdef LED6IR
			  digitalWrite(6, HIGH); 
			#endif  
		    if(results.value == down_button)        // robot backs up
            {
              left.writeMicroseconds(LeftFullRevPWM);
			  right.writeMicroseconds(RightFullRevPWM);
			  if (!IRcontrolmode) delay(2000);
            }
            else if(results.value == right_button)                       // robot turns right
            {
			  left.writeMicroseconds(LeftFullFwdPWM);
			  right.writeMicroseconds(RightStopPWM);
			  if (!IRcontrolmode) delay(100);
            }
            else if(results.value == left_button)                      // robot turns left
            {
              left.writeMicroseconds(LeftStopPWM);
			  right.writeMicroseconds(RightFullFwdPWM);
			  if (!IRcontrolmode) delay(100);
            }
            else if(results.value == up_button)    // robot goes forward
            {
              left.writeMicroseconds(LeftFullFwdPWM);
			  right.writeMicroseconds(RightFullFwdPWM);
			  if (!IRcontrolmode) 
			  {
				delay(100);
			  }
			  
            }
            else if(results.value == stop_button)    // detach servos - motor stop
            {
              left.detach();                      // Attach left signal to pin 13
              right.detach();                     // Attach right signal to pin 12 
            }
            else if(results.value == play_button)    // attach servos - motor start again. 
            {
				if (!left.attached())
					left.attach(leftMotorPin);
				if (!right.attached())
					right.attach(rightMotorPin);
            }
            else if(results.value == pause_button)    // pauses Arduino turtlebot instruction execution;; IR override active - traps here until released. 
            {
				left.writeMicroseconds(LeftStopPWM);
			    right.writeMicroseconds(RightStopPWM);  
				IRcontrolmode = !IRcontrolmode;
            }
			else if(results.value == ffwd_button)    // robot spins right 
            {
			  left.writeMicroseconds(LeftFullFwdPWM);
			  right.writeMicroseconds(RightFullRevPWM);
			  delay(500);
            }
			else if(results.value == rrwd_button)    // robot spins to left 
            {
			  left.writeMicroseconds(LeftFullRevPWM);
			  right.writeMicroseconds(RightFullFwdPWM);
			  delay(500);
            }
			else if(results.value == button_5)    // sets GPIO pin defined in TurtleBotmyIRcodes.h high
            {
				#ifdef button_5_GPIO
					digitalWrite(button_5_GPIO, HIGH); 
				#endif
            }
			else if(results.value == button_8)    // sets GPIO pin defined in TurtleBotmyIRcodes.h high
            {
				#ifdef button_5_GPIO
					digitalWrite(button_5_GPIO, LOW); 
				#endif
            }
			else if(results.value == button_6)    // sets GPIO pin defined in TurtleBotmyIRcodes.h high
            {
				#ifdef button_6_GPIO
					digitalWrite(button_6_GPIO, HIGH); 
				#endif
            }
			else if(results.value == button_9)    // sets GPIO pin defined in TurtleBotmyIRcodes.h high
            {
              #ifdef button_6_GPIO
				digitalWrite(button_6_GPIO, LOW); 
			  #endif
            }
			else if(results.value == button_7)    // pulses GPIO pin defined in TurtleBotmyIRcodes.h high
            {
			  #ifdef button_7_GPIO
				  digitalWrite(button_7_GPIO, HIGH); 
				  delay(100);
				  digitalWrite(button_7_GPIO, LOW); 
			  #endif
            }

		  irrecv.resume();   // Receive the next IR value
		  delay(100);
		  #ifdef LED6IR
			  digitalWrite(6, LOW); 
		  #endif 
		}
		else 
		{
				left.writeMicroseconds(LeftStopPWM);
			    right.writeMicroseconds(RightStopPWM); 
		}	
		IRoverride = IRcontrolmode;
	}
	/* exiting IR override trap */
	left.writeMicroseconds(finalLeftPwm);
	right.writeMicroseconds(finalRightPwm);

	delay(getMsForRevolutions(revolutions));
	stop();
	
}
// BL this functions allows all parameters to be passed in.
TurtleBot& TurtleBot::playTune(int speakerPin, int tempo, int note_length, int beats[], char notes[]) {
	pinMode(speakerPin, OUTPUT);
	for (int i = 0; i < note_length; i++) {
		if (notes[i] == ' ') {
			delay(beats[i] * tempo); // rest
		} else {
			playNote(notes[i], beats[i] * tempo, speakerPin);
		}
    // pause between notes
		delay(tempo / 2);
	}		
	return *this;
}
// BL this functions allows all parameters to be passed in to play a single note.
TurtleBot& TurtleBot::playTune(int speakerPin, int beats, char notes) {
	int tempo = 50;
	int note_length = 1;
	pinMode(speakerPin, OUTPUT);
	for (int i = 0; i < note_length; i++) {
		if (notes == ' ') {
			delay(beats* tempo); // rest
		} else {
			playNote(notes, beats * tempo, speakerPin);
		}
    // pause between notes
		delay(tempo / 2);
	}		
	return *this;
}
// BL this function plays tune defined in TurtleBotTune.h if only the speaker pin is passed in as variable 
TurtleBot& TurtleBot::playTune(int speakerPin) {
	int tempo = TEMPO;
	int note_length = NOTE_LENGTH;
	pinMode(speakerPin, OUTPUT);
	for (int i = 0; i < note_length; i++) {
		if (notes[i] == ' ') {
			delay(beats[i] * tempo); // rest
		} else {
			playNote(notes[i], beats[i] * tempo, speakerPin);
		}
    // pause between notes
		delay(tempo / 2);
	}		
	return *this;
}


TurtleBot& TurtleBot::stop() {
	left.writeMicroseconds(LeftStopPWM);
	right.writeMicroseconds(RightStopPWM);
	return *this;
}

void TurtleBot::playTone(int tone, int duration, int speakerPin) {
  for (long y = 0; y < duration * 1000L; y += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void TurtleBot::playNote(char note, int duration, int speakerPin) {
 	char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
	int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };
  for (int x = 0; x < 8; x++) {
    if (names[x] == note) {
      playTone(tones[x], duration, speakerPin);
    }
  }
}


