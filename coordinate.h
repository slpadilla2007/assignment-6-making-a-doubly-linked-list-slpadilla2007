#ifndef COORDINATE_H
#define COORDINATE_H

struct _coordinate {

	float x;
	float y;
	int coord_id;
	struct _coordinate *next;
	struct _coordinate *prev;

};

typedef struct _coordinate Coordinate;

void addCoordinate(Coordinate *list_end, float x, float y);
void deleteCoordinate(Coordinate *list_begin, int coordToDelete);
void forwardDisplay(Coordinate *list_begin);
void backwardDisplay(Coordinate *list_end);
int listLength(Coordinate *list_begin);
void closestTo(Coordinate *list_begin, float x, float y);

#endif
