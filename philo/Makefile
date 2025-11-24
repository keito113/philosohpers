NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
THREADS = -pthread
INCLUDES = -Iinclude

SRCS = src/main.c \
       src/init.c \
       src/monitor.c \
       src/parse.c \
       src/parse_utils.c \
       src/philo_thread.c \
       src/routine.c \
       src/start.c \
       src/time.c \
       src/util.c \
       src/fairness.c \
       src/cleanup.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(THREADS) $(OBJS) -o $(NAME)

src/%.o: src/%.c include/philo.h
	$(CC) $(CFLAGS) $(THREADS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
