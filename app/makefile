# Makefile pour AirWatcher

# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11 -I$(INCLUDE_DIR)


# Nom de l'exécutable
TARGET = AirWatcher

# Répertoires
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = out

# Liste des fichiers sources et headers
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Cible par défaut
all: $(OBJ_DIR) $(TARGET)

# Créer le dossier OBJ_DIR s’il n’existe pas
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Construction de l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compilation des .cpp en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: clean all
