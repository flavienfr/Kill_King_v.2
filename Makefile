CC = clang++
INC =	-I"./lib/lua" -L"./lib/lua" -llua5.3 \
		-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
MYINC =	-Ilib/glm \
		-Iinc
NAME = killking
FLAG = -w -std=c++14 -Wfatal-errors # -Wall -Wextra -Werror
SRC =	src/main.cpp \
		src/Game.cpp \
		src/Entity.cpp \
		src/EntityManager.cpp \
		src/TextureManager.cpp \
		src/AssetManager.cpp \
		src/Animation.cpp \
		src/Map.cpp \
		src/Components/TransformComponent.cpp \
		src/Components/SpriteComponent.cpp \
		src/Components/KeyBoardControlComponent.cpp \
		src/Components/TileComponent.cpp

OBJS = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(INC) $(OBJS) $(FLAG) -o $(NAME)  

.cpp.o : $(SRC)
	$(CC) $(MYINC) -c $< -o $(<:.cpp=.o)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY: all clean fclean re
