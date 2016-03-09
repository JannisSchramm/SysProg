#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von ParserTarget und TestParserTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestParser: ParserTarget TestParserTarget  
	g++ -g ../Tree/debug/SuperTree.o ../Tree/debug/SuperTreeList.o ../Tree/debug/ElementTree.o ../Symboltable/debug/Vector.o ../Symboltable/debug/Element.o ../Symboltable/debug/Information.o ../Token/debug/Token.o ../Scanner/debug/Scanner.o ../Buffer/debug/Buffer.o ../Automat/debug/Automat.o ../Automat/debug/Transformation.o ../Tree/debug/Tree.o ../Leaf/debug/Leaf.o ../Node/debug/Node.o ../Symboltable/debug/Symboltable.o debug/Parser.o debug/TestParser.o -o debug/ParserTest
	

# compilieren des Files Parser.cpp zu Parser.o, 
# das Objekt-File ist abhängig von src/Parser.cpp und src/Parser.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

ParserTarget :  src/Parser.cpp src/Parser.h 
	g++ -g  -c -Wall src/Parser.cpp -o debug/Parser.o  


# TestParser.o ist abhängig von src/TestParser.cpp und src/Parser.h
TestParserTarget :  src/TestParser.cpp src/Parser.h
	g++ -g  -c -Wall src/TestParser.cpp  -o debug/TestParser.o  



# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanParser:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeTestParser
	
	
#
# erstellen der shared library
#

ParserLib: ParserLibTarget
		g++ -shared lib/Parser.o  -o ../sharedlib/libParser.so 

	
# compilieren des Files Parser.cpp zu Parser.o mit dem Flag -fPIC (Position Independant Code)
ParserLibTarget :  src/Parser.cpp src/Parser.h
	g++ -g  -c -fPIC  src/Parser.cpp -o lib/Parser.o   



