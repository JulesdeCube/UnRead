BUILD_DIR=build
OBJECT_DIR=obj
SRC_DIR=src

SRC=main.c image/mask.c image/sample.c image/set.c
DEPS=image/mask.h image/sample.h image/set.h
BUILD=UnRead-0.1.0

CC=gcc
CFLAGS=-I$(SRC_DIR) -Wall -Wextra -Werror -std=c99 -pedantic -g

.PHONY: all help version run build clean
##
## A simple makefile for C project
##
## Usage : make <Target>
##
## Target :
all: help

help: ## print this help
help: version
	@fgrep -h "## " $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/^## //' |sed -e 's/\(.*\)## /- \1/'
	@echo -e "\nJules Lefebvre <juleslefebvre.pro@outlook.fr>"

version: ## print the makefile version
	@echo "C build v1.2.1"

run: ## build and run the programme
run: build
	@$(BUILD_DIR)/$(BUILD)

build: ## build the programme
build: $(BUILD_DIR)/$(BUILD)

clean: ## clean all precompiled files
clean: $(OBJECT_DIR)
	@echo "clean files"
	@$(RM) -r $(OBJECT_DIR)


$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c $(addprefix $(SRC_DIR)/, $(DEPS))
	@	@mkdir -p $(dir $@)
	@echo "compiling" $<
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(BUILD): $(BUILD_DIR)/ $(addprefix $(OBJECT_DIR)/, $(SRC:.c=.o))
	@echo -e "\nbuilding $(BUILD)"
	@$(CC) -o $(BUILD_DIR)/$(BUILD) $(addprefix $(OBJECT_DIR)/, $(SRC:.c=.o)) $(CFLAGS)
	@echo "Finish"

%/:
	@mkdir -p $@

