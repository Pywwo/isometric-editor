##
## EPITECH PROJECT, 2018
## AbstractVM
## File description:
## Makefile for the AbstractVM
##

SRC_DIR			=	$(realpath src)

SRC_MAIN_FILE		=	main.cpp

SRC_FILES		=		Editor.cpp	\
						Background.cpp	\
						Tile.cpp	\
						Layer.cpp	\
						Objects.cpp	\

SRC				= 	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRC_MAIN			= 	$(addprefix $(SRC_DIR)/, $(SRC_MAIN_FILE))

OBJ				=	$(SRC:%.cpp=%.o)

OBJ_MAIN			=	$(SRC_MAIN:%.cpp=%.o)

NAME			=   Editor

INCLUDE			=   -iquote src/ -iquote src/CLI -iquote include/

LDFLAGS			=	-std=c++14 -ltgui -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS		=	-W -Wall -Wextra -Wno-unknown-pragmas -Wshadow
CXXFLAGS		+=	$(INCLUDE)

CXX				=	g++

all: $(NAME)

$(NAME):	$(OBJ) $(OBJ_MAIN)
			$(CXX) -o $(NAME) $(OBJ_MAIN) $(OBJ) $(LDFLAGS)

clean:
				@echo Cleaning $(OBJ)
				$(RM) $(OBJ_MAIN) $(OBJ)
				@echo Cleaning done

fclean:			clean
				@echo Cleaning $(NAME)
				$(RM) $(NAME)
				@echo Cleaning done

re:				fclean all

debug:			CXXFLAGS += -g
debug:			re

.DEFAULT_GOAL := all
