/*
** exec_cmd.c for exec_cmd in /home/linard_f//42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Tue Mar 19 14:10:18 2013 fabien linardon
** Last update Sun May 26 22:01:55 2013 nicolas bridoux
*/

#include "42s.h"
#include "builtins.h"
#include "list.h"

int	exec_bin(char **av, t_shenv *shenv)
{
  char	*path;

  delete_inhibitors(av);
  if (handle_builtins(av, shenv) == EXIT_SUCCESS)
    return (EXIT_FAILURE);
  if (!(path = path_management(av[0], shenv)))
    return (EXIT_FAILURE);
  if (path && execve(path, av, shenv->envp) == -1)
    return (my_error(path));
  return (EXIT_SUCCESS);
}

int	there_is_exit(char **new, t_shenv *shenv)
{
  int	i;

  i = 0;
  while (new[i])
    {
      if ((i == 0 || (i > 0 && (!strcmp(new[i - 1], "|")
				|| is_and_or(new[i - 1]))))
	  && !strcmp(new[i], "exit"))
	{
	  shenv->exit = (new[i + 1] != NULL) ?
	    my_getnbr(new[i + 1]) % 256 : 0;
	  return (1);
	}
      ++i;
    }
  return (0);
}

int	exec_global(char **cmd, char **new, t_shenv *shenv, int n)
{
 int	ret;

  if (is_pipe(cmd) && !is_mass_redirect(cmd) && is_builtin(new, NULL))
    {
      delete_inhibitors(new);
      return (handle_builtins(new, shenv));
    }
  if (check_path(new, shenv, 0) == FALSE && my_free_tab(new))
    return (EXIT_FAILURE);
  if ((ret = lookfor_type(cmd, new, shenv, n)) ==
      EXIT_FAILURE && my_free_tab(new))
    return (-1);
  if (ret == -1 && my_free_tab(new))
    return (EXIT_FAILURE);
  my_free_tab(new);
  return (EXIT_SUCCESS);
}

int	exec_cmd(char **cmd, t_shenv *shenv, int n)
{
  char	**new;
  int	ret;

  ret = 0;
  my_free_tab(shenv->envp);
  shenv->envp = my_put_list_to_tab(shenv->env);
  if (!cmd || !(new = cut_cmd(cmd)))
    return (EXIT_SUCCESS);
  if (there_is_exit(new, shenv) && my_free_tab(new))
    return (-1);
  if (is_magic(cmd) && !(cmd = magic_quote(cmd, shenv, &ret)) && !ret)
    return (ret);
  if (!cmd && ret > 0)
    return (EXIT_FAILURE);
  if (!cmd && ret == -1)
    return (-1);
  if (!cmd || !(new = cut_cmd(cmd)))
    return (EXIT_SUCCESS);
  return (exec_global(cmd, new, shenv, n));
}
