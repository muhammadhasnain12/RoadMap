#ifndef LANE_H
#define LANE_H
#include<vector>
class Lane
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<std::vector<double>> L_bdr_point;
	std::vector<std::vector<double>> R_bdr_point;
	std::vector<std::vector<double>> centre_point;

public:
	Lane(float a, float b, float c, std::vector<std::vector<double>> l, std::vector<std::vector<double>> r, std::vector<std::vector<double>> d);
	float get_id(){return id;}
	float get_left_boundary_id(){return left_boundary_id;}
	float get_right_boundary_id(){return right_boundary_id;}
	std::vector<std::vector<double>> get_centre_point(){return centre_point;}
};
#endif
