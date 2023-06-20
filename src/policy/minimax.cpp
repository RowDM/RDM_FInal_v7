#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>
#include <vector>
//#include "./state.hpp"
#include "../config.hpp"
#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
 static std::string y_axis = "654321";
static std::string x_axis = "ABCDE";
Move Minimax::get_move(State *state, int depth){
 //std::ofstream rowan_debug("rowdebug.txt");
//rowan_debug<<"get_move accesed"<<'\n';
  
  
  Move bestmove=maximizerootnode(state,depth);
  //state->minimax(state,depth,true,state->legal_actions[0]);
  //state->bestmove=state->legal_actions[0];
  // Move move=state->bestmove;
  // rowan_debug<<"THIS IS THE MOVEMENT"<<std::endl;
  // rowan_debug<< move.first.first << " " << move.first.second << " "\
  //        << move.second.first << " " << move.second.second << std::endl;
  // rowan_debug.close();
  return bestmove;
}
//This method utilizes the minmax method and I realized that my understanding of it was flaswed
//beats random player and when white beats the greedy player
int Minimax::minimax(State* root, int depth,bool ismaximizingplayer,Move currmove)
{
 std::ofstream rowan_debug("alphabetadebug.txt",std::ios::app);
//  rowan_debug<<"----------------------------------------------------"<<std::endl;
//    if(ismaximizingplayer)
//   {
//     rowan_debug<<"MAXIMIZING"<<depth<<std::endl;
//   }
//   else
//   {
//     rowan_debug<<"MINIMIZING"<<depth<<std::endl;
//   }

//DONT NEED TO DO THIS BECAUSE THEIR NEXT STATE ALREADY DOES THIS
  // if(ismaximizingplayer==false)
  // {
  //   root->player=!(root->player);
  // }
  root->get_legal_actions();
  auto actions = root->legal_actions;
  //RDMgot rid of gamestate condition
  if(depth==0||actions.size()==0)
  {
    int val=root->evaluate();
    if(depth!=0)
    {
      rowan_debug<<"EXITED WHEN DEOTH NOT 0"<<std::endl;
    }
    
    return val;
  }

  int value;
  int maxval;
  Move bmove;
  if(ismaximizingplayer==true)
  {
    maxval=std::numeric_limits<int>::min();
    value=maxval;
    for(int i=0;i<actions.size();i++)
    {
    State* child=root->next_state(actions[i]);
     //RDM Check score
    //value =child->evaluate();
    int value=minimax(child,depth-1,false,actions[i]);
     
    //minimax flavor
    //maxval=std::max(value,maxval);
 // rowan_debug<<"DEPTH:"<<depth<<"NODEVAL"<<value<<"IT"<<i<<std::endl;
    

    
    if(maxval<value)
    {
      maxval=value;
      bmove=actions[i];
    }
   delete child;
    }
    root->bestmove=bmove;
  

       
    return maxval;
  }
  else
  {
    int currminval=std::numeric_limits<int>::max();
    int minval=currminval;
    for(int i=0;i<actions.size();i++)
    {
      State* child=root->next_state(actions[i]);
     //rowan_debug<<"currplayer"<<child->player<<"DEPTH"<<depth<<"isMAx"<<ismaximizingplayer<<std::endl;
     //RDM Check score

     ///RDM WE HAVE TO CREATE THE NEXT LEGAL STATES BASED ON THE ENEMY, BUT WE SCORE BASED ON
     //child->player=!(child->player);
    //currminval=child->evaluate();
    //minimax flavor
     
    int minval=minimax(child,depth-1,true,actions[i]);
    currminval=std::min(currminval,minval);
    //rowan_debug<<"DEPTH:"<<depth<<"NODEVAL"<<currminval<<"IT"<<i<<std::endl;
   

    
   delete child;
    }
    return currminval;
  }
}

Move Minimax::maximizerootnode(State* root, int depth)
{
  std::ofstream rowan_debug("maximizerootdebug.txt",std::ios::app);
  if(!(root->legal_actions.size()))
    root->get_legal_actions();
  Move bestmove;
  int bestscore=std::numeric_limits<int>::min();
  auto actions = root->legal_actions;
  for(int i=0;i<actions.size();i++)
  {
    State *child= root->next_state(actions[i]);
    //child now is set to be an opponent
    int score=minimax(child,depth,false,actions[i]);
    //motors.run (left,100)
    delete child;
    if(score>bestscore)
    {
      bestscore=score;
      bestmove=actions[i];
    }
   
   int pastfromx=bestmove.first.second;
      int pasttox=bestmove.second.second;
      int pastfromy=bestmove.first.first;
      int pasttoy=bestmove.second.first;
      rowan_debug<<"CurrentBest Move:"<<x_axis[pastfromx]<<y_axis[pastfromy]<<"-->"<<x_axis[pasttox]<<y_axis[pasttoy]<<std::endl;
  }
  rowan_debug.close();
  return bestmove;
}
