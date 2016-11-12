#include "AttractionMap.h"
#include"stdafx.h"

void AttractionMap::reset() {
	for (map<string, ArcNode*>::iterator it = Attractions.begin(); it != Attractions.end(); it++) 
	{
		it->second->total_distance = INT_MAX;
		it->second->total_fee = INT_MAX;
		it->second->from_ArcNode = "";
		it->second->visited = false;
	}
}

string AttractionMap::recover_route(const string & attrction)
{
	string back = attrction;
	string to = attrction;
	while ((back = Attractions.find(back)->second->from_ArcNode) != "")
	{
		to = back + " to " + to;
	}
	return to;
}

pair<int, int> AttractionMap::calc_route(string from, string to)
{
	priority_queue<ArcNode*, vector<ArcNode*>, Cheapest> candidates;
	ArcNode* arcnode = Attractions[from];
	arcnode->total_fee = 0;
	arcnode->total_distance = 0;
	candidates.push(arcnode);
	while (!candidates.empty()) {
		while ((arcnode = candidates.top())->visited)
			candidates.pop();
		arcnode->visited = true;
		candidates.pop();
		list<VNnode*> service_list = outgoing_service[arcnode->name];
		for (VNnode* service; !service_list.empty(); service_list.pop_front()) {
			//cout << service_list.front()->destination << endl;
			service = service_list.front();
				if ((Attractions[service->destination])->total_fee > (arcnode->total_fee + service->fee)) {
					Attractions[service->destination]->total_fee = arcnode->total_fee + service->fee;
					Attractions[service->destination]->from_ArcNode = arcnode->name;
					Attractions[service->destination]->total_distance = arcnode->total_distance + service->distance;
					candidates.push(Attractions[service->destination]);
			}
			
		}
	}

	// Return the total fee and total distance.
	// Return (INT_MAX, INT_MAX) if not path is found.
	if (Attractions[to]->visited) {
		return pair<int, int>(Attractions[to]->total_fee, Attractions[to]->total_distance);
	}
	else {
		return pair<int, int>(INT_MAX, INT_MAX);
	}
	
	return pair<int, int>();
}
void AttractionMap::change()
{
	map<string, list<AVnode*>>::iterator AV_it;
	map<string, ArcNode*>::iterator Arc_it;
	map<string, list<VNnode*>>::iterator VN_it;
	AV_it = AVList.begin();
	for (; AV_it != AVList.end(); AV_it++)
	{
		string name = AV_it->first;
		Attractions.insert(pair<string,ArcNode*>(name,new ArcNode(name)));
		list<VNnode*> lvn;
		list<AVnode*> lav = AV_it->second;
		for (list<AVnode*>::iterator it = lav.begin(); it != lav.end(); it++)
		{
			lvn.push_front((*it)->vnnode);
		}
		outgoing_service.insert(pair <string,list<VNnode*>>(name,lvn));
	}
	cout << "mission complete" << endl;
}
void AttractionMap::map_out()
{
	map<string, ArcNode*>::iterator it1 = Attractions.begin();
	map<string, list<VNnode*>>::iterator it2 = outgoing_service.begin();
	list<VNnode*>::iterator it3;
	list<VNnode*> ls;
	cout << "  ";
	for (; it1 != Attractions.end(); it1++)
		cout << it1->first << " ";
	cout << endl;
	for (; it2 != outgoing_service.end(); it2++)
	{
		cout << it2->first;
		ls = it2->second;
		it1 = Attractions.begin();
		for (; it1 != Attractions.end(); it1++)
		{
			if (it1->first==it2->first)
			{
				cout << "0 ";
			}
			for (it3 = ls.begin(); it3 != ls.end(); it3++)
			{
				if ((*it3)->destination == it1->first)
					cout << (*it3)->distance << " ";

			}
			cout << "no ";
		}
		cout << endl;
	}
	
}
void AttractionMap::DFSTravel(string name)
{
	
	if ((Attractions.find(name))->second->visited)
	{	
		return;
	}
	cout << name << endl;
	(Attractions.find(name))->second->visited = true;
	list<VNnode*> ls;
	list<VNnode*>::iterator it;
	ls = outgoing_service.find(name)->second;
	for ( it = ls.begin(); it != ls.end(); it++)
	{
		if (!Attractions.find((*it)->destination)->second->visited)
		{
			DFSTravel((*it)->destination);
		}
	}
	
	
}
;

AttractionMap::AttractionMap(string const &filename)
{
	//load_services_2(filename);
	load_services(filename);
	change();
	map_out();
	DFSTravel("±±ÃÅ");
}

void AttractionMap::load_services(string const &filename)
{
	ifstream inf(filename.c_str());
	string from, to;
	int fee, distance;

	while (inf.good())
	{
		inf >> from >> to >> fee >> distance;
		if (inf.good()) 
		{
			map<string, list<VNnode*> >::iterator mp = outgoing_service.find(from);
			if (mp == outgoing_service.end()) {
				list<VNnode*> ls;
				ls.push_front(new VNnode(to, fee, distance));
				outgoing_service.insert(pair<string, list<VNnode*>>(from, ls));
				Attractions.insert(pair<string, ArcNode*>(from, new ArcNode(from)));
			}
			else
				(mp->second).push_front(new VNnode(to, fee, distance));
		}
	}

	inf.close();
}

void AttractionMap::load_services_2(const string & filename)
{
	ifstream inf(filename.c_str());
	string from, to;
	int fee, distance;
	while (inf.good())
	{
		inf >> from >> to >> fee >> distance;
		if (inf.good())
		{
			map<string, list<AVnode*> >::iterator mp = AVList.find(from);
			if (mp == AVList.end())
			{
				list<AVnode*> ls;
				ArcNode* AN = new ArcNode(from);
				VNnode* VN = new VNnode(to, fee, distance);
				AVnode* AV = new AVnode(AN, VN);
				ls.push_front(AV);
				AVList.insert(pair<string, list<AVnode*>>(from, ls));
			}
			else
			{
				ArcNode* AN = new ArcNode(from);
				VNnode* VN = new VNnode(to, fee, distance);
				AVnode* AV = new AVnode(AN, VN);
				mp->second.push_front(AV);
			}
		}
	}

	inf.close();
}

AttractionMap::~AttractionMap() 
{
	Attractions.clear();
	outgoing_service.clear();
}

void AttractionMap::output_cheapest_route(const string & from, const string & to, ostream & out)
{
	reset();
	pair<int, int> totals = calc_route(from, to);

	if (totals.first == INT_MAX) {
		out << "There is no route from " << from << " to " << to << "\n";
	}
	else {
		out << "The cheapest route from " << from << " to " << to << "\n";
		out << "costs " << totals.first << " euros and spans " << totals.second
			<< " kilometers\n";
		cout << recover_route(to) << "\n\n";
	}
}

bool AttractionMap::is_vaild_ArcNode(const string & name)
{
	return Attractions.count(name) == 1;
}

