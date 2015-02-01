/*
 * TurtleBotmyIRcodes.h - Library for easy control of an Arduino Uno powered
 * Parallax BoE (Board of Education) robot.
 *
 * License:  Released into the public domain.
 * Authors:
 *   AD: Brad Lane
 * Change Log:
 *   2014-09-07 AD:  Conceptualized and initiated.
 */
#ifndef _TurtleBotmyIRcodes_H_
#define _TurtleBotmyIRcodes_H_

/* define default GPIO pins and functions */
/* undefined pins can be set-up in Arduino or Arudublock programs */

#define IRINPUTPIN 3 // pin used for IR receiver 

/* define which GPIO pins will be controlled by IR remote control */ 
/* by default button numbers are assigned to respect GPIO pin, but this can be changed. */
/* for example remote button_5 could turn on GPIO pin 2 by changing "#define button_5_GPIO 2" */ 


//#define button_0_GPIO 0	 				// unassigned 
//#define button_1_GPIO 1				    // unassigned 
//#define button_2_GPIO 2				    // unassigned 
//#define button_3_GPIO 3				    // unassigned 
//#define button_4_GPIO 4					// unassigned 
#define button_5_GPIO 5					// change state to HIGH on GPIO - 5 by default  
#define button_6_GPIO 6					// change state to HIGH on GPIO - 6 by default
#define button_7_GPIO 7					// LOW to HIGH pulse on GPIO - 7 by default 
//#define button_8_GPIO 8					// unassigned 
//#define button_9_GPIO 9				    // unassigned 
#define LED6IR								// flashes LED connected to GPIO6 to confirm IR receive is working. must also "#define button_6_GPIO 6"	- debug only	

/***** enter learned remote codes here from your remote *******/
/***** to learn IR codes run run any_remote sketch ***********/

#define right_button 3692585004 		// turn robot right - 1st IR code 
#define left_button 2507695210 			// turn robot left - 1st IR code 
#define down_button 1511671869 			// robot backward - 1st IR code 
#define select_button 3409756287 		// unassigned 
#define stop_button 3596197704 			// detach servo's (any mode)
#define play_button 825596396			// attach servo's (any mode)
#define pwr_button 4105841032			// unassigned 
#define up_button 741245183				// robot forward - 1st IR code 
//#define up_button 4294967295
#define pause_button 3642939240			// pause Ardublocks execution (invokes IR override mode)
#define ffwd_button 1726574660			// spin robot clockwise
#define rrwd_button 4277157420			// spin robot counter clockwise
#define button_0 1851193636				// unassigned 
#define button_1 2464125561				// unassigned 
#define button_2 2278412527				// unassigned 
#define button_3 930645859				// unassigned 
#define button_4 2769913147				// unassigned 
#define button_5 1558024125				// change state to HIGH on GPIO - 5 by default  
#define button_6 4382025 				// change state to HIGH on GPIO - 6 by default
#define button_7 834338975 				// LOW to HIGH pulse on GPIO - 7 by default 
#define button_8 356487335 				// change state to LOW on GPIO - 5 by default 
#define button_9 1752348172 			// change state to LOW on GPIO - 6 by default 

/* for IR control - BL */	


#endif /* _TurtleBotmyIRcodes_H_ */
