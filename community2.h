/*
 * community2.h
 *
 *  Created on: Dec 30, 2017
 *      Author: SunSmile
 */

#ifndef COMMUNITY2_H_
#define COMMUNITY2_H_
#include "global.h"

class community2 {
protected:
	/** Adj matrix of graph */
	vector<vector<int>> graph;
	vector<vector<int>> graph1;

	/** so cac dinh */
	int nodes;

	/** So luong cac dinh */
	int numnodes;

	/** So luong cac canh */
	int numedges;

	/** Bac cua cac community */
	vector<int> degs;

	/** Weight cua cac node */

	vector<int> weight;

	/** Bac cua cac dinh enumerate */
	vector<int> enudeg;

	/** cluster ID */
	vector<int> comm;

	/** cluster ID of node */
	vector<int> com_node;

	/** number of edges per comm */
	vector<int> com_loop;

	/** number of edges per node */
	vector<int> node_loop;

	/** weight of community */
	vector<int> weight_c;

	/** weight of node */
	vector<int> weight_n;

	/**link of node to node */
	vector<unsigned int> link;

	/** neighbor position */
	vector<unsigned int> neigh_pos;

	/** common edge */
	vector<unsigned int> edge_com;

	/** vector communities */
	vector<vector<int>> communities;

	/** vector edge-weight intra-communities */
	vector<int> in;

	/** vector weight-link */
	vector<int> w_link;

	/** number of neighbor */
	vector<int> nb_neighbor;

	/** list of created communities */
	vector<vector<int>> listcommunities;

public:
	/** Constructor */
	community2();

	/** Destructor */
	virtual ~community2();

