#include "AttractionMap.h"
#include"stdafx.h"

void AttractionMap::reset() {
	for (map<string, ArcNode*>::iterator it = Attractions.begin(); it != Attractions.end(); it++) 
	{
		it->second->total_distance = INT_MAX;
		it->second->total_fee = INT_MAX;
		it->second->from_ArcNode = "";
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
			service = service_list.front();
			if (Attractions[service->destination]->total_fee>(arcnode->total_fee + service->fee)) {
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
};

AttractionMap::AttractionMap(string const &filename)
{
	load_services(filename);
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

