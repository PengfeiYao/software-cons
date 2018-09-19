#ifndef GROUP_H
#define GROUP_H


#include <iostream>
#include <string>
#include <vector>

class group {
public:
	group(std::string groupNameIn);
	std::string getGroupName();
	bool hasSameGroup(std::string groupNameIn);
	std::string groupname;
};
#endif
