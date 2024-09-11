#pragma once
#include <iostream>
#include <variant>
#include <array>
#include "nbody.cpp"
#include "area.cpp"

class Blank {
public:
    Blank() : name("Unknown") {}
    Blank(const std::string& n) : name(n) {}

    void print() const {
        std::cout << "Blank: " << name << std::endl;
    }

private:
    std::string name;
};
class Node
{
public:
    Area area;
    int depth;
    using NodeContent = std::variant<Nbody, Blank, std::unique_ptr<Node>>;

    // Array to hold exactly 4 NBody or Node objects
    std::array<NodeContent, 4> contents;

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
         // fill it with NOTHING
    }
    

    Node() : area(0, 0, 0, 0), depth(0)
    {
        for (auto& item : contents) {
            item = Blank();  // All array elements are initially Blank
        }
    }
    void insertAt(size_t index, NodeContent content) {
        if (index < contents.size()) {
            contents[index] = std::move(content);  // Use move assignment
        } else {
            std::cerr << "Error: Index out of bounds." << std::endl;
        }
    }
    void update_mass()
    {
        int count = 0;
        double massTemp = 0.0;
        double xTemp = 0.0;
        double yTemp = 0.0;

        for (const auto& childObj : contents) {
            std::visit([&](auto&& obj) {
                using T = std::decay_t<decltype(obj)>;
                if constexpr (std::is_same_v<T, Nbody>) {
                    xTemp += obj.x;
                    yTemp += obj.y;
                    massTemp += obj.mass;
                    count++;
                } else if constexpr (std::is_same_v<T, Node>) { // Update the mass of the child node first
                    xTemp += obj.x;
                    yTemp += obj.y;
                    massTemp += obj.mass;
                    count++;
                }
            }, childObj);
        }
        if (count != 0)
        {
            x = xTemp / count;
            y = yTemp / count;

            mass = massTemp;


         }

    }   
};
