// AnalogFilter.h

#ifndef _ANALOGFILTER_h
#define _ANALOGFILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#include <ArduinoSTL.h>
#include <vector>

#define vclear(vctr) vector<int>().swap(vctr)

/*	Скорость и качество фильтрации неразрывно связаны. Увеличивая буфер фильтра,
	мы уменьшаем скорость, но увеличиваем качество фильтрации. И наоборот,
	уменьшая буфер фильтра, мы увеличиваем скорость, но снижаем качество.

	Данный фильтр не сглаживает данные, а отсекает лишние.
	
	AnalogFilter({0,1,1,1}); Мы задаем размер буфера 4.

	Буфер следует увеличивать при очень плотном потоке данных и уменьшать в случае,
	когда поток ПОЛЕЗНЫХ данных имеет некоторую прерывистость.

	Чем больше единиц, тем длиннее должна быть последовательность полезных данных
	(или: как много данных нужно для начала проверки в буфере)
	Чем больше нулей,  тем плотнее должны идти данные в последовательности

	Множитель устанавливается в случае нестабильного положения датчика. Изменение
	множителя увеличивает диапазон колебаний принимаемых за нуль.

	RangeCalculate(AnalogInput, 3) - нестабильное положение с множителем 3
	RangeCalculate(AnalogInput) - стабильное положение. Множитель по-умолчанию = 1
*/

using namespace std;

class AnalogFilter
{
private:
	vector<int> G;		
	vector<int> A;		
	vector<int> B;
	vector<int> F;		
	int size;
	int AcceptFind;		 //Необходимое кол-во единиц для начала поиска среди данных
	int SuccessCount;	 //Необходимая длина последовательности единиц в поисковой строке
	int zero;            //Нулевой уровень
	int range;			 //Диапазон нулевого уровня
	int rmax;			 //Максимальная граница диапазона	
	int rmin;			 //Минимальная граница диапазона
	int multiplier;      //Множитель перепадов. Увеличиваем диапазон нуля в обе стороны.
	
	
	int GetAcceptFindNow();
	int GetLiquid(vector<int> values);
	bool GCalculate();
	bool inZeroRange(int val);
	bool ZeroShifted();
	

	bool firstRun;

public:
	bool ready;  //Буфер фильтра заполнен, выдаваемые значения можно принимать за фильтрованные


	AnalogFilter(vector<int> etalon, int zero_line = 0); //constructor

	int In(int val);
	int GetRange();
	int GetZero();

	bool RangeCalculate(int val, int mul = 0); //Калибровка диапазона нуля. Чем чаще повторена, тем точнее диапазон.
	void RangeReset();
};
