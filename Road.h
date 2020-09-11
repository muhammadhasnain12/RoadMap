#ifndef ROAD_H
#define ROAD_H
#include <vector>
#include "Lane.h"
#include <iostream>
class Road
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
    std::vector<std::vector<double>> L_bdr_point;
	std::vector<std::vector<double>> R_bdr_point;
	std::vector<Lane> lanes;
public:
	Road(float a, float b, float c, std::vector<std::vector<double>> l, std::vector<std::vector<double>> r, std::vector<Lane> d);
	float get_id(){return id;}
	float get_left_boundary_id(){return left_boundary_id;}
	float get_right_boundary_id(){return right_boundary_id;}
	std::vector<std::vector<double>> get_l_bdr_points() { return L_bdr_point; }
	std::vector<std::vector<double>> get_R_bdr_points() { return R_bdr_point; }
	std::vector<Lane> get_lanes(){return lanes;}
    void get_road_info();
};
#endif
