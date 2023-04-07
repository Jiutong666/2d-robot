
#include "Node.h"


Node::Node(int row, int col, int distanceToS){
   //TODO
    this->row = row;
    this->col = col;
    this->distanceToS = distanceToS;
}
    
Node::~Node(){
   //TODO
}

int Node::getRow(){
   //TODO
    return this->row;
}

int Node::getCol(){
   //TODO
    return this->col;
}

int Node::getDistanceToS(){
   //TODO
    return this->distanceToS;
}

void Node::setDistanceToS(int distanceToS){
   //TODO
    this->distanceToS = distanceToS;
}
