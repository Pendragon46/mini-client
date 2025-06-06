SRCS = main.cpp MiniClient.cpp

OBJ_DIR = obj

OBJ = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

CXX = c++

CXXFLAG = -Wall -Wextra -Werror -I . -std=c++98

NAME = miniclient


$(OBJ_DIR)/%.o :	%.cpp
					mkdir -p $(OBJ_DIR)
					$(CXX) $(CXXFLAG) -c $< -o $@

all : $(NAME)

$(NAME) :	$(OBJ)
			$(CXX) $(CXXFLAG) $(OBJ) -o $(NAME)

clean :
			rm -rf $(OBJ_DIR)

fclean :	clean
			rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean