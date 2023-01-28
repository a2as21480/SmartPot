/*
 SmartPot.cpp - Library for SmartPot
 created by Hyojun lim, 2021 December 12
 Copyright(c) All Rights Reserved
*/

#include "Arduino.h"
#include "SmartPot.h"

void led(int pin) {
	enum LED {LED_R = 5, LED_G, LED_B};
	switch(pin) {
		case LED_R:
			digitalWrite(LED_R, 1);
			digitalWrite(LED_G, 0);
			digitalWrite(LED_B, 0);
			break;
			
		case LED_G:
			digitalWrite(LED_R, 0);
			digitalWrite(LED_G, 1);
			digitalWrite(LED_B, 0);
			break;
			
		case LED_B:
			digitalWrite(LED_R, 0);
			digitalWrite(LED_G, 0);
			digitalWrite(LED_B, 1);
			break;
	};
};