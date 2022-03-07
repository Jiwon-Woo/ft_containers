# compile flag
CXX = clang++
# CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXXFLAGS = -std=c++98
LFLAGS = -L$(LIB) -l$(LIBNAME)
IFLAGS = -I$(INCLUDE)
DFLAGS = -D$(MECRO)

# mecro & lib name
MECRO = FT
LIBNAME = stl

# exec name
# NAME = $(FT) $(STD)
NAME = $(FT)
FT = ft_container
STD = std_container

# directory name
INCLUDE = include
SRC = src
OBJ = obj
LIB = lib

# file name
MAIN = main.cpp
SOURCE = iterator vector
OBJECT = $(foreach file, $(SOURCE), $(OBJ)/$(file).o)
LIBRARY = $(LIB)/lib$(LIBNAME).a

# dependency
$(NAME): $(MAIN) $(LIBRARY)
	$(CXX) $(CXXFLAGS) $(LFLAGS) $(IFLAGS) $(DFLAGS) $(MAIN) -o $(FT)
	# $(CXX) $(CXXFLAGS) $(LFLAGS) $(IFLAGS) $(MAIN) -o $(STD)
$(LIBRARY): $(OBJECT)
	@mkdir -p $(LIB)
	ar rcs $(LIBRARY) $(OBJECT)
$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	@mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

# rules
all: $(NAME)
run: all
	./$(FT) > ft && ./$(STD) > std
	diff ft std || exit 0
	rm -rf ft std
clean:
	rm -rf $(OBJ) $(LIB)
fclean:
	rm -rf $(OBJ) $(LIB) $(NAME)
re: fclean all

.PHONY: all run clean fclean re