	/** Generating random or synthetic graph */
	void generate_graph(int n, float probability, bool synthetic, bool addcommunity,int nb_comadd,int min_size, int max_size, float denseprobability) {
		synthetic==true?numnodes = 24:numnodes = n;

		numedges = 0;
		nodes = numnodes;
		com_loop.resize(numnodes);
		node_loop.resize(numnodes,0);
		graph.resize(numnodes);
		weight_c.resize(numnodes,0);
		weight_n.resize(numnodes,0);
		weight.resize(numnodes,0);
		comm.resize(numnodes,0);
		com_node.resize(numnodes,0);
		degs.resize(numnodes,0);
		enudeg.resize(numnodes,0);
		nb_neighbor.resize(numnodes,0);
		communities.resize(numnodes);
		listcommunities.resize(numnodes);
		for (int i = 0; i < numnodes; ++i) {
			graph[i].resize(numnodes, 0);
			com_loop[i] = 0;
			node_loop[i] = 0;
			listcommunities.resize(numnodes);
		}
		if (synthetic) {
			graph[0][0] = 0;graph[0][1] = 1; graph[0][5] = 1; graph[0][6] = 1; graph[0][23] = 1;
			graph[1][1] = 0;graph[1][0] = 1; graph[1][6] = 1; graph[1][2] = 1;
			graph[2][2] = 0;graph[2][1] = 1; graph[2][6] = 1; graph[2][3] = 1;
			graph[3][3] = 0;graph[3][2] = 1; graph[3][8] = 1; graph[3][12] = 1; graph[3][4] = 1;
			graph[4][4] = 0;graph[4][3] = 1; graph[4][6] = 1; graph[4][5] = 1; graph[4][21] = 1; graph[4][22] = 1;
			graph[5][5] = 0;graph[5][6] = 1; graph[5][0] = 1; graph[5][14] = 1; graph[5][15] = 1; graph[5][22] = 1; graph[5][4] = 1;
			graph[6][6] = 0;graph[6][2] = 1; graph[6][1] = 1; graph[6][0] = 1; graph[6][5] = 1; graph[6][4] = 1;
			graph[7][7] = 0;graph[7][9] = 1; graph[7][8] = 1; graph[7][12] = 1; graph[7][13] = 1;
			graph[8][8] = 0; graph[8][9] = 1; graph[8][7] = 1; graph[8][3] = 1; graph[8][13] = 1;
			graph[9][9] = 0;graph[9][8] = 1; graph[9][7] = 1; graph[9][13] = 1; graph[9][10] = 1;
			graph[10][10] = 0;graph[10][9] = 1; graph[10][13] = 1;
			graph[11][11] = 0;graph[11][13] = 1; graph[11][16] = 1;
			graph[12][12] = 0;graph[12][3] = 1; graph[12][7] = 1; graph[12][13] = 1;
			graph[13][13] = 0;graph[13][12] = 1; graph[13][11] = 1; graph[13][10] = 1; graph[13][9] = 1; graph[13][8] = 1; graph[13][7] = 1;
			graph[14][14] = 0;graph[14][5] = 1; graph[14][15] = 1;
			graph[15][15] = 0;graph[15][5] = 1; graph[15][14] = 1; graph[15][20] = 1; graph[15][22] = 1;
			graph[16][16] = 0;graph[16][11] = 1; graph[16][17] = 1; graph[16][19] = 1;
			graph[17][17] = 0;	graph[17][16] = 1; graph[17][19] = 1; graph[17][18] = 1;
			graph[18][18] = 0;	graph[18][17] = 1; graph[18][19] = 1;
			graph[19][19] = 0;	graph[19][16] = 1; graph[19][17] = 1; graph[19][18] = 1;
			graph[20][20] = 0;	graph[20][21] = 1; graph[20][15] = 1; graph[20][22] = 1;
			graph[21][21] = 0;	graph[21][4] = 1; graph[21][20] = 1;
			graph[22][22] = 0;	graph[22][4] = 1; graph[22][5] = 1; graph[22][15] = 1; graph[22][20] = 1;
			graph[23][23] = 0;	graph[23][0] = 1;
		}
		else {
			for (int i = 0; i < n; i++){
				for (int j = 0; j < i; j++) {
					if(i==j){
						graph[i][j] = 0;
					}
					else {
						double p = ((double)rand()) / RAND_MAX;
						if (p < probability && i!=j) {
								graph[i][j] = 1;
								graph[j][i] = 1;

						}

					}
				}
			}
			if (addcommunity) {
				add_community( nb_comadd, min_size,  max_size,  denseprobability);
			}
		}
		// INIT THE NUMBER NEIGHBOR OF VERTICES
		for (int i = 0; i < numnodes; i++) {
			for (int j = 0; j < i; j++) {
				if (graph[i][j] == 1 && graph[j][i] ==1) {
					numedges++;
					degs[i]++;
					degs[j]++;
				}
			}
		}
		graph1 = graph;
		weight_c=degs;
		weight_n=degs;
		weight = degs;
		nb_neighbor = degs;
		enudeg[0] = degs[0];
		// INIT STORING THE LINK AND WEIGHT OF THIS LINK BETWEEN VERTICES
		for (int i = 0; i < numnodes; i++) {
			for (int j = 0; j < numnodes; j++) {
				if (graph[i][j] == 1 && graph[j][i] == 1) {
					link.push_back(j);
					w_link.push_back(1);
				}

			}
			if (i > 0) {
				enudeg[i] = enudeg[i-1] + degs[i];
			}
		}
		// INIT THE POSITION OF COMMUNITIES
		for (int i = 0; i < numnodes; i++) {
			comm[i] = i;

		}
		com_node= comm;

		// assign node to communities
		for (int i = 0; i < numnodes; ++i) {
			communities[i].push_back(i);
		}
	}
/*________________________LOUVAIN__________________________*/


