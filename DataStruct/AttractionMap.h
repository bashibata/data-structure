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

	//�������·��
	void output_cheapest_route(const string& from, const string& to,ostream& out);
	//�жϸ�λ���Ƿ��ܵ���
	bool is_vaild_ArcNode(const string& name);

private:
	//�ڽӱ�
	map<string, list<AVnode*>> AVList;
	//���ڴ��澰����Ϣ
	map<string, ArcNode*> Attractions;
	//���ڴ���ߵ���Ϣ
	map<string, list<VNnode*>> outgoing_service;
	//�����ļ������ڽӾ���
	void load_services(const string& filename);
	//�����ļ������ڽӱ�
	void load_services_2(const string& filename);
	//��ʼ��ͼ
	void reset();
	//���·��
	string recover_route(const string& attrction);
	//ʵ��Dijkstra�㷨
	pair<int, int> calc_route(string from,string to);
	//ת���ڽӱ��ڽӾ���
	void change();
	//��ʽ���������ͼ
	void map_out();
	//������ȱ���
	void DFSTravel(string name);
	
};


#endif // _ATTRACTION_H_

