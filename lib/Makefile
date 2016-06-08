##
## Makefile for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g
## 
## Made by guillaume fillon
## Login   <fillon_g@epitech.net>
## 
## Started on  Sat May 11 17:35:01 2013 guillaume fillon
## Last update Sun May 26 21:12:07 2013 nicolas bridoux
##

MAKE	= make --no-print-directory

all: list builtins

list:
	@$(MAKE) -C list

builtins:
	@$(MAKE) -C builtins

clean:
	@$(MAKE) clean -C list
	@$(MAKE) clean -C builtins

fclean: clean
	@$(MAKE) fclean -C list
	@$(MAKE) fclean -C builtins
	rm -rf liblist.a
	rm -rf libbuiltins.a
re:
	@$(MAKE) re -C list
	@$(MAKE) re -C builtins

.PHONY: all clean fclean re list builtins
