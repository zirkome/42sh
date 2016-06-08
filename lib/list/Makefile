##
## Makefile for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g
## 
## Made by guillaume fillon
## Login   <fillon_g@epitech.net>
## 
## Started on  Sat May 11 17:34:23 2013 guillaume fillon
## Last update Sun May 26 22:25:16 2013 guillaume fillon
##

CC	= 	gcc

RM    	= 	rm -f

OBJDIR	= 	../../obj/

NAME 	= 	liblist.a

SRC	=	my_free_list.c  	\
		my_get_node_eq.c	\
		my_put_in_end.c 	\
		my_put_in_list.c 	\
		my_put_list_to_tab.c	\
		my_list_size.c		\
		my_rm_eq.c 		\
		my_show_list.c 		\


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