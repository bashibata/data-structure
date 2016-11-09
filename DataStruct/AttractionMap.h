#pragma once
#ifndef _ATTRACTION_H_
#define _ATTRACTION_H_
#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<string>
#include<map>
#include<queue>

#include "Service.h"
#include "Attraction.h"
#include"stdafx.h"

using namespace std;

class Cheapest
{
public:
	Cheapest() {};
	bool operator()(ArcNode* attraction1,ArcNode* attraction2){
		return attraction1->total_fee > attraction2->total_fee;
		
	}
private:

};

class AttractionMap
{
public:
	AttractionMap(const string& filename);
	~AttractionMap(void);

	//计算最佳路线
	void output_cheapest_route(const string& from, const string& to,ostream& out);
	//判断该位置是否能到达
	bool is_vaild_ArcNode(const string& name);

private:
	//用于储存景点信息
	map<string, ArcNode*> Attractions;
	//用于储存边的信息
	map<string, list<VNnode*>> outgoing_service;
	//载入文件
	void load_services(const string& filename);
	//初始化图
	void reset();
	//输出路线
	string recover_route(const string& attrction);
	//实现Dijkstra算法
	pair<int, int> calc_route(string from,string to);
};


#endif // _ATTRACTION_H_

