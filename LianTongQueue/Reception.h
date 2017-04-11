#pragma once
#include<vector>
using namespace std;

class Reception
{
public:
	Reception();
	~Reception();
	float LastEndTime;//服务上一顾客结束时间
	vector<int>TotalCus;//已服务的客户编号
	float ServiceTotalTime;//服务总时间
	float FreeTime;//空闲时间
};

