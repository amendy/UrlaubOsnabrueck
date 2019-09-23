#ifndef EDGE_H
#define EDGE_H

#include "Node.h"


class Edge
{
public:

	Edge();

	Edge(Node& rSrc, Node& rDst);

	Edge(const Edge& rOther);

	virtual ~Edge();

	bool isConnectedTo(const Node& rNode) const;

	Node& getSrcNode() { return m_rSrc; }
	Node& getDstNode() { return m_rDst; }

	std::string toString() const;

	virtual double getWeight() { return 1; }


private:

	Node& m_rSrc;
	Node& m_rDst;

};

#endif