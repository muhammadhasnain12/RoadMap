#include "Lane.h"
Lane :: Lane(float a, float b, float c, std::vector<std::vector<double>> l, std::vector<std::vector<double>> r, std::vector<std::vector<double>> d)
{
	id = a;
	left_boundary_id = b;
	right_boundary_id = c;
	L_bdr_point = l;
    R_bdr_point = r;
	centre_point = d;
}