	/* SEARCH FOR NEIGHBOR COMMUNITIES */
	void neigh_comm(int node) {
		edge_com.clear();
		neigh_pos.clear();
		neigh_pos.resize(numnodes);
		edge_com.resize(numnodes);
		vector<unsigned int> commonedge(numnodes,0);
		int edge_comm;
		for ( int i = 0; i < degs[node]; i++) {
			unsigned int neigh_node;
			if (node == 0) {
				neigh_node = *(link.begin()+i);
				edge_comm = *(w_link.begin()+i);
			}
			else {
				neigh_node = *(link.begin()+enudeg[node-1]+i);
				edge_comm = *(w_link.begin() + enudeg[node-1] + i);
			}
			neigh_pos[i] = comm[neigh_node];
			commonedge[comm[neigh_node]] += edge_comm;
		}
		edge_com = commonedge;
	}

	/** INSERT NODE TO COMMUNITY */
	void insert(int node, int dcomm, int best_nblinks) {

		weight_c[dcomm] = weight_c[dcomm] + weight_n[node];
		com_loop[dcomm] = com_loop[dcomm] + best_nblinks + node_loop[node];
		comm[node] = dcomm;
	}

	/* REMOVE NODE FROM COMMUNITY */
	void remove(int node, int dcomm) {
		weight_c[dcomm] = weight_c[dcomm] - weight_n[node];
		if (com_loop[dcomm] > 0) {
			com_loop[dcomm] = com_loop[dcomm] - edge_com[dcomm] - node_loop[node];
		}
	}

	/* CALCULATE MODULARITY GAIN */
	double modularity_gain(int node, int comm_pos) {
		double edge_com2 = (double)edge_com[comm_pos];
		double degs_node = (double)weight_n[node];
		double weight_com = (double)weight_c[comm_pos];
		double numedge1 = (double)numedges;
		double dQ = ((edge_com2/numedge1) - 2*((degs_node*weight_com)/(4*numedge1*numedge1)));
		return dQ;
	}

	/* CALCULATE TOTAL MODULARITY */
	double total_modularity() {
		double modularity = 0, modularity1;
		double edgei;
		double modul1,modul2;

		for (int i = 0; i < numnodes; i++ ) {
			if (weight_c[i] > 0) {
				 edgei = (double)com_loop[i];
				 modul1 = edgei/(double)numedges;
				 modul2 = (double)weight_c[i]*(double)weight_c[i]/(4*(double)numedges*(double)numedges);
				modularity1 = modul1 - modul2;
				modularity = modularity + modularity1;
			}
		}
		return modularity;
	}

	/* MODULARITY LOUVAIN ( BLONDEL ET AL ) */
	void modularity_louvain() {
		double new_mod, cur_mod;
		vector<vector<int>> comlist;
		bool improvement;
		bool one_level;
		communities.clear();
		do {
			new_mod = total_modularity();
			cur_mod = new_mod;
			improvement = false;
			one_level = false;
			comlist.clear();
			comlist.resize(numnodes);
			// Scan node
			do {
				cur_mod = new_mod;
				for (int i = 0; i < numnodes; i++) {
					int best_nblinks = 0;
					double increase = 0;
					int node_comm = comm[i];
					int best_comm = node_comm;
					// Find node's community and neighbor community, common edge between node and community;
					neigh_comm(i);
					// remove node from its own community
					remove(i,comm[i]);
					// scan neighbor community
					for (int j = 0; j < degs[i]; j++) {
						double dQ = modularity_gain(i, neigh_pos[j] );
						if (dQ > increase) {
							increase = dQ;
							best_comm = neigh_pos[j];
							best_nblinks = edge_com[neigh_pos[j]];
							one_level = true;
						}
					}
					insert(i, best_comm, best_nblinks);
				}
				 new_mod = total_modularity();
			} while (new_mod > cur_mod );
			if (one_level == false) {break;}
			improvement = true;

			//RUN PHASE 2
			phase2();
		} while(improvement);
	}

