#ifndef EX4__MATRIXPROBLEM_H_
#define EX4__MATRIXPROBLEM_H_

#include "Searchable.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <list>

using namespace std;
template<typename T>
class MatrixProblem : public Searchable<T> {
 private:
  string matrixStr;
  int colsNum;
  int rowNum;
  vector<vector<T> > matrixVct;
  vector<State<T> *> states;

 public:
  /**
   * CTOR
   * @param str
   */
  MatrixProblem(string str) {
    this->matrixStr = str;
    this->rowNum = this->getNumRows();
    this->colsNum = this->getNumCols();
    this->creatingMatrixVector();
    this->createStates();
  }

  /**
   * getNumRows - returning the number of rows in the matrix.
   * @return int - the number of rows.
   */
  int getNumRows() {
    string tmp = this->matrixStr;
    int nCounter = 0;
    int tmpLen = tmp.length();

    for (int k = 0; k < tmpLen; k++) {
      if (tmp[k] == '\n')
        nCounter++;
    }
    return nCounter - 2;
  }

  /**
 * getNumCols - returning the number of cols in the matrix.
 * @return int - the number of cols.
 */
  int getNumCols() {
    string tmp = this->matrixStr;
    int i = 0;
    int countCols = 0;

    while (tmp[i] != '\n' && tmp[i] != '\r') {
      if (tmp[i] != ',' && tmp[i] != '-')
        countCols++;
      if (isdigit(tmp[i]) && isdigit(tmp[i + 1]))
        i += 2;
      else
        i++;
    }
    return countCols;
  }

  /**
   * creatingMatrixVector - the function creates the matrix from the str field.
   */
  void creatingMatrixVector() {
    string tmp = this->matrixStr;
    vector<T> vect;
    stringstream s(tmp);

    for (int j = 0; j < this->rowNum; j++) {
      // creating the vector - each col of the matrix
      for (int i; s >> i;) {
        vect.push_back(i);
        if (s.peek() == ',')
          s.ignore();
        if (s.peek() == '\n' || s.peek() == '\r')
          break;
      }

      // filling the rows of the matrix
      this->matrixVct.push_back(vect);
      vect.clear();
    }
  }

  /**
   * getInitialState - the function returns the initial state of the matrix.
   * @return State<T> * - the initial state.
   */
  State<T> *getInitialState() {
    // running over the str and finding the starting point
    string tmp = this->matrixStr;
    vector<T> vect;
    stringstream s(tmp);

    for (int i; s >> i;) {
      vect.push_back(i);
      if (s.peek() == ',' || s.peek() == '\n')
        s.ignore();
    }

    int vctSize = vect.size();
    int i = vect[vctSize - 4];
    int j = vect[vctSize - 3];

    T val = this->matrixVct[i][j];

    State<T> *initState = getStateByIndex(i, j);

    return initState;
  }

  /**
  * isGoalState - the function returns the true if the state we get as parameter is the goal state
  * of the matrix.
  * @return bool - true if the state we get as parameter is the goal state of the matrix,
  * and false otherwise.
  */
  bool isGoalState(State<T> *st) {
    State<T> *goalState = getGoalState();
    return st->isEqual(goalState);
  }

  /**
 * getGoalState - the function returns the goal state object
 * @return State<T> *st - goal state
 */
  State<T> *getGoalState() {
    // running over the str and finding the goal point
    string tmp = this->matrixStr;
    vector<T> vect;
    stringstream s(tmp);

    for (int i; s >> i;) {
      vect.push_back(i);
      if (s.peek() == ',' || s.peek() == '\n')
        s.ignore();
    }

    int vctSize = vect.size();
    int i = vect[vctSize - 2];
    int j = vect[vctSize - 1];

    T val = this->matrixVct[i][j];

    State<T> *goalState = getStateByIndex(i, j);
    if (goalState->getValue() == -1) {
      std::cerr << "goal point is -1" << std::endl;
    }

    return goalState;
  }

