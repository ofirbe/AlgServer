//
// Created by michael on 09/01/2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_
#include "Solver.h"
#include "CacheManager.h"
#include "Server.h"
#include "AlgServer.h"
using namespace server_side;

template<typename P, typename S>
class MyTestClientHandler : public ClientHandler {
 private:
  Solver<P, S> s; // P - problem and S - solution
  CacheManager<S> ch;
 public:
  /**
   * CTOR
   * @param s - the solver
   * @param ch - the cache manager
   */
  MyTestClientHandler(Solver<P, S> s, int capacity) {
    this->s = s;
    this->ch = CacheManager<S>(capacity);
  }

  /**
   * handleClient
   * @param input_stream
   * @param out_put_stream
   */
  void handleClient(InputStream *input_stream, OutPutStream *out_put_stream) {
    // reading the problem from the input
    P problem = input_stream->readFromStream(); // get the problem from the input
    S solution;

    if (problem == "end") // need to close the socket
      return;

    if (this->ch.isExist(problem) == 1) {
      // if the solution is available - return it
      solution = this->ch.get(problem);
    } else {
      // create the solution
      solution = this->s.solve(problem);
      // insert the new solution into the cache manager
      this->ch.insert(solution);
    }

    // writing the solution to the output
    out_put_stream->writeToStream(solution);
  }
};

#endif //EX4__MYTESTCLIENTHANDLER_H_