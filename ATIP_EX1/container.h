
#include <iostream>
#include <string>
#include <vector>

#ifndef CONTAINER_H

class Container {
    int weight_; //in KG.
    std::string destinationCode_; //5 english letters
    std::string id_; //ISO 6346 standard

public:
    Container(int weight, std::string destinationCode, std::string id);

    std::string getContainerId();
    std::string getDestCode();
};

#endif