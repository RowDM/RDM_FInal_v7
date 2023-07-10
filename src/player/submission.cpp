#include <iostream>
#include <fstream>
#include <map>

#include "../config.hpp"
#include "../state/state.hpp"
//#include "../policy/random.hpp"
#include "../policy/alphabeta.hpp"

//RDMinteresting stuff making changesss heloooo changes
State* root;
//using namespace std;
/**
 * @brief Read the board from the file
 * 
 * @param fin 
 */
void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        // std::cout << c << " ";
        board.board[pl][i][j] = c;
      }
      // std::cout << std::endl;
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}


/**
 * @brief based on your points versus the enemy's, choose a move and then write it into output file
 * 
 * @param fout 
 */
void write_valid_spot(std::ofstream& fout) {
  size_t writeto=0;
    size_t rfrom=1;
    size_t rto=2;
    size_t colfrom=2;
    size_t colto=2;
  std::map<char,size_t>chartosizet;
   std::map<size_t,size_t>inttoactualint;
   chartosizet[0]='A';
   chartosizet[1]='B';
   chartosizet[2]='C';
   chartosizet[3]='D';
   chartosizet[4]='E';
   char fromchar;
   char tochar;
   inttoactualint[0]=6;
   inttoactualint[1]=5;
   inttoactualint[2]=4;
   inttoactualint[3]=3;
   inttoactualint[4]=2;
   inttoactualint[5]=1;
  // Keep updating the output until getting killed.
  int depth=4;
  std::ofstream communicatewithgraphics("talktographics.txt");
  while(true) {
    
    //log<<"HELLO THEREEE"<<std::endl;
    //std::cout<<"TESTTING"<<std::endl;
    // Choose a random spot.
    auto move = AlphaB::get_move(root, depth);
    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;

     
         Point pointFrom(inttoactualint[rfrom], chartosizet[fromchar]);
    Point pointTo(inttoactualint[rto], chartosizet[tochar]);
    
    // Create a new Move object using the Point objects
    Move mymove(pointFrom, pointTo);
    communicatewithgraphics << (char)chartosizet[(int)move.first.second] << " " << inttoactualint[(int)move.first.first] << " "\
         << (char)chartosizet[(int)move.second.second] << " " << inttoactualint[(int)move.second.first] << std::endl;
    
   
    //RDM nvm found the gamelog.txt
  depth+=2;
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
    break;
  }
}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  srand(RANDOM_SEED);
  //std::ofstream fdeb("rowan_debug.txt");
  //fdeb<< "testing ..." << std::endl;
  //fdeb.flush();
  //fdeb.close();
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
