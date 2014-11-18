/**
 * @file: task/iface.h 
 * Interface of a programming task 2
 */
#include "../Utils/utils_iface.h"
#include <unordered_set>
#include <list>
#include <iterator>

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
#    define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif

// Simple debug assert
#if !defined(GRAPH_ASSERTD)
#    define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif

/**
 * Namespace for the programming task
 */
namespace Task
{
    //
    // Graph representation template
    // @param NodeT class representing nodes of graph, should be inherited from Graph::Node
    // @param EdgeT class representing edges of graph, should be inherited from Graph::Edge
    //
    template < class NodeT, class EdgeT> class Graph
    {
    public:
		typedef typename list<NodeT>::iterator NodeIterator;
		typedef typename list<EdgeT>::iterator EdgeIterator;
        typedef UInt32 UId; //< Unique id type for node and edge
        static const UId INVALID_UID = (UId) (-1);
		list<UId> countId;

        class Error: public std::exception
        {
		public:
			virtual const char* what() const throw()
			{
				return msg;
			}

			Error(const char* messageOfError)
			{
				msg = messageOfError;
			}
		private:
			const char* msg;
        };


		//template of own iterator
		template <class T> class ownIterator
		{
		public:
			ownIterator(const typename list<T>::iterator &constr) : ownIter(constr) {}

			bool operator!=(const ownIterator &it)
			{
				return ownIter != it.ownIter;
			}

			bool operator==(const ownIterator &it)
			{
				return ownIter == it.ownIter;
			}

			T &operator*()
			{
				return *ownIter;
			}

			ownIterator &operator++()
			{
				++ownIter;
				return *this;
			}

			ownIterator &operator--()
			{
				--ownIter;
				return *this;
			}

		private:
			typename list<T>::iterator ownIter;
		};


        //
        // Graph node representation
        //
        class Node
        {

			friend class Graph;

        public:
            //---- Iterator types ----
            typedef ownIterator<EdgeIterator> pred_iterator;// iterator for node's predecessor edges 
            typedef ownIterator<EdgeIterator> succ_iterator;// iterator for node's successor edges 

            pred_iterator preds_begin(); // Get iterator to the first predecessor edge
            pred_iterator preds_end();   // Get end iterator for the predecessors

            succ_iterator succs_begin(); // Get iterator to the first successor edge
            succ_iterator succs_end();   // Get end iterator for the successors

            Graph& graph();  // Get the graph reference
            UId uid() const; // Get the node's unique id 

            EdgeT& first_pred(); // Convinience routine returns first predecessor edge or throws an exception
            EdgeT& first_succ(); // Convinience routine returns first successor edge or throws an exception
            
            UInt32 num_preds() const; // Get the number of predecessors
            UInt32 num_succs() const; // Get the number of successors

        protected:
            Node( Graph& g); // Constructor of the node
			virtual ~Node() {} // Destructor of the node
        private:
            // ---- Default  and copy constructors turned off ---
            Node();
			//Data
   			list<EdgeIterator> predEdgeIter;
			list<EdgeIterator> succEdgeIter;
			UId nodeId;
			NodeIterator iter;
			Graph &nodeGraph;
        };

        // 
        // Graph edge representation
        //
        class Edge
        {

			friend class Graph;

        public:
            NodeT &pred(); // Get edge predecessor
            NodeT &succ(); // Get edge successor

            Graph& graph(); // Get the graph
            UId uid() const;// Get the edge's unique id
        protected:
            Edge( NodeT& p, NodeT& s); // Construct an edge between given nodes
			virtual ~Edge() {}
        private:
        // ---- Default  and copy constructors turned off ---
			Edge();
            Edge( const Edge &e);
			//Data
			UId edgeId;
			EdgeIterator iter;
			NodeT &predNode;
			NodeT &succNode;
			Graph &edgeGraph;
			typename list<EdgeIterator>::iterator predIter;
			typename list<EdgeIterator>::iterator succIter;
    };

    public:
    // ---- Graph interface ----
        typedef ownIterator<NodeT> node_iterator; // Iterator for the graph's nodes
        typedef ownIterator<EdgeT> edge_iterator; // Iterator for the graph's edges
               
        node_iterator nodes_begin(); // Get the iterator to the first node
        node_iterator nodes_end();   // Get the end iterator for the nodes

        edge_iterator edges_begin(); // Get the iterator to the first edge
        edge_iterator edges_end();   // Get the end iterator for the edges

        UInt32 num_nodes() const; // Get the number of nodes
        UInt32 num_edges() const; // Get the number of edges

        NodeT &create_node();                   // Create a new node and return reference to it
        EdgeT &create_edge( NodeT& pred, NodeT& succ); // Create a new edge between given nodes
    
        void remove( NodeT& node); // Remove and delete node
        void remove( EdgeT& edge); // Remove and delete edge

		virtual ~Graph() {} // Destructor, deletes all nodes and edges

		Graph()
		{
			countId.push_back(1);
		}

    private:
		//Data
		std::list<EdgeT> edgeList;
		std::list<NodeT> nodeList;
    };

    bool uTest( UnitTest *utest_p);
};

#include "graph_impl.h"
