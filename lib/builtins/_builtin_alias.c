/*
** _builtins_alias.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Wed May  8 17:19:46 2013 guillaume fillon
** Last update Sun May 26 15:18:10 2013 nicolas bridoux
*/

#include "builtins.h"
#include "list.h"

int		_builtin_alias(char **cmd, t_shenv *shenv)
{
  t_list	*match;

  if (cmd[1] == NULL)
    {
      my_show_alias(shenv->alias);
      return (EXIT_SUCCESS);
    }
  if (cmd[1] != NULL && cmd[2] == NULL)
    {
      match = my_get_node_eq(shenv->alias, cmd[1]);
      if (match != NULL)
  	printf("%s=\'%s\'\n", match->name, match->value);
    }
  if (cmd[1] && cmd[2] && strcmp(cmd[1], "") && strcmp(cmd[2], ""))
    {
      my_rm_eq(&(shenv->alias), cmd[1]);
      my_put_in_end(&(shenv->alias), my_strdup(cmd[1]), my_strdup(cmd[2]));
    }
  return (EXIT_SUCCESS);
}
