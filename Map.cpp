#include "Map.h"
#include "Lane.h"
#include "Road.h"
#include "picojson.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace picojson;
void Map :: load_data_from_file(std::string file_name)
{
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
	for(int i=0; i<2; i++)	// Loading the map file
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
			//Getting Line Left Boundary Points
			std::vector<double> L_bdr_points;
			std::vector<std::vector<double>> L_bdr_vec;
			auto left_points = all_lanes[j].get("left_boundary_points").get<array>();
      			for(int k=0; k<720; k++) // size_of(array of points)
      			{
                    L_bdr_points.push_back(left_points[k].get<array>()[0].get<double>());
                    L_bdr_points.push_back(left_points[k].get<array>()[1].get<double>());
                    L_bdr_vec.push_back(L_bdr_points);
      			}

      		std::vector<double> R_bdr_points; //GettingLine Right Boundary Points
			std::vector<std::vector<double>> R_bdr_vec;
			auto right_points = all_lanes[j].get("left_boundary_points").get<array>();
      			for(int k=0; k<720; k++) // size_of(array of points)
      			{
                    R_bdr_points.push_back(right_points[k].get<array>()[0].get<double>());
                    R_bdr_points.push_back(right_points[k].get<array>()[1].get<double>());
                    R_bdr_vec.push_back(R_bdr_points);
      			}
            std::vector<std::vector<double>> cp = vec;
			Lane lane{tid, tlb, trb, cp, L_bdr_vec, R_bdr_vec };
            l.push_back(lane);
		     }
             float tid = all_roads[i].get("id").get<double>(); //Loading Road data
             float tlb = all_roads[i].get("left_boundary_id").get<double>();
             float trb = all_roads[i].get("right_boundary_id").get<double>();
             std::vector<double> L_bdr_points; //Getting Road Left Boundary Points
			 std::vector<std::vector<double>> L_bdr_vec;
			 auto left_points = all_lanes[i].get("left_boundary_points").get<array>();
      			for(int k=0; k<720; k++) // size_of(array of points)
      			{
                    L_bdr_points.push_back(left_points[k].get<array>()[0].get<double>());
                    L_bdr_points.push_back(left_points[k].get<array>()[1].get<double>());
                    L_bdr_vec.push_back(L_bdr_points);
      			}

             std::vector<double> R_bdr_points; //Getting Road Right Boundary Points
             std::vector<std::vector<double>> R_bdr_vec;
             auto right_points = all_lanes[i].get("left_boundary_points").get<array>();
      			for(int k=0; k<720; k++) // size_of(array of points)
      			{
                    R_bdr_points.push_back(right_points[k].get<array>()[0].get<double>());
                    R_bdr_points.push_back(right_points[k].get<array>()[1].get<double>());
                    R_bdr_vec.push_back(R_bdr_points);
      			}

          std::vector<Lane> tl = l;
          Road road{tid, tlb, trb, L_bdr_vec, R_bdr_vec, tl, };
          roads_.push_back(road);
	 }
}
