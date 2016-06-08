/*
** exec_cmd.c for 42sh in /home/degreg_e/projets/42sh/srcs
**
** Made by enzo degregorio
** Login   <degreg_e@epitech.net>
**
** Started on  Tue Mar 19 16:15:23 2013 enzo degregorio
** Last update Sun May 26 16:45:18 2013 nicolas bridoux
*/

#include "42s.h"
#include "builtins.h"

int	dispatch_cmd(char **cmd, t_shenv *shenv, int n)
{
  if (cmd && (check_pipe(cmd, shenv) == EXIT_FAILURE ||
  	      check_redirection(cmd, shenv) == EXIT_FAILURE))
    return (EXIT_SUCCESS);
  if (shenv && cmd)
    return (exec_cmd(cmd, shenv, n));
  return (EXIT_SUCCESS);
}

int	check_path(char **av, t_shenv *shenv, int rk)
{
  char	*tmp;

  while (av && av[rk])
    {
      if (av[rk] && !strcmp(av[rk], "|"))
	++rk;
      else if (av[rk] && is_redirect(av[rk]))
	rk += 2;
      if (av[rk] && !is_redirect(av[rk]) && !is_builtin(&av[rk], NULL) &&
	  !(tmp = path_management(av[rk], shenv)))
	return (FALSE);
      else if (av[rk] && !is_redirect(av[rk]) && !is_builtin(&av[rk], NULL))
	av[rk] = tmp;
      if (!is_redirect(av[rk]) && !is_builtin(&av[rk], NULL) &&
	  access(tmp, X_OK))
	{
	  fprintf(stderr, "%s: Permission denied.\n", tmp);
	  xfree(1, &tmp);
	  return (FALSE);
	}
      while (av[rk] && av[++rk] &&
	     !is_redirect(av[rk]) && strcmp(av[rk], "|"));
    }
  return (TRUE);
}
