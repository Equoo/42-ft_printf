NAME = libftprintf.a
CC = cc
AR = ar -rcsT libft/libft.a
CFLAGS = -Wall -Wextra -Werror -MMD
SRCS = ft_printf.c\
       printf_utils.c\
       converts.c\

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/
OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SRCS_ALL)}
-include $(DEPS)

ifdef BONUS
	OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS_ALL)}
endif

.PHONY: all
all: $(NAME)

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -I libft -c $< -o $@

$(NAME): $(DIR_OBJ) $(OBJS) Makefile
	$(MAKE) -C ./libft
	$(AR) $@ $(OBJS)

.PHONY: clean
clean:
	$(MAKE) clean --no-print-directory -C ./libft
	rm -Rf $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean --no-print-directory -C ./libft
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all 

.DEFAULT_GOAL = all