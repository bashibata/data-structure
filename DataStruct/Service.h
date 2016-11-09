#pragma once
#ifndef _SERVICE_H
#define _SERVICE_H
#include<string>

using namespace std;

typedef struct VNnode
{
	//�ñߵĻ���
	int fee;
	//�ñߵĳ���
	int distance;
	//�Ըıߵ�����
	string destination;

	VNnode(string attraction, int f, int d):fee(f), distance(d), destination(attraction) {}
}VNnode; 

#endif // !_SERVICE_H
