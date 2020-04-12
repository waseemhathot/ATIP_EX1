
#include <iostream>

#ifndef CONTAINER_H

using std::string;

class Container {
    int weight_; //in KG.
    string destinationCode_; //5 english letters
    string id_; //ISO 6346 standard

public:
    Container(int weight, string destinationCode, string id);
};


class ContainerPosition {
    int floorIndex_;
    int rowIndex_;
    int colIndex_;
public:
    ContainerPosition(int floorIndex, int rowIndex, int colIndex);
};


#endif