	/* PHASE 2 : RECALCULATE THE GRAPH AND INIT DATA FOR PHASE 1 */
	void phase2() {
		vector<int> w_com_res;
		vector<int> s_loop_res;
		// ASSIGN COMMUNITY NUMBER OF NODE
		for ( int i = 0; i < nodes; ++i) {
			com_node[i] = comm[com_node[i]]; // QUAN TRONG
		}

		// COUNT NUMBERS OF NODE EVERY COMMUNITY
		vector<int> renumber(nodes, -1);
		for ( int i = 0; i < nodes; ++i) {
			renumber[com_node[i]] ++;
		}
		// COUNT THE NUMBER OF COMMUNITY
		int final = 0;
		for ( int i = 0; i < nodes; ++i) {
			if (renumber[i] != -1) {
				renumber[i] = final ++;
			}
		}

		// PUT NODE TO NEW COMMUNITY
		vector<vector<int>> res_commu(final);
		for ( int i = 0; i < nodes; ++i) {
			res_commu[renumber[com_node[i]]].push_back(i);

		}
		communities = res_commu;
		for (unsigned int i = 0; i < communities.size(); ++i) {
			for (unsigned int j = 0; j < communities[i].size(); ++j) {
				 com_node[communities[i][j]] = i;
			}
		}

		//RECALCULATE THE WEIGHT OF NEW NODE
		w_com_res.resize(final, 0);
		s_loop_res.resize(final, 0);
		int total_weight;
		for (unsigned int i = 0; i < communities.size(); ++i) {
			total_weight = 0;
			for (unsigned int j = 0; j < communities[i].size(); ++j) {
				total_weight = total_weight + weight[communities[i][j]];
			}
			w_com_res[i] = total_weight;
		}

		// RESET THE VARIABLE
		numnodes = final;
		weight_c.clear();
		weight_c = w_com_res;
		weight_n.clear();
		weight_n = w_com_res;
		degs.clear();
		degs.resize(numnodes);
		comm.clear();
		comm.resize(numnodes);
		com_loop.clear();
		com_loop.resize(final);
		node_loop.clear();
		node_loop.resize(final);

		// ASSIGN COMMUNITIES FOR NEW NODE
		for ( int i = 0; i < numnodes; ++i) {
			comm[i] = i;
		}

		// CREATE RESERVE GRAPH
		int node1, node2, nblink, self_loop;
		vector<vector<int>> graph_res;
		graph_res.resize(numnodes);
		for (int i = 0; i < numnodes; ++ i) {
			graph_res[i].resize(numnodes, 0);
		}

		// CALCULATE THE WEIGHT OF LINK BETWEEN COMMUNITIES
		for ( int i = 0; i < numnodes; ++i) {
			self_loop = 0;
			for ( int j = 0; j < numnodes; j++) {
				nblink = 0;
				if (i != j) {
					for (unsigned int h = 0; h < communities[i].size(); ++h) {
						node1 = communities[i][h];
						for (unsigned int k = 0; k < communities[j].size(); ++k) {
							node2 = communities[j][k];
							if (graph1[node1][node2]==1 && graph1[node2][node1] == 1) {
								nblink++;
							}
						}
					}
				}
				if (i == j) {
					for (unsigned int h = 0; h < communities[i].size(); ++h) {
						node1 = communities[i][h];
						for (unsigned int k = 0; k < communities[j].size(); ++k) {
							node2 = communities[j][k];
							if (graph1[node1][node2]==1 && graph1[node2][node1] == 1) {
								self_loop++;
							}
						}
					}
				}
				//ASSIGN THE LOOP OF NODE
				node_loop[i] = self_loop/2;
				com_loop[i] = self_loop/2;
				// ASSIGN WEIGHT OF LINK
				graph_res[i][j] = nblink;
			}

		}
		// REASSIGN THE NEIGHBOR OF NODE (LINK)
		for ( int i=0 ; i < numnodes; ++i) {
			for (int j = 0; j < i; ++j) {
				if(graph_res[i][j] != 0 && graph_res[i][j] != 0 && graph_res[i][j]== graph_res[j][i]) {
					degs[i] += 1;
					degs[j] += 1;
				}
			}
		}
		// SET NEW GRAPH
		graph.clear();
		graph = graph_res;
		enudeg[0] = degs[0];
		link.clear();
		w_link.clear();

		// SET NEW LINK AND WEIGHT LINK
		for (int i = 0; i < numnodes; i++) {
			for (int j = 0; j < numnodes; j++) {
				if (graph[i][j] !=0 && graph[j][i] != 0) {
					link.push_back(j);
					w_link.push_back(graph[i][j]);
				}
			}
			if (i > 0) {
				enudeg[i] = enudeg[i-1] + degs[i];
			}
		}
	}


