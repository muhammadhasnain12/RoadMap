#include "Map.h"
#include <iostream>

struct Point {
   int x, y;
};

struct Line {
   Point p1, p2;
};

bool onLine(Line l1, Point p) {        //check whether p is on the line or not
   if(p.x <= std::max(l1.p1.x, l1.p2.x) && p.x <= std::min(l1.p1.x, l1.p2.x) &&
      (p.y <= std::max(l1.p1.y, l1.p2.y) && p.y <= std::min(l1.p1.y, l1.p2.y)))
         return true;

   return false;
}

int direction(Point a, Point b, Point c) {
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;           //colinear
   else if(val < 0)
      return 2;          //anti-clockwise direction
      return 1;          //clockwise direction
}

bool isIntersect(Line l1, Line l2) {
   //four direction for two lines and points of other line
   int dir1 = direction(l1.p1, l1.p2, l2.p1);
   int dir2 = direction(l1.p1, l1.p2, l2.p2);
   int dir3 = direction(l2.p1, l2.p2, l1.p1);
   int dir4 = direction(l2.p1, l2.p2, l1.p2);

   if(dir1 != dir2 && dir3 != dir4)
      return true;           //they are intersecting
   if(dir1==0 && onLine(l1, l2.p1))        //when p2 of line2 are on the line1
      return true;
   if(dir2==0 && onLine(l1, l2.p2))         //when p1 of line2 are on the line1
      return true;
   if(dir3==0 && onLine(l2, l1.p1))       //when p2 of line1 are on the line2
      return true;
   if(dir4==0 && onLine(l2, l1.p2)) //when p1 of line1 are on the line2
      return true;
   return false;
}

bool checkInside(std::vector<double> poly, int n, Point p) {
   if(n < 720)
      return false;                  //when polygon has less than 3 edge, it is not polygon
   Line exline = {p, {9999, p.y}};   //create a point at infinity, y is same as point p
   int count = 0;
   int i = 0;
   do {
      Line side{poly[i], poly[(i+1)%n]};     //forming a line from two consecutive points of poly
      if(isIntersect(side, exline)) {          //if side is intersects exline
         if(direction(side.p1, p, side.p2) == 0)
            return onLine(side, p);
         count++;
      }
      i = (i+1)%n;
   } while(i != 0);
      return count&1;             //when count is odd
}



int main()
{
	Map map;
	map.load_data_from_file("map1.json");
 	//map.show();
	//Road road();
	//std::cout<<roads_[0].get_id()<<std::endl;
	std::vector<std::vector<double>> polygon_l;
	std::vector<std::vector<double>> polygon_r;
	polygon_l = map.roads_[0].get_l_bdr_points();
	polygon_r = map.roads_[0].get_R_bdr_points();

    Point arr[polygon_l.size()];
	//std::copy(polygon.begin(), polygon.end(), arr);
	//pushing vector of vector into single vector
	std::vector<double> l_myvector;
    std::vector<double> r_myvector;

    for (int i = 0; i < polygon_l.size(); ++i)
    {
        for (int j = 0; j < polygon_l[i].size(); ++j)
        {
            l_myvector.push_back(polygon_l[i][j]);
            //std::cout<<polygon[i][j]<<std::endl;
        }
    }


    //Reverse a Right vector
    for (int i = 0; i < polygon_r.size(); i++) {
        for (
            auto it = polygon_r[i].rbegin();
            it != polygon_r[i].rend(); it++)
            r_myvector.push_back(*it);
            //l_myvector.push_back(it[i]);
            //std::cout <<it[i] << std::endl;
    }
    std::vector<double> l_r_vector;
    for (int i = 0; i < l_myvector.size(); ++i){
        l_r_vector.push_back(l_myvector[i]);
        l_r_vector.push_back(r_myvector[i]);
    }

    std::cout<<"Right vector after converting into one D and reversing = "<<r_myvector.size()<<std::endl;
    std::cout<<"Left vector after converting into one D = "<<l_myvector.size()<<std::endl;
    std::cout<<"Concatenating left and right = "<<l_r_vector.size()<<std::endl;

    Point p = {25,30};

    int n = 720;

    if(checkInside(l_r_vector, n, p))
       std::cout << "Point is inside.";
    else
       std::cout << "Point is outside.";


}
