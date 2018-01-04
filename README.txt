========================================================================
	ANH-DUONG NGUYEN duongnguyenhumg.edu.vn
newman and blondel et al modularity optimization in community detection
========================================================================

The source code includes 3 main part:

1* Generate random graph and synthetic graph

2* Blondel et al. algorithm (louvain)

3* Newman algorithm

========================================================================

To adjust the input value of program, you can use the "tests.h"

Inside "tests.h", you can see two functions represent two algorithm Newman and Louvain.

Inside these functions, change the parameters of c.generate_graph (node, probability, synthetic, addcommunity, numbercommunity, minsize, maxsize, denseprobability);

   for example :  c.generate_graph(1000, 0.2 , true, false, 2, 100, 200, 0.8);

  
* 1st parameter (int)     : Numbers of nodes you want to create. for example 1000.

* 2nd parameter (double)  : creation probability of edges. For example 0.2

* 3rd parameter (boolean) : True is generate synthetic graph, False is generate random graph

* 4th parameter (boolean) : True is add more probable communities in random graph, False is only generate random graph

* 5th parameter (int)     : Number of probable communities add to graph

* 6th parameter (int)     : Minimum nodes of probable communities. For example : 100

* 7th parameter (int)     : Maximum nodes of probable communities. For example : 200 

* 8th parameter (double)  : Dense probability. For example : 0.8				

========================================================================

Notice : this source code does not include part which work with real data graph 

	




