##
## Makefile for 42sh in /home/fillon_g/projets/42sh
## 
## Made by guillaume fillon
## Login   <fillon_g@epitech.net>
## 
## Started on  Mon Mar 18 19:38:54 2013 guillaume fillon
## Last update Sun May 26 22:40:21 2013 guillaume fillon
##

NAME	= fsh
DESTDIR	= bin
PACKAGE	= familial_sh
VERSION	= 2.1
REV	= 189

all: lib $(NAME)

lib: list builtins

list:
	@make -C lib $@ --no-print-directory

builtins:
	@make -C lib $@ --no-print-directory

$(NAME):
	@make -C src ../$@ --no-print-directory

clean:
	@make clean -C lib
	@make clean -C src

fclean:
	@make fclean -C lib
	@make fclean -C src

coffee:
	@echo "Wait during we make your coffee ;)"
	@echo "                        ("
	@echo "                          )     ("
	@echo "                  ___...(-------)-....___"
	@echo "               .-\"\"       )    (         \"\"-."
	@echo "         .-'\`\`'|-._             )         _.-|"
	@echo "        /  .--.|   \`\"\"---...........---\"\"\`   |"
	@echo "       /  /    |                             |"
	@echo "       |  |    |                             |"
	@echo "        \  \   |          ----------          |"
	@echo "         \`\ \`\ |         |  COFFEE  |        |"
	@echo "           \`\ \`|         \`----------'         |"
	@echo "           _/ /\                             /"
	@echo "          (__/  \                           /"
	@echo "       _..---\"\"\` \                         /\`\"\"---.._"
	@echo "    .-'           \                       /          '-."
	@echo "   :               \`-.__             __.-'              :"
	@echo "   :                  ) \"\"---...---\"\" (                 :"
	@echo "    '._               \`\"--...___...--\"\`              _.'"
	@echo "      \"\"--..__                              __..--\"\"/"
	@echo "       '._     \"\"\"----.....______.....----\"\"\"     _.'"
	@echo "          \`\"\"--..,,_____            _____,,..--\"\"\`"
	@echo "                        \`\"\"\"----\"\"\"\`"


$(PACKAGE)-$(VERSION)_$(REV).tar.gz:
	@tar -cvzf $(PACKAGE)-$(VERSION)_$(REV).tar.gz `find . -name "*.c" -or -name "*.h" -or -name "Makefile"`

dist: $(PACKAGE)-$(VERSION)_$(REV).tar.gz

distclean:
	@rm -rf $(PACKAGE)-$(VERSION)_$(REV).tar.gz

install:
	@sudo cp $(NAME) /$(DESTDIR)
	@sudo cp $(NAME) /usr/$(DESTDIR)

uninstall:
	@sudo rm -rf /$(DESTDIR)/$(NAME)
	@sudo rm -rf /usr/$(DESTDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re list builtins $(NAME) lib
