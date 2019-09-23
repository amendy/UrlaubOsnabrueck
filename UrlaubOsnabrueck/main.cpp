#include <iostream>
#include "Graph.h"
#include"Connection.h"

using namespace std;

double globalFaktor = 1; // Variable um Funktion getweight zu controllieren

// Daten der Verbindung zu speichern
struct Info
{
	Node* m_ZielOrt;
	Node* m_StartOrt;
	double m_gesamtKost;
	double m_gesamtZeitBedarf;
	int m_gesamtStrecke;
};


//Funktion um die bidirectionale Verbindung zu gewährleisten
// diese Funktion ist ein Pointer von Graph mit den Verbindungen von Node und die zusätzlichen Information von Edge
// d.h die ist von Connection

void makeReversedConnection(Graph *ptrG, Node& rSrc, Node& rDes, double distance, int type)
{
	ptrG->addEdge(new Connection(rSrc, rDes, distance, type));
	ptrG->addEdge(new Connection(rDes, rSrc, distance, type));
}

int main()
{
	Graph g; //Ich gebe Graph einen Namen g damit ich danach drauf zugreifen kann

	Node& rFlughafen = g.addNode(new Node("Flughafen"));
	Node& rUmbrügglerAlm = g.addNode(new Node("Umbrüggler Alm"));
	Node& rSchlossAmbross = g.addNode(new Node("Schloss Ambross"));
	Node& rUniversität = g.addNode(new Node("Universitaet"));
	Node& rZentrum = g.addNode(new Node("Zentrum"));
	Node& rPatscherkoflTalStation = g.addNode(new Node("Patscherkofel Talstation"));
	Node& rPatscherkoflBergStation = g.addNode(new Node("Patscherkofl BergStation"));

	makeReversedConnection(&g, rFlughafen, rZentrum, 6, 1);
	makeReversedConnection(&g, rFlughafen, rZentrum, 5.5, 4);
	makeReversedConnection(&g, rFlughafen, rZentrum, 7, 3);
	makeReversedConnection(&g, rZentrum, rUmbrügglerAlm, 5.5, 1);
	makeReversedConnection(&g, rZentrum, rSchlossAmbross, 3.5, 1);
	makeReversedConnection(&g, rZentrum, rSchlossAmbross, 4, 2);
	makeReversedConnection(&g, rZentrum, rUniversität, 2, 1);
	makeReversedConnection(&g, rZentrum, rUniversität, 6, 2);
	makeReversedConnection(&g, rZentrum, rUniversität, 5, 3);
	makeReversedConnection(&g, rUniversität, rSchlossAmbross, 5, 1);
	makeReversedConnection(&g, rUniversität, rSchlossAmbross, 6.5, 2);
	makeReversedConnection(&g, rUniversität, rSchlossAmbross, 6, 3);
	makeReversedConnection(&g, rZentrum, rPatscherkoflTalStation, 4, 2);
	makeReversedConnection(&g, rPatscherkoflBergStation, rPatscherkoflTalStation, 5, 5);

	Node* rZielOrt = NULL;
	Node* rStartOrt = NULL;

	Info Verbindung;
	list <Info> VerbindungenListe; // liste alle besuchte Kunden zu speichern

	// das Menü bzw. die Anforderungen werden implementiert 

	bool quit = false;
	int menu1_wahl = 0;

	while (!quit)
	{
		double gesamtKost = 0;
		double gesamtZeit = 0;
		int strecke = 0;

		// Menue Zeigen und behandlung von falschen Eingaben
 	// Über eine If-Anfrage werde ich alle Cases durchgehen

		if (menu1_wahl == 0)
		{
			while (menu1_wahl < 1 || menu1_wahl > 4)
			{
				std::cout << "1- Verkehrswege-Netz ausgeben:" << std::endl
					<< "2- Verbindung planen und ausführen:" << std::endl
					<< "3- Gesamtliste der benutzten Verbindungen ausgeben:" << std::endl
					<< "4- Programm beenden" << std::endl
					<< "Eingabe: ";
				while (!(cin >> menu1_wahl)) // Falls Buschstabe eingetragen
				{
					cout << "Bitte Digit eingeben..." << endl;
					cin.clear();
					cin.ignore(132, '\n');
				}
			}
		}

		// Sortieren und Im Bildschirm zeigen
		else if (menu1_wahl == 1)
		{
			list<Node*> sorted = g.getNodes(); 
			//übergebe eine Liste von Nodes, die sorted heißt

			list<Edge*> edgeList = g.getEdges();

			// Ziele sortieren und ausgeben...
			// die sorted liste über die IDs der NodeListe

			sorted.sort([](const Node* a, const Node* b) { return a->getID() < b->getID(); });

			// In der For-Schleife iterieren und vergleichen. 

			for (auto nodeIt = sorted.begin(); nodeIt != sorted.end(); nodeIt++)
			{
				cout << " Ort:  " << (*nodeIt)->getID() << endl;
				for (auto edgeIt = g.getEdges().begin(); edgeIt != g.getEdges().end(); edgeIt++)
				{
					if ((*edgeIt)->getSrcNode().getID() == (*nodeIt)->getID())
					{
						Connection* pTeilConnection = dynamic_cast<Connection*>(*edgeIt);
						std::cout << "\t" << (pTeilConnection)->getTypeName() << " :" << (pTeilConnection)->toString()
							<< " " << (pTeilConnection)->getDistance() << "Km" << std::endl;
					}

				}
			}

			menu1_wahl = 0;
		}

		// ZielOrt auswählen und beste Route finden
		else if (menu1_wahl == 2)
		{
			int i = 1;
			vector<Node*> NodeList;
			for (auto nodeIt = g.getNodes().begin(); nodeIt != g.getNodes().end(); ++nodeIt)
			{
				cout << (i) << ")" << (*nodeIt)->getID() << endl;
				NodeList.push_back(*nodeIt);
				i++;
			}

			//Start und Ziel auswählen
			int startOrt = 0;
			int zielOrt = 0;
			while (startOrt < 1 || startOrt > 7)
			{
				cout << "Bitte start Ort auswaehlen" << endl << "Start Ort: ";

				while (!(cin >> startOrt)) // Falls Buschstabe statt Zahl eingetragen
				{
					cout << "Bitte Digit eingeben..." << endl;
					cin.clear();
					cin.ignore(132, '\n');
				}
				cout << endl;
			}

			while (zielOrt < 1 || zielOrt > 7)
			{
				cout << "Bitte Ziel Ort auswaehlen" << endl << "Ziel Ort: ";

				while (!(cin >> zielOrt)) // Falls Buschstabe statt Zahl eingetragen
				{
					cout << "Bitte Digit eingeben..." << endl;
					cin.clear();
					cin.ignore(132, '\n');
				}
				cout << endl;
			}
			rStartOrt = NodeList[startOrt - 1];
			rZielOrt = NodeList[zielOrt - 1];

			//Verbindung nach Zeit, nach Kosten oder nach Strecke optimieren.
			int optiemierungType = 0;

			cout << "Bitte whaelen Sie die Optiemierung.. " << endl;
			cout << "1) Nach Zeit" << endl;
			cout << "2) Nach Kost" << endl;
			cout << "3) Nach Strecken" << endl;
			cout << "Optiemierung Type: ";
			cin >> optiemierungType;
			cout << endl;

			if (optiemierungType == 1)
			{
				globalFaktor = 1;
			}
			else if (optiemierungType == 2)
			{
				globalFaktor = 2;
			}
			else
			{
				globalFaktor = 3;
			}

			deque<Edge*> path;
			g.findShortestPathDijkstra(path, *rStartOrt, *rZielOrt);

			int anzahlDerStrecke = 0;
			for (std::deque<Edge*>::iterator it = path.begin(); it != path.end(); it++)
			{
				Connection* pTeilConnection = dynamic_cast<Connection*>(*it);
				anzahlDerStrecke++;

				std::cout << "Teilroute: " << pTeilConnection->toString() <<
					";  " << pTeilConnection->getTypeName() <<
					";  Teilzeit: " << (pTeilConnection->getDistance()) / (pTeilConnection->getSpeed()) <<
					" Kost: " << (pTeilConnection->getKost()) << " euro" << endl;

				gesamtKost += (pTeilConnection->getKost());
				gesamtZeit += (pTeilConnection->getDistance()) / (pTeilConnection->getSpeed());
			}
			cout << " Anzahl der Strecke: " << anzahlDerStrecke << endl;
			cout << " Gesamt Kost: " << gesamtKost << " Euro" << endl;
			cout << "Gesamt Zeit: " << gesamtZeit << endl;

			Verbindung.m_StartOrt = rStartOrt;
			Verbindung.m_ZielOrt = rZielOrt;
			Verbindung.m_gesamtZeitBedarf = gesamtZeit;
			Verbindung.m_gesamtKost = gesamtKost;
			Verbindung.m_gesamtStrecke = anzahlDerStrecke;

			VerbindungenListe.push_back(Verbindung);

			menu1_wahl = 0;
		}
		else if (menu1_wahl == 3)
		{

			for (auto it = VerbindungenListe.begin(); it != VerbindungenListe.end(); it++)
			{
				cout << "Start Ort: " << it->m_StartOrt->getID() << " ; Ziel Ort: "
					<< it->m_ZielOrt->getID() << " ; Strecke: " << it->m_gesamtStrecke
					<< " ;Kost: " << it->m_gesamtKost << " ;Zeit: " << it->m_gesamtZeitBedarf << endl;

			}

			menu1_wahl = 0;
		}
		else if (menu1_wahl == 4)
		{
			return 0;
		}

	}

	return 0;
}
