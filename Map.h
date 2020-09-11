#include "Road.h"
#include <vector>
#include <string>
class Map
{
  //std::vector<Road> roads_;
public:
    std::vector<Road> roads_;
	void load_data_from_file(std::string file_name);
};

