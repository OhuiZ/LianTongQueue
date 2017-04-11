#include<iostream>
#include<queue>
#include<vector>
#include"Rand.h"
#include"Customer.h"
#include"Reception.h"

using namespace std;

#define Total_Service_Time 540

static int CustomerNumber = 0;
static float CurrentTime = 0;//��ǰʱ��
static float LastCustomerArrivalTime;//��һ�˿͵���ʱ��
static float CusWaitTotalTime = 0;//�˿͵ȴ�ʱ����

vector<Customer*> CustomerVector;//�˿�����
Reception r0, r1;//��������̨

int SelectR(float r0_time,float r1_time);
void UpdateData(int reception,int cus);

void main()
{
	Setsrand();//������������ӣ�ʹÿ�λ�õ�������в�ͬ
	//srand((unsigned)time(NULL));
	float MeanArrialTime;//�˿�ƽ������ʱ��
	float MeanServiceTime;//�˿�����ƽ������ʱ��
	cout << "������˿�ƽ������ʱ�䣺\n";
	cin >> MeanArrialTime;
	cout << "������˿�����ƽ������ʱ�䣺\n";
	cin >> MeanServiceTime;
	float temp_arrive = 0;
	while (true)  //�����˿�
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

	//������
	for (int i = 0; i < CustomerNumber; i++)
	{
		//ѡȡ����̨
		int s = SelectR(r0.LastEndTime, r1.LastEndTime);
		UpdateData(s,i);
	}

	cout << "����̨0������˿�����" << r0.TotalCus.size() << " ����ʱ�䣺" << r0.FreeTime << "�ܷ���ʱ�䣺" << r0.ServiceTotalTime << "\n";
	cout << "����̨1������˿�����" << r1.TotalCus.size() << " ����ʱ�䣺" << r1.FreeTime << "�ܷ���ʱ�䣺" << r1.ServiceTotalTime << "\n";
	float Rfree = r0.FreeTime + r1.FreeTime;
	float Rservice = r0.ServiceTotalTime + r1.ServiceTotalTime;
	cout << "�˿�������" << CustomerVector.size() << endl;
	cout << "�˿�ƽ���Ŷ�ʱ�䣺" << CusWaitTotalTime/CustomerNumber << endl;
	cout << "�˿�ƽ������ʱ�䣺" << (CusWaitTotalTime + Rservice) / CustomerNumber << endl;
	cout << "����̨�����ʣ�" << Rservice / (Rfree + Rservice) << endl;

	//for (int i = 0; i < CustomerVector.size(); i++)
	//{
	//	cout << CustomerVector[i]->CusNo << ":����ʱ�䣺" << CustomerVector[i]->ArrivalTime << " ����ʱ�䣺" << CustomerVector[i]->NeedServiceTime;
	//	cout << "  ��ʼʱ�䣺" << CustomerVector[i]->StartTime << "  �ȴ�ʱ�䣺" << CustomerVector[i]->WaitTime << endl;
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
		small = (int)(2 * rand() / (RAND_MAX + 1.0)); //���ѡ��һ������̨0 / 1
	else
		small = r0_time < r1_time ? 0 : 1;//���������һ�˿ͷ����
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