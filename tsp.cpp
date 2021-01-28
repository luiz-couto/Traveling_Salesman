#include "tsp.hpp"

#define INF 1000000000
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i, a, b) for(int i = int(a); i < int(b); i++)
#define debug(x) cout << #x << " = " << x << endl;
#define debug2(x,y) cout << #x << " = " << x << " --- " << #y << " = " << y << "\n";
#define debugA(x, l) { rep(i,0,l) { cout << x[i] << " "; } printf("\n"); }
#define debugM( x, l, c ) { rep( i, 0, l ){ rep( j, 0, c ) cout << x[i][j] << " "; printf("\n");}}
#define setM( x, l, c, k ) { rep( i, 0, l ){ rep( j, 0, c ) x[i][j] = k;}}

#define EUC_2D 1
#define ATT 2

vector<City*> cities;

int eucliDistance(City i, City j) {
    double xd = i.x - j.x;
    double yd = i.y - j.y;
    int distance = round(sqrt(xd*xd + yd*yd));
    return distance;
}

int attDistance(City i, City j) {
    double xd = i.x - j.x;
    double yd = i.y - j.y;
    double rij = sqrt((xd*xd + yd*yd)/10.0);
    int tij = round(rij);

    int distance;
    if (tij < rij) {
        distance = tij + 1;
    } else {
        distance = tij;
    }
    return distance;
}

int getClosestCity(int city) {
    
}

int main() {
    int distanceType;
    string line;
    for (int i=0; i<6; i++) {
        getline(cin, line);
        if (i == 4) {
            if (line.find("ATT") != string::npos) {
                distanceType = ATT;
            } else {
                distanceType = EUC_2D;
            }
        }
    }

    int count = 0;
    while(getline(cin, line)) {
        if (line == "EOF") continue;
        
        count++;
        int c =  atoi(strtok(&line[0], " "));
        int x =  atoi(strtok(NULL, " "));
        int y =  atoi(strtok(NULL, " "));

        City city = City(x,y);
        cities.push_back(&city);
    }

    int currentCity = rand() % count;
    int cost = 0;

    for (int i=0; i<count-1; i++) {
        cities[currentCity]->visited = true;
        int nextCity = getClosestCity(currentCity);
        int distance;
        
        if (distanceType == ATT) distance = attDistance(*cities[currentCity], *cities[nextCity]);
        else distance = eucliDistance(*cities[currentCity], *cities[nextCity]);
        
        cost += distance;
        currentCity = nextCity;
    }
    
    debug(cost);

    return 0;
    
}