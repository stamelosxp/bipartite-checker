#include <LEDA/graph/graph.h>
#include <vector>
#include <LEDA/core/queue.h>
#include <LEDA/core/random_source.h>
#include <LEDA/graph/graph_misc.h>

using namespace leda;

list<node> my_BFS(const graph& G, node s, node_array<int>& dist, node_array<edge>& pred, node_array<int>& color)
{
	list<node> nodes;

	queue<node> Q;
	node v, w;

	/* change dist of the source node s to 0 and append it to the queue */
	dist[s] = 0;
	Q.append(s);
	color[s] = 0; //0 = green 

	edge e;

	while (!Q.empty())
	{
		v = Q.pop();
		
		
		nodes.append(v);

		forall_inout_edges(e, v)
		{
			/* w is the other node of the edge e */
			w = G.opposite(v, e);

			/* if dist[w] < 0, then w is not already discovered, therefore append it to Q and update dist and pred */
			if (dist[w] < 0)
			{ 
				Q.append(w);
				
				dist[w] = dist[v] + 1;
				if(dist[w] % 2 == 0){
					color[w] = 0;
				}
				else{
					color[w] = 1; //1 = red 
				}
				pred[w] = e;
			}
		}

	}

	/* return all the discovered nodes */
	return nodes;
}
