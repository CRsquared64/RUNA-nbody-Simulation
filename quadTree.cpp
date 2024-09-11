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
        int get_quadrant(Nbody body, Area area)
        {
            float mid_x = (area.min_x + area.max_x) / 2;
            float mid_y = (area.min_y + area.max_y) / 2;
            
            if (body.x < mid_x)
            {
                if (body.y < mid_y)
                {
                    return 2;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if (body.y < mid_y)
                {
                    return 3;
                }
                else
                {
                    return 1;
                }
            }


        }
        void subdivide(Node node, int quadrant)
        {
            float mid_x = (node.min_x + node.max_x) / 2;
            float mid_y = (node.min_y + node.max_y) / 2;
            switch(quadrant)
            {
                case 0:
                    std::visit
            }
        }
    

        

};