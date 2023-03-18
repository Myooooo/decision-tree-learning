#ifndef CREDIT_RATING_H
#define CREDIT_RATING_H

#include <vector>
#include "DataStructs.h"

class CreditRating{

private:

    int number_of_nodes;        // stores the number of nodes in the decision tree

public:

    CreditRating();             // default constructor

    Node* DTL(std::vector<DataPair> data, int minleaf);                                 // execute decision tree learning on data with minleaf and return the root node
    attr_and_splitval chooseSplit(std::vector<DataPair> data);                          // calculate and return the best attribute and split value from data by its information gain
    std::string predict(Node* n, DataPair data);                                        // predict and return the expected label for the input data using the decision tree

    bool isAllEqual(std::vector<DataPair> data);                                        // returns true if xi=xj for all i,j OR yi=yj for all i,j in data
    std::string findOutputMode(std::vector<DataPair> data);                             // find and return the mode of output in data
    int findMaxIndex(int arr[7]);                                                       // find and return the index of maximum value in arr
    float calcInfoContent(std::vector<DataPair> data);                                  // calculate and return the information content for data
    float calcRemainder(int attr, float splitval, std::vector<DataPair> data);          // calculate and return the remainder of data at given attr and splitval

    void deleteNodes(Node* n);                                                          // deletes all nodes in the tree from a given node n

    ~CreditRating();            // default destructor

};

#endif