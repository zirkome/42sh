/*
** _builtins_set.c for builtin 42sh in /home/degreg_e/
**
** Made by enzo degregorio
** Login   <degreg_e@epitech.net>
**
** Started on  Fri May 10 16:29:29 2013 enzo degregorio
** Last update Tue May 21 20:32:54 2013 enzo degregorio
*/

#include "builtins.h"
#include "list.h"

static int	disp_lvar(t_shenv *shenv)
{
  my_show_list(shenv->lvar);
  return (EXIT_SUCCESS);
}

int		_builtin_set(char **cmd, t_shenv *shenv)
{
  t_list	*tmp;

  if (cmd[1] == NULL)
    return (disp_lvar(shenv));
  tmp = shenv->lvar;
  while (tmp != NULL)
    {
      if (strcmp(cmd[1], tmp->name) == 0)
	{
	  tmp->value = (cmd[2] == NULL) ? NULL : my_strdup(cmd[2]);
	  return (EXIT_SUCCESS);
	}
      tmp = tmp->next;
    }
  my_put_in_end(&shenv->lvar, my_strdup(cmd[1]),
		(cmd[2] == NULL) ? my_strdup(NULL) : my_strdup(cmd[2]));
  return (EXIT_SUCCESS);
}
