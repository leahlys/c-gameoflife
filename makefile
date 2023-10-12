EXECDIR=bin
OBJDIR=obj
SRCDIR=src
INCLUDEDIR=include
EXEC=gameoflife

CFLAGS= -Wall -g
CLIBRARIES= -lncurses



all: $(EXECDIR)/$(EXEC)

$(EXECDIR)/$(EXEC): $(OBJDIR)/main.o 
	gcc-13 $(CFLAGS) $(CLIBRARIES) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h 
	gcc-13 $(CFLAGS) $(CLIBRARIES) -c $< -I $(INCLUDEDIR) -o $@


.PHONY: mrproper clean
	
mrproper:
	rm $(EXECDIR)/$(EXEC)

clean:
	rm $(OBJDIR)/*.o

gcc-version:
	gcc-13 --version
