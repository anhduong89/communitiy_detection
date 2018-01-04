/*
 * Program.cpp
 *
 *  Created on: Dec 24, 2017
 *      Author: XMGOwner
 */

#include "global.h"
#include "tests.h"


int main() {

	// we run the newmann algorithm
	modularity_newman();

	// run the louivan algorithm
	modularity_louvain();

	return 0;

}




