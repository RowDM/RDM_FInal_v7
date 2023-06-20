#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

#include "../config.hpp"


typedef std::pair<size_t, size_t> Point;
typedef std::pair<Point, Point> Move;
class Board{
  public:
    char board[2][BOARD_H][BOARD_W] = {{
      //white
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},
    }, {
      //black
      {6, 5, 4, 3, 2},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }};
};

enum GameState {
  UNKNOWN = 0,
  WIN,
  DRAW,
  NONE
};

class StepInfo{
  //friend class State;
  public:
  StepInfo(Move pastmove,Move currmove, int nodeval, int nodedepth, int iteration): pastmove(pastmove), currmove(currmove), nodeval(nodeval), nodedepth(nodedepth),iteration(iteration){};
  Move currmove;
  Move pastmove;
  int nodeval;
  int nodedepth;
  int iteration;
};

class State{
  public:
    //You may want to add more property for a state
    GameState game_state = UNKNOWN;
    Board board;
    int player = 0;
    std::vector<Move> legal_actions;
    
    State(){};
    State(int player): player(player){};
    State(Board board): board(board){};
    State(Board board, int player): board(board), player(player){};
    
    int evaluate();
    // int minimax(State* root, int maxdepth,bool ismaximizingplayer, Move currmove);
    // Move maximizerootnode(State* root,int depth);
    //int alphabeta(State* root, int maxdepth,int alpha, int beta, bool ismaximizingplayer, std::vector<StepInfo> sinfo,Move pastmove);
    Move bestmove;
    State* next_state(Move move);
    void get_legal_actions();
    std::string encode_output();
    std::string encode_state();
};

#endif