/*
** _setenv.c for 42sh in /home/kokaz/projets/42sh/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.eu>
**
** Started on  Tue Mar  19 01:20:33 2013 guillaume fillon
** Last update Thu May 16 16:48:14 2013 guillaume fillon
*/

#include "builtins.h"
#include "list.h"

int		_builtin_setenv(char **cmd, t_shenv *shenv)
{
  t_list	*tmp;

  if (cmd[1] == NULL)
    return (_builtin_env(NULL, shenv));
  tmp = shenv->env;
  while (tmp != NULL)
    {
      if (strcmp(cmd[1], tmp->name) == 0)
	{
	  tmp->value = (cmd[2] == NULL) ? NULL : my_strdup(cmd[2]);
	  return (EXIT_SUCCESS);
	}
      tmp = tmp->next;
    }
  my_put_in_end(&shenv->env, my_strdup(cmd[1]),
		 (cmd[2] == NULL) ? NULL : my_strdup(cmd[2]));
  return (EXIT_SUCCESS);
}
