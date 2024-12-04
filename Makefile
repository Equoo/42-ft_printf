NAME = libftprintf.a
CC = cc
AR = ar -rcs
ARMERGE = echo "create libftprintf.a\naddlib libft/libft.a\naddlib libftprintf.a\nsave\nend" | ar -M
LIB = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -MMD
SRCS = ft_printf.c\
       printf_utils.c\
       converts.c
DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/
OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SRCS)}
-include $(DEPS)

.PHONY: all
all: $(NAME)

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -I libft -c $< -o $@

$(LIB):
	$(MAKE) -C ./libft

$(NAME): $(LIB) $(DIR_OBJ) $(OBJS) Makefile
	$(AR) $@ $(OBJS)
	$(ARMERGE)

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