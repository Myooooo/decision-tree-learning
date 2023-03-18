#include <string>
#include <algorithm>
#include <cmath>
#include "CreditRating.h"

using namespace std;

// default constructor
CreditRating::CreditRating(){
    // initiate number of nodes to 0
    number_of_nodes = 0;
}

// execute decision tree learning on data with minleaf and return the root node
Node* CreditRating::DTL(vector<DataPair> data, int minleaf){
    attr_and_splitval result;
    vector<DataPair> left;
    vector<DataPair> right;

    // check if the node should be the leaf node
    if(data.size() <= minleaf || isAllEqual(data)){
        // create and return a new leaf node with label
        Node* node = new Node();
        node -> label = findOutputMode(data);
        node -> attr = 0;
        node -> splitval = 0;
        node -> left = NULL;
        node -> right = NULL;
        number_of_nodes ++;
        return node;
    }

    // find the best attribute and splitvalue
    result = chooseSplit(data);

    // split data into two vectors using the best attribute and split value
    left.clear();
    right.clear();
    for(int i = 0; i < data.size(); i++){
        if(data[i].attributes[result.attr] <= result.splitval){
            left.push_back(data[i]);
        }else{
            right.push_back(data[i]);
        }
    }

    // create a new node and recursively build the decision tree
    Node* node = new Node();
    node -> label = "null";
    node -> attr = result.attr;
    node -> splitval = result.splitval;
    node -> left = DTL(left, minleaf);
    node -> right = DTL(right, minleaf);
    number_of_nodes ++;

    return node;
}

// calculate and return the best attribute and split value from data by its information gain
attr_and_splitval CreditRating::chooseSplit(vector<DataPair> data){
    // initiate variables
    attr_and_splitval best = {0,0};
    float splitval = 0;
    float bestgain = 0;
    float gain = 0;
    float infoContent = calcInfoContent(data);

    // iteratively find the best attribute and split value by its information gain
    for(int attr = 0; attr < 5; attr++){

        // sort the vector by current attribute
        sort(data.begin(), data.end(), [attr](const DataPair &a, const DataPair &b)
			{return  a.attributes[attr] < b.attributes[attr];});

        // calculate the information gain for each split value
        for(int i = 0; i < data.size() - 1; i++){
            splitval = 0.5 * (data[i].attributes[attr] + data[i + 1].attributes[attr]);
            gain = infoContent - calcRemainder(attr, splitval, data);

            // update the best gain, attribtue and split value if new gain is greater than the current best gain
            if(gain > bestgain){
                bestgain = gain;
                best.attr = attr;
                best.splitval = splitval;
            }
        }

    }

    return best;
}

// predict and return the expected label for the input data using the decision tree
string CreditRating::predict(Node* n, DataPair data){
    // iterate to the leaf node
    while(n -> label == "null"){
        // choose a way in the tree by comparing its attribute to the split value at node
        if(data.attributes[n -> attr] <= n -> splitval){
            n = n -> left;
        }else{
            n = n -> right;
        }
    }

    // return label of the leaf node
    return n -> label;
}

// returns true if xi=xj for all i,j OR yi=yj for all i,j in data
bool CreditRating::isAllEqual(std::vector<DataPair> data){
    // flags for x and y
    bool x_flag = true;
    bool y_flag = true;

    // iteratively check if there's a different element for x and y
    for(int i = 1; i < data.size(); i++){
        // check for different elements for x
        // break the loop if found and go-on with y
        for(int j = 0; j < 5; j++){
            if(data[i].attributes[j] != data[0].attributes[j]){
                x_flag = false;
                break;
            }
        }
        
        // check for different elements for y
        // break the loop if found
        if(data[i].rating != data[0].rating){
            y_flag = false;
            break;
        }
    }

    // if either xs or ys are identical return true
    return x_flag || y_flag;
}

