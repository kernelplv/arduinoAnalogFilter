// 
// 
// 

#include "AnalogFilter.h"
#include <algorithm>

AnalogFilter::AnalogFilter(vector<int> etalon, int zero_line = 0) {

	G = etalon;
	size = G.size();
	AcceptFind = 0;
	SuccessCount = 0;
	ready = false;
	zero = zero_line;
	rmax = zero;
	rmin = zero;
	multiplier = 0;
	firstRun = false;

	for (int x : G)
	{
		if (x != 0) { AcceptFind++; }
		else { SuccessCount++; F.push_back(x);	}
	}

	fill(F.begin(), F.end(), 1);
	//G.clear();
	//vclear(G); //100% resize
}

int AnalogFilter::GetAcceptFindNow()
{
	int Result = 0;

	for (int x : G)
	{
		if (!inZeroRange(x)) Result++;
	}

	return Result;
}

int AnalogFilter::GetLiquid(vector<int> values)
{
	int Result = 0;
	int delimiter = 0;
	int sum = 0;

	for (int x : values)
	{
		if (!inZeroRange(x)) sum += x;
		else delimiter++;
	}

	delimiter = values.size() - delimiter;

	if (delimiter == 0) delimiter = 1;

	Result = sum / (delimiter);

	return Result;
}
bool AnalogFilter::GCalculate()
{
	for (int i = 0; i<size; i++)
	{
		if ((!inZeroRange(A[i])) || (!inZeroRange(B[i]))) G[i]=1;
		else G[i] = 0;
	}
	return true;
}

bool AnalogFilter::RangeCalculate(int val, int mul = 0)
{
	if (!firstRun) { rmin = val; firstRun = true; }
	if (mul == 0) multiplier = 1;
	else multiplier = mul;
	
	int trange = 0;

	if (val > rmax) rmax = val;
	else if (val < rmin) rmin = val;

	if (abs(rmax) > abs(rmin)) trange = abs(rmax);
	else trange = abs(rmin);

	zero = (rmax + rmin) / 2;
	range = (trange - zero) * multiplier;

	//cout << "min-max" << rmin << "-" << rmax << endl;
	//cout << "MAXorMIN-" << trange << endl;
	//cout << "zero-" << zero << endl;
	//cout << "range-" << range << endl;

	return true;
}
bool AnalogFilter::inZeroRange(int val)
{
	if ((val >= zero - range) && (val <= zero + range)) return true;
	else return false;
}
int AnalogFilter::GetRange()
{
	return range;
}
int AnalogFilter::GetZero()
{
	return zero;
}
void AnalogFilter::RangeReset()
{
	firstRun = false;

	RangeCalculate(A[size - 1], multiplier);
	RangeCalculate(A[size - 1], multiplier);
	RangeCalculate(A[size - 1], multiplier);
}
bool AnalogFilter::ZeroShifted()
{
	int sum = 0;

	for (int t = 0; t < size; t++)
	{
		sum += A[t]+B[t];
	}

	sum = sum / ( size * 2 ); //two buffer arrays

	if ((sum < rmin) || (sum > rmax)) 
	{ 
		//cout << "out of range" << endl;  
		return true; 
	}
	else 
	{ 
		//cout << "normal state" << endl; 
		return false; 
	}

}

int AnalogFilter::In(int val)
{
	int sum = 0;
	int bpos = 0;				//Начало найденной последовательности единиц
	int epos = 0;
	int oneLiquid = 0;
	int twoLiquid = 0;
	int Result = 0;
	vector<int>::iterator itb;

	if (A.size() < size)
	{
		A.push_back(val); 
	}
	else if (B.size() < size)
	{
		B.push_back(val);
	}
	else
	{
		ready = true; 
		// Вычисление поисковой строки
		GCalculate();

		if (GetAcceptFindNow() >= AcceptFind)
		{// в поисковой строке найдено необходимое кол-во единиц

			//поиск минимальной последовательности
			itb = search(G.begin(), G.end(), F.begin(), F.end());

			
			if (itb != G.end())
			{//минимальная последовательность найдена

				bpos = itb - G.begin();    
				epos = bpos + SuccessCount;

				oneLiquid = GetLiquid(vector<int>(A.begin() + bpos, A.begin() + epos));
				twoLiquid = GetLiquid(vector<int>(B.begin() + bpos, B.begin() + epos));

				/* Если изменить направление сравнения, фильтр будет округлять данные
				   в меньшую сторону. */
				if (oneLiquid > twoLiquid) Result = oneLiquid;
				else if (oneLiquid < twoLiquid) Result = twoLiquid;
				else Result = 0;

			}
			else
			{
				//not found
				Result = 0; 
			}
		}

		A.erase(A.begin()); A.push_back(val);
		B.erase(B.begin()); //
		//G.erase(G.begin()); 
		//cout << "result " << size << endl;
		//if (ZeroShifted()) RangeReset();
		return Result;
	}
}