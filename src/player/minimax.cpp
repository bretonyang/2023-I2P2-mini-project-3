#include <iostream>
#include <fstream>

#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/minimax.hpp"


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

  for (int pl = 0; pl < 2; pl++) {
    for (int i = 0; i < BOARD_H; i++) {
      for (int j = 0; j < BOARD_W; j++) {
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
 * @brief randomly choose a move and then write it into output file
 * 
 * @param fout 
 */
void write_valid_spot(std::ofstream& fout) {
  // Keep updating the output until getting killed.
  // output result from depth: 0, 2, 4, 6, 8, ... (if can be calculated in time)
  // Reason: avoid not outputting anything after exceeding the time limit.
  int depth = 3; 
  while(true) {
    auto move = Minimax::get_move(root, depth);
    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second << std::endl;
    
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
    depth += 2;
  }
}


/**
 * @brief Main function for minimax player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  std::ifstream fin(argv[1]); // state
  std::ofstream fout(argv[2]); // action

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
