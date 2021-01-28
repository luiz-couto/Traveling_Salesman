#ifndef TSP_H
#define TSP_H

#include <bits/stdc++.h>

using namespace std;

struct City {
    int x;
    int y;
    int index;
    bool visited;
    City(int x, int y, int index) {
        this->x = x;
        this->y = y;
        this->index = index;
        this->visited = false;
    }
};

#endif