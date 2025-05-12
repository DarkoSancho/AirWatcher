#todolist : verifier si les dir existent et sinon les créer et 

#Variable:

#compilateur
CXX = g++

#Option de compilation
CXXFLAGS = -ansi -pedantic -Wall -std=c++17   -I$(INCLUDE_DIR)

#nom de l'executable
TARGET = AirWatcher

#dossier contenant les .cpp
SRC_DIR = src

#dossier contenant les .h
INCLUDE_DIR = include

#dossier pour les .o 
OBJ_DIR = out

#liste des fichiers dans SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

#liste des fichiers dans INCLUDE_DIR 
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

#liste des fichiers dans OBJ_DIR
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

#règle pour construire l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

#régple pour compiler de cpp à .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#regle executé lorsque qu'on appelle le makefile  
all: $(TARGET)

#nettoie le fichier executable et les .o
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)





.PHONY: clean all