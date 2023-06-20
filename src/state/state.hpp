#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

#include "../config.hpp"


typedef std::pair<size_t, size_t> Point;
typedef std::pair<Point, Point> Move; // (from, to)

const int INF = 1000000000; // 1e9 
const int material_value[7] = {0, 2, 6, 7, 8, 20, 1000}; // empty, pawn, rook, knight, bishop, queen, king

// empty, pawn, rook, knight, bishop, queen, king
const int white_piece_square_table[7][BOARD_H][BOARD_W] = {
  {
    // empty
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
  }, {
    // pawn
    {50, 50, 50, 50, 50},
    {30, 30, 20, 10, 10},
    {5, 5, 10, 10, 25},
    {5, -5, 0, 0, 0},
    {5, 10, 10, -20, -20},
    {0, 0, 0, 0, 0},
  }, {
    // rook
    {0, 0, 0, 0, 0},
    {5, 10, 10, 10, 5},
    {-5, 0, 0, 0, -5},
    {-5, 0, 0, 0, -5},
    {-5, -5, 0, 0, -5},
    {-5, -5, 5, 0, -5},
  },{
    // knight
    {-50, -40, -30, -40, -50},
    {-40, -20, 0, -20, -40},
    {-30, 15, 20, 15, -30},
    {-30, 15, 20, 15, -30},
    {-40, -20, 5, -20, -40},
    {-50, -40, -30, -40, -50},
  }, {
    // bishop
    {-20, -10, -10, -10, -20},
    {-10, 5, 5, 0, -10},
    {-10, 5, 10, 5, -10},
    {-10, 5, 5, 5, -10},
    {-10, 0, 5, 0, -10},
    {-20, -10, -10, -10, -20},
  }, {
    // queen
    {-20, 0, 0, 0, -20},
    {-10, 0, 0, 0, -10},
    {-10, 5, 5, 5, -10},
    {-10, 5, 5, 5, -10},
    {-10, 0, 0, 0, -10},
    {-20, -10, -10, -10, -20},
  }, {
    // king
    {-30, -40, -50, -40, -30},
    {-30, -40, -50, -40, -30},
    {-30, -40, -50, -40, -30},
    {-30, -30, -30, -30, -30},
    {20, 0, 0, 0, 20},
    {20, 30, 0, 30, 20},
  }
};

class Board{
  public:
    char board[2][BOARD_H][BOARD_W] = {{
      //white
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},
    }, {
      //black
      {6, 5, 4, 3, 2},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }};
};

enum GameState {
  UNKNOWN = 0,
  WIN,
  DRAW,
  NONE
};


class State{
  public:
    //You may want to add more property for a state
    GameState game_state = UNKNOWN;
    Board board;
    int player = 0;
    std::vector<Move> legal_actions;
    
    State(){};
    State(int player): player(player){};
    State(Board board): board(board){};
    State(Board board, int player): board(board), player(player){};
    
    int evaluate();
    State* next_state(Move move);
    void get_legal_actions();
    std::string encode_output();
    std::string encode_state();
};

#endif