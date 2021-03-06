#ifndef CME212_GRAPH_HPP
#define CME212_GRAPH_HPP

/** @file Graph.hpp
 * @brief An undirected graph type
 */

#include <algorithm>
#include <vector>
#include <cassert>
#include <set>
#include <string>
#include <functional>

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
  // Use this space for declarations of important internal types you need
  // later in the Graph's definition.
  // (As with all the "YOUR CODE HERE" markings, you may not actually NEED
  // code here. Just use the space if you need it.)
  //
  // PUBLIC TYPE DEFINITIONS
  //
 public:
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
    // Allocate memory for datastructures so we do not need to reallocate during
    // runtime.
    Points.reserve(40000);
    Edges.reserve(350000);
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
        this->id=size_type(-1);
        this->graph=nullptr;
    }

    /** Return this node's position. */
    const Point& position() const {
      return graph->Points[id];
    }

    /** Return this node's index, a number in the range [0, graph_size). */
    size_type index() const {
      return this->id;
    }

    /** Test whether this node and @a n are equal.
     *
     * Equal nodes have the same graph and the same index.
     */
    bool operator==(const Node& n) const {
        bool test=(n.graph==this->graph&&n.index()==this->id);
        return test;
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
        if(this->id<n.index()){
            return true;
        }
        if(this->id==n.index()){
            std::less<Graph*> comp;
            return comp(this->graph,n.graph);
        }
      return false;
    }

   private:
    // Allow Graph to access Node's private member data and functions.
    friend class Graph;
    size_type id;
    Graph* graph;
    Node(size_type i,const Graph* id_graph){
        this->graph=const_cast<Graph*>(id_graph);
        this->id=i;
    }
    // Use this space to declare private data members and methods for Node
    // that will not be visible to users, but may be useful within Graph.
    // i.e. Graph needs a way to construct valid Node objects
  };

  /** Return the number of nodes in the graph.
   *
   * Complexity: O(1).
   */
  size_type size() const {
    return this->Points.size();
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
    Points.push_back(position);
    return this->node(this->Points.size()-1);        
  }

  /** Determine if a Node belongs to this Graph
   * @return True if @a n is currently a Node of this Graph
   *
   * Complexity: O(1).
   */
  bool has_node(const Node& n) const {
    // HW0: YOUR CODE HERE
    bool in_graph;
    if(n.index()>this->size()){
        in_graph=false;
    }
    in_graph=this->node(n.index())==n;
    (void) n;            // Quiet compiler warning
    return in_graph;
  }

  /** Return the node with index @a i.
   * @pre 0 <= @a i < num_nodes()
   * @post result_node.index() == i
   *
   * Complexity: O(1).
   */
  Node node(size_type i) const {
    if (i>=this->Points.size()){
        std::cout<< "Index: "<<i<<" out of bounds."<<std::endl; 
        return Node();
    }
    else{
        return Node(i,this);        
    }
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
        id=size_type(-1);
        graph=nullptr;
    }

    /** Return a node of this Edge */
    Node node1() const {
        auto pair=graph->Edges[this->id];
        return graph->node(pair.first);      
    }

    /** Return the other node of this Edge */
    Node node2() const {
        auto pair=graph->Edges[this->id];
        return graph->node(pair.second);      
    }

    /** Test whether this edge and @a e are equal.
     *
     * Equal edges represent the same undirected edge between two nodes.
     */
    bool operator==(const Edge& e) const {
        if(this->node1()==e.node1()&&this->node2()==e.node2()){
            return true;
        }       
        if(this->node1()==e.node2()&&this->node2()==e.node1()){
            return true;
        }       
        return false;
    }

    /** Test whether this edge is less than @a e in a global order.
     *
     * This ordering function is useful for STL containers such as
     * std::map<>. It need not have any interpretive meaning.
     */
    bool operator<(const Edge& e) const {
        //The ordering is defined in the same way ordering on std::pair is
        //defined.
        if(this->node1()<e.node1()&&this->node2()<e.node2()){
            return true;
        }
        else{
            return false;
        }
    }

   private:
    // Allow Graph to access Edge's private member data and functions.
    friend class Graph;
    size_type id;
    Graph* graph;
    Edge(size_type i,const Graph* id_graph){
        this->graph=const_cast<Graph*>(id_graph);
        this->id=i;
    }
    // Use this space to declare private data members and methods for Edge
    // that will not be visible to users, but may be useful within Graph.
    // i.e. Graph needs a way to construct valid Edge objects
  };

  /** Return the total number of edges in the graph.
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  size_type num_edges() const {
    return Edges.size();
  }

  /** Return the edge with index @a i.
   * @pre 0 <= @a i < num_edges()
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  Edge edge(size_type i) const {
    if(i>Edges.size()){
        return Edge();      
    }
    else{
        return Edge(i,this);
    }
  }

  /** Test whether two nodes are connected by an edge.
   * @pre @a a and @a b are valid nodes of this graph
   * @return True if for some @a i, edge(@a i) connects @a a and @a b.
   *
   * Complexity: No more than O(num_nodes() + num_edges()), hopefully less
   */
  bool has_edge(const Node& a, const Node& b) const {
    std::pair<size_type,size_type> edge1 (a.index(),b.index());
    std::pair<size_type,size_type> edge2 (b.index(),a.index());
    if(std::find(this->Edges.begin(),this->Edges.end(),edge1)!=Edges.end()){
        return true;
    }
    if(std::find(this->Edges.begin(),this->Edges.end(),edge2)!=Edges.end()){
        return true;
    }
    else{
        return false;
    }
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
    std::pair<size_type,size_type> edge1 (a.index(),b.index());
    std::pair<size_type,size_type> edge2 (b.index(),a.index());
    auto pos1=std::find(this->Edges.begin(),this->Edges.end(),edge1);
    auto pos2=std::find(this->Edges.begin(),this->Edges.end(),edge2);
    if(pos1 !=Edges.end()){
        auto index=pos1-Edges.begin();
        return this->edge(size_type(index));
    }
    if(pos2!=Edges.end()){
        auto index=pos1-Edges.begin();
        return this->edge(size_type(index));
    }
    this->Edges.push_back(edge1);
    return this->edge(this->Edges.size()-1);
  }

  /** Remove all nodes and edges from this graph.
   * @post num_nodes() == 0 && num_edges() == 0
   *
   * Invalidates all outstanding Node and Edge objects.
   */
  void clear() {
    Points.clear();
    Edges.clear();
  }

 private:
    std::vector<Point> Points;
    std::vector<std::pair<size_type,size_type>> Edges; 
  // Use this space for your Graph class's internals:
  //   helper functions, data members, and so forth.

};

#endif // CME212_GRAPH_HPP
