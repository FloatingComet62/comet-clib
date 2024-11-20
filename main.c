#include "lib.h"

#ifdef COMET_LIB_TEST
#include "test.h"
#else

int main() {
  // str s = str_init("Hello World");
  // info(s.data);
  // str_deinit(s);

  graph g = graph_init(4);
  int weight = 1.0;
  graphMUT_add_bidirectional_edge(&g, 0, 1, optional_init_some(&weight));
  graphMUT_add_edge(&g, 1, 2, optional_init_some(&weight));
  printf("Degree of node 1: %d\n", graph_get_degree(g, 1));
  graph_deinit(g);

  return 0;
}

#endif
