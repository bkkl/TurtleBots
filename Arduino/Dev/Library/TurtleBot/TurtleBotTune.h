/*
 * TurtleBot.h - Library for easy control of an Arduino Uno powered
 * Parallax BoE (Board of Education) robot.
 *
 * License:  Released into the public domain.
 * Authors:
 *   AD: Brad Lane
 * Change Log:
 *   2014-11-24 AD:  Conceptualized and initiated.
 *  based from: http://forum.arduino.cc/index.php?topic=1390.0 
 */
#ifndef _TurtleBotTune_H_
#define _TurtleBotTune_H_

/* define values to be used for the turtlebot.playtune() function */
/* uncomment only one tune */
/* Jingle Bells */ 
#define TEMPO 250 
#define NOTE_LENGTH 47
static const int beats[]={1,1,2,1,1,2,1,1,1,1,4,1,1,1,1,1,1,2,1,1,1,1,2,2,1,1,2,1,1,2,1,1,1,1,4,1,1,1,1,1,1,2,1,1,1,1,4};
static const char notes[]= "eeeeeeegcdefffffeeeddedgeeeeeeegcdefffffeeggfdc";
/* Jingle Bells */ 

/* Hark the Herald */ 
//#define TEMPO 250 
//#define NOTE_LENGTH 77
//static const int beats[]={2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8};
//static const char notes[]= "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf ";
/* Hark the Herald */ 

/* O come all Ye Faithful */ 
//#define TEMPO 200
//#define NOTE_LENGTH 64
//static const int beats[]={ 2,4,2,2,4,4,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,3,1,6,2,4,2,2,4,4,2,2,2,2,3,1,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,4,3,1,6,8 };
//static const char notes[]= "ggdgadbabCbaggsesgabsedd DCbCbabgasedggsgagdbbabCbabCbagsgCbagg ";
/* O come all Ye Faithful */ 



#endif /* _TurtleBotmyIRcodes_H_ */
