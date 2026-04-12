SRCS =	main.c		\
		utils.c		\
		parsing.c	\
		start.c		\
		routine.c	\
		server.c	\
		print.c		\
		clean.c		\

CC = cc -Wall -Werror -Wextra

NAME = philo

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "TOUT EST GOOD🤓👍🔥"

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "TOUT LES FICHIERS .o 💀"

fclean: clean
	@rm -f $(NAME)
	@echo "philo 💀"

re: fclean all

.PHONY: all clean fclean re