##
## Makefile for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g
##
## Made by guillaume fillon
## Login   <fillon_g@epitech.net>
##
## Started on  Sat May 11 17:30:02 2013 guillaume fillon
## Last update Sun May 26 22:25:11 2013 guillaume fillon
##

CC 	=	gcc

NAME	= 	../fsh

OBJDIR	=	../obj/

VPATH	=	.:exec_cmd:history:levenshtein:prompt:prompt/autocomplete:utils:termcaps

CFLAGS	=	-Wall -Wextra
CFLAGS	+=	-I../includes

LDFLAGS	+=	-lncurses
LDFLAGS	+=	-L../lib -lbuiltins
LDFLAGS	+=	-L../lib -llist

SRC     =	main.c			\
		handle_status.c		\
		job_control.c		\
		my_getcwd.c		\
		display_prompt.c	\
		replace_alias.c		\
		xfree.c			\
		my_strdup.c		\
		copy_env.c		\
		get_cmd.c		\
		epur_str.c		\
		parsing.c		\
		parse_cmd.c		\
		output_redirect.c 	\
		input_redirect.c 	\
		dispatch_cmd.c		\
		copy_path.c		\
		check_redir_pipe.c	\
		cut_cmd.c 		\
		cut_paste.c		\
		exec_cmd.c 		\
		look_for_type.c		\
		is_redirect.c 		\
		pipe.c 			\
		cut_magic.c		\
		magic_quote.c		\
		exec_magic.c		\
		error.c 		\
		my_strcat.c 		\
		path_management.c	\
		globing.c		\
		add_history_line.c	\
		read_fd.c		\
		magic_read.c		\
		levenshtein.c		\
		termcaps.c		\
		correction.c		\
		history.c		\
		put_in_raw.c		\
		catch_cmd.c		\
		cmd_tab.c		\
		capacity.c		\
		delete.c		\
		arrow_management.c	\
		inhibitors.c		\
		inhibitors_utils.c	\
		env_var.c		\
		aff_histo.c		\
		replace_local_var.c	\
		autocomplete.c		\
		autocomplete_utils.c	\
		search_binary.c		\
		one_completion_and_binary.c\
		load_conf_file.c	\
		my_getnbr.c		\

OBJ     =	$(addprefix $(OBJDIR), $(SRC:.c=.o))

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@strip $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re list builtins
