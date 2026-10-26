#┌─────────────────────────────────────────────────────────────────────────────┐#
#│                                                                             │#
#│  Makefile                                               ▒▒▒▒    ▒▒▒▒        │#
#│                                                         ▒▒▒▒    ▒▒▒▒        │#
#│  By: 0xK92JL4                                               ▒▒▒▒            │#
#│                                                           ▒▒▒▒▒▒▒▒          │#
#│  Created: 2026/10/17 12:31:30 by 0xK92JL4                 ▒▒▒▒▒▒▒▒          │#
#│  Updated: 2026/10/17 12:31:30 by 0xK92JL4                 ▒▒    ▒▒          │#
#│                                                                             │#
#└─────────────────────────────────────────────────────────────────────────────┘#

CXX        := c++
PKG_CONFIG := pkg-config

BIN_DIR   := build/bin
SRC_DIR   := src
LIB_DIR   := $(SRC_DIR)/lib
OBJ_DIR   := .obj
THEME_DIR := build/themes
ASSET_DIR := templates

TARGET  := $(BIN_DIR)/media-center
THEME_H := $(THEME_DIR)/Theme.h

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

PKGS := sdl2

CPPFLAGS += -isystem $(LIB_DIR) -I$(THEME_DIR) -MMD -MP
CPPFLAGS += $(shell $(PKG_CONFIG) --cflags $(PKGS))
CXXFLAGS += -std=c++17 -Wall -Wextra -Wpedantic
LDLIBS   += $(shell $(PKG_CONFIG) --libs $(PKGS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(THEME_H): theme.yml $(shell find $(ASSET_DIR) -name '*.svg')
	./theme-builder.rb

$(OBJS): | $(THEME_H)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) build

-include $(DEPS)

.PHONY: all run clean
