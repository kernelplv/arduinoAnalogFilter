/*
 Name:		AnalogFilter_0_1.ino
 Created:	18.06.2017 22:31:18
 Author:	kerne
*/

// the setup function runs once when you press reset or power the board
#include "AnalogFilter.h"
#include <ArduinoSTL.h>

AnalogFilter AF = AnalogFilter({ 1,1,1,0,0,0,0});

int rowValues = 0;
static int flrValues;

void setup() {

	int t = 15;

	Serial.begin(9600);

	//Serial.println("Test started!");
	//Serial.println("Range test...");
	delay(2000);

	while (t--)
	{
		AF.RangeCalculate(analogRead(A3),3);

		Serial.println("$");
		Serial.print(analogRead(A3));
		Serial.print(" ");
		Serial.print(AF.GetZero() + AF.GetRange());
		Serial.print(" ");
		Serial.print(AF.GetZero() - AF.GetRange());
		Serial.println(";");

		delay(500);
	}

	//Serial.print("Нулевая зона: ");  Serial.println(AF.GetZero());
	//Serial.print("Диапазон нуля: "); Serial.println(AF.GetRange());
	//Serial.print("Точка отсчета: "); Serial.println(AF.GetRange()+AF.GetZero());
	//pinMode(A3, INPUT);
}


void loop() {

	rowValues = analogRead(A3);

	//if (AF.ready == true)
	//{
	//cout << AF.In(analogRead(A3)) << endl;
	//AF.RangeCalculate(analogRead(A3), 4);
	
	Serial.println("$");
	Serial.print(rowValues);
	Serial.print(" ");
	Serial.print(AF.GetZero()+AF.GetRange());
	Serial.print(" ");
	Serial.print(AF.In(analogRead(A3)));
	Serial.println(";");

	//}
	//else AF.In(0);

	delay(100);
}
