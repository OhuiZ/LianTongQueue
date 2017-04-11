#include"Customer.h"
#include"Rand.h"

Customer::Customer()
{	
    CusNo = 0;
	ArrivalTime = 0;
	WaitTime = 0;
	StartTime = -1;
    NeedServiceTime = -1;
}
Customer::~Customer()
{

}