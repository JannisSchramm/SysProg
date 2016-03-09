#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von NodeTarget und TestNodeTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestNode: NodeTarget TestNodeTarget  
	g++ -g ../Tree/debug/SuperTree.o ../Tree/debug/ElementTree.o ../Tree/debug/SuperTreeList.o ../Tree/debug/Tree.o debug/Node.o debug/TestNode.o -o debug/NodeTest
	

# compilieren des Files Node.cpp zu Node.o, 
# das Objekt-File ist abhängig von src/Node.cpp und src/Node.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

NodeTarget :  src/Node.cpp src/Node.h 
	g++ -g  -c -Wall src/Node.cpp -o debug/Node.o  


# TestNode.o ist abhängig von src/TestNode.cpp und src/Node.h
TestNodeTarget :  src/TestNode.cpp src/Node.h
	g++ -g  -c -Wall src/TestNode.cpp  -o debug/TestNode.o  



# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanNode:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeTestNode
	
	
#
# erstellen der shared library
#

NodeLib: NodeLibTarget
		g++ -shared lib/Node.o  -o ../sharedlib/libNode.so 

	
# compilieren des Files Node.cpp zu Node.o mit dem Flag -fPIC (Position Independant Code)
NodeLibTarget :  src/Node.cpp src/Node.h
	g++ -g  -c -fPIC  src/Node.cpp -o lib/Node.o   



