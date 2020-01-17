//
// Created by michael on 17/01/2020.
//

#ifndef EX4__DFS_H_
#define EX4__DFS_H_

#include "Searcher.h"
#include <iostream>
#include <stack>
using namespace std;

template<typename T, typename S>
class DFS : public Searcher<T, S> {
  S search(Searchable<T> *searchObj) {
    return this->runDFS(searchObj->getInitialState());
  }

  // Searchable<T> *searchObj - graph
  // State<T> *initPoint - vertex v
  void runDFS(Searchable<T> *searchObj, State<T> *initState) {
    stack<State<T> *> stateStack;

    // push the initial state to the stack
    stateStack.push(initState);

    while (!stateStack.empty()) {
      State<T> *currState = stateStack.pop();

    }
  }
};

#endif //EX4__DFS_H_