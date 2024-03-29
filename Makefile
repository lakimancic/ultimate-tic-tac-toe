SRC_DIR         := src
OBJ_DIR         := obj
BIN_DIR         := bin
TARGET          := tic-tac-toe

ifeq ($(OS),Windows_NT)
SRCS := $(shell (if not exist obj mkdir obj) && (if not exist bin mkdir bin) && DIR *.cpp /S /B)
else
SRCS := $(shell mkdir -p obj bin && cd obj && find ../ -name *.cpp)
endif

CXX                     := g++
CXX_FLAGS       := -Wall -Wextra -std=c++17 -ggdb

${TARGET}: all run
 
ifeq ($(OS),Windows_NT)
run:
	cls && cd bin && main
else
run:
	clear && cd bin && ./main
endif

all: allobjs
	$(CXX) $(CXX_FLAGS) ${OBJ_DIR}/*.o -o ${BIN_DIR}/main

allobjs: clean
	cd ${OBJ_DIR} && $(CXX) $(CXX_FLAGS) -c ${SRCS}

ifeq ($(OS),Windows_NT)
clean:
	del /s /q ${OBJ_DIR} && del /s /q ${BIN_DIR}
else
clean:
	rm -rf ${OBJ_DIR}/* && rm -rf ${BIN_DIR}/*
endif