#pragma once
class Area
{
public:
    double min_x, min_y, max_x, max_y;
    Area(double min_x, double min_y, double max_x, double max_y)
    {
        this->min_x = min_x;
        this->min_y = min_y;
        this->max_x = max_x;
        this->max_y = max_y;
    }
    Area() : min_x(0), min_y(0), max_x(0), max_y(0) {};
};