import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.CyclicBarrier;

class Nbody{
    
    static final double G = 6.67e-11;
    final int COLUMNS = 10;
    final int ROWS = 10;
    Point[] p;
    Point[] v;
    Point[] f;
    double[] m;
    double time;
    double start = 0.0;
    double finish;
    double DT;
    int moves = 0;
    int interactions = 0;

    public Nbody(int n, int steps){
        p = new Point[n];
        v = new Point[n];
        f = new Point[n];
        m = new double[n];
        DT = 1;
        finish = steps*DT;

        init(n);
        runSims4(n);

    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int steps = Integer.parseInt(args[1]);
        new Nbody(n, steps);
        System.out.println("Hej");
    }


    public void init(int n){
        Random rand = new Random();
        double x, y;
        for(int i = 0; i<n; i++){
            //randomly spaces out bodies in a grid
            x = rand.nextDouble() * COLUMNS;
            y = rand.nextDouble() * ROWS;
            p[i] = new Point(x, y, i);

            x = rand.nextDouble()*5;
            y = rand.nextDouble()*5;
            v[i] = new Point(0, 0);

            x = rand.nextDouble();
            y = rand.nextDouble();
            f[i] = new Point(0, 0);

            m[i] = rand.nextDouble()*10e+6;

        }
    }

    //double G = 6.67e-11;
    /*
    initialize the positions, velocities, forces, and masses;
    # calculate total force for every pair of bodies
    */

    public void calculateForces(int n) {
        double distance, magnitude; 
        Point direction;
        for (int i = 0; i <n-1; i++){
            for (int j = i+1; j < n; j++) {
                distance = Math.sqrt(Math.pow((p[i].x - p[j].x),2) +
                Math.pow((p[i].y - p[j].y),2));
                distance = Math.max(distance, 0.1);
                magnitude = (G*m[i]*m[j]) / Math.pow(distance,2);
                direction = new Point(p[j].x-p[i].x, p[j].y-p[i].y);
                f[i].x = f[i].x + magnitude*direction.x/distance;
                f[j].x = f[j].x - magnitude*direction.x/distance;
                f[i].y = f[i].y + magnitude*direction.y/distance;
                f[j].y = f[j].y - magnitude*direction.y/distance;

            }
        }
    }

    public void moveBodies(int n) {
        Point deltav;
        Point deltap;
        for (int i = 0; i < n; i++) {
            //System.out.println("Body " + p[i].id + ": x: " + p[i].x + " y: " + p[i].y);
            deltav = new Point(f[i].x / m[i] * DT, f[i].y / m[i] * DT);
            deltap = new Point((v[i].x + deltav.x/2) * DT, 
                                (v[i].y + deltav.y/2) * DT);
            v[i].x = v[i].x + deltav.x;
            v[i].y = v[i].y + deltav.y;
            p[i].x = p[i].x + deltap.x;
            p[i].y = p[i].y + deltap.y;
            f[i].x = f[i].y = 0.0; // reset force vector
            ///System.out.println("Body " + p[i].id + ": x: " + p[i].x + " y: " + p[i].y);
        }
    }

    public void runSims4(int n) {
    // Run the simulation with time steps of DT
        long t1 = System.nanoTime();
        for (time = start; time < finish; time += DT) {
            calculateForces(n);
            moveBodies(n);
        }
        long t2 = System.nanoTime();
        System.out.println("Completed in " + (t2 - t1) / 1E6 + "ms");
    }
}

