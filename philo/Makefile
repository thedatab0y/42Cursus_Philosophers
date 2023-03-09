NAME		=	philo

HEADER_NAME	=	philo.h

HEADER_PATH	=	includes/

SRCS_PATH	= 	srcs/

SRCS_LIST	=	main.c			parser.c	initialize.c\
				print.c			utils.c		create_threads.c\
				simulation.c

HEADER		=	$(addprefix $(HEADER_PATH), $(HEADER_NAME))

SRCS		=	$(addprefix $(SRCS_PATH), $(SRCS_LIST))

OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CC			=	gcc

INCLUDES	=	-I$(HEADER_PATH)

CFLAGS		=	-Wall -Wextra -Werror $(INCLUDES)

PTHREAD		=	-lpthread

.PHONY		:	all clean fclean re

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(PTHREAD) $(OBJS) -o $@

%.o			:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
	$(RM) $(OBJS)

fclean		:	clean
	$(RM) $(NAME)

re			:	fclean all