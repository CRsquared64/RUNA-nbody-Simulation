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
        bool check_in_range(const Nbody& body) const 
        {
            return (body.x >= area.min_x && body.x <= area.max_x) &&
                (body.y >= area.min_y && body.y <= area.max_y);
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
        void subdivide(Node& node, int quadrant) {
            float mid_x = (node.min_x + node.max_x) / 2;
            float mid_y = (node.min_y + node.max_y) / 2;

            switch (quadrant) {
                case 0: {
                    auto insertNode = std::make_unique<Node>(node.min_x, mid_y, mid_x, node.max_y, node.depth + 1);
                    node.insertAt(0, std::move(insertNode));
                    break;
                }
                case 1: {
                    auto insertNode = std::make_unique<Node>(mid_x, mid_y, node.max_x, node.max_y, node.depth + 1);
                    node.insertAt(1, std::move(insertNode));
                    break;
                }
                case 2: {
                    auto insertNode = std::make_unique<Node>(node.min_x, node.min_y, mid_x, mid_y, node.depth + 1);
                    node.insertAt(2, std::move(insertNode));
                    break;
                }
                case 3: {
                    auto insertNode = std::make_unique<Node>(mid_x, node.min_y, node.max_x, mid_y, node.depth + 1);
                    node.insertAt(3, std::move(insertNode));
                    break;
                }
                default:
                    std::cerr << "Invalid quadrant: " << quadrant << std::endl;
                    break;
            }
        }
                

    };