/*
 Soil_Moisture.h - Library for Soil Moisture Sensor
 created by Hyojun lim, 2021 December 11
 Copyright(c) All Rights Reserved
*/
 
#ifndef __Soil_Moisture_h__
#define __Soil_Moisture_h__
 
#include "Arduino.h"
 
class Soil_Moisture {
	private:
		uint8_t _pin;
	
	public:
		Soil_Moisture(uint8_t pin);
		
		int read();
};
#endif