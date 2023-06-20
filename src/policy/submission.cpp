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
 static std::string y_axis = "654321";
static std::string x_axis = "ABCDE";
static int counter =0;
Move AlphaB::get_move(State *state, int depth){
 std::ofstream rowan_debug("difffolder.txt",std::ios::app);
//rowan_debug<<"get_move accesed"<<'\n';

  if(!state->legal_actions.size())
    state->get_legal_actions();
  
    //std::ofstream eraseprev("alphabetadebug.txt");
    //eraseprev<<"\n"<<std::endl;
    //eraseprev.close();
   std::vector<StepInfo> sinfo;
   Move firstmove(Point(-1, -1), Point(-1, -1));
  alphabeta(state,depth,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),true,sinfo,state->legal_actions[0]);
  //state->minimax(state,depth,true,state->legal_actions[0]);
  //state->bestmove=state->legal_actions[0];
  Move move=state->bestmove;
  rowan_debug<<"THIS IS THE MOVEMENT"<<std::endl;
  rowan_debug<< move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
  rowan_debug.close();
  return state->bestmove;
}

int AlphaB::alphabeta(State* root, int depth,int alpha, int beta,bool ismaximizingplayer,std::vector<StepInfo> sinfo,Move pastmove)
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
    for(int i=0;i<sinfo.size();i++)
    {
      int fromx=sinfo[i].currmove.first.second;
      int tox=sinfo[i].currmove.second.second;
      int fromy=sinfo[i].currmove.first.first;
      int toy=sinfo[i].currmove.second.first;

      int pastfromx=sinfo[i].pastmove.first.second;
      int pasttox=sinfo[i].pastmove.second.second;
      int pastfromy=sinfo[i].pastmove.first.first;
      int pasttoy=sinfo[i].pastmove.second.first;
       rowan_debug<<"Past Move:"<<x_axis[pastfromx]<<y_axis[pastfromy]<<"-->"<<x_axis[pasttox]<<y_axis[pasttoy]<<"Move:"<<x_axis[fromx]<<y_axis[fromy]<<"-->"<<x_axis[tox]<<y_axis[toy]<<" NODEVAL"<<sinfo[i].nodeval<<" DEPTH"<<sinfo[i].nodedepth<<" IT"<<sinfo[i].iteration<<std::endl;
    }
    rowan_debug<<"-----------------------------------------------"<<std::endl;
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
   // value =child->evaluate();
    sinfo.push_back(StepInfo(pastmove,actions[i],value,depth,i));
    int alphab=alphabeta(child,depth-1,alpha,beta,false,sinfo,actions[i]);
     
    //minimax flavor
    value=std::max(value,alphab);
 // rowan_debug<<"DEPTH:"<<depth<<"NODEVAL"<<value<<"IT"<<i<<std::endl;
    alpha=std::max(alpha,value);


   if(maxval<value)
    {
      maxval=value;
      bmove=actions[i];
    }
    if(alpha>=beta)
    {
      break;
    }
    
   delete child;
    }
    root->bestmove=bmove;
    int fromx=bmove.first.second;
      int tox=bmove.second.second;
      int fromy=bmove.first.first;
      int toy=bmove.second.first;

       rowan_debug<<"Best Move:"<<x_axis[fromx]<<y_axis[fromy]<<"-->"<<x_axis[tox]<<y_axis[toy]<<std::endl;
       counter=counter+1;
      rowan_debug<<"TIMESRUN"<<counter<<std::endl;
    return maxval;
  }
  else
  {
    int currminval=std::numeric_limits<int>::max();
    int minval=currminval;
    for(int i=0;i<actions.size();i++)
    {
      State* child=root->next_state(actions[i]);
     rowan_debug<<"currplayer"<<child->player<<"DEPTH"<<depth<<"isMAx"<<ismaximizingplayer<<std::endl;
     //RDM Check score

     ///RDM WE HAVE TO CREATE THE NEXT LEGAL STATES BASED ON THE ENEMY, BUT WE SCORE BASED ON
     //child->player=!(child->player);
    //currminval=child->evaluate();
    //minimax flavor
     sinfo.push_back(StepInfo(pastmove,actions[i],currminval,depth,i));
    int alphab=alphabeta(child,depth-1,alpha,beta,true,sinfo,actions[i]);
    currminval=std::min(currminval,alphab);
    //rowan_debug<<"DEPTH:"<<depth<<"NODEVAL"<<currminval<<"IT"<<i<<std::endl;
    beta=std::min(beta,currminval);

    if(beta<=alpha)
    {
      break;
    }

   delete child;
    }
    return currminval;
  }
}



