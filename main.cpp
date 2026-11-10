#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "coordinate.h"
//Function prototypes are in coordinate.h file
using namespace std;

int main(int argc, char **argv) {
	
	//Sets total to given argument using stoi function
	char *input = argv[1];
	int total = stoi(input);
	
	//If total is negative or 0, prints error message and ends code
	if (total <= 0) {
		cout << "Invalid coordinate total." << endl;
		return 1;
	}
	
	//Uses time seed for random generation
	srand(time(0));
	float theX = rand() % 101;
	float theY = rand() % 101;
	
	//Makes head and tail pointers
	Coordinate *head = nullptr;
	Coordinate *tail = nullptr;
	
	//First node
	head = new Coordinate;
	head->x = theX;
	head->y = theY;
	head->coord_id = 0;
	head->next = nullptr;
	head->prev = nullptr;
	tail = head;

	//Creates all needed nodes
	for (int i = 1; i < total; i++) {
		theX = rand() % 101;
		theY = rand() % 101;
		addCoordinate(tail, theX, theY);
		//Sets tail to new last node
		tail = tail->next;
	}
	
	//Displays list length
	cout << "Total number of coordinates: " << listLength(head) << endl;
	
	//Calls forward display function
	forwardDisplay(head);

	//Calls backward display function
	backwardDisplay(tail);

	//Calls closest to function
	theX = rand() % 101;
	theY = rand() % 101;
	closestTo(head, theX, theY);
	
	//Deletes all coordinates
	for (int i = 0; i < total; i++) {
		deleteCoordinate(head, i);
	}
	
	//Code done yippee
	return 0;

}

void addCoordinate(Coordinate *list_end, float x, float y) {
	
	//Returns error message and ends function if given a null pointer
	//I added this to every function
	if (list_end == nullptr) {
		cout << "Please create first node in main." << endl;
		return;
	}
	
	//Makes new coordinate
	Coordinate *newCoord = new Coordinate;
	newCoord->x = x;
	newCoord->y = y;
	newCoord->next = nullptr;
	newCoord->prev = list_end;
	newCoord->coord_id = newCoord->prev->coord_id + 1;
	
	//Sets the next of the previous node to the newCoord
	newCoord->prev->next = newCoord;

}

void deleteCoordinate(Coordinate *list_begin, int coordToDelete) {
	
	if (list_begin == nullptr) {
		cout << "No coordinates to delete." << endl;
		return;
	}

	Coordinate *temp = list_begin;

	while (temp != nullptr) {
		if (temp->coord_id == coordToDelete) {
			if (temp->prev != nullptr) {
				temp->prev->next = temp->next;
			}

			if (temp->next != nullptr) {
				temp->next->prev = temp->prev;
			}
			
			delete temp;
			cout << "Coordinate of ID " << coordToDelete << " deleted." << endl;
			
			return;
		} else {
			temp = temp->next;
		}
	}
	
	//If no return has happened (i.e. no coordinate of the given ID was found), prints error message
	cout << "No coordinate of ID " << coordToDelete << " found." << endl;
	
}

void forwardDisplay(Coordinate *list_begin) {

	if (list_begin == nullptr) {
		cout << "No coordinates to display." << endl;
		return;
	}

	Coordinate *temp = list_begin;

	cout << "\nForward Display:" << endl;

	while (temp != nullptr) {
		cout << "\nCoordinate " << temp->coord_id << endl;
		cout << "(" << temp->x << ", " << temp->y << ")" << endl;
		temp = temp->next;
	}

}

void backwardDisplay(Coordinate *list_end) {
	
	if (list_end == nullptr) {
		cout << "No coordinates to display." << endl;
		return;
	}

	Coordinate *temp = list_end;

	cout << "\nBackward Display:" << endl;

	while (temp != nullptr) {
		cout << "\nCoordinate " << temp->coord_id << endl;
		cout << "(" << temp->x << ", " << temp->y << ")" << endl;
		temp = temp->prev;
	}

}

int listLength(Coordinate *list_begin) {
	
	if (list_begin == nullptr) {
		cout << "No coordinates made." << endl;
		return 0;
	}

	int length = 0;

	Coordinate *temp = list_begin;

	//While the end hasn't been reached, adds to length
	while (temp != nullptr) {
		length++;
		temp = temp->next;
	}

	//Returns length
	return length;

}

void closestTo(Coordinate *list_begin, float x, float y) {

	if (list_begin == nullptr) {
		cout << "No coordinates made." << endl;
		return;
	}

	Coordinate *temp = list_begin;
	Coordinate *closest = nullptr;
	
	//Sets minimum distance to the initial distance between the first pt and given pt
	//Might or might not be the actual smallest distance
	float minDist = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));
	float dist = 0;
	
	//Calculates distance
	while (temp != nullptr) {
		dist = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));

		if (dist <= minDist) {
			minDist = dist;
			closest = temp;
		}

		temp = temp->next;
	}

	if (closest != nullptr) {
		cout << "\nThe closest point to (" << x << ", " << y << ") is coordinate "
			<< closest->coord_id << ", (" << closest->x << ", " << closest->y
			<< "). They have a distance of " << minDist << "." << endl;
	} else {
		cout << "No closest point found." << endl;
	}

}
