#pragma once
#ifndef _SERVICE_H
#define _SERVICE_H
#include<string>

using namespace std;

typedef struct VNnode
{
	//该边的花销
	int fee;
	//该边的长度
	int distance;
	//对改边的描述
	string destination;

	VNnode(string attraction, int f, int d):fee(f), distance(d), destination(attraction) {}
}VNnode; 

#endif // !_SERVICE_H
