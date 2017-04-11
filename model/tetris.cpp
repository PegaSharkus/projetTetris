#include "tetris.h"
#include "direction.h"
#include <stdexcept>

using namespace GJ_GW;

Tetris::Tetris(std::string &name): timer_ {MAXIMUM_TIMER}, winScore_{validateWinScore(1000)},
    winLines_{validateWinLines(10)}, winTime_{validateWinTime(300000)}, gameState_{GameState::NONE},
    player_{Player(name)}, board_{Board(validateWidth(10), validateHeight(20))}
{}

unsigned Tetris::getTimer() const{
    return timer_;
}

unsigned Tetris::getWinScore() const{
    return winScore_;
}

unsigned Tetris::getWinLines() const{
    return winLines_;
}

unsigned Tetris::getWinTime() const{
    return winTime_;
}

Player Tetris::getPlayer() const{
    return player_;
}

Bric Tetris::getNextBric() const{
    return bag_.getNextBric();
}

Board Tetris::getBoard() const{
    return board_;
}

GameState Tetris::getGameState() const{
    return gameState_;
}

void Tetris::setBag(std::vector<Bric> newBag, bool keepBag){
    if(keepBag){
        bag_.add(newBag);
    } else{
        bag_ = BricsBag(newBag);
    }
}

void Tetris::startGame(std::string name, unsigned width, unsigned height,
                       unsigned winScore, unsigned winLines, unsigned winTime,
                       unsigned level){
    gameState_ = GameState::NONE;
    timer_ = MAXIMUM_TIMER;
    for(unsigned u {0}; u < level; ++u){
        setTimer();
    }
    player_.setPlayer(name);
    board_ = Board(validateWidth(width), validateHeight(height));
    winScore_ = validateWinScore(winScore);
    winLines_ = validateWinLines(winLines);
    winTime_ = validateWinTime(winTime);
    notifyObservers();
    generateBric(true);
}

unsigned Tetris::validateWidth(unsigned width){
    if(width < MINIMUM_WIDTH || width > MAXIMUM_WIDTH){
        throw std::invalid_argument(message("largeur", width, MINIMUM_WIDTH, MAXIMUM_WIDTH));
    }
    return width;
}

unsigned Tetris::validateHeight(unsigned height){
    if(height < MINIMUM_HEIGHT || height > MAXIMUM_HEIGHT){
        throw std::invalid_argument(message("hauteur", height, MINIMUM_HEIGHT, MAXIMUM_HEIGHT));
    }
    return height;
}

unsigned Tetris::validateWinScore(unsigned winScore){
    if(winScore < MINIMUM_WIN_SCORE || winScore > MAXIMUM_WIN_SCORE){
        throw std::invalid_argument(message("score de victoire", winScore, MINIMUM_WIN_SCORE, MAXIMUM_WIN_SCORE));
    }
    return winScore;
}

unsigned Tetris::validateWinLines(unsigned winLines){
    if(winLines < MINIMUM_WIN_LINES || winLines > MAXIMUM_WIN_LINES){
        throw std::invalid_argument(message("nombre de lignes de victoire", winLines, MINIMUM_WIN_LINES, MAXIMUM_WIN_LINES));
    }
    return winLines;
}

unsigned Tetris::validateWinTime(unsigned winTime){
    if(winTime < MINIMUM_WIN_TIME || winTime > MAXIMUM_WIN_TIME){
        throw std::invalid_argument(message("temps de victoire", winTime, MINIMUM_WIN_TIME, MAXIMUM_WIN_TIME));
    }
    return winTime;
}

std::string Tetris::message(const std::string &label, unsigned value, unsigned min, unsigned max) const{
    return label +" non valide : "+ std::to_string(value) +" n'est pas compris entre "+ std::to_string(min) +" et "+ std::to_string(max);
}

void Tetris::generateBric(bool first){
    bool ok {1};
    unsigned count{0};
    bag_.shuffle(first);
    currentBric_ = bag_.getCurrentBric();
    unsigned midBoard = board_.getWidth()/2;
    unsigned midSide = currentBric_.getMiddle().getX() + 1;

    for(unsigned u {0}; u < midBoard-midSide; ++u){
        currentBric_.move(Direction::RIGHT);
    }
    while(ok && count < currentBric_.getShape().size()){
        ok = board_.checkCase(currentBric_.getShape().at(count));
        ++count;
    }

    if(ok){
        for(Position p : currentBric_.getShape()){
            board_.swapCase(p, currentBric_.getColor());
        }
        setGameState(GameState::ON);
    } else{
        setGameState(GameState::LOOSE);
    }
    notifyObservers();
}

void Tetris::drop(){
    unsigned count {0};
    bool ok {1};
    while(ok){
        ok = checkMove(Direction::DOWN, count);
        ++count;
    }
}

bool Tetris::checkMove(Direction dir, unsigned dropsCount){
    bool ok {1};
    unsigned count {0};
    Bric destination = currentBric_;
    destination.move(dir);
    while(ok && count < destination.getShape().size()){
        if(! currentBric_.contains(destination.getShape().at(count))){
            ok = board_.checkCase(destination.getShape().at(count));
        }
        ++count;
    }
    if(ok)
        moveBric(dir);
    if(! ok && dir == Direction::DOWN){
        checkLines(currentBric_.getHigherY(), dropsCount);
        generateBric();
    }
    return ok;
}

void Tetris::checkRotate(){
    bool ok {1};
    unsigned count {0};
    Bric destination = currentBric_;
    destination.rotate();
    while(ok && count < destination.getShape().size()){
        if(! currentBric_.contains(destination.getShape().at(count))){
            ok = board_.checkCase(destination.getShape().at(count));
        }
        ++count;
    }
    if(ok){
        rotateBric();
    }
}

void Tetris::rotateBric(){
    for(Position p : currentBric_.getShape()){
        board_.swapCase(p, Color());
    }
    currentBric_.rotate();
    for(Position p : currentBric_.getShape()){
        board_.swapCase(p, currentBric_.getColor());
    }
    notifyObservers();
}

void Tetris::moveBric(Direction dir){
    for(Position p : currentBric_.getShape()){
        board_.swapCase(p, Color());
    }
    currentBric_.move(dir);
    for(Position p : currentBric_.getShape()){
        board_.swapCase(p, currentBric_.getColor());
    }
    if(dir != Direction::DOWN)
        notifyObservers();
}

void Tetris::checkLines(unsigned top, unsigned dropsCount){
    unsigned linesFilled;
    linesFilled = board_.checkColumn(top);
    if(player_.setNbLines(linesFilled))
        setLevel();
    player_.setScore(dropsCount, linesFilled);
    if(player_.getScore() >= winScore_){
        setGameState(GameState::SCORE);
    } else if(player_.getNbLines() >= winLines_){
        setGameState(GameState::LINE);
    }
    notifyObservers();
}

void Tetris::setGameState(GameState gameState){
    gameState_ = gameState;
}

void Tetris::next(unsigned timeElapsed){
    if(timeElapsed < winTime_){
        checkMove(Direction::DOWN);
    } else{
        setGameState(GameState::TIME);
    }
    notifyObservers();
}

void Tetris::setLevel(){
    if(player_.getNbLines()%2 == 0)
        setTimer();
}

void Tetris::setTimer(){
    if(timer_ > MINIMUM_TIMER)
        timer_ -= 200;
    if(timer_ < MINIMUM_TIMER)
        timer_ = MINIMUM_TIMER;
}
