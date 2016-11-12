#pragma once
#include<string>
#include"Service.h"
#ifndef _ARCNODE_H
#define _ARCNODE_H

using namespace std;
//景点结构体
typedef struct ArcNode
{
	string name;
	bool visited;
	//到达该节点的总花费
	int total_fee;
	//到达该节点的总距离
	int total_distance;
	//路线上的上一个节点
	string from_ArcNode;
	ArcNode() : name(""), visited(false), total_fee(0), total_distance(0), from_ArcNode("") {};
	ArcNode(string const &s) :name(s), visited(false), total_fee(0), total_distance(0), from_ArcNode("") {};
}ArcNode;


typedef struct AVnode
{
	ArcNode* arcnode;
	VNnode* vnnode;
	AVnode(ArcNode* arc, VNnode* vn) :arcnode(arc), vnnode(vn) {};
}AVnode;
#endif // !_ARCNODE_H

// _ARCNODE_H

