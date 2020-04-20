#include <iostream>
#include <cstdlib>
#include "container.h"


Container::Container(int weight, std::string destinationCode, std::string id) {
    weight_ = weight;
    destinationCode_ = destinationCode;
    id_ = id;
}

std::string Container::getContainerId() {

    return id_;
}

std::string Container::getDestCode() {
    
    return destinationCode_;
}
