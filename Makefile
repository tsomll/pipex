NAME    =   pipex
CC      =   gcc
SRCS    =   pipex.c utils.c ft_split.c parsing.c \
			utils2.c here_doc.c
HEADER	=	pipex.h
OBJS	=	$(SRCS:%.c=%.o)
FLAGS   =   -Wall -Werror -Wextra
.PHONY  :   all clean fclean re bonus
all     :	$(NAME)
$(NAME)	:	$(OBJS)
					@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
%.o		:	$.c $(HEADER)
			@$(CC) $(FLAGS) $(OBJS) $@
clean   :
	rm -f $(OBJS)
fclean  :   clean
	rm -f ${NAME}
re      :   fclean all