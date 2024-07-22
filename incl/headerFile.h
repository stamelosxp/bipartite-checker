#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <LEDA/graph/graph.h>
#include <vector>
#include <LEDA/core/queue.h>
#include <LEDA/core/random_source.h>
#include <LEDA/graph/graph_misc.h>

leda::list<leda::node> my_BFS(const leda::graph& G, leda::node s, leda::node_array<int>& dist, leda::node_array<leda::edge>& pred, leda::node_array<int>& color);

#endif