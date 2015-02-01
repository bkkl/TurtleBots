/*
 * TurtleBot.h - Library for easy control of an Arduino Uno powered
 * Parallax BoE (Board of Education) robot.
 *
 * License:  Released into the public domain.
 * Authors:
 *   AD:  Andrew C. Dassing
 *	 BL:  Brad Lane
 * Change Log:
 *   2014-03-06 AD:  Conceptualized and initiated.
 *   2014-09-11 BL:  Added includes for IRremote.h and "TurtleBotmyIRcodes.h"
 *   2014-11-23 BL:  adding playtune function
 */
 


#ifndef _TurtleBot_H_
#define _TurtleBot_H_

#include <Servo.h>
#include <IRremote.h> // - BL
#include "TurtleBotmyIRcodes.h" // -BL

class TurtleBot {

friend class IRrecv;

public:
	TurtleBot();
	TurtleBot(const int leftMotorPin, const int rightMotorPin,
			const float wheelDiameter, const float axleTrack);
	~TurtleBot();

	TurtleBot& playTune(int speakerPin, int tempo, int note_length, int beats[], char notes[]); //BL - pass in all values
	TurtleBot& playTune(int speakerPin, int beats, char notes); // BL play a single note
	TurtleBot& playTune(int speakerPin); // BL play tune defined in TurtleBotTune.h
	TurtleBot& stop();
	TurtleBot& forward(const float revolutions);
	TurtleBot& backward(const float revolutions);

	TurtleBot& turnLeft();	// 90 degrees
	TurtleBot& turnLeft(const float degrees);
	TurtleBot& turnRight();   // 90 degrees
	TurtleBot& turnRight(const float degrees);

	TurtleBot& spinLeft();  // 90 degrees
	TurtleBot& spinLeft(const float degrees);
	TurtleBot& spinRight(); // 90 degrees


	/*
	 * spinRight(degrees) - spins in place clockwise approximately the number of degrees specified.
	 *
	 * @param degrees the number of degrees to spin clockwise.
	 *
	 * @author A.C. Dassing
	 */
	TurtleBot& spinRight(const float degrees);

	void steer(const float speed);

	void setRevolutionsPerSecond(const float revPerSec);

	static const int LeftFullFwdPWM = 1700;
	static const int LeftStopPWM = 1500;
	static const int LeftFullRevPWM = 1300;

	static const int RightFullFwdPWM = 1300;
	static const int RightStopPWM = 1500;
	static const int RightFullRevPWM = 1700;

	static const float SteerSpinLEFT = -200.0;
	static const float SteerTurnLEFT = -100.0;
	static const float SteerFORWARD = 0.0;
	static const float SteerTurnRIGHT = +100.0;
	static const float SteerSpinRIGHT = +200.0;
/* for IR control - BL */	
	static const int IRpin = IRINPUTPIN; // sets IR input pin to pin defined in TurtleBotmyIRcodes.h - BL
	IRrecv irrecv;   // init IR receive structure - BL
	decode_results results; // results buffer - BL 
	
	
private:
	void init();
	void engage(const float revolutions);
	long getMsForRevolutions (const float revolutions);
	float getTurnRevsForDegrees(const float degrees);
	float getSpinRevsForDegrees(const float degrees);
	void playTone(int tone, int duration, int speakerPin);
	void playNote(char note, int duration, int speakerPin);
	
	Servo left;
	Servo right;

	float revPerMs;

	float steering;

	int leftMotorPin;
	int leftPwm;

	int rightMotorPin;
	int rightPwm;

	float wheelDiameter; //cm
	float axleTrack;  //cm
	float speed;  // rotations/sec

};

#endif /* _TurtleBot_H_ */
