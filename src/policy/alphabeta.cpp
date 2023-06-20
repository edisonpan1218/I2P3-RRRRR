#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

int find_alphabeta(int depth, bool player, State* state, int alpha, int beta){
  if(depth == 0) return state->evaluate();
  if(player){
    int value = -1e9;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    for(auto  i : actions){
      State* tmp = state->next_state(i);
      value = std::max(find_alphabeta(depth - 1, !player, tmp, alpha, beta), value);
      alpha = std::max(alpha, value);
      if (alpha >= beta) break;
    }
    return value;
  }
  else{
    int value = 1e9;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    for(auto i : actions){
      State *tmp = state->next_state(i);
      value = std::min(find_alphabeta(depth - 1, !player, tmp, alpha, beta), value);
      beta = std::min(beta, value);
      if(beta <= alpha) break;
    }
    return value;
  }
}

/**
 * @brief Randomly get a legal action    
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int target = -1e9 - 5;
  Move Max;
  for(int i = 0; i < actions.size(); i ++){
    State* tmp = state->next_state(actions[i]);
    int v = find_alphabeta(depth, false, tmp, -1e9, 1e9);
    if(v > target){
      Max = actions[i];
      target = v;
    }
  }
  return Max;
  /*
  auto actions = state->legal_actions;
  Move Max;
  int max_sum = 1e9;
  for(auto i : actions){
    State* tmp = state->next_state(i);
    if(tmp->evaluate() < max_sum){
      Max = i;
      max_sum = tmp->evaluate();
    }
  }
  return Max;*/
}

