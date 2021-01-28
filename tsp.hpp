#ifndef TSP_H
#define TSP_H

#include <bits/stdc++.h>

using namespace std;

struct City {
    int x;
    int y;
    bool visited;
    City(int x, int y) {
        this->x = x;
        this->y = y;
        this->visited = false;
    }
};

#endif