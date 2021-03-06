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

template <typename V>
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
	/** Structure containing the node's information */
	struct internal_node;
	/** Vector containing the nodes' information of the graph */
	std::vector<internal_node> m_graph_nodes;

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
	/** Value type for node's value */
	using node_value_type = V;
	/** Predeclaration of Edge type. */
	class Edge;
	/** Synonym for Edge (following STL conventions). */
	using edge_type = Edge;
	  /** Type of node iterators, which iterate over all graph nodes. */
	class NodeIterator;
	/** Synonym for NodeIterator */
	using node_iterator = NodeIterator;
	/** Type of edge iterators, which iterate over all graph edges. */
	class EdgeIterator;
	/** Synonym for EdgeIterator */
	using edge_iterator = EdgeIterator;
	/** Type of incident iterators, which iterate incident edges to a node. */
	class IncidentIterator;
	/** Synonym for IncidentIterator */
	using incident_iterator = IncidentIterator;
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
	class Node : private totally_ordered<Node> {
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
			return (m_graph_ptr->m_graph_nodes)[m_node_index].m_node_point;
		}
		/** Return this node's index, a number in the range [0, graph_size). */
		size_type index() const {
			return m_node_index;
		}
		/** Return this node's value */
		node_value_type& value() {
			return m_graph_ptr->m_graph_nodes[m_node_index].m_node_value;
		}
		/** Return this node's value */
		const node_value_type& value() const {
			return m_graph_ptr->m_graph_nodes[m_node_index].m_node_value;
		}
		/** Return this node's degree */
		size_type degree() const {
			return (m_graph_ptr->m_adjacency)[m_node_index].size();
		}
		/** Return the first iterator over the incident edges on a specific node */
		incident_iterator edge_begin() const {
			return IncidentIterator(m_graph_ptr, m_node_index, 0);
		}
		/** Return the last iterator over the incident edges on a specific node */
		incident_iterator edge_end() const {
			return IncidentIterator(m_graph_ptr, m_node_index, (m_graph_ptr->m_adjacency)[m_node_index].size());
		}
		/** Test whether this node and @a n are equal.
		 *
		 * Equal nodes have the same graph and the same index.
		 */
		bool operator==(const Node& n) const {
			return m_graph_ptr->has_node(n) && m_node_index==n.index();
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
			if (m_graph_ptr==n.m_graph_ptr) {
				return m_node_index<n.index();
			}
			else {
				return  m_graph_ptr<n.m_graph_ptr;
			}
		}

	  private:
		// Allow Graph to access Node's private member data and functions.
		friend class Graph;
		// Declaration of private data members and methods for Node
		// that will not be visible to users, but may be useful within Graph.
		// i.e. Graph needs a way to construct valid Node objects
		graph_type* m_graph_ptr;
		size_type m_node_index;	
		/** Construct a valid node. */
 		Node(const graph_type* graph_ptr, size_type node_index) :
 			m_graph_ptr(const_cast<graph_type*>(graph_ptr)),
 			m_node_index(node_index) {
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
	Node add_node(const Point& position, const node_value_type& node_value=node_value_type()) {
		internal_node n{ position, node_value };
		m_graph_nodes.push_back(n);
		std::vector<size_type> tmp;
		m_adjacency.push_back(tmp);
		return Node(this, size() - 1); 
	}
	/** Determine if a Node belongs to this Graph
	 * @return True if @a n is currently a Node of this Graph
	 *
	 * Complexity: O(1).
	 */
	bool has_node(const Node& n) const {
		assert(n.m_node_index<size());
		return n.m_graph_ptr==this;
	}
	/** Return the node with index @a i.
	 * @pre 0 <= @a i < num_nodes()
	 * @post result_node.index() == i
	 *
	 * Complexity: O(1).
	 */
	Node node(size_type i) const {
		assert(i<size());
		return Node(this, i);
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
	class Edge : private totally_ordered<Edge> {
	  public:
		/** Construct an invalid Edge. */
		Edge() {
 		}
		/** Return a node of this Edge */
		Node node1() const {
	 		return Node(m_graph_ptr, m_node1_index);
		}
		/** Return the other node of this Edge */
		Node node2() const {
			return Node(m_graph_ptr, m_node2_index);
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
			if (m_graph_ptr==e.m_graph_ptr) {
				if (std::max(m_node1_index, m_node2_index)!=std::max(e.m_node1_index, e.m_node2_index)) {
						return std::max(m_node1_index, m_node2_index)<std::max(e.m_node1_index, e.m_node2_index);
					}
				else {
					return std::min(m_node1_index, m_node2_index)<std::min(e.m_node1_index, e.m_node2_index);
				}
			}
			else {
				return m_graph_ptr<e.m_graph_ptr;
			}
		}

	  private:
		// Allow Graph to access Edge's private member data and functions.
		friend class Graph;
		// Declaration of private data members and methods for Edge
		// that will not be visible to users, but may be useful within Graph.
		// i.e. Graph needs a way to construct valid Edge objects
		Graph* m_graph_ptr;
		size_type m_node1_index;
		size_type m_node2_index;		
 		/** Construct a valid edge. */
		Edge(const Graph* graph_ptr, size_type node1_index, size_type node2_index) :
 			m_graph_ptr(const_cast<graph_type*>(graph_ptr)),
 			m_node1_index(node1_index),
			m_node2_index(node2_index) {
		}
	};

	/** Return the total number of edges in the graph.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	size_type num_edges() const {
		size_type tmp = 0;
		for (unsigned i=0; i<m_adjacency.size(); i++) {
			tmp += m_adjacency[i].size();
		}
		return tmp / 2;
	}
	/** Return the edge with index @a i.
	 * @pre 0 <= @a i < num_edges()
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	Edge edge(size_type i) const {
		assert(i<num_edges());

		return *(std::next(edge_begin(), i));
	}
	/** Test whether two nodes are connected by an edge.
	 * @pre @a a and @a b are valid nodes of this graph
	 * @return True if for some @a i, edge(@a i) connects @a a and @a b.
	 *
	 * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
	 */
	bool has_edge(const Node& a, const Node& b) const {
		if (a.m_graph_ptr!=this || b.m_graph_ptr!=this) {
			return false;
 		}
 		std::vector<size_type> tmp = m_adjacency[a.index()];
 		size_type index = b.index();
 		for (unsigned i=0; i<tmp.size(); i++) {
	 		if (tmp[i]==index) {
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
		if (a.m_graph_ptr==this && b.m_graph_ptr==this) {
 			std::vector<size_type> tmp = m_adjacency[a.index()];
 			size_type index = b.index();
 			for (unsigned i=0; i<tmp.size(); i++) {
	 			if (tmp[i]==index) {
					return Edge(this, a.index(), b.index());
				}
 			}
 		}
		m_adjacency[b.index()].push_back(a.index());
		m_adjacency[a.index()].push_back(b.index());
		return Edge(this, a.index(), b.index());
	}
	/** Remove all nodes and edges from this graph.
	 * @post num_nodes() == 0 && num_edges() == 0
	 *
	 * Invalidates all outstanding Node and Edge objects.
	 */
	void clear() {
		this->m_graph_nodes.clear();
		this->m_adjacency.clear();
	}

	//
	// Node Iterator
	//

	/** @class Graph::NodeIterator
	 * @brief Iterator class for nodes. A forward iterator. */
	class NodeIterator : private totally_ordered<NodeIterator> {
	 public:
		// These type definitions let us use STL's iterator_traits.
		using value_type        = Node;                     // Element type
		using pointer           = Node*;                    // Pointers to elements
		using reference         = Node&;                    // Reference to elements
		using difference_type   = std::ptrdiff_t;           // Signed difference
		using iterator_category = std::input_iterator_tag;  // Weak Category, Proxy

		/** Construct an invalid NodeIterator. */
		NodeIterator() {
		}
		/** Dereferencing operator
	 	* @pre 0 <= @a m_node_index < num_nodes()
	 	* @post 0 <= @a result.index() < num_nodes()
	 	*/
		Node operator*() const {
			return Node(m_graph_ptr, m_node_index);
		}
		/** Increment operator
		* @pre 0 <= @a m_node_index < num_nodes()
	 	* @post 0 <= @a result.m_node_index < num_nodes()
	 	*/
		NodeIterator& operator++() {
			++m_node_index;
			return *this;
		}
		/** Test whether this iterator and @a it are equal. */
		bool operator==(const NodeIterator& node_it) const {
			return m_node_index==node_it.m_node_index && m_graph_ptr==node_it.m_graph_ptr;
		}

	 private:
		friend class Graph;
		graph_type* m_graph_ptr;
		size_type m_node_index;
		/** Construct a valid NodeIterator. */
		NodeIterator(const Graph* graph_ptr, size_type node_index) :
			m_graph_ptr(const_cast<graph_type*>(graph_ptr)),
			m_node_index(node_index) {
		}
	};

	/** Return the first iterator over the graph's nodes */
	node_iterator node_begin() const {
		return NodeIterator(this, 0);
	}
	/** Return the last iterator over the  graph's nodes */
	node_iterator node_end() const {
		return NodeIterator(this, size());
	}

	//
	// Incident Iterator
	//
	/** @class Graph::IncidentIterator
	 * @brief Iterator class for edges incident to a node. A forward iterator. */
	class IncidentIterator : private totally_ordered<IncidentIterator> {
	  public:
		// These type definitions let us use STL's iterator_traits.
		using value_type        = Edge;                     // Element type
		using pointer           = Edge*;                    // Pointers to elements
		using reference         = Edge&;                    // Reference to elements
		using difference_type   = std::ptrdiff_t;           // Signed difference
		using iterator_category = std::input_iterator_tag;  // Weak Category, Proxy

		/** Construct an invalid IncidentIterator. */
		IncidentIterator() {
		}
		/** Dereferencing operator
	 	* @pre 0 <= @a m_node_index < num_nodes()
	 	* @pre 0 <= @a m_incident_index < @a m_graph_ptr->m_adjacency[m_node_index].size()
	 	*/
		Edge operator*() const {
			return Edge(m_graph_ptr, m_node_index, (m_graph_ptr->m_adjacency)[m_node_index][m_incident_index]);
		}
		/** Increment operator
	 	* @post 0 <= @a m_incident_index < @a m_graph_ptr->m_adjacency[m_node_index].size()
	 	*/
		IncidentIterator& operator++() {
			++m_incident_index;
			return *this;
		}
		/** Test whether this iterator and @a iit are equal.*/
		bool operator==(const IncidentIterator& iit) const {
			return m_graph_ptr==iit.m_graph_ptr && m_node_index==iit.m_node_index && m_incident_index==iit.m_incident_index;
		}

	  private:
		friend class Graph;
		const Graph* m_graph_ptr;
		const size_type m_node_index;
		size_type m_incident_index;
		/** Construct a valid IncidentIterator. */
		IncidentIterator(const Graph* graph_ptr, const size_type node_index, size_type incident_index) : 
			m_graph_ptr(graph_ptr),
			m_node_index(node_index),
			m_incident_index(incident_index) {
		}
	};

	//
	// Edge Iterator
	//
	/** @class Graph::EdgeIterator
	 * @brief Iterator class for edges. A forward iterator. */
	class EdgeIterator : private totally_ordered<EdgeIterator> {
	  public:
		// These type definitions let us use STL's iterator_traits.
		using value_type        = Edge;                     // Element type
		using pointer           = Edge*;                    // Pointers to elements
		using reference         = Edge&;                    // Reference to elements
		using difference_type   = std::ptrdiff_t;           // Signed difference
		using iterator_category = std::input_iterator_tag;  // Weak Category, Proxy

		/** Construct an invalid EdgeIterator. */
		EdgeIterator() {
		}
		/** Dereferencing operator
	 	* @pre 0 <= @a m_node1_index < num_nodes()
	 	* @pre 0 <= @a m_edge_index < @a m_graph_ptr->m_adjacency[m_node1_index].size()
	 	*/
		Edge operator*() const {
			return Edge(m_graph_ptr, m_node1_index, (m_graph_ptr->m_adjacency)[m_node1_index][m_edge_index]);
		}
		/** Increment operator
	 	* @post 0 <= @a m_edge_index < @a m_graph_ptr->m_adjacency[m_node1_index].size()
	 	* Iterate over all the edges only once.
	 	*/
		EdgeIterator& operator++() {
			++m_edge_index;
			while (m_node1_index < m_graph_ptr->m_adjacency.size()) {
				while (m_edge_index < m_graph_ptr->m_adjacency[m_node1_index].size()) {
					if (m_node1_index < m_graph_ptr->m_adjacency[m_node1_index][m_edge_index]) {
						return *this;
					}
					++m_edge_index;
				}
				++m_node1_index;
				m_edge_index = 0;
			}
			return *this;
		}
		/** Test whether this iterator and @a edge_it are equal.*/
		bool operator==(const EdgeIterator& edge_it) const {
			return m_graph_ptr==edge_it.m_graph_ptr && m_node1_index==edge_it.m_node1_index && m_edge_index==edge_it.m_edge_index;
		}

	  private:
		friend class Graph;
		Graph* m_graph_ptr;
		size_type m_node1_index;
		size_type m_edge_index;
		/** Construct a valid EdgeIterator. */
		EdgeIterator(const Graph* graph_ptr, size_type node1_index, size_type edge_index) : 
			m_graph_ptr(const_cast<Graph*>(graph_ptr)),
			m_node1_index(node1_index),
			m_edge_index(edge_index) {
		}
	};

	/** Return the first iterator over the graph edges */
	edge_iterator edge_begin() const {
		return EdgeIterator(this, 0, 0);
	}
	/** Return the last iterator over the graph edges */
	edge_iterator edge_end() const {
		return EdgeIterator(this, m_adjacency.size(), 0);
	}

  private:
	// Graph class's internals:
	// helper functions, data members, and so forth.
	struct internal_node {
		Point m_node_point;
		node_value_type m_node_value;
	};
	/** Adjacency 2D-vector of the graph */
	std::vector<std::vector<size_type>> m_adjacency;
};
#endif // CME212_GRAPH_HPP
