# compile flag
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g3
LFLAGS = -L$(LIB) -l$(LIBNAME)
IFLAGS = -I$(INCLUDE)
DFLAGS = -D$(MECRO)

# mecro & lib name
MECRO = FT
LIBNAME = stl

# exec name
NAME = $(FT) $(STD)
FT = ft_container
STD = std_container

# directory name
INCLUDE = includes
SRC = srcs
OBJ = obj
LIB = lib

# file name
MAIN = $(SRC)/vector_test.cpp
TEST = vector_test map_test main
SOURCE = iterator map stack tree utils vector
HEADER = $(foreach src, $(SOURCE), $(INCLUDE)/$(src).hpp)
OBJECT = $(foreach file, $(TEST), $(OBJ)/$(file).o)
LIBRARY = $(LIB)/lib$(LIBNAME).a
FT_OUT = ft.out
STD_OUT = std.out

# dependency
$(NAME): $(MAIN) $(LIBRARY)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(IFLAGS) $(DFLAGS) $(MAIN) -o $(FT)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(IFLAGS) $(MAIN) -o $(STD)
$(LIBRARY): $(OBJECT)
	@mkdir -p $(LIB)
	ar rcs $(LIBRARY) $(OBJECT)
$(OBJ)/%.o: $(SRC)/%.cpp $(HEADER)
	@mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

# argument
ARGV = 1000

# rules
all: $(NAME)
run: all
	./$(FT) $(ARGV) > $(FT_OUT) && ./$(STD) $(ARGV) > $(STD_OUT)
	diff $(FT_OUT) $(STD_OUT) || exit 0
	rm -rf $(FT_OUT) $(STD_OUT)
clean:
	rm -rf $(OBJ) $(LIB)
fclean:
	rm -rf $(OBJ) $(LIB) $(NAME) $(FT_OUT) $(STD_OUT)
re: fclean all

.PHONY: all run clean fclean re