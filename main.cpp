/*
 * TSP problem using Simulated Annealing
 * CSE 6140 project @ Georgia Institute of Technology
 *
 * Created by Yingqiao Zheng on 11/17/2018
 */

#include <iostream>
#include <float.h>
#include "SA_TSP.h"
// #include "parse_graph.h"
#include "fileReader.h"


int main(int argc, char *argv[]) {
    // initialize a tour
    Tour test;
    test.path.clear();
    test.tour_length = 0;

    // parameters for SA
    SApara tsp;
    // end temperature
    tsp.endTemp = 0;
    // initial temperature
    tsp.iniTemp = DBL_MAX;
    // decay rate
    tsp.deRate = 0.999;
    // max runtime (sec)
    tsp.maxTime = 10;

    // GRAPH vector<vector<int>>
    GRAPH graph;
    // store the number of cities in a graph
    int numNode = 0;
    // name of current city
    string cityName;

    // outputfile: solution
    string ofp;
    // output file: trace
    string ofp_trace;
    // ifp = argv[1];
    // ofp = argv[2];


    vector<string> fileName = {"Atlanta", "Berlin", "Boston", "Champaign", "Cincinnati",
                               "Denver", "NYC", "Philadelphia", "Roanoke", "SanFrancisco",
                               "Toronto", "UKansasState", "ulysses16", "UMissouri"};

    for (int seed = 0; seed < 1; ++seed) {
        for (int loop = 3; loop < fileName.size(); ++loop) {
        // for (int loop = 3; loop < ; ++loop) {
            fileReader ifp("/Users/zoe/GaTech/CSE6140-CSEAlgorithm/assignment/project/DATA/tsp/" + fileName[loop] + ".tsp");
            // ifp = "/Users/zoe/GaTech/CSE6140-CSEAlgorithm/assignment/project/DATA/tsp/";
            ofp = "/Users/zoe/GaTech/CSE6140-CSEAlgorithm/assignment/project/DATA/solution/output/";
            ofp_trace = "/Users/zoe/GaTech/CSE6140-CSEAlgorithm/assignment/project/DATA/trace/output/";

//            ifp += fileName[loop];
//            ifp += ".tsp";
            // convert seed into string so that it could be add to file name
            string it = to_string(seed);
            // solution output file path
            ofp += fileName[loop] + "_LS1_" + to_string((int)tsp.maxTime) + "_" + it + ".sol";
            // trace output file path
            ofp_trace += fileName[loop] + "_LS1_" + to_string((int)tsp.maxTime) + "_" + it + ".trace";

            // set random seed
            srand((unsigned int) seed);


            try {
                // parseToAdjMatrix(graph, cityName, numNode, ifp);
                // read file to graph
                graph = ifp.readGraphIntoMatrix();
                numNode = (int)graph.size();
                cout << "City Name: " << fileName[loop] << ";\nSize: " << numNode << endl;

                //startState(test, graph, numNode);
                cout << "*********************** First Path ***********************" << endl;
                // initialize first state
                initTour(test, numNode, graph);
                firstState(test, graph, 8000);
                printPath(test);

                // run SA
                SimulatedAnnealing(tsp, test, graph, ofp_trace);
                cout << "*********************** Final Result ***********************" << endl;
                printPath(test);

                // write solution file (note that trace file output is inside SA funciont itself)
                outputToFile(ofp, graph, test);
            } catch (const char *msg) {
                // catch error
                cerr << msg << endl;;
                exit(1);
            }// end of try and catch
            //ifp.clear();
            // clear the string for the use of next loop
            ofp.clear();
            ofp_trace.clear();

        }// end of for (int loop = 0; loop < 1; ++loop)
    }// end of for (int seed = 0; seed < 10; ++seed)
    return 0;
}