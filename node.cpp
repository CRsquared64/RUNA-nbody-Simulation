#include <iostream>
#include "area.cpp"

class Node {
public:
    Node* children[4];
    int min_x, min_y, max_x, max_y;
    area childArea; 
    area Area;

    int x,y,mass;

    Node(int Min_x, int Min_y, int Max_x, int Max_y) 
        : min_x(Min_x), min_y(Min_y), max_x(Max_x), max_y(Max_y), Area(Min_x, Min_y, Max_x, Max_y) {
        for (int i = 0; i < 4; ++i) {
            children[i] = nullptr;
        }
    }

    void update_child_area(){
        int count = 0;
        int total_mass = 0;
        int sum_x = 0;
        int sum_y = 0;


    }
};
