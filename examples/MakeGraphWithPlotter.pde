/*
 Name:		AnalogFilter_0_1.ino
 Created:	18.06.2017 22:31:18
 Author:	kerne
*/

// the setup function runs once when you press reset or power the board
#include "AnalogFilter.h"
#include <ArduinoSTL.h>

AnalogFilter AF({ 1,1,1,1,1,1,0,0,0,0 });

void setup() {
	Serial.begin(9600);
}


int rowValues = 0;
int flrValues = 0;

void loop() {

	rowValues = analogRead(A0);
	flrValues = AF.In(analogRead(A0));

	Serial.println("$");
	Serial.println(rowValues);
	Serial.println(" ");
	Serial.println(flrValues);
	Serial.println(";");
}

0 1 0 0 1 5 0 0 0
0 0 6 0 3 1 1 2 1
0 1 1 0 1 1 1 1 1    7 из 9. Проверка разрешена
					 Посл-ть найдена на [4, 6]
					 6/2 или 5/3  -> 3
					 
1 0 0 1 5 0 0 0 1
0 6 0 3 1 1 2 1 0
1 1 0 1 1 1 1 1 1    8 из 9. Проверка разрешена
					 Посл-ть найдена на [3, 5]
					 6/2 или 5/3  -> 3
					 
0 0 1 5 0 0 0 1 0
6 0 3 1 1 2 1 0 1
1 0 1 1 1 1 1 1 1    8 из 9. Проверка разрешена
					 Посл-ть найдена на [2, 5]
					 6/2 или 5/3  -> 3
					 
0 1 5 0 0 0 1 0 2
0 3 1 1 2 1 0 1 2
0 1 1 1 1 1 1 1 1    8 из 9. Проверка разрешена
					 Посл-ть найдена на [1, 4]
					 6/2 или 5/3  -> 3
					 
1 5 0 0 0 1 0 2 3
3 1 1 2 1 0 1 2 0
1 1 1 1 1 1 1 1 1    9 из 9. Проверка разрешена
					 Посл-ть найдена на [0, 3]
					 6/2 или 5/3  -> 3				

5 0 0 0 1 0 2 3 0
1 1 2 1 0 1 2 0 0
1 1 1 1 1 1 1 1 0    8 из 9. Проверка разрешена
					 Посл-ть найдена на [0, 3]
					 5/1 или 4/3  -> 5
					 
Было : 0 1 0 0 1 5 0 0 0 0 0 6 0 3 1 1 2 1 1 0 0 1 2 2 3 0 0  
Есть : 0 3 0 3 0 3 0 3 0 5 0 1 0 1 0                          {1,1,1,1,1,1,0,0,0}
     : 0 3 0 3 0 3 0 3 0 5 0 0 0							  {1,1,1,1,1,1,0,0,0,0}
	 : 0 3 0 3 0 3 0 3 0 0 0 0 0							  {1,1,1,1,1,0,0,0,0,0}

0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0

0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1

0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 1 1

0 0 0 0 0 0 1 0 2
0 0 0 0 0 0 0 1 2
0 0 0 0 0 0 1 1 1

Было : 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 2 2 3 0 0
Есть : 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 							{1,1,1,1,1,1,0,0,0}

Комментарий:
В данном случае поток полезных данных слишком неплотный,
поэтому данные в конце последовательности воспринимаются
как помехи.

Изменим шаблон фильтра:

Было : 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 2 2 3 0 0
Есть : 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0					{1,1,1,1,0,0,0}

