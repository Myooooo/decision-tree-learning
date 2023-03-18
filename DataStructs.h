#ifndef DATA_H
#define DATA_H

#include <vector>

// stores the attributes and rating in a datapair
struct DataPair{
    // WC_TA, RE_TA, EBIT_TA, MVE_BVTD, S_TA
    float attributes[5];
    std::string rating;
};

// stores the variables in a node
struct Node{
    std::string label;
    int attr;
    float splitval;
    Node* left;
    Node* right;
};

// stores the attribute and corresponding split value
struct attr_and_splitval{
    int attr;
    float splitval;
};

#endif