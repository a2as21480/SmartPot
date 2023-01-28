/*
 Soil_Moisture.cpp - Library for Soil Moisture Sensor
 created by Hyojun lim, 2021 December 11
 Copyright(c) All Rights Reserved
 */
 
#include "Arduino.h"
#include "Soil_Moisture.h"
 
 Soil_Moisture::Soil_Moisture(uint8_t pin) {
	 pin = _pin;
 };
 
 int Soil_Moisture::read() {
	 return map(analogRead(_pin), 0, 1023, 99, 0);
 };