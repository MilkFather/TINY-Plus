BIN := ./bin/
OBJ := ./obj/
HEAD := ./include/
SRC := ./src/
RES := ./test/

EXEC_NAME := tiny

CC := g++
CCFLAGS := -std=c++11 -Wall -Os -I$(HEAD)
LINKFLAGS := 

build: $(BIN)$(EXEC_NAME) testdata

testdata:
	cp -R $(RES) $(BIN)

$(BIN)$(EXEC_NAME): $(OBJ)tiny.o $(OBJ)lex/lexical.o $(OBJ)lex/lexstate.o $(OBJ)syntax/syntax.o $(OBJ)syntax/syntaxgenerator.o $(OBJ)tinyexception.o
	@mkdir -p $(BIN)
	$(CC) $(CCFLAGS) $(LINKFLAGS) -o $(BIN)$(EXEC_NAME) $^
	chmod +x $(BIN)$(EXEC_NAME)

$(OBJ)tiny.o: $(SRC)tiny.cpp $(HEAD)lex/lexical.h $(HEAD)syntax/syntax.h $(HEAD)tinyexception.h 
	@mkdir -p $(OBJ)
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ)lex/lexical.o: $(SRC)lex/lexical.cpp $(HEAD)lex/lexical.h $(HEAD)lex/lexdef.h $(HEAD)lex/lexstate.h $(HEAD)tinyexception.h
	@mkdir -p $(OBJ)lex
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ)lex/lexstate.o: $(SRC)lex/lexstate.cpp $(HEAD)lex/lexstate.h $(HEAD)lex/lexdef.h
	@mkdir -p $(OBJ)lex
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ)syntax/syntax.o: $(SRC)syntax/syntax.cpp $(HEAD)syntax/syntax.h $(HEAD)tinyexception.h
	@mkdir -p $(OBJ)syntax
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ)syntax/syntaxgenerator.o: $(SRC)syntax/syntaxgenerator.cpp $(HEAD)syntax/syntaxgenerator.h $(HEAD)lex/lexdef.h
	@mkdir -p $(OBJ)syntax
	$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ)tinyexception.o: $(SRC)tinyexception.cpp $(HEAD)tinyexception.h
	@mkdir -p $(OBJ)
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -r $(BIN)
	rm -r $(OBJ)