
NAME = hds
# Compilation settings
CC = clang++
CFLAGS = -Werror -Wextra -Wall -O3
GLFW = -Llib -lglfw3
GLEW = -Llib -lglew
FRAMEWORK =  $(GLFW) $(GLEW) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Custom paths
DIR_SRCS = srcs/
DIR_OBJS = objs/
DIR_INCS = -Iincs/ -Iincs/glfw -I/incs/glm -I/incs/GL

#------------------------------------------------------------------------------#

FILES =	main.cpp \
		Model.cpp \
		Parser.cpp \
		Terrain.cpp \
		View.cpp \
		Camera.cpp \
		Exceptions.cpp \
		GLObject.cpp \
		Shader.cpp \
		Drop.cpp \
		AModule.cpp \
		Water.cpp \
		Borders.cpp \
		WaterBorders.cpp \


#------------------------------------------------------------------------------#

# Apply custom paths
SRCS = $(addprefix $(DIR_SRCS), $(FILES))
OBJS = $(addprefix $(DIR_OBJS), $(FILES:.cpp=.o))

# Colors
RED = \x1b[31;01m
GREEN = \x1b[32;01m
CYAN = \x1b[34;01m
RESET = \x1b[39;49;00m

# Rules
all: $(NAME)
	
$(NAME): $(OBJS)
	@ printf "Linking  "
	@ $(CC) $(OBJS) $(CFLAGS) $(DIR_INCS) $(FRAMEWORK) -o $(NAME)
	@ printf "$(GREEN)DONE$(RESET)\n"
	@ echo "Program $(RED)$(NAME)$(RESET) -> $(GREEN)COMPLETED$(RESET)"

$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
	@ echo "Building $(CYAN)$< $(RESET)"
	@ mkdir -p $(DIR_OBJS)
	@ $(CC) $(CFLAGS) $(DIR_INCS) -c $< -o $@

clean:
	@ rm -f $(OBJS)
	@ rm -rf $(DIR_OBJS)
	@ echo "Clean    $(GREEN)DONE$(RESET)"

fclean: clean
	@ rm -f $(NAME)
	@ echo "Fclean   $(GREEN)DONE$(RESET)"

re: fclean all

.PHONY: all clean fclean re