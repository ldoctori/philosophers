NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror

TREADS_FLAG = -pthread

SOURCE = philo.c lists.c helpers.c free_destroy.c \
		philo_action.c ft_atoi.c

OBJECT = $(SOURCE:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	$(CC) $(FLAGS) $(TREADS_FLAG) -o $(NAME) $(OBJECT)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all