#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>

const double G = 0.6;
const double dt = 0.01;
const double threshold = 4;

class Nbody {
public:
    double mass;
    double x, y;
    double xv, yv;
    double fx, fy;
    double radius;
    std::vector<Nbody*> ignore;

    Nbody(double x, double y, double mass = 1) : x(x), y(y), mass(mass), xv(0), yv(0), fx(0), fy(0), radius(1) {}

    std::tuple<double, double> force_calculation(Nbody* other) {
        double obj_x = other->x;
        double obj_y = other->y;
        double obj_dist_x = obj_x - x;
        double obj_dist_y = obj_y - y;

        double dist = std::sqrt(obj_dist_x * obj_dist_x + obj_dist_y * obj_dist_y);
        double force = (G * mass * other->mass) / (dist * dist);

        double angle = std::atan2(obj_dist_y, obj_dist_x);

        double force_x = std::cos(angle) * force;
        double force_y = std::sin(angle) * force;

        return std::make_tuple(force_x, force_y);
    }

    double node_check(Node* node) {
        double s = node->max_x - node->min_x;
        double distance_x = x - node->x;
        double distance_y = y - node->y;
        double d = std::sqrt(distance_x * distance_y);
        double s_d = s / d;
        return s_d;
    }

    void update_position(std::vector<Nbody*>& bodies) {
        double total_fx = 0;
        double total_fy = 0;
        double total_impulse_x = 0;
        double total_impulse_y = 0;

        for (auto& body : bodies) {
            if (body == this || std::find(ignore.begin(), ignore.end(), body) != ignore.end()) continue;

            double fx, fy;
            std::tie(fx, fy) = force_calculation(body);
            if (dynamic_cast<Nbody*>(body)) {
                double impulse_x, impulse_y;
                std::tie(impulse_x, impulse_y) = collide(body);
                total_impulse_x += impulse_x * body->mass;
                total_impulse_y += impulse_y * body->mass;
            }
            total_fx += fx;
            total_fy += fy;
        }

        xv += total_fx / mass * dt;
        yv += total_fy / mass * dt;

        xv -= total_impulse_x;
        yv -= total_impulse_y;
    }

    void final_update() {
        x += xv * dt;
        y += yv * dt;
    }

    void eat_me(Nbody* other) {
        double rel_pos_x = other->x - x;
        double rel_pos_y = other->y - y;
        double dist = std::sqrt(rel_pos_x * rel_pos_x + rel_pos_y * rel_pos_y);
        if (dist < 2 * threshold) {
            mass += other->mass;
            x = (other->x + x) / 2;
            y = (other->y + y) / 2;

            xv += other->xv;
            yv += other->yv;
            radius += other->radius;

            other->x = -100000;
            other->y = -100000;
        }
    }

    std::tuple<double, double> collide(Nbody* other) {
        double rel_pos_x = other->x - x;
        double rel_pos_y = other->y - y;
        double rel_vel_x = other->xv - xv;
        double rel_vel_y = other->yv - yv;
        double dist = std::sqrt(rel_pos_x * rel_pos_x + rel_pos_y * rel_pos_y);

        if (dist < 2 * threshold) {
            ignore.push_back(other);
            double normal_x = rel_pos_x / dist;
            double normal_y = rel_pos_y / dist;
            double vel_along_normal = rel_vel_x * normal_x + rel_vel_y * normal_y;

            if (vel_along_normal < 0) {
                double impulse_scalar = -2 * vel_along_normal / (mass + other->mass);
                double impulse_x = impulse_scalar * normal_x * 0.8;
                double impulse_y = impulse_scalar * normal_y * 0.8;
                return std::make_tuple(impulse_x, impulse_y);
            }
        }

        if (std::find(ignore.begin(), ignore.end(), other) != ignore.end() && dist > 2 * 10) {
            ignore.erase(std::remove(ignore.begin(), ignore.end(), other), ignore.end());
        }

        return std::make_tuple(0, 0);
    }
};
