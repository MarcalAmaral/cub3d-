# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 07:47:48 by rbutzke           #+#    #+#              #
#    Updated: 2024/08/22 18:43:33 by myokogaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----------------------------------------------------------------------------------------
# Static library
NAME			:= cub3D.a

#-----------------------------------------------------------------------------------------
# Compiler and flags
CFLAGS			:= -Wall -Werror -Wextra -MMD -g
CC				:= cc
O_FLAGS			:= -c

#-----------------------------------------------------------------------------------------
# Command to clean up files
CMD_CLEAN		:= rm -Rf

#-----------------------------------------------------------------------------------------
# DIRECTORY and Header file
UTILS			:= utils/
PARSE			:= parse/
HOOK_MOVE		:= hook_move/
DRAW_IMAGE		:= draw_image/
RAYCASTING		:= raycasting/
TEXTURE			:= pixels_texture/
INCLUDE			:= ../includes
MLX42			:= ../lib/MLX42/include/MLX42/
LIBFT			:= ../lib/lib_get_print/includes/

#-----------------------------------------------------------------------------------------
# Header file includes
INCLUDES		:= -I $(RAYCASTING)\
				-I$(INCLUDE)\
				-I $(UTILS)\
				-I $(PARSE)\
				-I $(HOOK_MOVE)\
				-I $(MLX42)\
				-I $(LIBFT)\
				-I $(DRAW_IMAGE)\
				-I $(TEXTURE)

#-----------------------------------------------------------------------------------------
# Source files
FILE_UTILS		:= utils.c
FILE_PARSE		:= parse.c
FILE_PARSE		+= $(addprefix cleaner/, clear.c)
FILE_PARSE		+= $(addprefix error/, arguments_file.c identifiers.c memalloc.c rgb.c)
FILE_PARSE		+= $(addprefix validation/, arguments.c file.c identifiers.c rgb.c)
FILE_HOOK		:= hook.c
FILE_DRAW_IMAGE	:= draw_image.c
FILE_RAY		:= ray_casting.c dda.c
FILE_TEXTURE	:= pixels_texture.c

#-----------------------------------------------------------------------------------------
# Source files
SRC_FILES		:= $(addprefix $(DRAW_IMAGE), $(FILE_DRAW_IMAGE))\
					$(addprefix $(RAYCASTING), $(FILE_RAY))\
					$(addprefix $(UTILS), $(FILE_UTILS))\
					$(addprefix $(PARSE), $(FILE_PARSE))\
					$(addprefix $(HOOK_MOVE), $(FILE_HOOK))\
					$(addprefix $(TEXTURE), $(FILE_TEXTURE))\
					main.c\

#-----------------------------------------------------------------------------------------
NUM_FILES	:= $(words $(SRC_FILES))

#-----------------------------------------------------------------------------------------
# Directory for object files
OBJS		:= objs
O_FILE		:= $(SRC_FILES:%.c=$(OBJS)/%.o)
DEP_FILES   := $(O_FILE:%.o=%.d)

#-----------------------------------------------------------------------------------------
# Default rule to create the static library
all: $(NAME)

#-----------------------------------------------------------------------------------------
# Rule to create the static library
$(NAME): $(O_FILE)
	@ar -rc $(NAME) $(O_FILE)
	@echo ""

#-----------------------------------------------------------------------------------------
# Rule to compile source files into object files
$(OBJS)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(INCLUDES) $(O_FLAGS) $(CFLAGS) $< -o $@
	@$(eval COUNT := $(shell echo $$(($(COUNT)+1))))
	@printf "Creating the program binaries   [%s]\r" $(shell echo "$$(($(COUNT) * 100 / $(NUM_FILES)))%")

#-----------------------------------------------------------------------------------------
# Include dependency files
#-include $(DEP_FILES)

#-----------------------------------------------------------------------------------------
# Rule to clean
clean:
	@$(CMD_CLEAN) $(OBJS) $(NAME)