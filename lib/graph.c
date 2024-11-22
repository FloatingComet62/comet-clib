#include "../lib.h"

graph graph_init(u32 number_of_nodes) {
  f64* data = calloc(number_of_nodes * number_of_nodes, sizeof(f64));
  if (data == NULL) {
    errr("Failed to allocate memory");
  }
  for (u32 i = 0; i < number_of_nodes * number_of_nodes; i++) {
    data[i] = 0.0;
  }
  return (graph){data, number_of_nodes};
}

void graph_deinit(const graph self) { free(self.data); }

f64* graph_at(graph* g, u32 from, u32 to) {
  return g->data + from * g->number_of_nodes + to;
}

void graphMUT_add_edge(graph* self, u32 from, u32 to) {
  *graph_at(self, from, to) = 1.0;
}
void graphMUT_add_edge_weighted(graph* self, u32 from, u32 to, f64 weight) {
  *graph_at(self, from, to) = weight;
}

void graphMUT_add_bidirectional_edge(graph* self, u32 node1, u32 node2) {
  *graph_at(self, node1, node2) = 1.0;
  *graph_at(self, node2, node1) = 1.0;
}

void graphMUT_add_bidirectional_edge_weighted(graph* self, u32 node1, u32 node2,
                                              f64 weight) {
  *graph_at(self, node1, node2) = weight;
  *graph_at(self, node2, node1) = weight;
}

u32 graph_get_degree(const graph self, u32 node) {
  f64* nodeData = self.data + node * self.number_of_nodes;
  u32 degree = 0;
  for (u32 i = 0; i < self.number_of_nodes; i++) {
    if (nodeData[i] > 0.0) {
      degree++;
    }
  }
  return degree;
}

graph graph_transpose(graph* self) {
  graph g = graph_init(self->number_of_nodes);
  for (u32 i = 0; i < self->number_of_nodes; i++) {
    for (u32 j = 0; j < self->number_of_nodes; j++) {
      *graph_at(&g, i, j) = *graph_at(self, j, i);
    }
  }
  return g;
}

graph graph_get_bidirectional(graph* self) {
  graph g = graph_init(self->number_of_nodes);
  for (u32 i = 0; i < self->number_of_nodes; i++) {
    for (u32 j = 0; j < self->number_of_nodes; j++) {
      f64 normal = *graph_at(self, i, j);
      f64 transpose = *graph_at(self, j, i);
      if (normal != 0.0) {
        *graph_at(&g, i, j) = normal;
      } else {
        *graph_at(&g, i, j) = transpose;
      }
    }
  }
  return g;
}

vec graph_get_edges(graph* self) {
  vec output = vec_init(sizeof(graph_edge));
  graph_edge edge;
  for (u32 from = 0; from < self->number_of_nodes; from++) {
    for (u32 to = 0; to < self->number_of_nodes; to++) {
      if (from == to) {
        continue;
      }
      if (*graph_at(self, from, to) == 0.0) {
        continue;
      }
      edge.from = from;
      edge.to = to;
      vecMUT_push_value(&output, &edge);
    }
  }
  return output;
}

void search_recursive(graph* g, u32 current_node, vec* output, vec* visited) {
  *(bool*)vec_at_assume(visited, current_node) = true;
  vecMUT_push(output, &current_node);

  for (u32 i = 0; i < g->number_of_nodes; i++) {
    bool* next_node = vec_at_assume(visited, i);
    f64* edge = graph_at(g, current_node, i);
    if (*edge <= 0.0 || *next_node) {
      continue;
    }

    search_recursive(g, i, output, visited);
  }
}

vec graph_depth_first_search(graph* self, u32 source_node) {
  if (source_node >= self->number_of_nodes) {
    return vec_init(sizeof(u32));
  }
  vec output = vec_init(sizeof(u32));
  vec visited = vec_init_reserve(sizeof(bool), self->number_of_nodes);
  for (u32 i = 0; i < self->number_of_nodes; i++) {
    *(bool*)vec_at_assume(&visited, i) = false;
  }
  search_recursive(self, source_node, &output, &visited);
  vec_deinit(visited);
  return output;
}

vec graph_breadth_first_search(graph* self, u32 source_node) {
  if (source_node >= self->number_of_nodes) {
    return vec_init(sizeof(u32));
  }
  vec output = vec_init(sizeof(u32));
  vec queue = vec_init(sizeof(u32));
  u32 dequeuing_index = 0;

  vec visited = vec_init_reserve(sizeof(bool), self->number_of_nodes);
  for (u32 i = 0; i < self->number_of_nodes; i++) {
    *(bool*)vec_at_assume(&visited, i) = false;
  }

  *(bool*)vec_at_assume(&visited, source_node) = true;
  vecMUT_push(&queue, &source_node);

  while (queue.length > dequeuing_index) {
    u32 current = *(u32*)vec_at_assume(&queue, dequeuing_index);
    dequeuing_index++;
    vecMUT_push(&output, &current);

    for (u32 i = 0; i < self->number_of_nodes; i++) {
      bool* next_node = vec_at_assume(&visited, i);
      f64* edge = graph_at(self, current, i);
      if (*edge <= 0.0 || *next_node) {
        continue;
      }
      *(bool*)vec_at_assume(&visited, i) = true;
      vecMUT_push(&queue, &i);
    }
  }
  vec_deinit(queue);
  vec_deinit(visited);
  return output;
}