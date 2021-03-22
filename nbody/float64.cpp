#include <omp.h>
#include <iostream>
#include <string>
#include <mutex>
#include <stdlib.h>
#include <math.h>

using namespace std;
//test comment
typedef struct Point{
    double x;
    double y;
    mutex mtx;
} Point;

const int MAX_BODIES = 500;

int numWorkers, finish;
int n;
Point* p = new Point[MAX_BODIES];
Point* v = new Point[MAX_BODIES];
Point* f= new Point[MAX_BODIES];
double* m = new double[MAX_BODIES];
const double G = 6.67e-11;
const int DT = 1;
const int X_GRID = 10;
const int Y_GRID = 10;


void calculateForces() {
    double distance, magnitude; 
    Point direction;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            distance = sqrt( pow((p[i].x - p[j].x), 2) +
                pow((p[i].y - p[j].y), 2));
            if (distance < 0.2) {
                distance = 0.2;
            }
            magnitude = (G*m[i]*m[j]) / pow(distance, 2);
            direction.x = p[j].x-p[i].x;
            direction.y = p[j].y-p[i].y;
            f[i].x += magnitude*direction.x/distance;
            f[i].y += magnitude*direction.y/distance;

            f[j].x -= magnitude*direction.x/distance;
            f[j].y -= magnitude*direction.y/distance;
        }
    }
}

//move the bodies assigned to worker w
void moveBodies() {
    Point deltav; //# dv=f/m * DT
    Point deltap; // dp=(v+dv/2) * DT
    Point force; //(0.0, 0.0);
    force.x=0.0;
    force.y=0.0;
    for (int i = 0; i<n; i++) {

        force.x += f[i].x; 
        force.y += f[i].y; 
        f[i].x = 0.0;
        f[i].y = 0.0;
        
        deltav.x = force.x/m[i] * DT;
        deltav.y = force.y/m[i] * DT;
        
        deltap.x = (v[i].x + deltav.x/2) * DT;
        deltap.y =  (v[i].y + deltav.y/2) * DT;

        v[i].x = v[i].x + deltav.x;
        v[i].y = v[i].y + deltav.y;
        p[i].x = p[i].x + deltap.x;
        p[i].y = p[i].y + deltap.y;
        force.x = force.y = 0.0;
        if(i==0){
            printf("Body %d: x: %f y: %f\n", i, p[i].x, p[i].y);
        }

    } 
}
void run(){
    //run the simulation with time steps of DT
    for(int i = 0; i<finish; i+=DT) {
        calculateForces();
        moveBodies();
    } 
}


double randZeroToOne() {
    return rand() / (RAND_MAX + 1.);
}

void init(){
    double x, y;
    
    for(int i = 0; i<n; i++){
        //randomly spaces out bodies in a grid
        x = randZeroToOne() * X_GRID;
        y = randZeroToOne() * Y_GRID;
        p[i].x = x;
        p[i].y = y;

        v[i].x = 0;
        v[i].y = 0;

        f[i].x = 0;
        f[i].y = 0;
        

        m[i] = randZeroToOne()*10e+6;
    }
}




int main(int argc, char* argv[]){
    n = stoi(argv[1]);
    if (n > MAX_BODIES) {
        printf("NO.");
        exit(1);
    }
    int steps = stoi(argv[2]);
    printf("%d threads\n", numWorkers);
    //omp_set_num_threads(numWorkers);

    finish = DT*steps;

    init();

    run();

    return 0;
}