#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "CreditRating.h"

using namespace std;

// read data from file at path, store into a vector and return it
// isTrain should be true if file at path is training data
vector<DataPair> readData(char* path, bool isTrain){
    ifstream readFile(path);
    stringstream ss;
    string line;
    int lineNum = 0;

    vector<DataPair> dataPairs;
    dataPairs.clear();

    // iterate through each line of the file
	while(getline(readFile, line)){

        // initiate string stream
		ss.clear();
		ss.str(line);

        // temp variables
        float WC_TA, RE_TA, EBIT_TA, MVE_BVTD, S_TA;
        string RATING;

        // skip first line
        if(lineNum != 0){
            // check if file at path is training data
            if(isTrain){
                // create training data pairs and store into vector
                ss >> WC_TA >> RE_TA >> EBIT_TA >> MVE_BVTD >> S_TA >> RATING;
                dataPairs.push_back({{WC_TA, RE_TA, EBIT_TA, MVE_BVTD, S_TA}, RATING});
            }else{
                // create testing data and store into vector
                ss >> WC_TA >> RE_TA >> EBIT_TA >> MVE_BVTD >> S_TA;
                dataPairs.push_back({{WC_TA, RE_TA, EBIT_TA, MVE_BVTD, S_TA}, "null"});
            }
        }

        // increment line number
        lineNum ++;
    }

    readFile.close();

    return dataPairs;
}

int main(int argc, char** argv){

    // copy input arguments
    char* train = argv[1];
    char* test = argv[2];
    int minleaf = atoi(argv[3]);

    // create object
    CreditRating cr;

    // read data from given path
    vector<DataPair> train_data = readData(train, true);
    vector<DataPair> test_data = readData(test, false);

    // decision tree learning using input training data
    Node* n = cr.DTL(train_data, minleaf);

    // apply testing data on the decision tree and print output labels
    for(int i = 0; i < test_data.size(); i++){
        cout << cr.predict(n, test_data[i]) << endl;
    }

    // delete nodes in the decision tree
    cr.deleteNodes(n);

    return 0;
}