#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestAutomat: TransformationTarget AutomatTarget  TestAutomatTarget  
	g++ -g  debug/Transformation.o debug/Automat.o  debug/TestAutomat.o   -o debug/AutomatTest
	

# compilieren des Files Automat.cpp zu Automat.o, 
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

AutomatTarget :  src/Automat.cpp src/Automat.h 
	g++ -g  -c -Wall src/Automat.cpp -o debug/Automat.o  

TransformationTarget :  src/Transformation.cpp src/Transformation.h 
	g++ -g  -c -Wall src/Transformation.cpp -o debug/Transformation.o  


# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
TestAutomatTarget :  src/TestAutomat.cpp src/Automat.h
	g++ -g  -c -Wall src/TestAutomat.cpp  -o debug/TestAutomat.o  



# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanAutomat:
	rm -rf debug/*
	rm -rf lib/*
	$(MAKE) AutomatTarget
	$(MAKE) TransformationTarget
	
	
#
# erstellen der shared library
#

AutomatLib: AutomatLibTarget
		g++ -shared lib/Automat.o  -o ../sharedlib/libAutomat.so 
		
TransformationLib: TransformationLibTarget
		g++ -shared lib/Transformation.o  -o ../sharedlib/libTransformation.so

	
# compilieren des Files Automat.cpp zu Automat.o mit dem Flag -fPIC (Position Independant Code)
AutomatLibTarget :  src/Automat.cpp src/Automat.h
	g++ -g  -c -fPIC  src/Automat.cpp -o lib/Automat.o 
	
TransformationLibTarget :  src/Transformation.cpp src/Transformation.h
	g++ -g  -c -fPIC  src/Transformation.cpp -o lib/Transformation.o     



