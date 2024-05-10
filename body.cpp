#include <iostream>
#include <cmath>
#include<chrono>
#include <vector>
#include <math.h> 
#include "node.cpp"

using namespace std;

const double G = 0.6;
const double dt = 0.01;

class Nbody{
    public:
        double mass;
        double x;
        double y;

        double xv = 0;
        double yv = 0;


        vector<Nbody> ignore; // ignore list for body calculations

        Nbody(double x, double y, double mass){
            this->mass = mass;
            this->x = x;
            this->y = y;

        }

        tuple<double, double> force(Nbody other){
            double obj_dist_x, obj_dist_y, dist, force, angle, fx,fy;
            obj_dist_x = other.x - x;
            obj_dist_y = other.y - y;

            dist = sqrt(pow(obj_dist_x, 2)+pow(obj_dist_y,2));
            force = G * mass * other.mass / (pow(dist,2));

            angle = atan2(obj_dist_y, obj_dist_x);

            fx = cos(angle) * force;
            fy = sin(angle) * force;

            return {fx,fy};




        }
        double node_check(Node node){
            double s,d;
            s = node.max_x - node.min_x;
            d = sqrt(pow((x - node.x),2) + pow((y - node.y),2));
            return (s / d);
        }
        void update_position(){
            

        }


}