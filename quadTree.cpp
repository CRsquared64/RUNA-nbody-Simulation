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
        bool check_in_range(Nbody body)
        {
            if (area.min_x < body.x <= area.max_x)
            {
                if (area.min_y <= body.y < area.max_y)
                {
                    return true;
                }
                else
                {return false;}
            }
            else
            {return false;}
        }
};