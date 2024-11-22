#include "lib.h"

#ifdef COMET_LIB_TEST
#include "test.h"
#else

int main() {
  graph g = graph_init(7);

  graphMUT_add_edge(&g, 0, 1);
  graphMUT_add_edge(&g, 0, 2);
  graphMUT_add_edge(&g, 1, 3);
  graphMUT_add_edge(&g, 2, 4);
  graphMUT_add_edge(&g, 1, 5);
  graphMUT_add_edge(&g, 2, 6);

  vec nodes = graph_breadth_first_search(&g, 0);
  for (int i = 0; i < nodes.length; i++) {
    printf("%d\n", *(u32*)vec_at_assume(&nodes, i));
  }

  vec_deinit(nodes);
  graph_deinit(g);

  return 0;
}

#endif
