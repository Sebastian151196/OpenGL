#ifndef GETBMP_H
#define GETBMP_H
#include <string.h>
#include <iostream>
using namespace std;

struct BitMapFile
{
   int sizeX;
   int sizeY;
   unsigned char *data;
};

BitMapFile *getBmp(string filename);

#endif