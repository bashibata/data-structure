#pragma once
#include<string>
#include"Service.h"
#ifndef _ARCNODE_H
#define _ARCNODE_H

using namespace std;
//����ṹ��
typedef struct ArcNode
{
	string name;
	bool visited;
	//����ýڵ���ܻ���
	int total_fee;
	//����ýڵ���ܾ���
	int total_distance;
	//·���ϵ���һ���ڵ�
	string from_ArcNode;
	ArcNode() : name(""), visited(false), total_fee(0), total_distance(0), from_ArcNode("") {};
	ArcNode(string const &s) :name(s), visited(false), total_fee(0), total_distance(0), from_ArcNode("") {};
}ArcNode;


typedef struct Attraction
{
	ArcNode arcnode;
	VNnode vnnode;
	Attraction(ArcNode arc, VNnode vn) :arcnode(arc), vnnode(vn) {};
}Atrraction;
#endif // !_ARCNODE_H

// _ARCNODE_H

