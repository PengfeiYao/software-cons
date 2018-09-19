/*
 * LAB_4_PENGFEI_YAO.CPP
 *
 *  Created on: 2017/12/2
 *      Author: pengfeiyao
 *      EMAIL: pzy0006
 */

#include <iostream>
#include <vector>
#include "Register.h"

using namespace std;

int main(int argc, char *argv[])
{
	Register r = Register();
	while(!r.endGame())
	{
		r.beginItemize();
	}
	return 0;
}


