# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 09:06:23 by goteixei          #+#    #+#              #
#    Updated: 2025/04/15 15:33:48 by goteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Colors (for terminal output) ---
RESET			= $(shell printf "\33[0m")
RED				= $(shell printf "\33[31m")
GREEN			= $(shell printf "\33[32m")
WHITE			= $(shell printf "\33[37m")
YELLOW			= $(shell printf "\33[33m")
BLUE			= $(shell printf "\33[34m")

# --- Symbols / Emojis (requires UTF-8 terminal) ---
CHECKMARK		= ✅
CROSSMARK		= ❌
GEAR			= ⚙️
FOLDER			= 📁
SPARKLES		= ✨

# --- Program Name ---
NAME 			= philo

# Directories
INC_DIR			= inc/
LIB_DIR			= lib/
SRC_DIR			= src/

# --- Compiler and Flags ---
CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -g
CFLAGS			+= -I$(INC_DIR)

# -------------------------------------------------------------
# MANDATORY
# -------------------------------------------------------------

#MANDATORY_SRC	= $(MANDATORY_DIR)main.c
MANDATORY_SRC	= $(SRC_DIR)utils.c\
				  $(SRC_DIR)init.c\
				  $(SRC_DIR)threads.c\
				  $(SRC_DIR)main.c

# Object files in the same directory as source
MANDATORY_OBJ	= $(MANDATORY_SRC:.c=.o)

# -------------------------------------------------------------
# MANDATORY
# RULES
# -------------------------------------------------------------

all:			$(NAME)

$(NAME):		$(MANDATORY_OBJ) 
				@echo "$(YELLOW)Compiling $(NAME) (Mandatory)...$(RESET)"
				@$(CC) $(CFLAGS) $(MANDATORY_OBJ) -o $(NAME) -lreadline
				@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"
				@echo "$(GREEN)+---------------------------------------------+"
				@echo "|                                             |"
				@echo "|       $(CHECKMARK) $(NAME) build successful!        |"
				@echo "|                                             |"
				@echo "+---------------------------------------------+$(RESET)"


# --- Cleaning Rules ---

clean:
				@echo "$(YELLOW)Object files cleaning start$(RESET)"
				@echo "Cleaning project objects..."
				@$(RM) $(MANDATORY_OBJ)
#				@echo "Cleaning Libft objects (if possible)..."
#				@-if [ -d "$(LIBFT_SRC_DIR)" ]; then make -s -C $(LIBFT_SRC_DIR) clean; fi
				@echo "$(GREEN)Object files cleaned successfully!$(RESET)"

fclean:			clean
				@echo "$(YELLOW)Executable files cleaning start$(RESET)"
				@echo "Cleaning executable $(NAME)..."
				@$(RM) $(NAME)
#				@echo "Cleaning Libft library (if possible)..."
#				@-if [ -d "$(LIBFT_SRC_DIR)" ]; then make -s -C $(LIBFT_SRC_DIR) fclean; fi
#				@echo "Removing entire Libft repository clone directory $(LIBFT_REPO_DIR)..."
#				@$(RM) $(LIBFT_REPO_DIR)
				@echo "$(GREEN)Clean complete.$(RESET)"

re:				fclean all

# --- Utility Rules ---

# Rule to use valgrind
valgrind:		all
				@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
					--track-origins=yes --trace-children=yes --tool=drd --tool=helgrind -fsanitize=thread ./philo

.PHONY:			all clean fclean re valgrind

#.SILENT
