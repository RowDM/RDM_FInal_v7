#include <iostream>
#include <fstream>

#include "../config.hpp"
#include "../state/state.hpp"
//#include "../policy/random.hpp"
#include "../policy/minimax.hpp"

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
  // Keep updating the output until getting killed.
  int depth=1;
  while(true) {
    
    //log<<"HELLO THEREEE"<<std::endl;
    //std::cout<<"TESTTING"<<std::endl;
    // Choose a random spot.
    auto move = Minimax::get_move(root, depth);
    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
    //RDM nvm found the gamelog.txt
  depth++;
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
