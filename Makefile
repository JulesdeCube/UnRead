BUILD_DIR=build
OBJECT_DIR=obj
SRC_DIR=src

PATH_NEURAL_NETWORK=neural_network
SRC_NEURAL_NETWORK=layer.c neural_network.c neurone.c utils.c
DEPS_NEURAL_NETWORK=$(SRC_NEURAL_NETWORK:.c=.h)

PATH_DATA_SET=data_set
SRC_DATA_SET=mask.c sample.c set.c utils.c
DEPS_DATA_SET=$(SRC_DATA_SET:.c=.h)

PATH_SEGMENTATION=segmentation
SRC_SEGMENTATION=segmentation.c auto_rotation.c
DEPS_SEGMENTATION=$(SRC_SEGMENTATION:.c=.h)

PATH_PREPROCESSING=preprocessing
SRC_PREPROCESSING=change_color.c tools.c rotate.c resize.c noise.c histo_grey_lvl.c resize_char.c
DEPS_PREPROCESSING=$(SRC_PREPROCESSING:.c=.h)

SRC=main.c\
$(addprefix $(PATH_NEURAL_NETWORK)/, $(SRC_NEURAL_NETWORK))\
$(addprefix $(PATH_DATA_SET)/, $(SRC_DATA_SET))\
$(addprefix $(PATH_SEGMENTATION)/, $(SRC_SEGMENTATION))\
$(addprefix $(PATH_PREPROCESSING)/,  $(SRC_PREPROCESSING))

DEPS=$(addprefix $(PATH_NEURAL_NETWORK)/, $(DEPS_NEURAL_NETWORK))\
$(addprefix $(PATH_DATA_SET)/, $(DEPS_DATA_SET))\
$(addprefix $(PATH_PREPROCESSING)/,$(DEPS_PREPROCESSING))\
$(addprefix $(PATH_SEGMENTATION)/, $(DEPS_SEGMENTATION))

BUILD=UnRead-1.1.0

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
	@echo "\nJules Lefebvre <juleslefebvre.pro@outlook.fr>"

version: ## print the makefile version
	@echo "C build v1.2.2"

install: ## install all dependence to compile project
	@echo "creating needed folder"
	@mkdir -p cuted_line
	@mkdir -p cuted_char
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

run: ## build and run the programme
run: build
	@$(BUILD_DIR)/$(BUILD)

build: ## build the programme
build: $(BUILD_DIR)/$(BUILD)

clean: ## clean all precompiled files
	@echo "clean files"
	@$(RM) -r $(OBJECT_DIR)
	@$(RM) -r cuted_line
	@$(RM) -r cuted_char



$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c $(addprefix $(SRC_DIR)/, $(DEPS))
	@mkdir -p $(dir $@)
	@echo "compiling" $<
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(BUILD): $(BUILD_DIR)/ $(addprefix $(OBJECT_DIR)/, $(SRC:.c=.o))
	@echo "\nbuilding $(BUILD)"
	@$(CC) -o $(BUILD_DIR)/$(BUILD) $(addprefix $(OBJECT_DIR)/, $(SRC:.c=.o)) $(CFLAGS)
	@echo "Finish"

%/:
	@mkdir -p $@
