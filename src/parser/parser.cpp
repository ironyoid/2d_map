#include "parser.hpp"
#include "points.hpp"
#include <fstream>
#include <charconv>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

Parser::Parser(string path) : path(path){};

void Parser::WriteLine(Line2D line) {
    std::ofstream output(path.c_str(), std::ifstream::app);
    output << line.ToString() << std::endl;
    output.close();
}

std::pair<std::string, std::string> Parser::FindString(std::string s, std::string del) {
    std::string a, b;
    int end = s.find(del);
    if(std::string::npos != end) {
        a = s.substr(0, end);
        s.erase(s.begin(), s.begin() + end + del.length());
        b = s;
    } else {
        a = "";
        b = "";
    }
    return std::make_pair(a, b);
};

std::optional<Line2D> Parser::ReadLine(string line, uint32_t width, uint32_t height) {
    std::optional<Line2D> ret = std::nullopt;
    Line2D line2d;
    auto [a, b] = FindString(line, ";");
    auto [x1, y1] = FindString(a, ",");
    auto [x2, y2] = FindString(b, ",");
    if((x1 != "") && (y1 != "") && (x2 != "") && (y2 != "")) {
        float xf1, yf1, xf2, yf2;
        std::from_chars(x1.data(), x1.data() + x1.size(), xf1);
        std::from_chars(y1.data(), y1.data() + y1.size(), yf1);
        std::from_chars(x2.data(), x2.data() + x2.size(), xf2);
        std::from_chars(y2.data(), y2.data() + y2.size(), yf2);
        line2d.a.x = static_cast<int32_t>(xf1 * width);
        line2d.a.y = static_cast<int32_t>(yf1 * height);
        line2d.b.x = static_cast<int32_t>(xf2 * width);
        line2d.b.y = static_cast<int32_t>(yf2 * height);
        ret = line2d;
    }
    return ret;
}

std::vector<Line2D> Parser::ReadLines(uint32_t width, uint32_t height) {
    std::vector<Line2D> ret;
    std::ifstream input(path.c_str(), std::ifstream::in);
    if(!input.fail()) {
        for(std::string line; getline(input, line);) {
            auto res = ReadLine(line, width, height);
            if(res) {
                ret.push_back(res.value());
            }
        }
    }
    return ret;
}

void Parser::WriteLines(std::vector<Line2D> lines, Point2D position) {
    std::ofstream output(path.c_str(), std::ifstream::out | std::ofstream::trunc);
    for(auto n : lines) {
        output << n.ToStringNormalized(position) << std::endl;
    }
    output.close();
}