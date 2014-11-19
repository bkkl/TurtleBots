/*

#include "IRremote.h"
#include "IRremoteTools.h"
#include <Arduino.h>

int RECV_PIN = 3; // the pin the IR receiver is connected to
IRrecv irrecv; // an instance of the IR receiver object
decode_results results; // container for received IR codes

void beginIRremote(){

	irrecv.attach(RECV_PIN); // Start the receiver
	irrecv.enableIRIn(); // Start the receiver
}

bool IRrecived(){
	return irrecv.decode(&results);
}

void resumeIRremote(){
    irrecv.resume(); // resume receiver
}

unsigned long getIRresult(){
	return results.value;

	
	*/