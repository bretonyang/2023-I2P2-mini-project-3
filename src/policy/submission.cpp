#include <cstdlib>
#include <algorithm>
#include <vector>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief get a legal move by alpha beta algorithm
 * 
 * @param state Now state
 * @param depth search depth for alpha beta, specified by the caller (should be > 0)
 * @return Move 
 */
Move Submission::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions(); 
  
  return get_move_helper(state, depth);
}

/**
 * Running the first layer of alpha beta on the max player.
 * @param depth should be > 0
 * @return action leading to minimum next state value 
 */
Move Submission::get_move_helper(State *state, int depth) {
  int max_value = -INF; 
  int alpha = -INF; 
  int beta = INF; // NOTE: beta in the root node is always INF
  std::vector<Move> potential_moves;
  
  for (Move action : state->legal_actions) {
    int potential_value = alphabeta(state->next_state(action), depth - 1, alpha, beta, false);

    if (potential_value > max_value) {
      max_value = potential_value;
      potential_moves.clear();
      potential_moves.push_back(action);
    }
    else if (potential_value == max_value) {
      potential_moves.push_back(action);
    }

    alpha = std::max(alpha, max_value);
    if (alpha > beta) break;
  }
  return potential_moves[rand() % potential_moves.size()];
}

int Submission::alphabeta(State *state, int depth, int alpha, int beta, bool is_max_player) {
  if (state->game_state == WIN || depth == 0) {
    if (is_max_player) return state->evaluate();
    else return -(state->evaluate()); // NOTE: evaluate() returns opponent's value 
  }
  
  if (is_max_player) { // find max value
    int max_value = -INF;
    for (Move action : state->legal_actions) {
      max_value = std::max(max_value, alphabeta(state->next_state(action), depth - 1, alpha, beta, false));
      alpha = std::max(alpha, max_value);
      if (alpha > beta) break; // beta cutoff
    }
    return max_value;
  }
  else { // find min value
    int min_value = INF;
    for (Move action : state->legal_actions) {
      min_value = std::min(min_value, alphabeta(state->next_state(action), depth - 1, alpha, beta, true));
      beta = std::min(beta, min_value);
      if (alpha > beta) break; // alpha cutoff
    }
    return min_value;
  }
}