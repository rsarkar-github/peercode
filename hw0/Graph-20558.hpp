#ifndef CME212_GRAPH_HPP
#define CME212_GRAPH_HPP

/** @file Graph.hpp
 * @brief An undirected graph type
 */

#include <algorithm>
#include <vector>
#include <cassert>

#include "CME212/Util.hpp"
#include "CME212/Point.hpp"


/** @class Graph
 * @brief A template for 3D undirected graphs.
 *
 * Users can add and retrieve nodes and edges. Edges are unique (there is at
 * most one edge between any pair of distinct nodes).
 */
class Graph {
  private:
	// Declarations of important internal types needed
	// later in the Graph's definition.
	struct internal_node;
	struct internal_edge;
	std::vector<internal_node> m_graph_nodes;
	std::vector<internal_edge> m_graph_edges;

  public:
	//
	// PUBLIC TYPE DEFINITIONS
	//
	/** Type of this graph. */
	using graph_type = Graph;
	/** Predeclaration of Node type. */
	class Node;
	/** Synonym for Node (following STL conventions). */
	using node_type = Node;
	/** Predeclaration of Edge type. */
	class Edge;
	/** Synonym for Edge (following STL conventions). */
	using edge_type = Edge;
	/** Type of indexes and sizes.
		Return type of Graph::Node::index(), Graph::num_nodes(),
		Graph::num_edges(), and argument type of Graph::node(size_type) */
	using size_type = unsigned;

	//
	// CONSTRUCTORS AND DESTRUCTOR
	//
	/** Construct an empty graph. */
	Graph() {
	}
	/** Default destructor */
	~Graph() = default;

	//
	// NODES
	//
	/** @class Graph::Node
	 * @brief Class representing the graph's nodes.
	 *
	 * Node objects are used to access information about the Graph's nodes.
	 */
	class Node {
	  public:
		/** Construct an invalid node.
		 *
		 * Valid nodes are obtained from the Graph class, but it
		 * is occasionally useful to declare an @i invalid node, and assign a
		 * valid node to it later. For example:
		 *
		 * @code
		 * Graph::node_type x;
		 * if (...should pick the first node...)
		 *   x = graph.node(0);
		 * else
		 *   x = some other node using a complicated calculation
		 * do_something(x);
		 * @endcode
		 */
		Node() {
 		}
		/** Return this node's position. */
		const Point& position() const {
			return (m_ptr_graph->m_graph_nodes)[m_index].m_node_point;
		}
		/** Return this node's index, a number in the range [0, graph_size). */
		size_type index() const {
			return m_index;
		}
		/** Test whether this node and @a n are equal.
		 *
		 * Equal nodes have the same graph and the same index.
		 */
		bool operator==(const Node& n) const {
			return m_ptr_graph->has_node(n) && m_index==n.index();
		}
		/** Test whether this node is less than @a n in a global order.
		 *
		 * This ordering function is useful for STL containers such as
		 * std::map<>. It need not have any geometric meaning.
		 *
		 * The node ordering relation must obey trichotomy: For any two nodes x
		 * and y, exactly one of x == y, x < y, and y < x is true.
		 */
		bool operator<(const Node& n) const {
			return m_index<n.index();
		}
	
	  private:
		// Allow Graph to access Node's private member data and functions.
		friend class Graph;
		// Declaration of private data members and methods for Node
		// that will not be visible to users, but may be useful within Graph.
		// i.e. Graph needs a way to construct valid Node objects
		size_type m_index;
		const Graph* m_ptr_graph;
		/** Construct a valid node. */
 		Node(size_type index, const Graph* ptr_graph) :
 			m_index(index),
 			m_ptr_graph(ptr_graph) {
 		}
	};

	/** Return the number of nodes in the graph.
	 *
	 * Complexity: O(1).
	 */
	size_type size() const {
		return m_graph_nodes.size();
	}
	/** Synonym for size(). */
	size_type num_nodes() const {
		return size();
	}
	/** Add a node to the graph, returning the added node.
	 * @param[in] position The new node's position
	 * @post new num_nodes() == old num_nodes() + 1
	 * @post result_node.index() == old num_nodes()
	 *
	 * Complexity: O(1) amortized operations.
	 */
	Node add_node(const Point& position) {
		internal_node n;
		n.m_node_point = position;
		m_graph_nodes.push_back(n);
		size_type i = size();
		return Node(i - 1, this); 
	}
	/** Determine if a Node belongs to this Graph
	 * @return True if @a n is currently a Node of this Graph
	 *
	 * Complexity: O(1).
	 */
	bool has_node(const Node& n) const {
		return n.m_ptr_graph==this;
	}
	/** Return the node with index @a i.
	 * @pre 0 <= @a i < num_nodes()
	 * @post result_node.index() == i
	 *
	 * Complexity: O(1).
	 */
	Node node(size_type i) const {
		assert(i<size());
		return Node(i, this);
	}

