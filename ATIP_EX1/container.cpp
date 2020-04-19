#include <iostream>
#include <vector>
#include <cstdlib>
#include "container.h"

using std::string;


Container::Container(int weight, string destinationCode, string id) {
    weight_ = weight;
    destinationCode_ = destinationCode;
    id_ = id;
}

string Container::getContainerId() {

    return id_;
}

string Container::getDestCode() {
    
    return destinationCode_;
}