// find and return the mode of output in data
string CreditRating::findOutputMode(vector<DataPair> data){
    // count for the number of occurance of AAA, AA, A, BBB, BB, B, CCC
    int count[7] = {};
    int index;

    // count number of occurance
    for(int i = 0; i < data.size(); i++){
        if(data[i].rating == "AAA"){
            count[0]++;
        }else if(data[i].rating == "AA"){
            count[1]++;
        }else if(data[i].rating == "A"){
            count[2]++;
        }else if(data[i].rating == "BBB"){
            count[3]++;
        }else if(data[i].rating == "BB"){
            count[4]++;
        }else if(data[i].rating == "B"){
            count[5]++;
        }else if(data[i].rating == "CCC"){
            count[6]++;
        }
    }

    // find the index of max value in count
    index = findMaxIndex(count);

    // check for uniqueness of the mode
    if(index == -1){
        // if the mode is not unique return unknown
        return "unknown";
    }else{
        // if the mode is unique return the corresponding label
        switch(index){
            case 0: return "AAA";
            case 1: return "AA";
            case 2: return "A";
            case 3: return "BBB";
            case 4: return "BB";
            case 5: return "B";
            case 6: return "CCC";
        }
    }
}

// find and return the index of maximum value in arr
// returns -1 if not unique
int CreditRating::findMaxIndex(int arr[7]){
    // initiate variables
    int max = arr[0];
    int index = 0;
    bool isUnique = true;

    // iterate through the array
    for(int i = 1; i < 7; i++){
        // if value at current index is greater update max and index
        // if value at current index is the same as max mark isUnique as false
        if(arr[i] > max){
            max = arr[i];
            index = i;
            isUnique = true;
        }else if(arr[i] == max){
            isUnique = false;
        }
    }

    // return the index if unique
    // return -1 if not unique
    if(isUnique){
        return index;
    }else{
        return -1;
    }

}

// calculate and return the information content for data
float CreditRating::calcInfoContent(vector<DataPair> data){
    // AAA, AA, A, BBB, BB, B, CCC
    float p[7] = {};
    float total = data.size();
    float infoContent = 0;

    // count number of occurance
    for(int i = 0; i < total; i++){
        if(data[i].rating == "AAA"){
            p[0]++;
        }else if(data[i].rating == "AA"){
            p[1]++;
        }else if(data[i].rating == "A"){
            p[2]++;
        }else if(data[i].rating == "BBB"){
            p[3]++;
        }else if(data[i].rating == "BB"){
            p[4]++;
        }else if(data[i].rating == "B"){
            p[5]++;
        }else if(data[i].rating == "CCC"){
            p[6]++;
        }
    }

    // update information content by the probability of each attribute
    for(int i = 0; i < 7; i++){
        // calculate the probability of occurance
        p[i] /= total;
        // avoid illegal log2(0)
        if(p[i] == 0){
            infoContent -= 0;
        }else{
            infoContent -= p[i] * log2(p[i]);
        }
    }

    return infoContent;
}

// calculate and return the remainder of data at given attr and splitval
float CreditRating::calcRemainder(int attr, float splitval, vector<DataPair> data){
    // initiate variables
    float p_gt = 0;
    float p_lt = 0;
    float i_gt = 0;
    float i_lt = 0;
    float total = data.size();
    float remainder = 0;

    // vectors that stores the splited data
    vector<DataPair> gt;
    vector<DataPair> lt;

    // split the data by given attribute and split value
    gt.clear();
    lt.clear();
    for(int i = 0; i < total; i++){
        if(data[i].attributes[attr] > splitval){
            gt.push_back(data[i]);
            p_gt++;
        }else{
            lt.push_back(data[i]);
            p_lt++;
        }
    }

    // calculate the probability of occurance
    p_gt /= total;
    p_lt /= total;

    // calculate the information content for each dataset
    i_gt = calcInfoContent(gt);
    i_lt = calcInfoContent(lt);

    // calculate the remainder
    remainder = (p_gt * i_gt) + (p_lt * i_lt);

    return remainder;
}

// deletes all nodes in the tree from a given node n
void CreditRating::deleteNodes(Node* n){
    // recursively delete nodes to its left and right when it is not a leaf node
    // delete itself when its a leaf node
    if(n -> label == "null"){
        Node* left = n -> left;
        Node* right = n -> right;
        delete n;
        number_of_nodes --;
        deleteNodes(left);
        deleteNodes(right);
    }else{
        delete n;
        number_of_nodes --;
    }
}

CreditRating::~CreditRating(){
}