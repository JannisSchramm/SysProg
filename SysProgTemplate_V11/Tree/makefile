# Definition der Variablen

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib

SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/SuperTree.o \
	$(OBJDIR)/ElementTree.o \
	$(OBJDIR)/Tree.o \
	$(OBJDIR)/SuperTreeList.o \
	$(OBJDIR)/TreeTest.o 
	
	#$(OBJDIR)/xx1.o \
	#$(OBJDIR)/xxn.o

OBJSFORTREELIB =  \
	$(LIBDIR)/SuperTree.o \
	$(LIBDIR)/ElementTree.o \
	$(LIBDIR)/Tree.o \
	$(LIBDIR)/SuperTreeList.o \
	$(LIBDIR)/TreeTest.o#\


#
#		Targets zum Bauen des Tests
#

# Variante mit geringen Makefile-Kenntnissen

## Linken der Object-Files
#makeTestSymboltable: $(OBJDIR)/Symboltable.o $(OBJDIR)/TestSymboltable.o
#	g++ -g $(OBJDIR)/Symboltable.o $(OBJDIR)/TestSymboltable.o -o $(BINDIR)/SymboltableTest
#
#	
## compilieren der Source-files
#
#$(OBJDIR)/Symboltable.o :  $(SRCDIR)/Symboltable.cpp 
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/Symboltable.o  $(SRCDIR)/Symboltable.cpp
#
#
#$(OBJDIR)/TestSymboltable.o :  $(SRCDIR)/TestSymboltable.cpp $(SRCDIR)/Symboltable.h
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/TestSymboltable.o  $(SRCDIR)/TestSymboltable.cpp
#

# Variante mit guten Makefile-Kenntnissen

makeTestTree: TreeTest


TreeTest: $(OBJS)
	g++ -g $^ -o $(BINDIR)/TreeTest
	
	
# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall  -o $@  $<

# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR)

cleanTree:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
	$(MAKE) makeTestTree
	
#	
# erstellen der shared library
#

#SymboltableLib:$(LIBDIR)/Symboltable.o
#		g++ -shared  -o $(SHAREDLIB)/libSymboltable.so $(LIBDIR)/Symboltable.o 
#
#	
#$(LIBDIR)/Symboltable.o :  $(SRCDIR)/Symboltable.cpp 
##	@mkdir -p `dirname $(OBJDIR)/$*.o`
#	@echo "g++ $*.cpp"
#	g++ -g  -c -fPIC  -o $(LIBDIR)/Symboltable.o  $(SRCDIR)/Symboltable.cpp 
#


TreeLib:$(OBJSFORTREELIB)
		g++ -shared  -o $(SHAREDLIB)/libTree.so $^ 

	
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
#	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "g++ $*.cpp"
	g++ -g  -c -fPIC  -o $@  $<

