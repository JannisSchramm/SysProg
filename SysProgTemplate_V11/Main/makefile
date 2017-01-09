#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von MainTarget und TestMainTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestMain: MainTarget testMainTarget  
	g++ -g debug/Main.o -o debug/MainTest
	

# compilieren des Files Main.cpp zu Main.o, 
# das Objekt-File ist abhängig von src/Main.cpp
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

MainTarget :  MainComp
	g++ -g  ../Token/debug/Token.o 	../Automat/debug/Transformation.o ../Automat/debug/Automat.o ../Buffer/debug/Buffer.o ../Symboltable/debug/Vector.o ../Symboltable/debug/Information.o ../Symboltable/debug/Element.o ../Symboltable/debug/Symboltable.o ../Scanner/debug/Scanner.o debug/Main.o -o debug/Main


MainComp:	src/Main.cpp
	g++ -g  -c -Wall src/Main.cpp -o debug/Main.o  


# TestMain.o ist abhängig von src/TestMain.cpp
#TestMainTarget :  src/TestMain.cpp
##	g++ -g  -c -Wall src/TestMain.cpp  -o debug/TestMain.o  



# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanMain:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) MainTarget
	
	
#
# erstellen der shared library
#

MainLib: MainLibTarget
		g++ -shared lib/Main.o  -o ../sharedlib/libMain.so 

	
# compilieren des Files Main.cpp zu Main.o mit dem Flag -fPIC (Position Independant Code)
MainLibTarget :  src/Main.cpp
	g++ -g  -c -fPIC  src/Main.cpp -o lib/Main.o   



