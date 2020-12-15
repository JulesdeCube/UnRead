BUILD_DIR=build
OBJECT_DIR=obj
SRC_DIR=src

SRC=main.c $(addprefix neural_network/, layer.c neural_network.c neurone.c utils.c ) $(addprefix image/, mask.c sample.c set.c utils.c ) $(addprefix load_Image/, load.c change_color.c tools.c segmentation.c rotate.c resize.c noise.c histo_grey_lvl.c auto_rotation.c resize_char.c)
DEPS=$(addprefix neural_network/, layer.h neural_network.h neurone.h utils.h ) $(addprefix image/, mask.h sample.h set.h utils.h ) $(addprefix load_Image/, load.h change_color.h tools.h segmentation.h rotate.h resize.h noise.h histo_grey_lvl.h auto_rotation.h resize_char.h)
BUILD=UnRead-0.1.0

CC=gcc
GTK_CFLAGS=$(shell pkg-config --cflags gtk+-3.0)
GTK_LIB=$(shell pkg-config --libs gtk+-3.0)
CFLAGS=-I$(SRC_DIR) $(GTK_CFLAGS) -Wall -Wextra -Werror -std=c99 -pedantic -g $(GTK_LIB) -export-dynamic -lm

PACKAGES=libgtk-3-dev

.PHONY: all help version run build clean install
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

install: ## install all dependence to compile project
	@echo "install packages : $(PACKAGES)"
ifneq "$(shell whereis apk)" "apk:"
	@apk add --no-cache $(PACKAGES)
else ifneq "$(shell whereis apt-get)" "apt-get:"
	@sudo apt-get install $(PACKAGES)
else ifneq "$(shell whereis dnf)" "dnf:"
	@sudo dnf install $(PACKAGES)
else ifneq "$(shell whereis zypper)" "zypper:"
	@sudo zypper install $(PACKAGES)
else ifneq "$(shell whereis pacman)" "pacman:"
	@sudo pacman -Sy $(PACKAGES)
else ifneq "$(shell whereis nix-env)" "nix-env:"
	@sudo nix-env --install $(PACKAGES)
else
	@echo "ERROR: package manager not found.">&2
endif
	@echo "creating needed folder"
	@mkdir -p cuted_line
	@mkdir -p cuted_char

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
	@mkdir -p $(dir $@)
	@echo "compiling" $<
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(BUILD): $(BUILD_DIR)/ $(addprefix $(OBJECT_DIR)/, $(SRC:.c=.o))
	@echo -e "\nbuilding $(BUILD)"
	@$(CC) -o $(BUILD_DIR)/$(BUILD) $(addprefix $(OBJECT_DIR)/, $(SRC:.c=.o)) $(CFLAGS)
	@echo "Finish"

%/:
	@mkdir -p $@
