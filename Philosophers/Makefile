# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 09:06:23 by goteixei          #+#    #+#              #
#    Updated: 2025/05/13 16:07:50 by goteixei         ###   ########.fr        #
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

# Default empty, will be overridden by specific targets like 'sanitize' or 'tsan'
# Using '?=' assigns if not already set (e.g. from environment or command line).
EXTRA_COMPILE_FLAGS	?=
EXTRA_LINK_FLAGS	?=

# General Sanitizer Flags (ASan, LSan, UBSan)
# These are good for general memory error detection.
GEN_SAN_FLAGS	= -fsanitize=address,leak,undefined -fno-omit-frame-pointer -g

# Thread Sanitizer Flags (TSan)
# Use TSan separately from GEN_SAN_FLAGS as they can sometimes conflict or be very slow together.
TSAN_FLAGS		= -fsanitize=thread -fno-omit-frame-pointer -g

# Base Compiler Flags (always applied)
BASE_CFLAGS		= -Wall -Wextra -Werror -g -pthread
BASE_CFLAGS		+= -I$(INC_DIR)

# Base flags applied to all linking processes
BASE_LDFLAGS	= -pthread

# Final Compiler Flags (combines base with any extras)
CFLAGS			= $(BASE_CFLAGS) $(EXTRA_COMPILE_FLAGS)
LDFLAGS			= $(BASE_LDFLAGS) $(EXTRA_LINK_FLAGS)

# -------------------------------------------------------------
# MANDATORY
# -------------------------------------------------------------

#MANDATORY_SRC	= $(MANDATORY_DIR)main.c
MANDATORY_SRC	= $(SRC_DIR)init.c\
				  $(SRC_DIR)actions.c\
				  $(SRC_DIR)destroy.c\
				  $(SRC_DIR)forks.c\
				  $(SRC_DIR)monitor.c\
				  $(SRC_DIR)routine.c\
				  $(SRC_DIR)routine_utils.c\
				  $(SRC_DIR)threads.c\
				  $(SRC_DIR)time.c\
				  $(SRC_DIR)utils.c\
				  $(SRC_DIR)utils_libft.c\
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
				@$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LDFLAGS) -o $(NAME)
				@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"
				@echo "$(GREEN)+---------------------------------------------+"
				@echo "|                                             |"
				@echo "|         $(CHECKMARK) $(NAME) build successful!          |"
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
# Example:
# make memcheck ARGS="4 410 200 200"
memcheck:		
				@echo "$(BLUE)--- Ensuring standard build for Valgrind Memcheck ---$(RESET)"
				@$(MAKE) --no-print-directory fclean # Ensure no old sanitized build
				@$(MAKE) --no-print-directory all # Build standard version
				@echo "$(BLUE)--- Running Valgrind Memcheck on ./$(NAME) ---$(RESET)"
				@valgrind --leak-check=full \
						  --show-leak-kinds=all \
						  --track-origins=yes \
						  --log-file=valgrind-memcheck.log \
						  ./$(NAME) $(ARGS)
				@echo "$(BLUE)Memcheck log created: valgrind-memcheck.log$(RESET)"

# Sanitizer Build Targets

sanitize:
				@echo "$(BLUE)--- Building with General Sanitizers (ASan, LSan, UBSan) ---$(RESET)"
				@$(MAKE) --no-print-directory fclean
				@$(MAKE) --no-print-directory all EXTRA_COMPILE_FLAGS="$(GEN_SAN_FLAGS)" EXTRA_LINK_FLAGS="$(GEN_SAN_FLAGS)"
				@echo "$(GREEN)$(CHECKMARK) Built $(NAME) with general sanitizers.$(RESET)"
				@echo "$(BLUE)Run with: ./$(NAME) $(ARGS)$(RESET)"

tsan:
				@echo "$(BLUE)--- Building with Thread Sanitizer (TSan) ---$(RESET)"
				@$(MAKE) --no-print-directory fclean
				@$(MAKE) --no-print-directory all EXTRA_COMPILE_FLAGS="$(TSAN_FLAGS)" EXTRA_LINK_FLAGS="$(TSAN_FLAGS)"
				@echo "$(GREEN)$(CHECKMARK) Built $(NAME) with Thread Sanitizer.$(RESET)"
				@echo "$(BLUE)Run with: ./$(NAME) $(ARGS)$(RESET)"

# --- Phony Targets ---
.PHONY:			all clean fclean re valgrind

#.SILENT
