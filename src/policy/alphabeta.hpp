#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for alpha beta policy, 
 * your policy class should have get_move method
 */
class Alphabeta{
public:
  static Move get_move(State *state, int depth); 
  static Move get_move_helper(State *state, int depth);
  static int alphabeta(State *state, int depth, int alpha, int beta, bool is_max_player);
};