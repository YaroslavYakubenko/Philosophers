NAME				= philo

SRCS_DIR			= srcs/
OBJS_DIR			= objs/

GREEN				= \033[0;92m
COLOR				= \033[0m

SUCCES				= @echo "$(GREEN)Philosophers compiled successfully$(COLOR)"


SRCS				= ${SRCS_DIR}main.c \
					  ${SRCS_DIR}checks.c \
					  ${SRCS_DIR}utils.c \
					  ${SRCS_DIR}init.c \
					  ${SRCS_DIR}philo.c \
					  ${SRCS_DIR}philo_routine.c \
					#   ${SRCS_DIR}time.c \
					#   ${SRCS_DIR}print.c \
					#   ${SRCS_DIR}check.c

# OBJS				= $(SRCS:.c=.o)
OBJS				= $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

CFLAGS				= -Wall -Wextra -Werror -pthread -I. #-fsanitize=thread
CC					= cc

RM					= rm -rf

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
		@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		$(SUCCES)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJS_DIR)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re