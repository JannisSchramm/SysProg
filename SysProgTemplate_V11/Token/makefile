#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von TokenTarget und TestTokenTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestToken: TokenTarget TestTokenTarget  
	g++ -g debug/Token.o debug/TestToken.o -o debug/TokenTest
	

# compilieren des Files Token.cpp zu Token.o, 
# das Objekt-File ist abhängig von src/Token.cpp und src/Token.h
# flag:
# -c --> compilieren
# -Wall --> alle meldungen erzeugen

TokenTarget :  src/Token.cpp src/Token.h 
	g++ -g  -c -Wall src/Token.cpp -o debug/Token.o  


# TestToken.o ist abhängig von src/TestToken.cpp und src/Token.h
TestTokenTarget :  src/TestToken.cpp src/Token.h
	g++ -g  -c -Wall src/TestToken.cpp  -o debug/TestToken.o  



# loeschen aller files im verzeichnis obj und lib und neu bauen

cleanToken:
	rm -rf obj/*
	rm -rf lib/*
	$(MAKE) makeTestToken
	
	
#
# erstellen der shared library
#

TokenLib: TokenLibTarget
		g++ -shared lib/Token.o  -o ../sharedlib/libToken.so 

	
# compilieren des Files Token.cpp zu Token.o mit dem Flag -fPIC (Position Independant Code)
TokenLibTarget :  src/Token.cpp src/Token.h
	g++ -g  -c -fPIC  src/Token.cpp -o lib/Token.o   



