#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


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
  Move Max;
  int max_sum = 0;
  for(int i = 0; i < actions.size(); i ++){
    State* tmp = state->next_state(actions[i]);
    if(tmp->evaluate() > max_sum){
      Max = actions[i];
      max_sum = tmp->evaluate();
    }
  }
  return Max;
}