	/***** __________________NEWMAN____________________ **/


	/** MODULARITY GAIN */
	double modularity_gain2(unsigned int com1, unsigned int com2, int edgecom) {
		double edge_com2 = (double)edgecom;
		double weight_com1 = (double)weight_c[com1];
		double weight_com2 = (double)weight_c[com2];
		double numedge1 = (double)numedges;
		double dQ = ((edge_com2/numedge1) - 2*((weight_com1*weight_com2)/(4*numedge1*numedge1)));
		return dQ;
	}


	/** TOTAL MODULARITY */
	double total_modularity2() {
		double modularity = 0, modul1, modul2, modularity1, edgei;

		for (unsigned int i = 0; i < communities.size(); ++i) {
			if (weight_c[i] > 0) {
				edgei = (double)com_loop[i];
				 modul1 = edgei/(double)numedges;
				 modul2 = (double)weight_c[i]*(double)weight_c[i]/(4*(double)numedges*(double)numedges);
				modularity1 = modul1 - modul2;
				modularity = modularity + modularity1;
			}
		}
		return modularity;
	}

	/** SEARCH FOR NEIGHBOR COMMUNITIES */
	pair<vector<unsigned int>::iterator, vector<int>::iterator> neighbor(unsigned int com_pos) {

		if (com_pos == 0) {
			return make_pair(link.begin(), w_link.begin());
		}
		else {
			return make_pair(link.begin() + enudeg[com_pos - 1], w_link.begin() + enudeg[com_pos - 1]);
		}
	}

	/** MERGE 2 COMMUNITES AND ERASE UNNESCESSARY COMMUNITY */
	void merge(unsigned int com1, unsigned int com2, int edge_common) {
		vector<int> sum;
		sum = communities[com1];
		sum.insert(sum.end(), communities[com2].begin(), communities[com2].end());
		communities[com1] = sum;
		communities.erase(communities.begin()+ com2);
	}

	/** RECALCULATE THE COMMUNITIES */
	void re_communities(){
		vector<vector<int>> com_res;
		for (unsigned int i = 0; i < communities.size(); ++i) {
			com_res.push_back(communities[i]);
		}
		communities.clear();
		communities = com_res;
		unsigned self_loop, edge, node1, node2;
		vector<vector<int>> graph_res;
		graph_res.resize(communities.size());
		for (unsigned int i = 0; i < communities.size(); ++ i) {
			graph_res[i].resize(communities.size(), 0);
		}
		for ( unsigned int i = 0; i < communities.size(); ++i) {
			self_loop = 0;
			for (unsigned int j = 0; j < communities.size(); j++) {
				edge = 0;
				// XET WEIGHT OF LINK GIUA 2 COMMUNITIES KHAC NHAU
				if (i != j) {
					for (unsigned int h = 0; h < communities[i].size(); ++h) {
						node1 = communities[i][h];
						for (unsigned int k = 0; k < communities[j].size(); ++k) {
							node2 = communities[j][k];
							if (graph[node1][node2]==1 && graph[node2][node1] == 1) {
								edge++;
							}
						}
					}
				}
				if (i == j) {
					for (unsigned int h = 0; h < communities[i].size(); ++h) {
						node1 = communities[i][h];
						for (unsigned int k = 0; k < communities[j].size(); ++k) {
							node2 = communities[j][k];
							if (graph[node1][node2]==1 && graph[node2][node1] == 1) {
								self_loop++;

							}
						}
					}

				}
				com_loop[i] = self_loop/2;
				graph_res[i][j] = edge++;
			}
		}
		degs.clear();
		degs.resize(communities.size());
		enudeg.clear();
		enudeg.resize(communities.size());
		link.clear();
		w_link.clear();

		for ( unsigned int i=0 ; i < communities.size(); ++i) {
			for (unsigned int j = 0; j < i; ++j) {
				if(graph_res[i][j] != 0 && graph_res[i][j] != 0 && graph_res[i][j]== graph_res[j][i]) {
					degs[i] += 1;
					degs[j] += 1;
				}
			}
		}
		enudeg[0] = degs[0];

		for (unsigned int i = 0; i < graph_res.size(); i++) {
			for (unsigned int j = 0; j < graph_res.size(); j++) {
				if (graph_res[i][j] !=0 && graph_res[j][i] != 0) {
					link.push_back(j);
					w_link.push_back(graph_res[i][j]);
				}
			}
			if (i > 0) {
				enudeg[i] = enudeg[i-1] + degs[i];
			}
		}
		int total_weight;
		weight_c.clear();
		weight_c.resize(communities.size());
		for (unsigned int i = 0; i < communities.size(); ++i) {
			total_weight = 0;
			for (unsigned int j = 0; j < communities[i].size(); ++j) {
				total_weight = total_weight + weight[communities[i][j]];

			}
			weight_c[i] = total_weight;
		}
	}

