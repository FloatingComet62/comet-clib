#include "../lib.h"

graph graph_init(u32 number_of_nodes) {
  f64* data = malloc(number_of_nodes * number_of_nodes * sizeof(f64));
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

void graphMUT_add_edge(graph* self, u32 from, u32 to, optional weight) {
  if (!weight.has_data) {
    *graph_at(self, from, to) = 1.0;
    return;
  }
  *graph_at(self, from, to) = *(f64*)&weight.data;
}

void graphMUT_add_bidirectional_edge(graph* self, u32 from, u32 to,
                                     optional weight) {
  if (!weight.has_data) {
    *graph_at(self, from, to) = 1.0;
    *graph_at(self, to, from) = 1.0;
    return;
  }
  *graph_at(self, from, to) = *(f64*)&weight.data;
  *graph_at(self, to, from) = *(f64*)&weight.data;
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
