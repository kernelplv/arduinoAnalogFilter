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

/*	�������� � �������� ���������� ���������� �������. ���������� ����� �������,
	�� ��������� ��������, �� ����������� �������� ����������. � ��������,
	�������� ����� �������, �� ����������� ��������, �� ������� ��������.

	������ ������ �� ���������� ������, � �������� ������.
	
	AnalogFilter({0,1,1,1}); �� ������ ������ ������ 4.

	����� ������� ����������� ��� ����� ������� ������ ������ � ��������� � ������,
	����� ����� �������� ������ ����� ��������� �������������.

	��� ������ ������, ��� ������� ������ ���� ������������������ �������� ������
	(���: ��� ����� ������ ����� ��� ������ �������� � ������)
	��� ������ �����,  ��� ������� ������ ���� ������ � ������������������

	��������� ��������������� � ������ ������������� ��������� �������. ���������
	��������� ����������� �������� ��������� ����������� �� ����.

	RangeCalculate(AnalogInput, 3) - ������������ ��������� � ���������� 3
	RangeCalculate(AnalogInput) - ���������� ���������. ��������� ��-��������� = 1
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
	int AcceptFind;		 //����������� ���-�� ������ ��� ������ ������ ����� ������
	int SuccessCount;	 //����������� ����� ������������������ ������ � ��������� ������
	int zero;            //������� �������
	int range;			 //�������� �������� ������
	int rmax;			 //������������ ������� ���������	
	int rmin;			 //����������� ������� ���������
	int multiplier;      //��������� ���������. ����������� �������� ���� � ��� �������.
	
	
	int GetAcceptFindNow();
	int GetLiquid(vector<int> values);
	bool GCalculate();
	bool inZeroRange(int val);
	bool ZeroShifted();
	

	bool firstRun;

public:
	bool ready;  //����� ������� ��������, ���������� �������� ����� ��������� �� �������������


	AnalogFilter(vector<int> etalon, int zero_line = 0); //constructor

	int In(int val);
	int GetRange();
	int GetZero();

	bool RangeCalculate(int val, int mul = 0); //���������� ��������� ����. ��� ���� ���������, ��� ������ ��������.
	void RangeReset();
};
