NAME = pipex

SRC = $(addprefix mandatory/, \
	pipex.c \
	childs.c \
	ft_split.c \
	ft_strjoin.c \
	ft_strncmp.c \
	free.c)

SRC_BONUS = $(addprefix bonus/, \
			pipex_bonus.c \
			childs_bonus.c \
			free.c \
			ft_split.c \
			ft_strjoin.c \
			ft_strncmp.c)

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(SRC_BONUS: .c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) mandatory/pipex.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus : $(BONUS_OBJ) bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJ)
				
.PHONY : clean fclean bonus re all