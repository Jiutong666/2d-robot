
#include "NodeList.h"
#include <iostream>



NodeList::NodeList(int cap){
    this->length = 0;
    nodes = new NodePtr[cap];
    this->capacity = cap;
}


NodeList::~NodeList(){
    for (int i = 0; i < this->length; i++) {
        delete this->nodes[i];
    }
    delete this->nodes;
}

NodeList::NodeList(NodeList& other){
    // TODO
    this->length = other.length;
    this->capacity = other.capacity;
    nodes = new NodePtr[this->capacity];
    for (int i = 0; i < other.length; i++) {
        // deep copy
        NodePtr temp = new Node(other.nodes[i]->getRow(), other.nodes[i]->getCol(), other.nodes[i]->getDistanceToS());
        this->nodes[i] = temp;
    }
}


int NodeList::getLength(){
    return this->length;
}


NodePtr NodeList::get(int i){
    NodePtr temp = new Node(this->nodes[i]->getRow(), this->nodes[i]->getCol(), this->nodes[i]->getDistanceToS());
    return temp;
}

void NodeList::addBack(NodePtr newNode){
    NodePtr temp = new Node(newNode->getRow(), newNode->getCol(), newNode->getDistanceToS());
    this->nodes[this->length] = temp;
    this->length++;
}

bool NodeList::containsNode(NodePtr node){
    for (int i = 0; i < this->length; i++) {
        if (this->nodes[i]->getCol() == node->getCol() && this->nodes[i]->getRow() == node->getRow()) return true;
    }
    return false;
}

void NodeList::clear(){
    for (int i = 0; i < this->length; i++) {
        delete this->nodes[i];
    }
    this->length = 0;
    
}

void NodeList::depCpyFromPointer(NodeList* oth)
{
    clear();
    this->length = oth->length;
    this->capacity = oth->capacity;
    nodes = new NodePtr[this->capacity];
    for (int i = 0; i < oth->length; i++) {
        // deep copy
        NodePtr temp = new Node(oth->nodes[i]->getRow(), oth->nodes[i]->getCol(), oth->nodes[i]->getDistanceToS());
        this->nodes[i] = temp;
    }

}


