#pragma once
#include <iostream>
#include <variant>
#include <array>
#include "nbody.cpp"
#include "area.cpp"

class Node
{
public:
    Area area;
    int depth;
    using ChildrenVariant = std::variant<Nbody, Node>; // holds objects
    std::array<std::optional<ChildrenVariant>, 4> childrenArray;  // Use std::optional to delay initialization

    double x = 0;
    double y = 0;
    double mass = 0;

    double min_x, min_y, max_x, max_y;


    Node(double min_x, double min_y, double max_x, double max_y, int depth)
        : area(min_x, min_y, max_x, max_y), depth(depth)
    {
        this->min_x = min_x;
        this->min_y = min_y;
        this->max_x = max_x;
        this->max_y = max_y;
        childrenArray.fill(std::nullopt); // fill it with NOTHING
    }
    

    Node() : area(0, 0, 0, 0), depth(0)
    {
        childrenArray.fill(std::nullopt);
    }
    void insert_child(int index, ChildrenVariant child)
    {
        if (index >= 0 && index < 4) {
            childrenArray[index] = std::move(child);
        }
    }


    void update_mass()
    {
        int count = 0;
        double massTemp = 0.0;
        double xTemp = 0.0;
        double yTemp = 0.0;

        for (auto &child : childrenArray)
        {
            if (child)
            {
                std::visit([&](auto &childObj)
                {
                    xTemp+= childObj.x;
                    yTemp += childObj.y;

                    massTemp += childObj.mass;
                    count++;
                }, *child);

            }
        }
        if (count != 0)
        {
            x = xTemp / count;
            y = yTemp / count;

            mass = massTemp;


         }

    }   
};
