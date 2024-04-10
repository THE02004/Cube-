MAKEFLAGS += --no-print-directory

PROJ     := Cube
TARGET   := $(PROJ).exe
DTARGET  := $(PROJ)_debug.exe
EXT      := c
COMP     := gcc

INC_DIR  := include
SRC_DIR  := src
OBJ_DIR  := objs

HDS_FILES := $(wildcard $(INC_DIR)/*.h) $(wildcard $(INC_DIR)/**/*.h)
GCH_FILES := $(addsuffix .gch,$(HDS_FILES))
SRC_FILES := $(wildcard $(SRC_DIR)/*.$(EXT)) $(wildcard $(SRC_DIR)/**/*.$(EXT))
OBJ_FILES := $(patsubst %.$(EXT),%.o, $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_FILES)))

INC_PATHS := $(addprefix -I , $(sort $(dir $(HDS_FILES))))
LIB_PATHS := -L lib/
LIB_FLAGS := -lraylib -lopengl32 -lgdi32 -lwinmm
APP_FLAGS := -std=c2x -Wall

EXE_FLAGS := $(LIB_PATHS) $(LIB_FLAGS) $(APP_FLAGS)
D_FLAGS   := $(LIB_PATHS) $(LIB_FLAGS) $(APP_FLAGS) -g
O_FLAGS   := $(INC_PATHS) $(APP_FLAGS) -g

build: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(COMP) $^ -o $@ $(EXE_FLAGS)

start:
	./$(TARGET)

debug: $(DTARGET)

$(DTARGET): $(OBJ_FILES)
	$(COMP) $^ -o $@ $(D_FLAGS)

startDebug:
	gdb ./$(DTARGET)

objects: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(EXT)
	$(COMP) -c $< -o $@ $(O_FLAGS)

clean:
	del /Q /F $(OBJ_DIR)\*.o
	del /Q /F .\$(TARGET)
	del /Q /F .\$(DTARGET)
