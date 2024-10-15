NAME				= philo

SRCS_DIR			= srcs/

GREEN				= \033[0;92m
COLOR				= \033[0m

SUCCES				= @echo "$(GREEN)Philosophers compiled successfully$(COLOR)"


SRCS				= ${SRCS_DIR}main.c \
					  ${SRCS_DIR}checks.c \
					  ${SRCS_DIR}utils.c \
					  ${SRCS_DIR}init.c \
					  ${SRCS_DIR}philo.c \
					#   ${SRCS_DIR}time.c \
					#   ${SRCS_DIR}print.c \
					#   ${SRCS_DIR}check.c

OBJS				= $(SRCS:.c=.o)

CFLAGS				= -Wall -Wextra -Werror -pthread -I. #-fsanitize=thread
CC					= cc

RM					= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		$(SUCCES)

clean:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re