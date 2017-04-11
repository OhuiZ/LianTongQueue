#include<iostream>
#include<time.h>
#include<stdlib.h>

void Setsrand()
{
	srand((unsigned)time(NULL));
}

//double U_Random()
//{
//	double f=(double)(1 * rand() / (RAND_MAX + 1.0));
//	return f;
//}

float Possion(float Lambda)
{
	int  k = 0;
	long double p = 1.0;
	long double l = exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/

	while (p >= l)
	{
		double u = (double)(1 * rand() / (RAND_MAX + 1.0));
		p *= u;
		k++;
	}
	return k - 1 + (double)(1 * rand() / (RAND_MAX + 1.0));

	/*int i = 0;
	double p = exp(-15.0f);
	double f1 = 0, f2, u;
	u = U_Random();
	while (true)
	{
		p = p * 15 / (i + 1);
		f2 = p + f1;
		i++;
		if (f1 <= u && u<f2)
			break;
		f1 = f2;
	}
	return i;*/
}

double Normal_Gauss(double mean, double stdc)
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if (phase == 0) 
	{
		do 
		{
			double U1 = (double)(1 * rand() / (RAND_MAX + 1.0));
			double U2 = (double)(1 * rand() / (RAND_MAX + 1.0));

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return mean + X*stdc;
}

