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
			ft_strncmp.c \
			file.c)

GNL = 	gnl/get_next_line.c \
		gnl/get_next_line_utils.c 

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(SRC_BONUS:.c=.o)

GNL_OBJ = $(GNL:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) mandatory/pipex.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ) $(BONUS_OBJ) $(GNL_OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus : $(BONUS_OBJ) $(GNL_OBJ) bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJ) $(GNL_OBJ)

.PHONY : clean fclean bonus re all