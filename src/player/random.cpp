#include <iostream>
#include <fstream>
#include <map>

#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/random.hpp"

//#include <SFML/Graphics.hpp>


State* root;

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

void displayboard()
{
	// sf::RenderWindow window(
	// 	sf::VideoMode(640, 480),
	// 	"Hello World");
	// sf::CircleShape shape(200);

	// while (window.isOpen())
	// {
	// 	sf::Event event;
	// 	while (
	// 		window.pollEvent(event))
	// 		if (event.type ==
	// 		sf::Event::Closed)
	// 			window.close();

	// 	window.clear();
	// 	window.draw(shape);
	// 	window.display();
	// }
	return ;
}

int rndnum=0;
/**
 * @brief randomly choose a move and then write it into output file
 * 
 * @param fout 
 */
void write_valid_spot(std::ofstream& fout) {
  displayboard();
  // Keep updating the output until getting killed.
  std::ofstream rowan_debug("debugmymove.txt");
  //std::ifstream movestr("mymove.txt");
  rowan_debug<<"Make your move:"<<std::endl;
  //write to 0 means it is the past, and 1 means I have overwritten and want this one to be read
    int checkrndnum;
    size_t rfrom=1;
    size_t rto=2;
    size_t colfrom=2;
    size_t colto=2;
    //movestr>>writeto>>colfrom>>rfrom>>colto>>rto;
   // rowan_debug << rfrom << " " << rto<< " "\
         << colfrom << " " << colto<< std::endl;
    // Point pointFrom(rfrom, colfrom);
    // Point pointTo(rto, colto);
    
    // // Create a new Move object using the Point objects
    // Move mymove(pointFrom, pointTo);

   std::map<char,size_t>chartosizet;
   std::map<size_t,size_t>inttoactualint;
   chartosizet['A']=0;
   chartosizet['B']=1;
   chartosizet['C']=2;
   chartosizet['D']=3;
   chartosizet['E']=4;
   char fromchar;
   char tochar;
   inttoactualint[6]=0;
   inttoactualint[5]=1;
   inttoactualint[4]=2;
   inttoactualint[3]=3;
   inttoactualint[2]=4;
   inttoactualint[1]=5;
  while(checkrndnum!=rndnum) {
    //rowan_debug << (int)mymove.first.first << " " << (int)mymove.first.second << " "\
         << (int)mymove.second.first << " " << (int)mymove.second.second << std::endl;
    // Choose a random spot.
    //auto move = Random::get_move(root, 0);
  std::ifstream movestr("mymove.txt");
  movestr>>checkrndnum>>fromchar>>rfrom>>tochar>>rto;
  rowan_debug<<"while loop accessed"<<std::endl;
   // rowan_debug << rfrom << " " << rto<< " "\
         << colfrom << " " << colto<< std::endl;
    
    //break;
   }
   rndnum++;
  Point pointFrom(inttoactualint[rfrom], chartosizet[fromchar]);
    Point pointTo(inttoactualint[rto], chartosizet[tochar]);
    
    // Create a new Move object using the Point objects
    Move mymove(pointFrom, pointTo);
    rowan_debug << (int)mymove.first.first << " " << (int)mymove.first.second << " "\
         << (int)mymove.second.first << " " << (int)mymove.second.second << std::endl;
    fout << mymove.first.first << " " << mymove.first.second << " "\
         << mymove.second.first << " " << mymove.second.second << std::endl;
    
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
  rndnum++;
     std::ofstream writestr("mymove.txt");
     writestr<<rndnum<<" "<< fromchar<< " " << rfrom<< " "\
         << tochar << " " << rto << std::endl;

}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
