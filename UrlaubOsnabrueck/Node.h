#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>


// forward-deklaration
class Edge;


class Node
{
public:


	Node();

	Node(std::string line, std::string id) : m_line(line), m_id(id) { s_numInstances++; }
	Node(std::string id) : m_id(id) { s_numInstances++; }
	std::string getID() const { return m_id; }
	std::string getLine() const { return m_line; }

	std::list<Edge*>& getOutEdges() { return m_outgoingEdges; }
	std::list<Edge*>& getInEdges() { return m_incomingEdges; }

private:

	std::string m_id;
	std::string m_line;

	std::list<Edge*> m_outgoingEdges;
	std::list<Edge*> m_incomingEdges;

	static int s_numInstances;

};


#endif