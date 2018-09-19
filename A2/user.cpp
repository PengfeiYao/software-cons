#include <string>
#include "user.h"

using namespace std;

user::user(string userNameIn) {
	username = userNameIn;
}
string user::getUsername() {
	return username;
}
