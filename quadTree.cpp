#pragma once
#include "area.cpp"
#include "node.cpp"
#include "nbody.cpp"

class QuadTree
{
    public:
        Area area;
        Node root;
        int max_depth = 0;
        QuadTree(Area area, int max_depth)
        :  root(area.min_x, area.min_y, area.max_x, area.max_y, 0)
        {
            
            this->area = area;
            this->max_depth = max_depth;
           
            
        }
};