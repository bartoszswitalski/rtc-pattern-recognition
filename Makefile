# $@ == target
# $< == first dependency
APPNAME = app

CC = g++

CFLAGS =  

SRC_DIR = src
HDR_DIR = hdr
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
TARGETS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%)

.PHONY: dir
dir:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	$(RM) -rf $(BUILD_DIR)
    
all: $(TARGETS) 

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I$(HDR_DIR) $< -o $@