	/* MODULARITY NEWMAN */
	void modularity_newman() {
		bool improvement;
		double modularity;
		double max_dQ;
		int best_edge;

		int best_com1  , best_com2 ;
		do {
			modularity = total_modularity2();
			max_dQ = 0;
			improvement = false;
			best_com1 = -1; best_com2 = -1;

			for ( unsigned int i = 0; i < communities.size(); ++i) {
				pair<vector<unsigned int>::iterator, vector<int>::iterator> nbor = neighbor(i);

				for ( signed int j = 0; j < degs[i]; ++j) {
					double gain = modularity_gain2(i, *(nbor.first + j), *(nbor.second + j));
					if (gain > max_dQ) {
						max_dQ = gain;
						best_com1 = i;
						best_com2 = (int)*(nbor.first + j);
						best_edge = *(nbor.second + j);
						improvement = true;
					}
				}
			}
			if (improvement == false) {break;}
			if(best_com1 != -1 && best_com2 != -1) {merge(best_com1, best_com2, best_edge);}

			//RECALCULATE THE COMMUNITIES
			re_communities();
			modularity = total_modularity2();
			//cout << "modularity" << modularity;
		} while (improvement);
	}

	/** SHOW_INFO SCRIPT */
	void show_graph() {
		for (int i = 0; i < numnodes; i++) {
			cout << i << " : ";
			for (int j = 0; j < numnodes; j++) {
				cout << graph[i][j] << " ";
			}
			cout << "\n";
		}
		cout << endl;
	}
	void show_graph(vector<vector<int>> graph_res) {
		for (unsigned int i = 0; i < communities.size(); i++) {
			cout << i << " : ";
			for (unsigned int j = 0; j < communities.size(); j++) {
				cout << graph_res[i][j] << " ";
			}
			cout << "\n";
		}
		cout << endl;
	}

