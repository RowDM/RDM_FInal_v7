#include <cstdlib>
#include <iostream>
#include <fstream>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
 //std::ofstream rowan_debug("rowdebug.txt");
//rowan_debug<<"get_move accesed"<<'\n';

  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  
  Move bestmove=state->maximizerootnode(state,depth);
  //state->minimax(state,depth,true,state->legal_actions[0]);
  //state->bestmove=state->legal_actions[0];
  // Move move=state->bestmove;
  // rowan_debug<<"THIS IS THE MOVEMENT"<<std::endl;
  // rowan_debug<< move.first.first << " " << move.first.second << " "\
  //        << move.second.first << " " << move.second.second << std::endl;
  // rowan_debug.close();
  return bestmove;
}