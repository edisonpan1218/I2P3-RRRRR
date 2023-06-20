#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./minimax.hpp"

int find_minimax(int depth, bool player, State* state){
  if(depth == 0) return state->evaluate();
  if(player){
    int value = 0;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    for(int i = 0; i < actions.size(); i ++){
      State* tmp = state->next_state(actions[i]);
      value = std::max(find_minimax(depth - 1, false, tmp), value);
    }
    return value;
  }
  else{
    int value = 1e9;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    for(int i = 0; i < actions.size(); i ++){
      State *tmp = state->next_state(actions[i]);
      value = std::min(find_minimax(depth - 1, true, tmp), value);
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
  /*
  auto actions = state->legal_actions;
  int target = find_minimax(depth, true, state);
  for(int i = 0; i < actions.size(); i ++){
    State* tmp = state->next_state(actions[i]);
    if(tmp->evaluate() == target){
      return actions[i];
    }
  }*/
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
  return Max;
}

