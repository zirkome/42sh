##
## Makefile for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g
## 
## Made by guillaume fillon
## Login   <fillon_g@epitech.net>
## 
## Started on  Sat May 11 17:34:40 2013 guillaume fillon
## Last update Sun May 26 22:25:20 2013 guillaume fillon
##

CC	= 	gcc

RM    	= 	rm -f

OBJDIR	= 	../../obj/

NAME 	= 	libbuiltins.a

SRC	=	builtins.c		\
		_builtin_cd.c		\
		_builtin_pwd.c		\
		_builtin_export.c	\
		_builtin_echo.c		\
		_builtin_alias.c	\
		_builtin_unalias.c	\
		_builtin_env.c		\
		_builtin_getenv.c	\
		_builtin_setenv.c	\
		_builtin_unsetenv.c	\
		_builtin_set.c		\
		_builtin_unset.c	\
		_builtin_history.c	\
		_builtin_help.c		\

OBJ	 = 	$(addprefix $(OBJDIR), $(SRC:.c=.o))

CFLAGS 	+= -Wall -Wextra
CFLAGS	+= -I ../../includes

$(OBJDIR)%.o:	%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) ..

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re