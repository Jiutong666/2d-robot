
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols){
	this->rows = rows;
	this->cols = cols;

	if (rows >= 0 && cols >= 0) {
		this->env = new char* [rows];
		for (int i = 0; i != rows; ++i) {
			this->env[i] = new char[cols];
		}
	}

	this->ReachableNodes = new NodeList(rows * cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			this->env[i][j] = env[i][j];
			// find 'S' position
			if (this->env[i][j] == 'S') {
				initialPosition(i, j);
			}
		}
	}
	this->goalId = -1;
}

PathPlanner::~PathPlanner(){
	for (int i = 0; i != rows; ++i) {
		delete env[i];
	}
	delete env;
}

void PathPlanner::initialPosition(int row, int col){
	NodePtr temp = new Node(row, col, 0);
	this->ReachableNodes->addBack(temp);
}

NodeList* PathPlanner::getReachableNodes(){
	NodeList* Close = new NodeList(rows*cols);
	int n = 0;
	while (n < this->ReachableNodes->getLength()) {
		NodePtr p = this->ReachableNodes->get(n);
		if (Close->containsNode(p)) {
			n++;
			continue;
		}
		Close->addBack(p);

		// Check whether the point above the current node is reachable
		NodePtr temp = checkPoint(p->getRow() - 1, p->getCol(), p->getDistanceToS() + 1); // up
		if (temp != NULL) {
			// the point above the current node is reachable
			if (this->env[temp->getRow()][temp->getCol()] == 'G') {
				// Subscript of storage node 'G' in ReachableNodes
				this->goalId = this->ReachableNodes->getLength();
			}
			this->ReachableNodes->addBack(temp);
			delete temp;
		}

		// Check whether the point below the current node is reachable
		temp = checkPoint(p->getRow() + 1, p->getCol(), p->getDistanceToS() + 1); // down
		if (temp != NULL) {
			// the point below the current node is reachable
			if (this->env[temp->getRow()][temp->getCol()] == 'G') {
				// Subscript of storage node 'g' in ReachableNodes
				this->goalId = this->ReachableNodes->getLength();
			}
			this->ReachableNodes->addBack(temp);
			delete temp;
		}

		// Check whether the point on the left of the current node is reachable
		temp = checkPoint(p->getRow(), p->getCol() - 1, p->getDistanceToS() + 1); // left
		if (temp != NULL) {
			// the point on the left of the current node is reachable
			if (this->env[temp->getRow()][temp->getCol()] == 'G') {
				// Subscript of storage node 'G' in ReachableNodes
				this->goalId = this->ReachableNodes->getLength();
			}
			this->ReachableNodes->addBack(temp);
			delete temp;
		}

		// Check whether the point on the right of the current node is reachable
		temp = checkPoint(p->getRow(), p->getCol() + 1, p->getDistanceToS() + 1); // right
		if (temp != NULL) {
			// the point on the right of the current node is reachable
			if (this->env[temp->getRow()][temp->getCol()] == 'G') {
				// Subscript of storage node 'G' in ReachableNodes
				this->goalId = this->ReachableNodes->getLength();
			}
			this->ReachableNodes->addBack(temp);
			delete temp;
		}
		delete p;
		n++;
	}
	Close->clear();
	delete Close;

	NodeList* res = new NodeList(1);
	res->depCpyFromPointer(this->ReachableNodes); // deep copy

	return res;
}

NodeList* PathPlanner::getPath(){
	// pathFromGoal2Start contains the path from the goal point to the start point
	NodeList* pathFromGoal2Start = new NodeList(rows*cols); 
	// get the goal point's row, col and distance
	NodePtr goal = this->ReachableNodes->get(goalId);
	int distance = goal->getDistanceToS();
	// nextRow is used to record the row of the next node
	int nextRow = goal->getRow();
	// nextCol is used to record the col of the next node
	int nextCol = goal->getCol();
	pathFromGoal2Start->addBack(goal);
	delete goal;

	// From the back to the front, find the point with the distance less than 1 in the reachable nodes
	int curr_id = goalId - 1;
	while (curr_id >= 0) {
		NodePtr curr = this->ReachableNodes->get(curr_id);
		if (curr->getDistanceToS() == distance - 1 && checkAdjacentPoints(curr, nextRow, nextCol)) {
			// add the node into pathFromGoal2Start and then update nextRow, nextCol and distance
			NodePtr temp = new Node(curr->getRow(), curr->getCol(), curr->getDistanceToS());
			pathFromGoal2Start->addBack(temp);
			nextRow = curr->getRow();
			nextCol = curr->getCol();
			distance--;
			delete temp;
		}
		curr_id--;
	}

	// Reverse linked list
	NodeList* PathFromStart = new NodeList(rows*cols);
	curr_id = pathFromGoal2Start->getLength() - 1;
	while (curr_id >= 0) {
		NodePtr temp = pathFromGoal2Start->get(curr_id);
		PathFromStart->addBack(temp);
		delete temp;
		curr_id--;
	}

	delete pathFromGoal2Start;
	return PathFromStart;
}



NodePtr PathPlanner::checkPoint(int row, int col, int distacne){
	
	// Check whether the boundary is exceeded
	if (row<0 || col<0 || row>=this->rows || col>=this->cols) {
		return NULL;
	}

	// Check reachable
	if (this->env[row][col] == '.' || this->env[row][col] == 'G') {
		NodePtr temp = new Node(row , col, distacne);
		if (this->ReachableNodes->containsNode(temp)) {
			delete temp;
			return NULL;
		}
		return temp;
	}
	return NULL;
}

bool PathPlanner::checkAdjacentPoints(NodePtr node, int row, int col)
{
	if (node->getCol() == col) {
		// check up and down
		if (node->getRow() == row - 1 || node->getRow() == row + 1) {
			return true;
		}
	}
	else if (node->getRow() == row) {
		// check left and right
		if (node->getCol() == col - 1 || node->getCol() == col + 1) {
			return true;
		}
	}

	return false;
}