	//
	// EDGES
	//
	/** @class Graph::Edge
	 * @brief Class representing the graph's edges.
	 *
	 * Edges are order-insensitive pairs of nodes. Two Edges with the same nodes
	 * are considered equal if they connect the same nodes, in either order.
	 */
	class Edge {
	  public:
		/** Construct an invalid Edge. */
		Edge() {
 		}
		/** Return a node of this Edge */
		Node node1() const {
	 		return (m_ptr_graph->m_graph_edges)[m_index].m_node1;
		}
		/** Return the other node of this Edge */
		Node node2() const {
			return (m_ptr_graph->m_graph_edges)[m_index].m_node2;
		}
		/** Test whether this edge and @a e are equal.
		 *
		 * Equal edges represent the same undirected edge between two nodes.
		 */
		bool operator==(const Edge& e) const {
			return (node1()==e.node1() && node2()==e.node2()) || 
				(node1()==e.node2() && node2()==e.node1());
		}
	
		/** Test whether this edge is less than @a e in a global order.
		 *
		 * This ordering function is useful for STL containers such as
		 * std::map<>. It need not have any interpretive meaning.
		 */
		bool operator<(const Edge& e) const {
			return m_index<e.m_index;
		}

	  private:
		// Allow Graph to access Edge's private member data and functions.
		friend class Graph;
		// Declaration of private data members and methods for Edge
		// that will not be visible to users, but may be useful within Graph.
		// i.e. Graph needs a way to construct valid Edge objects
		size_type m_index;
		const Graph* m_ptr_graph;
 		/** Construct a valid edge. */
		Edge(size_type index, const Graph* ptr_graph) :
 			m_index(index),
 			m_ptr_graph(ptr_graph) {
		}
	};

	/** Return the total number of edges in the graph.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	size_type num_edges() const {
		return m_graph_edges.size();
	}
	/** Return the edge with index @a i.
	 * @pre 0 <= @a i < num_edges()
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	Edge edge(size_type i) const {
		assert(i<num_edges());
		return Edge(i, this);
	}
	/** Test whether two nodes are connected by an edge.
	 * @pre @a a and @a b are valid nodes of this graph
	 * @return True if for some @a i, edge(@a i) connects @a a and @a b.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	bool has_edge(const Node& a, const Node& b) const {
		if (a.m_ptr_graph!=this || b.m_ptr_graph!=this) {
			return false;
 		}
		for (unsigned i=0; i<num_edges(); i++) {
	 		if ((m_graph_edges[i].m_node1==a && m_graph_edges[i].m_node2==b) || 
	 			(m_graph_edges[i].m_node1==b && m_graph_edges[i].m_node2==a)) {
				return true;
			}
		}
		return false;
	}
	/** Add an edge to the graph, or return the current edge if it already exists.
	 * @pre @a a and @a b are distinct valid nodes of this graph
	 * @return an Edge object e with e.node1() == @a a and e.node2() == @a b
	 * @post has_edge(@a a, @a b) == true
	 * @post If old has_edge(@a a, @a b), new num_edges() == old num_edges().
	 *       Else,                        new num_edges() == old num_edges() + 1.
	 *
	 * Can invalidate edge indexes -- in other words, old edge(@a i) might not
	 * equal new edge(@a i). Must not invalidate outstanding Edge objects.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	Edge add_edge(const Node& a, const Node& b) {
		if (a.m_ptr_graph==this && b.m_ptr_graph==this) {
			for (unsigned i=0; i<num_edges(); i++) {
				if ((m_graph_edges[i].m_node1==a && m_graph_edges[i].m_node2==b) || 
					(m_graph_edges[i].m_node1==b && m_graph_edges[i].m_node2==a)) {
					return Edge(i, this);
				}
			}
		}
		internal_edge e;
		e.m_node1 = a;
		e.m_node2 = b;
		m_graph_edges.push_back(e);
		size_type i = num_edges();
		return Edge(i - 1, this);
	}
	/** Remove all nodes and edges from this graph.
	 * @post num_nodes() == 0 && num_edges() == 0
	 *
	 * Invalidates all outstanding Node and Edge objects.
	 */
	void clear() {
		this->m_graph_nodes.clear();
		this->m_graph_edges.clear();
	}

  private:
	// Graph class's internals:
	// helper functions, data members, and so forth.
	struct internal_node {
		Point m_node_point;
	};
	struct internal_edge {
		node_type m_node1;
		node_type m_node2;
	};
};
#endif // CME212_GRAPH_HPP
