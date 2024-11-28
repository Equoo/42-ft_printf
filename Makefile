NAME = libftprintf.a
CC = cc
AR = ar -rcs
CFLAGS = -Wall -Wextra -Werror -MMD
SRCS = ft_printf.c
SRCS_BONUS = f
SRCS_ALL = $(SRCS) $(SRCS_BONUS)

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/
OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS)}
OBJS_BONUS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS_BONUS)}
OBJS_ALL = ${OBJS} ${OBJS_BONUS}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SRCS_ALL)}
-include $(DEPS)

ifdef BONUS
	OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS_ALL)}
endif

.PHONY: all
all: $(NAME)

.PHONY: bonus
bonus: $(OBJS_BONUS)
	$(MAKE) BONUS=1 all

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -I libft -c $< -o $@

$(NAME): $(DIR_OBJ) $(OBJS) Makefile
	$(MAKE) -C ./libft
	$(AR) $@ $(OBJS)

.PHONY: clean
clean:
	$(MAKE) clean -C ./libft
	rm -Rf $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all 

.DEFAULT_GOAL = all