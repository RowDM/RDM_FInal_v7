#include <cstdlib>
#include <iostream>
#include <fstream>

#include "../state/state.hpp"
#include "./pieceval.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Pval::get_move(State *state, int depth){
 std::ofstream rowan_debug("rowdebug.txt", std::ios::app);
//rowan_debug<<"get_move accesed"<<'\n';

  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;

  Point to;
  // legal_actions is a vector of Moves
  //we are only interested on the "to" so only accessing the legal_actions.second stuff
  //it seems type Move gives the coordinates
  int maxval;
  Move bestmove;
  //rowan_debug<<"before for loop"<<'\n';
  //rowan_debug<<"size:"<<actions.size()<<'\n';
  for(int i=0;i<actions.size();i++)
  {
    rowan_debug<<"accessed forloop: "<<i<<'\n';
    //board is a 3d matrix
    // State* self_board;
    // self_board=state;
    //currb= state->board.board[state->player];
    //State* state=state;


    int fromy=actions[i].first.first;
    int fromx=actions[i].first.second;
    int toy=actions[i].second.first;
    int tox=actions[i].second.second;
     //rowan_debug<<"from"<<fromy<<fromx<<'\n';
     //rowan_debug<<"to"<<toy<<tox<<'\n';

    //auto self_board = state->board.board[state->player];

    //RDM Make Move
    int piececode=state->board.board[state->player][fromy][fromx];
    //rowan_debug<<"piececodefirst"<<(piececode)<<'\n';
    state->board.board[state->player][fromy][fromx]=0;
    int beforepiece=state->board.board[state->player][toy][tox];
    //rowan_debug<<"beforepieacefirst"<<(int)state->board.board[state->player][toy][tox]<<'\n';
    state->board.board[state->player][toy][tox]=piececode; 
    int oppnpiece=0;
    if(state->board.board[1-state->player][toy][tox]!=0)
    {
oppnpiece=state->board.board[1-state->player][toy][tox];
state->board.board[1-state->player][toy][tox]=0;
    }

    //RDM Check score
    int currscore=state->evaluate();

    //RDM Move pieces back for self
    state->board.board[state->player][fromy][fromx]=piececode;
    state->board.board[state->player][toy][tox]=beforepiece;
    //RDM Move pieces back for enemy
    state->board.board[1-state->player][toy][tox]=oppnpiece;
    //rowan_debug<<"piececodeafter"<<(int)state->board.board[state->player][fromy][fromx]<<'\n';
    //rowan_debug<<"afterpieacefirst"<<(int)state->board.board[state->player][toy][tox]<<'\n';
    //std::ofstream log("gamelog.txt");
    //log<<currscore<<std::endl;
    //log.close();
   // rowan_debug<<currscore<<'\n';
   rowan_debug<<"beforepiece"<<beforepiece<<std::endl;
    if(i==0)
    {
      maxval=currscore;
      maxval=currscore;
      bestmove=actions[i];
      std::cout<<currscore<<std::endl;
    }
    if(currscore>maxval)
    {
      
    rowan_debug<<"curr maxval:"<<maxval<<'\n';
      maxval=currscore;
      bestmove=actions[i];
      std::cout<<currscore<<std::endl;
    }

//MAKE SURE THAT THE STATE POINTER IS A COPY
  }
  rowan_debug.close();
  return bestmove;
}