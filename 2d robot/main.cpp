/*
*short 1-paragraph description 
*implement Milestone 1,2,3,4
* 
* In Milestone 2:
* 1. I implemented Node class and NodeList class.
* 2. I declared and defined a function "checkPoint" to check whether 
* the point is a reachable point and is not in ReachableNodes list. 
* This function retrun NodePtr if it is a reachable point, return 
* NULL if it is not a reachable point.
* 3. In getReachableNodes(), I implemented the algorithm described 
* in the pseudo code. Realchablenodes, a private member of the 
* pathplanner class, is used as the open list in the pseudo code.
* Define the NodeList* Close in the getreachablenodes() function
* as the closed list in the pseudo code.
* 
* 
* In Milestone 3:
* 1. I declared and defined a function "checkadjacentpoints" to check 
* whether the node is adjacent to the given coordinates.
* 2. In getPath(), I found the path start from the goal node in the
* NodeList ReachableNodes and used the function "checkadjacentpoints"
* to find out the nodes in the NodeList ReachableNodes that should 
* be in the path among its four neighbors. After finding the first node, 
* reverse the whole path to get the path from "start" to "goal"
* 
* In Milestone 4:
* 1. For NodeList: 
*   A. Change the type of the field nodes in the NodeList class to a generic
* 1D array of pointers. 
*   B. Add an int private member capacity to represent 
* the capacity of NodeList. 
*   C. Add a function: depCpyFromPointer(NodeList* oth). Used to copy through
*   the NodeList pointer
*   D. Release nodes in destructor.
* 2. For PathPlanner:
*   A. Request memory space for private member env in constructor.
*   B. Free memory space of env in destructor.
* 3. For main
*   A. Change the type of Env to a generic 2D array.
*   B. Modify function readEnvStdin(), so that it can dynamically
*   adjust the env size according to the size of the input rectangular map.
*   C. Modify function printPath(), so that it can print the map according 
*   to the number of rows and columns entered.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include "milestone4.h"


// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
Env readEnvStdin(int &rows, int& cols);

void printReachablePositions(Env env, NodeList* reachablePositions);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution, int rows, int cols);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    //testNode();
    //testNodeList();
    //std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    int rows = 0, cols = 0;
    Env env = readEnvStdin(rows,cols);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathplanner = new PathPlanner(env, rows, cols);
    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();

    //printReachablePositions(env, reachablePositions);

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution, rows, cols);

    delete_env(env,rows,cols);
    delete pathplanner;
    delete reachablePositions;
    delete solution;

}





/*
void readEnvStdin(Env env){
    //TODO 
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            std::cin >> env[i][j];
        }
    }
}
*/

Env readEnvStdin(int &rows, int &cols){
    //TODO 
    std::string map = "";
    while (1) {
        char c;
        if (!std::cin.get(c)) {
            rows++;
            break;
        }
        
        if (c != '\n') { 
            if(rows==0) cols++;
            map += c;
        }
        else {
            rows++;
        }
    }

    Env env = make_env(rows,cols);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            env[i][j] = map[i * cols + j];
        }
    }
 
    return env;
}

void printPath(Env env, NodeList* solution, int rows, int cols) {
    //TODO
    NodePtr currPoint, nextPoint;
    // Determine what symbol to use by checking where the next node is in the current node
    for (int i = 1; i < solution->getLength() - 1; i++) {
        currPoint = solution->get(i);
        nextPoint = solution->get(i + 1);
        int currRow = currPoint->getRow();
        int currCol = currPoint->getCol();
        int nextRow = nextPoint->getRow();
        int nextCol = nextPoint->getCol();
        if (currRow + 1 == nextRow) {
            // The next node is below the current node
            env[currRow][currCol] = 'v';
        }
        else if (currRow - 1 == nextRow) {
            // The next node is above the current node
            env[currRow][currCol] = '^';
        }
        else if (currCol + 1 == nextCol) {
            // The next node is on the right of the current node
            env[currRow][currCol] = '>';
        }
        else if (currCol - 1 == nextCol) {
            // The next node is on the left of the current node
            env[currRow][currCol] = '<';
        }
        delete currPoint;
        delete nextPoint;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //printf("%c",env[i][j]);
            std::cout << env[i][j];
        }
        if(i<rows-1) std::cout << std::endl;
        // std::cout << std::endl;
    }
}

void printReachablePositions(Env env, NodeList* reachablePositions){
    //TODO
    int i = 0;
    NodePtr temp;
    while (i < reachablePositions->getLength()) {
        temp = reachablePositions->get(i);
        env[temp->getRow()][temp->getCol()] = temp->getDistanceToS() + 'a';
        delete temp;
        i++;
    }
    for (i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }

}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList(100);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}