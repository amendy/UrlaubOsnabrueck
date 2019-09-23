#include "Graph.h"
#include <list>
#include <fstream>
#include <algorithm>
#include <limits>
#include <map>

//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		delete *it;
	}

	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		delete *it;
	}
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
	if (findNode(pNewNode->getID()) != NULL)
	{
		throw "Duplicated NodeID";
	}

	m_nodes.push_back(pNewNode);
	return *pNewNode;

	// TEST:
	// Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes in main.cpp erstellen
	// Testen Sie mit der Funktion 'findNode', ob die hinzugefügten Nodes im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
	m_edges.push_back(pNewEdge);

	std::list<Node*>::iterator itSrcNode;
	itSrcNode = std::find(m_nodes.begin(), m_nodes.end(), &pNewEdge->getSrcNode());
	if (itSrcNode == m_nodes.end())
	{
		addNode(&pNewEdge->getSrcNode());
	}

	std::list<Node*>::iterator itDstNode;
	itDstNode = std::find(m_nodes.begin(), m_nodes.end(), &pNewEdge->getDstNode());
	if (itDstNode == m_nodes.end())
	{
		addNode(&pNewEdge->getDstNode());
	}

	return *pNewEdge;
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node& rNode)
{
	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); )
	{
		Edge* pCurrentEdge = *it;

		if (pCurrentEdge->isConnectedTo(rNode))
		{
			// erase gibt uns einen Iterator auf das Element nach dem gelöschten Element zurück		
			it = m_edges.erase(it);
		}
		else
		{
			it++;
		}
	}

	m_nodes.remove(&rNode);
	delete &rNode;
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge)
{
	m_edges.remove(&rEdge);
	delete &rEdge;
}


//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		Node* pCurrentNode = *it;

		if (pCurrentNode->getID() == id)
		{
			return pCurrentNode;
		}
	}

	return NULL;
}


Node* Graph::showNode() {

	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		Node* pCurrentNode = *it;

		return pCurrentNode;
	}
}

//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
{
	std::vector<Edge*> ret;

	// - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
	// - füge die Zeiger der Edges in den vector 'ret' ein.



	return ret;

	// TEST:
	// Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
	// und anschließend ein paar Edges im Graph suchen.
	// Prüfen Sie, ob Edges gefunden wurden und geben Sie die gefunden Edges auf der Kommandozeile aus!
}

//---------------------------------------------------------------------------------------------------------------------

void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
{
	Node* src = findNode(rSrcNode.getID());
	Node* dst = findNode(rDstNode.getID());

	if (src == NULL || dst == NULL)
	{
		return;
	}

	std::list<Node*> Q;
	std::map<Node*, RouteInfo> nodeInfo;

	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		nodeInfo[*it] = { std::numeric_limits<double>::max(), NULL, NULL };
		Q.push_back(*it);
	}

	nodeInfo[src].dist = 0;

	while (!Q.empty())
	{
		Node* u = Q.front(); // erstes Element in der Liste
		for (std::list<Node*>::iterator it = Q.begin(); it != Q.end(); it++)
		{
			if (nodeInfo[*it].dist < nodeInfo[u].dist)
			{
				u = *it;
			}
		}
		Q.remove(u);

		// Abbruchbedingung
		if (u == dst)
		{
			for (Node* pCurrentNode = dst;
				nodeInfo[pCurrentNode].prevEdge != NULL;
				pCurrentNode = nodeInfo[pCurrentNode].prevNode)
			{
				rPath.push_front(nodeInfo[pCurrentNode].prevEdge);
			}
			return;
		}


		for (std::list<Edge*>::iterator it = u->getOutEdges().begin(); it != u->getOutEdges().end(); it++)
		{
			Edge* pNeighbourEdge = *it;
			Node* pNeighbourNode = &pNeighbourEdge->getDstNode();

			double newDistance = nodeInfo[u].dist + pNeighbourEdge->getWeight();

			if (newDistance < nodeInfo[pNeighbourNode].dist)
			{
				RouteInfo& vInfo = nodeInfo[pNeighbourNode];
				vInfo.dist = newDistance;
				vInfo.prevNode = u;
				vInfo.prevEdge = pNeighbourEdge;
			}
		}

	}

	/*
	Ein häufiges Anwendungsproblem für Graphen-Anwendungen besteht darin,
	den Pfad zwischen verschiedenen Nodes zu finden, die direkt oder indirekt über Edges miteinander verbunden sind.
	Um den optimalsten Pfad(den mit den geringsten Kantengewichten) zu finden, gibt es den Dijkstra-Algorithmus!
	Pseudocode (Quelle: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
	>>>
	function Dijkstra(Graph, source):

		  create vertex set Q

		  for each vertex v in Graph:             // Initialization
			  dist[v] ← INFINITY                  // Unknown distance from source to v
			  prev[v] ← UNDEFINED                 // Previous node in optimal path from source
			  add v to Q                          // All nodes initially in Q (unvisited nodes)

		  dist[source] ← 0                        // Distance from source to source

		  while Q is not empty:
			  u ← vertex in Q with min dist[u]    // Source node will be selected first
			  remove u from Q

			  for each neighbor v of u:           // where v is still in Q.
				  alt ← dist[u] + length(u, v)
				  if alt < dist[v]:               // A shorter path to v has been found
					  dist[v] ← alt
					  prev[v] ← u

		  return dist[], prev[]
	<<<

	Betrachten Sie den Pseudocode und setzen Sie ihn in C++ um.
	Sortieren Sie am Ende das Ergebnis in die richtige Reihenfolge um
	und geben sie die kürzeste Route zwischen rSrcNode und rDstNode als Liste von Edges zurück.

	TEST:
	Testen Sie diese Funktion, indem Sie einen Graph in main.cpp erstellen
	und sich die kürzesteste Route zwischen 2 Nodes zurückgeben lassen.
	*/

}


//---------------------------------------------------------------------------------------------------------------------

