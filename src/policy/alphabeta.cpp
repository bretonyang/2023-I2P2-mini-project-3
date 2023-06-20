#include <cstdlib>
#include <algorithm>
#include <vector>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief get a legal move by minimax algorithm
 * 
 * @param state Now state
 * @param depth search depth for minimax, specified by the caller (should be > 0)
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions(); 
  
  return get_move_helper(state, depth);
}

/**
 * Running the first layer of minimax on the max player.
 * @param depth should be > 0
 * @return action leading to minimum next state value 
 */
Move Alphabeta::get_move_helper(State *state, int depth) {
  int max_value = -INF; 
  std::vector<Move> potential_moves;
  
  for (Move action : state->legal_actions) {
    int potential_value = minimax(state->next_state(action), depth - 1, false);
    if (potential_value > max_value) {
      max_value = potential_value;
      potential_moves.clear();
      potential_moves.push_back(action);
    }
    else if (potential_value == max_value) {
      potential_moves.push_back(action);
    }
  }
  return potential_moves[(rand() + depth) % potential_moves.size()];
}

int Alphabeta::minimax(State *state, int depth, bool is_max_player) {
  if ((state->game_state == WIN || depth == 0) && is_max_player) 
    return state->evaluate();
  if ((state->game_state == WIN || depth == 0) && !is_max_player) 
    return -(state->evaluate()); // NOTE: evaluate() returns opponent's value 
  
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