	void show_communities() {
		cout << "\n";
		for (unsigned int i = 0; i < communities.size(); ++i) {
			cout << i << ": ";
			for (unsigned int j = 0; j < communities[i].size(); ++j) {
				cout << communities[i][j] << " ";
			}
			cout << "\n";
		}
	}
	void show_deg() {
		cout << "\n";
		for (unsigned int i = 0; i < degs.size(); i++) {
			cout << "(deg" << i << ")" << degs[i] << " ";
		}
		cout << endl;
	}
	void show_enudeg() {
		cout << "\n";
		for (unsigned int i = 0; i < enudeg.size(); i++) {
			cout << "enudeg("<< i << ")" << enudeg[i] << " ";
		}

		cout << endl;
	}
	void show_weight_cn() {
		cout << "\n";
		for (unsigned int i = 0; i < weight_c.size(); i++) {
			cout << "weigh("<< i << ")" << weight_c[i] << " ";
		}

		cout << endl;
	}
	void show_link() {
		cout << "\n";
		cout << "link: ";
		for (unsigned int i = 0; i < link.size(); i++) {
					cout <<"link:" <<link[i] << "--";


		}
		cout << endl;
		cout << "w_link: ";
		for (unsigned int i = 0; i < link.size(); i++) {

					cout  <<w_link[i] << " ";

		}
		cout << endl;
	}
	void show_loop() {
		cout << "\n";
		cout << "loop: ";
		for (int i = 0; i < numnodes; i++) {
						cout <<"com"<< i << ":"<<com_loop[i] << " "   ;
					}
		cout <<endl;
	}
	void show_info() {
		cout << "number of edges : " << numedges << endl;
		cout << "numnodes" << numnodes << endl;

		for (int i = 0; i < numnodes; ++i) {
			if (node_loop[i] != 0) {
				cout << "node_loop" << node_loop[i];
			}
			else if (com_loop[i] != 0) {
				cout << "com_loop" << com_loop[i];
			}
			else {
				cout << "no edge!";
				cout << "no com_loop";
			}
			cout << "weight_c" << weight_c[i] << " ";
		}
		cout << endl;
		int total_weight = 0;
		for (int i = 0; i < numnodes; ++i) {
			total_weight = total_weight + weight_c[i];
		}
		cout << "total weight =" << total_weight;

	}
	void list_communities() {
		cout << "\n";
		for (unsigned int i = 0; i < listcommunities.size(); ++i) {
			if (listcommunities[i].size() == 0) continue;
			cout << i << ": ";
			for (unsigned int j = 0; j < listcommunities[i].size(); ++j) {

				cout << listcommunities[i][j] << " ";
			}
			cout << "\n";
		}
	}

	/** ADD COMMUNITY TO RANDOM GRAPH */
	double getNextInt(int a) {
	    return rand()%a;
	}

	double getNextInt(int a, int b) {
	    return a + rand()%(b - a);
	}

	double getNextFloat() {
	    return 1.0*rand()/RAND_MAX;
	}
	void add_community(int nb_comadd,int min_size, int max_size, float denseprobability) {
	    int N = graph.size();
	    vector<int> mask(N, 0);
	    // Select n1 from all nodes, then create a dense graph from these nodes
	    for (int t = 0; t < nb_comadd; t++) {
	        int n1 = (min_size + rand()%(max_size - min_size));

	        vector<int> selected;
	        for (int i = 0; i < n1; i++) {
	           // while (true) {
	                int u = getNextInt(N);
	                if (mask[u] == 0) {
	                    mask[u] == 1;
	                    selected.push_back(u);
	                   // break;
	                }

	            //}
	        }

	        listcommunities.push_back(selected);
	        for (unsigned int i = 0; i < selected.size(); i++)
	            for (unsigned int j = 0; j < selected.size(); j++) {
	                int u = selected[i];
	                int v = selected[j];
	                double p = ((double)rand()) / RAND_MAX;
	                if (p < denseprobability && i != j) {
	                    graph[u][v] = 1;
	                    graph[v][u] = 1;
	                }
	            }
	    }

	}

	void read_data() {
		vector<vector<int>> reserve;
		reserve.resize(10);
		for (int i = 0; i < 10; i++) {
			reserve[i].resize(10,0);
		}
		ifstream infile;

		infile.open("C:/Users/SunSmile/eclipse-workspace/duongmodular/com-amazon.ungraph.txt");

		string line;
		while (getline(infile, line)) {
			string breal,creal;
			if (istringstream(line) >> breal >>creal && breal[0] != '#' ) {
				istringstream ss(line);

				int b,c;
				ss >> b >> c;
				cout << b <<" " << c << endl;
				reserve[b-1][c-1] = 1;
				reserve[c-1][b-1] = 1;
			}
		}
		infile.close();
	}


};

#endif /* COMMUNITY2_H_ */
