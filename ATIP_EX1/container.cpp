#include <iostream>
#include <vector>
#include <cstdlib>


using std::string;


class ContainerPosition {
    int floorIndex_;
    int rowIndex_;
    int colIndex_;
public:
    ContainerPosition(int floorIndex, int rowIndex, int colIndex){
        floorIndex_ = floorIndex;
        rowIndex_ = rowIndex;
        colIndex_ = colIndex;
    }
};

class Container {
    int weight_; //in KG.
    string destinationCode_; //5 english letters
    string id_; //ISO 6346 standard

public: 
    Container(int weight, string destinationCode, string id) {
        weight_ = weight;
        destinationCode_ = destinationCode;
        id_ = id;
    }
};