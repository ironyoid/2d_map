#pragma once
#include <iostream>
#include <string>
#include <stdint.h>
#include "points.hpp"
#include <optional>
#include <sys/types.h>
#include <vector>
#include <utility>

class Parser
{
    string path;

   public:
    Parser(string path);
    void WriteLine (Line2D line);
    void WriteLines (std::vector<Line2D> lines, Point2D position);
};