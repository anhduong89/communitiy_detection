/*
 * tests.h
 *
 *  Created on: Dec 24, 2017
 *      Author: XMGOwner
 */

#ifndef TESTS_H_
#define TESTS_H_

#include "community2.h"


/** Run modularity according to the Louvain algorithm */
void modularity_louvain() {
	community2 c;

	//INPUT (node, Prob, synthetic, add_community, number, min,max , denseProb)
	//node : number of vertices
	//Prob : init probability for 1000 nodes (0.2)
	//synthetic : true = sample graph, false = random graph
	//add_community : true = add probable communities, false = not
	//number : number of communities to add
	// min,max : min and max node per communities
	//denseProb : probability for adding probable communities ( 0.8 )
	c.generate_graph(1000, 0.2 , false,false,2, 100, 200, 0.8);
	//c.show_graph();

	cout << "START MODULARITY_LOUVAIN" << endl;
	auto start1 = std::chrono::high_resolution_clock::now();
	c.modularity_louvain();

	//cout << "SHOW LIST PROBABLE COMMUNITIES" << endl;
	//c.list_communities();

	//cout << "SHOW CALCULATE COMMUNITIES" << endl;
	//c.show_communities();

	auto finish1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed1 = finish1 - start1;
	std::cout << "Execution time: " << elapsed1.count() << " s\n";

	cout << " FINISHED! " << endl;
}

/** Run modularity following the Newman algorithm */
 void modularity_newman() {
 	auto start = std::chrono::high_resolution_clock::now();
 	community2 c;

 	c.generate_graph(500, 0.2 , false,false,2, 17, 30, 0.8);

 	cout << "GENERATE GRAPH SUCCESS !" << endl;

 	c.modularity_newman();
 	//c.show_communities();
 	cout << " modularity_newman SUCCESS" << endl;
 	auto finish = std::chrono::high_resolution_clock::now();
 	std::chrono::duration<double> elapsed = finish - start;
 	std::cout << "Execution time: " << elapsed.count() << " s\n";

 	cout << " FINISHED! " << endl;

}

#endif /* TESTS_H_ */
