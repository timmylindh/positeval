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
Point f[MAX_BODIES][MAX_BODIES];
double* m = new double[MAX_BODIES];
const double G = 6.67e-11;
const int DT = 1;
const int COLUMNS = 200;
const int ROWS = 200;

void addPoint(Point & p, double dx, double dy) {
    p.mtx.lock();
    p.x += dx;
    p.y += dy;
    p.mtx.unlock();
}

void calculateForces() {
    double distance, magnitude; 
    Point direction;
    //#pragma omp for schedule(dynamic)
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
            addPoint(f[i][j], magnitude*direction.x/distance, magnitude*direction.y/distance);
            addPoint(f[j][i], -magnitude*direction.x/distance, -magnitude*direction.y/distance);
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
    //#pragma omp for schedule(static)
    for (int i = 0; i<n; i++) {
        //sum the forces on body i and reset f[*,i]
        for (int k = 0; k<numWorkers; k++) {
            force.x += f[k][i].x; 
            force.y += f[k][i].y; 
            f[k][i].x = 0.0;
            f[k][i].y = 0.0;
        }
        deltav.x = force.x/m[i] * DT;
        deltav.y = force.y/m[i] * DT;
        
        deltap.x = (v[i].x + deltav.x/2) * DT;
        deltap.y =  (v[i].y + deltav.y/2) * DT;

        v[i].x = v[i].x + deltav.x;
        v[i].y = v[i].y + deltav.y;
        p[i].x = p[i].x + deltap.x;
        p[i].y = p[i].y + deltap.y;
        force.x = force.y = 0.0;
        printf("Body %d: x: %f y: %f\n", i, p[i].x, p[i].y);
    } 
}
void run(){
    //run the simulation with time steps of DT
    #pragma omp parallel 
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
        x = randZeroToOne() * COLUMNS;
        y = randZeroToOne() * ROWS;
        p[i].x = x;
        p[i].y = y;

        x = randZeroToOne()*5;
        y = randZeroToOne()*5;
        v[i].x = 0;
        v[i].y = 0;

        for (int worker = 0; worker < numWorkers; worker++) {
            x = randZeroToOne();
            y = randZeroToOne();
            f[worker][i].x = 0;
            f[worker][i].y = 0;
        }

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
    numWorkers = stoi(argv[3]);
    printf("%d threads\n", numWorkers);
    //omp_set_num_threads(numWorkers);

    finish = DT*steps;

    // for(int i = 0; i<numWorkers; i++){
    //     f[i] = new Point[1];
    // }
    init();
    printf("init done2.\n");
    double start_time = omp_get_wtime();
    run();
    double end_time = omp_get_wtime();
    double delta = end_time - start_time;
    printf("\nFinished in %lf.\n", delta);
    return 0;
}