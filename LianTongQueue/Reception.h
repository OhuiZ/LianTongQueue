#pragma once
#include<vector>
using namespace std;

class Reception
{
public:
	Reception();
	~Reception();
	float LastEndTime;//������һ�˿ͽ���ʱ��
	vector<int>TotalCus;//�ѷ���Ŀͻ����
	float ServiceTotalTime;//������ʱ��
	float FreeTime;//����ʱ��
};

