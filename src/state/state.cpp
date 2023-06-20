#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <vector>
#include "./state.hpp"
#include "../config.hpp"


/**
 * @brief evaluate the state
 * 
 * @return int 
 */
 static std::string y_axis = "654321";
static std::string x_axis = "ABCDE";
static int counter=0;
int State::alphabeta(State* root, int depth,int alpha, int beta,bool ismaximizingplayer,std::vector<StepInfo> sinfo,Move pastmove)
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
    State* child=next_state(actions[i]);
     //RDM Check score
   // value =child->evaluate();
    sinfo.push_back(StepInfo(pastmove,actions[i],value,depth,i));
    int alphab=root->alphabeta(child,depth-1,alpha,beta,false,sinfo,actions[i]);
     
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
      State* child=next_state(actions[i]);
     rowan_debug<<"currplayer"<<child->player<<"DEPTH"<<depth<<"isMAx"<<ismaximizingplayer<<std::endl;
     //RDM Check score

     ///RDM WE HAVE TO CREATE THE NEXT LEGAL STATES BASED ON THE ENEMY, BUT WE SCORE BASED ON
     //child->player=!(child->player);
    //currminval=child->evaluate();
    //minimax flavor
     sinfo.push_back(StepInfo(pastmove,actions[i],currminval,depth,i));
    int alphab=root->alphabeta(child,depth-1,alpha,beta,true,sinfo,actions[i]);
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










int State::evaluate(){
std::ofstream rowan_debug("rowdebug.txt");
  
  //std::ofstream rowan_debug("newdebug.txt");
   //std::ofstream rowan_debug("newdebug.txt", std::ios::app);
  // [TODO] design your own evaluation function
  //easiest: return the score of your pieces minus enemy pieces
  //a Board is 3dimensional, first element is either 0 (white) or 1 (black)
  //1 is pawn 2 points
  //2 is rook 6 points
  //4 is bishop 8 points
  //5 is queen 20 points
  //3 is knight 7 points
  //6 is king (infinite value) 1000000
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];

  int oppkingx=0;
  int oppkingy=0;
  int mykingx=0;
  int mykingy=0;
  for(int r=0;r<BOARD_H;r++)
  {
    for(int c=0;c<BOARD_W;c++)
  {
    if(oppn_board[r][c]==6)
    {
      oppkingy=r;
      oppkingx=c;
    }
    if(self_board[r][c]==6)
    {
      mykingy=r;
      mykingx=c;
      rowan_debug<<"found kingpos"<<mykingy<<mykingx<<std::endl;
    }
  }}


  int currboardval=0;
  for(int r=0;r<BOARD_H;r++)
  {
    for(int c=0;c<BOARD_W;c++)
  {
    
    //can make an improvement by adding if both self and oopn board are not empty
    //rowan_debug<<"my board piece"<<self_board[r][c]<<'\n';
    //rowan_debug<<"enemy board piece"<<this->board.board[1 - this->player][r][c]<<'\n';
    int currselfboardpiece=self_board[r][c];
    int curroppboardpiece=oppn_board[r][c];
    //rowan_debug<<"my board piece"<<currselfboardpiece<<'\n';
    //rowan_debug<<"enemy board piece"<<curroppboardpiece<<'\n';
    double diff_x = c- oppkingx;
    double diff_y = r - oppkingy;

    double squared_diff_x = pow(diff_x, 2);
    double squared_diff_y = pow(diff_y, 2);

    double sum_of_squared_diffs = squared_diff_x + squared_diff_y;

    double distance = sqrt(sum_of_squared_diffs);
    int distmultiplier=(7-((int)distance));

    

     diff_x = c- mykingx;
     diff_y = r - mykingy;

     squared_diff_x = pow(diff_x, 2);
     squared_diff_y = pow(diff_y, 2);

     sum_of_squared_diffs = squared_diff_x + squared_diff_y;

     distance = sqrt(sum_of_squared_diffs);
     int endistmultiplier=(7-((int)distance));
  //int currselfval;
  // if(c!=0&&r!=0&&((int)distance)<3)
  // {
  //   if(((int)self_board[r-1][c-1])==1||((int)self_board[r-1][c-1])==4||((int)self_board[r-1][c-1])==5)
  //   {
  //     currboardval+=2;
  //   }
  // }
  // if(c!=BOARD_W-1&&r!=BOARD_H&&((int)distance)<3)
  // {
  //   if(((int)self_board[r-1][c+1])==1||((int)self_board[r-1][c+1])==4||((int)self_board[r-1][c+1])==5)
  //   {
  //     currboardval+=2;
  //   }
  // }
     int currmypieceval=0;
     int currenpieceval=0;
     if(currselfboardpiece!=0)
     {
      switch(currselfboardpiece)
    {
      case 1:
        currmypieceval=(1);
      break;
      case 2:
        currmypieceval=(5);
      break;
      case 3:
        currmypieceval=(3);
      break;
      case 4:
        currmypieceval=(3);
      break;
      case 5:
        currmypieceval=(9);
      break;
      case 6:
        currmypieceval=1000000;
      break;
      
    }
      //Reward middle control
      int ctrmidw=1;
     if(r>=2&&r<=3&&c>=1&&c<=3)
     {
      ctrmidw=2;
      currmypieceval*=ctrmidw;
     }
     //pawn in front of king is very important
     if(r==mykingy&&currselfboardpiece==1)
     {
      currmypieceval=5;
     }

     //distance from enemyking weight
     //currmypieceval*=distmultiplier;
     }
    
    //rowan_debug<<"currmyboardpiece"<<currselfboardpiece<<"val after"<<currboardval<<'\n';
    //rowan_debug<<self_board[r][c]<<'\n';
    if(curroppboardpiece!=0)
    {
      switch(curroppboardpiece)
      {
        case 1:
          currenpieceval=1;
        break;
        case 2:
          currenpieceval=5;
        break;
        case 3:
          currenpieceval=3;
        break;
        case 4:
          currenpieceval=3;
        break;
        case 5:
          currenpieceval=9;
        break;
        case 6:
          currenpieceval=1000000;
        break;
        
      }
      //Penalize enemy middle control
      int ctrmidw=1;
     if(r>=2&&r<=3&&c>=1&&c<=3)
     {
      ctrmidw=2;
      currenpieceval*=ctrmidw;
     }
    }
    //rowan_debug<<"curropsboardpiece"<<curroppboardpiece<<"val"<<currboardval<<'\n';
    //rowan_debug<<currboardval<<'\n';
    currboardval+=currmypieceval;
    currboardval-=currenpieceval;
    //currenpieceval*=endistmultiplier;
  }
  }
