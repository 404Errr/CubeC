#include <math.h>

#ifndef DATA_H_
#define DATA_H_

namespace std {
int Y = 0, X = 1, Z = 2;

int DEPTH = 30;
int HEIGHT = 30;
int WIDTH = 30;

float PIECE_COUNT_RATIO = ((WIDTH+HEIGHT+DEPTH)/(float)3)*2-1;
int PIECE_SIZE_MIN_OFFSET = (int) ((WIDTH+HEIGHT+DEPTH)/3%3), PIECE_SIZE_MAX_OFFSET = (int) ((WIDTH+HEIGHT+DEPTH)/3%3);

int PIECE_COUNT = (int) (WIDTH*HEIGHT*DEPTH/PIECE_COUNT_RATIO);
int PIECE_SIZE_MIN = (int) (floor((WIDTH*HEIGHT*DEPTH)/(float) PIECE_COUNT)-PIECE_SIZE_MIN_OFFSET);
int PIECE_SIZE_MAX = (int) (ceil((WIDTH*HEIGHT*DEPTH)/(float) PIECE_COUNT)-PIECE_SIZE_MAX_OFFSET);

bool PRINT_CHECK = false;

int BORING_PLANE_COUNT = PIECE_SIZE_MAX-(ceil((PIECE_SIZE_MAX-PIECE_SIZE_MIN)/(float)2));
int MAX_2D_CLUSTERS = (int) ((((WIDTH+HEIGHT+DEPTH)/(float)3)-3)*3)+1;
int MAX_3D_CUBIES = 5;
bool CHECK_3D = true;
bool CHECK_IDENTICAL = true;
bool CHECK_TOO_MANY_ON_PLANE = true;
bool CHECK_DIAGONAL_COLLISION = true;
bool CHECK_SURROUND_COLLISION = true;

}

#endif
