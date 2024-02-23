NAME = philo

SRCS = main.c utils_str.c utils_time.c utils_thread.c init.c exit.c routines.c 
HEADER = philo.h

OBJS = $(SRCS:.c=.o)

CLANG = gcc
# C_FLAGS = -Wall -Wextra -Werror
INCLUDE	= -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(C_FLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	# $(CLANG) $(C_FLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c $(HEADER)
	$(CLANG) -c $< -o $@
	# $(CLANG) $(C_FLAGS) -c $< -o $@

.PHONY: all clean fclean re