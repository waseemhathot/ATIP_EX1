
#include <iostream>

#ifndef CONTAINER_H

using std::string;

class Container {
    int weight_; //in KG.
    string destinationCode_; //5 english letters
    string id_; //ISO 6346 standard

public:
    Container(int weight, string destinationCode, string id);

    string getContainerId();
    string getDestCode();
};


#endif