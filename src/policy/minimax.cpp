#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./minimax.hpp"

double find_minimax(int depth, bool player, State* state){
  
  if(depth == 0) return state->evaluate();
  if(player){
    double value = -1e9;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    for(auto  i : actions){
      State* tmp = state->next_state(i);
      value = std::max(find_minimax(depth - 1, !player, tmp), value);
    }
    return value;
  }
  else{
    double value = 1e9;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    for(auto i : actions){
      State *tmp = state->next_state(i);
      value = std::min(find_minimax(depth - 1, !player, tmp), value);
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
Move MiniMax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  double target = -1e9;
  Move Max;
  for(int i = 0; i < actions.size(); i ++){
    State* tmp = state->next_state(actions[i]);
    int v = find_minimax(depth, false, tmp);
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

