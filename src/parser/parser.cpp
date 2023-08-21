#include "parser.hpp"
#include "points.hpp"
#include <fstream>

Parser::Parser(string path) : path(path){};

void Parser::WriteLine(Line2D line) {
    std::ofstream output(path.c_str(), std::ifstream::app);
    output << line.ToString() << std::endl;
    output.close();
}

void Parser::WriteLines(std::vector<Line2D> lines, Point2D position) {
    std::ofstream output(path.c_str(), std::ifstream::out | std::ofstream::trunc);
    for(auto n : lines) {
        output << n.ToStringNormalized(position) << std::endl;
    }
    output.close();
}