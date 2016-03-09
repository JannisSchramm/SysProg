#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von LeafTarget und TestLeafTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestLeaf: LeafTarget TestLeafTarget  
	g++ -g ../Symboltable/debug/Symboltable.o ../Symboltable/debug/Element.o ../Symboltable/debug/Information.o ../Symboltable/debug/Vector.o ../Tree/debug/SuperTree.o debug/Leaf.o debug/TestLeaf.o -o debug/LeafTest 
	

# compilieren des Files Leaf.cpp zu Leaf.o, 
# das Objekt-File ist abhängig von src/Leaf.cpp und src/Leaf.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

LeafTarget :  src/Leaf.cpp src/Leaf.h 
	g++ -g  -c -Wall src/Leaf.cpp -o debug/Leaf.o  


# TestLeaf.o ist abhängig von src/TestLeaf.cpp und src/Leaf.h
TestLeafTarget :  src/TestLeaf.cpp src/Leaf.h
	g++ -g  -c -Wall src/TestLeaf.cpp  -o debug/TestLeaf.o  



# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanLeaf:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeTestLeaf
	
	
#
# erstellen der shared library
#

LeafLib: LeafLibTarget
		g++ -shared lib/Leaf.o  -o ../sharedlib/libLeaf.so 

	
# compilieren des Files Leaf.cpp zu Leaf.o mit dem Flag -fPIC (Position Independant Code)
LeafLibTarget :  src/Leaf.cpp src/Leaf.h
	g++ -g  -c -fPIC  src/Leaf.cpp -o lib/Leaf.o   



