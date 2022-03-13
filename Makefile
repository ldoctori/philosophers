NAME = philosophers

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

SOURCE = philosophers.c

OBJECT = $(SOURCE:.o=.c)

HEADER = philosophers.h

%.o:%.c $(HEADER)
	$(CC) -I $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	$(CC) $(FLAGS) $(OBJECT) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all