  /**
    * getAllPossibleStates - the function returns the neighbors of the state we get as parameter.
    * @param st - the state.
    * @return vector<State<T> *> - vector of neighbors.
    */
  vector<State<T> *> getAllPossibleStates(State<T> *st) {
    vector<State<T> *> vect;
    State<T> *state1 = NULL;
    State<T> *state2 = NULL;
    State<T> *state3 = NULL;
    State<T> *state4 = NULL;

    int i = st->getI();
    int j = st->getJ();

    if ((i == 0 && j == this->colsNum - 1)) {
      if (matrixVct[i][j - 1] != -1) state1 = getStateByIndex(i, j - 1);
      if (matrixVct[i + 1][j] != -1) state2 = getStateByIndex(i + 1, j);;
    } else if (i == this->rowNum - 1 && j == 0) {
      if (matrixVct[i - 1][j] != -1) state1 = getStateByIndex(i - 1, j);;
      if (matrixVct[i][j + 1] != -1) state2 = getStateByIndex(i, j + 1);;
    } else if (i == 0 && j == 0) {
      if (matrixVct[i + 1][j] != -1) state1 = getStateByIndex(i + 1, j);;
      if (matrixVct[i][j + 1] != -1) state2 = getStateByIndex(i, j + 1);;
    } else if (i == 0 && j != 0) {
      if (matrixVct[i][j + 1] != -1) state1 = getStateByIndex(i, j + 1);;
      if (matrixVct[i][j - 1] != -1) state2 = getStateByIndex(i, j - 1);;
      if (matrixVct[i + 1][j] != -1) state3 = getStateByIndex(i + 1, j);;
    } else if (i != 0 && j == 0) {
      if (matrixVct[i + 1][j] != -1) state1 = getStateByIndex(i + 1, j);;
      if (matrixVct[i - 1][j] != -1) state2 = getStateByIndex(i - 1, j);;
      if (matrixVct[i][j + 1] != -1) state3 = getStateByIndex(i, j + 1);;
    } else if (i == this->rowNum - 1 && j == this->colsNum - 1) {
      if (matrixVct[i][j - 1] != -1) state1 = getStateByIndex(i, j - 1);;
      if (matrixVct[i - 1][j] != -1) state2 = getStateByIndex(i - 1, j);;
    } else if (i == this->rowNum - 1 && j != this->colsNum - 1) {
      if (matrixVct[i][j - 1] != -1) state1 = getStateByIndex(i, j - 1);;
      if (matrixVct[i][j + 1] != -1) state2 = getStateByIndex(i, j + 1);;
      if (matrixVct[i - 1][j] != -1) state3 = getStateByIndex(i - 1, j);;
    } else if (i != this->rowNum - 1 && j == this->colsNum - 1) {
      if (matrixVct[i][j - 1] != -1) state1 = getStateByIndex(i, j - 1);;
      if (matrixVct[i - 1][j] != -1) state2 = getStateByIndex(i - 1, j);;
      if (matrixVct[i + 1][j] != -1) state3 = getStateByIndex(i + 1, j);;
    } else {
      if (matrixVct[i - 1][j] != -1) state1 = getStateByIndex(i - 1, j);;
      if (matrixVct[i][j - 1] != -1) state2 = getStateByIndex(i, j - 1);;
      if (matrixVct[i + 1][j] != -1) state3 = getStateByIndex(i + 1, j);;
      if (matrixVct[i][j + 1] != -1)state4 = getStateByIndex(i, j + 1);;
    }

    if (state1 != NULL) vect.push_back(state1);
    if (state2 != NULL) vect.push_back(state2);
    if (state3 != NULL) vect.push_back(state3);
    if (state4 != NULL) vect.push_back(state4);

    return vect;
  }

  /**
   * createSolution - creating the string of the path by the path list we get.
   * @param pathLst - the list of states that represents the path.
   * @return string - string of the path.
   */
  string createSolution(list<State<T> *> pathLst) {
    string str = "";
    long cost = 0;
    while (!pathLst.empty()) {
      State<T> *state = pathLst.front();

      pathLst.pop_front();
      cost += state->getValue();

      int currI = state->getI();
      int currJ = state->getJ();
      if (!pathLst.empty()) {
        State<T> *state = pathLst.front();
        pathLst.pop_front();
        int nextI = state->getI();
        int nextJ = state->getJ();

        cost += state->getValue();

        if (currI == nextI - 1) {
          str += "DOWN(";
        }

        if (currJ == nextJ - 1) {
          str += "RIGHT(";
        }

        if (currI == nextI + 1) {
          str += "UP(";
        }

        if (currJ == nextJ + 1) {
          str += "LEFT(";
        }

        pathLst.push_front(state);

        str += to_string(cost);
        str += ")-";

        cost -= state->getValue();

      } else
        break;
    }

    string newStr = str.substr(0, str.size() - 1);
    newStr += '\n';
    return newStr;
  }

  /**
   * createStates - the function creates vector of states* by the matrix values.
   */
  void createStates() {
    for (int i = 0; i < this->rowNum; i++) {
      for (int j = 0; j < this->colsNum; j++) {
        State<T> *state = new State<T>(i, j, matrixVct[i][j]);
        this->states.push_back(state);
      }
    }
  }

  /**
   * getStates - returns the states vector.
   * @return vector<State<T> *> - the states vector.
   */
  vector<State<T> *> getStates() {
    return this->states;
  }

  /**
   * getStateByIndex - the function gets i and j indexes and returns a pointer to the current state.
   * @param i - i index.
   * @param j -j index.
   * @return State<T> * - the pointer to the state.
   */
  State<T> *getStateByIndex(int i, int j) {
    for (int k = 0; k < this->states.size(); k++) {
      State<T> *state = this->states[k];
      if (state->getI() == i && state->getJ() == j && state->getValue() == this->matrixVct[i][j]) {
        return state;
      }
    }
  }

};

#endif //EX4__MATRIXPROBLEM_H_