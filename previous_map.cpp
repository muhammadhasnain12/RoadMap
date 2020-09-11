#include "Map.h"
#include "Lane.h"
#include "picojson.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace picojson;


void Map :: load_data_from_file(std::string file_name)
{
	// pre processing
	std::ifstream f(file_name); //taking file as inputstream
	std::string json;
	if(f)
	{
		std::ostringstream ss;
	  	ss << f.rdbuf(); // reading data
	  	json = ss.str();
	}
	picojson::value v;
	std::string err;
	picojson::parse(v, json.c_str(), json.c_str() + strlen(json.c_str()), &err);
	if (!err.empty())
	{
		std::cerr << err << std::endl;
	}
	auto all_roads = v.get("roads").get<array>();
	// Loading the map file 
	for(int i=0; i<2; i++)
	{
	  	auto all_lanes = all_roads[i].get("lanes").get<array>();
	  	std::vector<Lane> l;
    		for(int j=0; j<2; j++)
    		{
			std::vector<double> tmp_points;
			std::vector<std::vector<double>> vec;
			auto all_points = all_lanes[j].get("centre_point").get<array>();
      			for(int k=0; k<720; k++) // size_of(array of points)
      			{
				tmp_points.push_back(all_points[k].get<array>()[0].get<double>());
		  		tmp_points.push_back(all_points[k].get<array>()[1].get<double>());
		    		vec.push_back(tmp_points);
      			}
			float tid = all_lanes[j].get("id").get<double>();
			float tlb = all_lanes[j].get("left_boundary_id").get<double>();
			float trb = all_lanes[j].get("left_boundary_id").get<double>();
			std::vector<std::vector<double>> cp = vec;
			Lane lane{tid, tlb, trb, cp};
      			// fill other lane data
		 	l.push_back(lane);
		 }
		 float tid = all_roads[i].get("id").get<double>();
		 float tlb = all_roads[i].get("left_boundary_id").get<double>();
		 float trb = all_roads[i].get("right_boundary_id").get<double>();
		 std::vector<Lane> tl = l;
		 Road road{tid, tlb, trb, tl};
	   	 // fill other road data
     		 roads_.push_back(road);
	 }
}
