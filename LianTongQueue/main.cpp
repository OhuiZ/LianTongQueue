#include<iostream>
#include<queue>
#include<vector>
#include"Rand.h"
#include"Customer.h"
#include"Reception.h"

using namespace std;

#define Total_Service_Time 540

static int CustomerNumber = 0;
static float CurrentTime = 0;//当前时间
static float LastCustomerArrivalTime;//上一顾客到来时间
static float CusWaitTotalTime = 0;//顾客等待时间总

vector<Customer*> CustomerVector;//顾客数组
Reception r0, r1;//两个服务台

int SelectR(float r0_time,float r1_time);
void UpdateData(int reception,int cus);

void main()
{
	Setsrand();//设置随机数种子，使每次获得的随机序列不同
	//srand((unsigned)time(NULL));
	float MeanArrialTime;//顾客平均到达时间
	float MeanServiceTime;//顾客所需平均服务时间
	cout << "请输入顾客平均到达时间：\n";
	cin >> MeanArrialTime;
	cout << "请输入顾客所需平均服务时间：\n";
	cin >> MeanServiceTime;
	float temp_arrive = 0;
	while (true)  //产生顾客
	{
		temp_arrive = CurrentTime + Possion(MeanArrialTime);
		if (temp_arrive > Total_Service_Time)
			break;

		Customer  *newCus = new Customer();
		newCus->CusNo = ++CustomerNumber;
		newCus->ArrivalTime = temp_arrive;
		newCus->NeedServiceTime = Normal_Gauss(MeanServiceTime, 1);
		CurrentTime += newCus->NeedServiceTime;

		CustomerVector.push_back(newCus);
	}

	//服务安排
	for (int i = 0; i < CustomerNumber; i++)
	{
		//选取服务台
		int s = SelectR(r0.LastEndTime, r1.LastEndTime);
		UpdateData(s,i);
	}

	cout << "服务台0：服务顾客数：" << r0.TotalCus.size() << " 空闲时间：" << r0.FreeTime << "总服务时间：" << r0.ServiceTotalTime << "\n";
	cout << "服务台1：服务顾客数：" << r1.TotalCus.size() << " 空闲时间：" << r1.FreeTime << "总服务时间：" << r1.ServiceTotalTime << "\n";
	float Rfree = r0.FreeTime + r1.FreeTime;
	float Rservice = r0.ServiceTotalTime + r1.ServiceTotalTime;
	cout << "顾客总数：" << CustomerVector.size() << endl;
	cout << "顾客平均排队时间：" << CusWaitTotalTime/CustomerNumber << endl;
	cout << "顾客平均逗留时间：" << (CusWaitTotalTime + Rservice) / CustomerNumber << endl;
	cout << "服务台利用率：" << Rservice / (Rfree + Rservice) << endl;

	//for (int i = 0; i < CustomerVector.size(); i++)
	//{
	//	cout << CustomerVector[i]->CusNo << ":到达时间：" << CustomerVector[i]->ArrivalTime << " 服务时间：" << CustomerVector[i]->NeedServiceTime;
	//	cout << "  开始时间：" << CustomerVector[i]->StartTime << "  等待时间：" << CustomerVector[i]->WaitTime << endl;
	//}

	/*Possion Test*/
	/*int p;
	for (int i = 0; i < 30; i++)
	{
		p = possion();
		printf("%d\n", p);
	}*/
	
	/*Normal_Gauss Test*/
	/*double g1 = Normal_Gauss(5,1);
	double g2 = Normal_Gauss(5,1);
	cout << g1 << endl;
	cout << g2 << endl;*/

	system("pause");
}

int SelectR(float r0_time, float r1_time)
{
	int small;
	if (r0_time == r1_time)
		small = (int)(2 * rand() / (RAND_MAX + 1.0)); //随机选择一个服务台0 / 1
	else
		small = r0_time < r1_time ? 0 : 1;//较早结束上一顾客服务的
	return small;
}

void UpdateData(int reception,int cusID)
{
	int ID = CustomerVector[cusID]->CusNo;
	float SerTime = CustomerVector[cusID]->NeedServiceTime;
	float ArriTime = CustomerVector[cusID]->ArrivalTime;

	if (reception == 0)
	{
		r0.TotalCus.push_back(ID);
		r0.ServiceTotalTime += SerTime;
		if (r0.LastEndTime <= ArriTime)
		{
			r0.FreeTime += ArriTime - r0.LastEndTime;
			r0.LastEndTime = ArriTime + SerTime;
			CustomerVector[cusID]->StartTime = ArriTime;
		}
		else
		{
			CustomerVector[cusID]->StartTime = r0.LastEndTime;
			CustomerVector[cusID]->WaitTime += r0.LastEndTime - ArriTime;
			r0.LastEndTime += SerTime;

			CusWaitTotalTime += CustomerVector[cusID]->WaitTime;
		}
	}
	else
	{
		r1.TotalCus.push_back(ID);
		r1.ServiceTotalTime += SerTime;
		if (r1.LastEndTime <= ArriTime)
		{
			r1.FreeTime += ArriTime - r1.LastEndTime;
			r1.LastEndTime = ArriTime + SerTime;
			CustomerVector[cusID]->StartTime = ArriTime;
		}
		else
		{
			CustomerVector[cusID]->StartTime = r0.LastEndTime;
			CustomerVector[cusID]->WaitTime += r0.LastEndTime - ArriTime;
			r1.LastEndTime += SerTime;

			CusWaitTotalTime += CustomerVector[cusID]->WaitTime;
		}
	}
}