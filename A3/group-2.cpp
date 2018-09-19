#include <string>
#include "group.h"

using namespace std;

group::group(string groupNameIn) {
	groupname = groupNameIn;
}
string group::getGroupName() {
	return groupname;
}

