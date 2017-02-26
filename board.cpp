#include "board.h"
#include <stdexcept>
#include <ostream>
#include <iomanip>

namespace g40853{

Board::Board(unsigned width, unsigned height):
width_{width}, height_{height}
{
    for(unsigned i = 0; i < height; ++i){
        for(unsigned j = 0; j < width; ++j){
            grid_.push_back(Position(j,i));
        }
    }
}



std::vector<unsigned> Board::checkLines(){
    std::vector<unsigned> filledLines;
    unsigned check {0}, y {0};
    for(Position p : grid_){
        if(y == p.getY()){
            if(p.isFilled()){
                ++check;
                if(check == width_){
                    filledLines.push_back(p.getY());
                }
            }
        } else{
            check = 0;
        }
    }
    return filledLines;
}

void Board::line(unsigned lineNum){
    for(Position p : grid_){
        if(p.getY() == lineNum){
            p.swapFilled();
        }
    }
}

/*std::string Board::to_string() const{
    std::string s;
    for(Position p : grid_){
        s += "|";
        (p.isFilled())? s+="B" : s+=" ";
        if(p.getX() == width_){
            s += "|\n";
        }
    }
    return s;
}

std::ostream & operator<<(std::ostream & out, const Board & in){
    out << in.to_string();
    return out;
}*/

}
