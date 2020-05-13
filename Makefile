CC = clang++
NAME = killking
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
MKDIR_P ?= mkdir -p
INC =	-I"./lib/lua" -L"./lib/lua" -llua5.3 \
		-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
MYINC =	-Ilib/glm -Iinc -Ilib/lua
FLAG = -w -std=c++14 -Wfatal-errors # -Wall -Wextra -Werror

SRC := $(shell find $(SRC_DIRS) -name *.cpp)

OBJS := $(SRC:%=$(BUILD_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(INC) $(OBJS) $(FLAG) -o $(NAME)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(MYINC) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY: all clean fclean re
