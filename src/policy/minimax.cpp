#include <cstdlib>
#include <algorithm>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief get a legal move by minimax algorithm
 * 
 * @param state Now state
 * @param depth search depth for minimax, specified by the caller (should be > 0)
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions(); 
  
  return get_move_helper(state, depth);
}

/**
 * Running the first layer of minimax on the max player.
 * @param depth should be > 0
 * @return action leading to maximum next state value 
 */
Move Minimax::get_move_helper(State *state, int depth) {
  Move max_move;
  int max_value = -INF;
  
  // find max_move leading to next_state with max_value
  for (Move action : state->legal_actions) {
    int potential_value = minimax(state->next_state(action), depth - 1, false);
    if (potential_value > max_value) {
      max_value = potential_value;
      max_move = action;
    }
  }
  return max_move;
}

int Minimax::minimax(State *state, int depth, bool is_max_player) {
  if (state->game_state == WIN && is_max_player) return INF;
  if (state->game_state == WIN && !is_max_player) return -INF;
  if (depth == 0) return state->evaluate();
  
  if (is_max_player) { // find max value
    int max_value = -INF;
    for (Move action : state->legal_actions) {
      max_value = std::max(max_value, minimax(state->next_state(action), depth - 1, false));
    }
    return max_value;
  }
  else { // find min value
    int min_value = INF;
    for (Move action : state->legal_actions) {
      min_value = std::min(min_value, minimax(state->next_state(action), depth - 1, true));
    }
    return min_value;
  }
}
