SRC_DIR_APP1 := applicationA
SRC_DIR_APP2 := applicationB
BIN_DIR :=  $(shell pwd)/bin
OBJ_DIR :=  $(shell pwd)/obj
LIB_DIR :=  $(shell pwd)/lib 
INCLUDE :=-I include/
CC := gcc
SRC1 := $(wildcard $(SRC_DIR_APP1)/*.c)
OBJ1 := $(OBJ_DIR)/applicationA.o
SRC2 := $(wildcard $(SRC_DIR_APP2)/*.c)
OBJ2 := $(OBJ_DIR)/applicationB.o
EXE1 := $(BIN_DIR)/applicationA
EXE2 := $(BIN_DIR)/applicationB
LIBPARSER := $(LIB)/libparser.so
LIBHANDLER := $(LIB)/libhandler.so
LIBA := -Lbin/ -lpthread  -lparser -lhandler 
LIBB := -lpthread 


all : $(LIBPARSER) $(LIBHANDLER) $(EXE1) $(EXE2)

$(EXE1):$(OBJ1)
	$(CC)  $^  -o $@ $(LIBA)
$(EXE2):$(OBJ2)
	$(CC)  $^  -o $@ $(LIBB)
$(OBJ1):$(SRC1)
	$(CC) $(INCLUDE)  -c $< -o $@
$(OBJ2):$(SRC2)
	$(CC) $(INCLUDE)  -c $< -o $@

$(LIBPARSER):
	mkdir $(BIN_DIR) $(OBJ_DIR)
	$(CC) -fPIC $(INCLUDE) -c lib/parser.c -o bin/parser.o
	$(CC) -shared  -Wl,-soname,$(shell pwd)/bin/libparser.so -o $(shell pwd)/bin/libparser.so $(shell pwd)/bin/parser.o -ljson-c

$(LIBHANDLER):
	$(CC) -fPIC $(INCLUDE) -c lib/filechangehandler.c -o bin/handler.o
	$(CC) -shared  -Wl,-soname,$(shell pwd)/bin/libhandler.so -o $(shell pwd)/bin/libhandler.so $(shell pwd)/bin/handler.o
clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