//   //CHECK if they can eat my king on the next move
  State* caneatking= new State(this->board,1-(this->player));
  caneatking->get_legal_actions();
  auto enemyactions=caneatking->legal_actions;
  bool kingpresent=false;
  rowan_debug<<"KINGPOSR"<<mykingy<<"KINGPOSC"<<mykingx<<std::endl;
  
 for(int i=0;i<enemyactions.size();i++)
 {
      int fromx=enemyactions[i].first.second;
       int tox=enemyactions[i].second.second;
       int fromy=enemyactions[i].first.first;
       int toy=enemyactions[i].second.first;
    rowan_debug<<"CurrentEnemy Move:"<<x_axis[fromx]<<y_axis[fromy]<<"-->"<<x_axis[tox]<<y_axis[toy]<<std::endl;
    
  State* myboardafterenemymove=next_state(enemyactions[i]);
   auto self_boardafterenemymove = myboardafterenemymove->board.board[this->player];
  for(int r=0;r<BOARD_H;r++)
  {
    for(int c=0;c<BOARD_W;c++)
  {
    if(self_boardafterenemymove[r][c]==6)
    {
      
      rowan_debug<<"found kingposafterenemymove"<<r<<c<<std::endl;
    }
  }}
  rowan_debug<<"THIS IS AT KINGS POSITION"<<(int)(self_boardafterenemymove[mykingy][mykingx])<<std::endl;
    if(self_boardafterenemymove[mykingy][mykingx]==6)
    {
      kingpresent=true;
      rowan_debug<<"KING IS PRESENT"<<std::endl;
    }
    else
    {
       rowan_debug<<"KING NOT PRESENT"<<std::endl;
    }
  
 }
      
  if(kingpresent==false)
  {
    rowan_debug<<"Your king will be eaten"<<std::endl;
    currboardval-=1000000;
  }
  else
  {
    rowan_debug<<"Your king will not be eaten"<<std::endl;
  }
  delete caneatking;
  rowan_debug<<"IN EVALUATE FUNCTION"<<'\n';
  rowan_debug<<currboardval<<'\n';
  if(oppkingx==0)
  {
    currboardval+=10000000;
  }
  
  return currboardval;
}




/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}