// DataStruct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

using namespace std;

int main(int argc, char* argv[]) {

	try {

		//AttractionMap rs("services.txt");
		AttractionMap rs("test.txt");
		/*
		
		*/
		while (true) {

			cerr << "\n\nEnter a start and destination city:  ('quit' to exit)\n";

			string from, to;
			cin >> from;
			if (from == "quit") break;
			cin >> to;

			if (rs.is_vaild_ArcNode(from) && rs.is_vaild_ArcNode(to)) {
				rs.output_cheapest_route(from, to, cout);
			}
			else {
				cout << "Please enter valid cities\n\n";
			}

		}

		return EXIT_SUCCESS;

	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown exception caught\n";
	}

	return EXIT_FAILURE;
}

