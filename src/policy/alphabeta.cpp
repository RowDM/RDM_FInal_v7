#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaB::get_move(State *state, int depth){
 std::ofstream rowan_debug("rowdebug.txt",std::ios::app);
//rowan_debug<<"get_move accesed"<<'\n';

  if(!state->legal_actions.size())
    state->get_legal_actions();
  
    std::ofstream eraseprev("alphabetadebug.txt");
    eraseprev<<"\n"<<std::endl;
    eraseprev.close();
   std::vector<StepInfo> sinfo;
   Move firstmove(Point(-1, -1), Point(-1, -1));
  state->alphabeta(state,depth,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),true,sinfo,state->legal_actions[0]);
  //state->minimax(state,depth,true,state->legal_actions[0]);
  //state->bestmove=state->legal_actions[0];
  Move move=state->bestmove;
  rowan_debug<<"THIS IS THE MOVEMENT"<<std::endl;
  rowan_debug<< move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
  rowan_debug.close();
  return state->bestmove;
}