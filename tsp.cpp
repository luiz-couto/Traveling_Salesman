#include "tsp.hpp"

#define INF 1000000000
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i, a, b) for(int i = int(a); i < int(b); i++)
#define debugLine() cout << "PASSSOUUU AQUUIIII" << endl;
#define debug(x) cout << #x << " = " << x << endl;
#define debug2(x,y) cout << #x << " = " << x << " --- " << #y << " = " << y << "\n";
#define debugA(x, l) { rep(i,0,l) { cout << x[i] << " "; } printf("\n"); }
#define debugM( x, l, c ) { rep( i, 0, l ){ rep( j, 0, c ) cout << x[i][j] << " "; printf("\n");}}
#define setM( x, l, c, k ) { rep( i, 0, l ){ rep( j, 0, c ) x[i][j] = k;}}

#define EUC_2D 1
#define ATT 2

vector<City*> cities;
int distanceType;

int eucliDistance(City* i, City* j) {
    double xd = i->x - j->x;
    double yd = i->y - j->y;
    int distance = round(sqrt(xd*xd + yd*yd));
    return distance;
}

int attDistance(City* i, City* j) {
    double xd = i->x - j->x;
    double yd = i->y - j->y;
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

int getClosestCity(int currCity) {
    int minDist = INT_MAX;
    int cityInd;
    for (City* city : cities) {
        if (city->visited == true || city->index == currCity) continue;

        int distance;
        if (distanceType == ATT) distance = attDistance(cities[currCity], city);
        else distance = eucliDistance(cities[currCity], city);

        if (distance < minDist) {
            cityInd = city->index;
            minDist = distance;
        }

    }
    return cityInd;
}

int getDistance(City *a, City *b) {
    int distance;
    if (distanceType == ATT) distance = attDistance(a, b);
    else distance = eucliDistance(a, b);
    return distance;
}

int getTotalCost(vector<int> tour) {
    int total = 0;
    for (int i=0; i<tour.size()-1; i++) {
        int distance = getDistance(cities[tour[i]], cities[tour[i+1]]);
        total = total + distance;
    }
    total = total + getDistance(cities[tour[0]], cities[tour[tour.size()-1]]);
    return total;
}

int getRandomLRC(int currCity) {
    double alpha = 0.01;
    int greaterDis = 0;
    int smallestDis = 1000000;

    int grtCity, smallCity;

    for (City* city : cities) {
        if (city->visited == true || city->index == currCity) continue;

        int distance = getDistance(cities[currCity], city);

        if (distance < smallestDis) {
            smallCity = city->index;
            smallestDis = distance;
        }

        if (distance > greaterDis) {
            grtCity = city->index;
            greaterDis = distance;
        }

    }

    double limit = double(smallestDis) + (alpha*(double(greaterDis) - double(smallestDis)));

    vector<int> lrc;

    for (City* city : cities) {
        if (city->visited == true || city->index == currCity) continue;
        int distance = getDistance(cities[currCity], city);

        if (double(distance) <= limit) {
            lrc.push_back(city->index);
        }

    }

    srand(time(NULL)+time(NULL)*currCity);
    int selectedPos = rand() % lrc.size();

    return lrc[selectedPos];
} 

void runGreddy(TSP* tsp, int count) {

    srand(time(NULL));
    int currentCity = rand() % count;
    int first = currentCity;
    int cost = 0;

    tsp->tour.push_back(currentCity);

    for (int i=0; i<count-1; i++) {

        cities[currentCity]->visited = true;
        
        int nextCity = getRandomLRC(currentCity);
        int distance;

        tsp->tour.push_back(nextCity);

        if (distanceType == ATT) distance = attDistance(cities[currentCity], cities[nextCity]);
        else distance = eucliDistance(cities[currentCity], cities[nextCity]);
        
        cost += distance;
        currentCity = nextCity;
    }

    int lastDistance;
    if (distanceType == ATT) lastDistance = attDistance(cities[currentCity], cities[first]);
    else lastDistance = eucliDistance(cities[currentCity], cities[first]);

    cost += lastDistance;

    tsp->bestCost = cost;

}

void runOPT(TSP *tsp, int count) {
    runGreddy(tsp, count);
    int size = tsp->tour.size();
    vector<int> bestTour = tsp->tour;

    for (int i=1; i<size-2; i++) {
        for (int j=i+1; j<size; j++) {
            if (j-1 == 1) {
                continue;
            }

            vector<int> newTour(bestTour);

            for (int k=0; (k+i)<j; k++) {
                newTour[k+i] = bestTour[j-k-1];
            }

            if (getTotalCost(newTour) < tsp->bestCost) {
                tsp->tour = newTour;
                tsp->bestCost = getTotalCost(newTour);
            }
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    TSP *tsp = new TSP();

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
        if (line == "EOF") break;

        count++;
        int c = atoi(strtok(&line[0], " "));
        int x = atoi(strtok(NULL, " "));
        int y = atoi(strtok(NULL, " "));

        City *city = new City(x,y,count-1);
        cities.push_back(city);
    }

    for (int i=0; i<10; i++) {
        runOPT(tsp, count);
        for (City* city : cities) {
          city->visited = false;
        } 
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    debug(tsp->bestCost);
    debug(elapsed.count());
    
    return 0;
}