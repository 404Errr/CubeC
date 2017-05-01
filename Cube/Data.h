#include <math.h>

#ifndef DATA_H_
#define DATA_H_

namespace std {

int Y = 0, X = 1, Z = 2;

int DEPTH = 3;
int HEIGHT = 3;
int WIDTH = 3;

float PIECE_COUNT_RATIO = ((WIDTH+HEIGHT+DEPTH)/(float)3)*2-1;
int PIECE_SIZE_MIN_OFFSET = (int) ((WIDTH+HEIGHT+DEPTH)/3%3), PIECE_SIZE_MAX_OFFSET = (int) ((WIDTH+HEIGHT+DEPTH)/3%3);

int PIECE_COUNT = (int) (WIDTH*HEIGHT*DEPTH/PIECE_COUNT_RATIO);
int PIECE_SIZE_MIN = (int) (floor((WIDTH*HEIGHT*DEPTH)/(float) PIECE_COUNT)-PIECE_SIZE_MIN_OFFSET);
int PIECE_SIZE_MAX = (int) (ceil((WIDTH*HEIGHT*DEPTH)/(float) PIECE_COUNT)-PIECE_SIZE_MAX_OFFSET);

bool PRINT_CHECK = false;
bool RUN_CHECKS = true;

bool CHECK_FLAT = true;
bool CHECK_TOO_MANY_ON_PLANE = true;
int PLANE_COUNT = PIECE_SIZE_MAX-(ceil((PIECE_SIZE_MAX-PIECE_SIZE_MIN)/(float)2));
bool CHECK_2D = true;
int MAX_2D_CLUSTERS = 1;//(int) ((((WIDTH+HEIGHT+DEPTH)/(float)3)-3)*3)+1;
bool CHECK_3D = true;
int MAX_3D_CUBIES = 5;
//bool CHECK_IDENTICAL = true;
bool CHECK_DIAGONAL_COLLISION = false;
bool CHECK_SURROUND_COLLISION = false;

}

#endif
