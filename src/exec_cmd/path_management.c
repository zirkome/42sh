/*
** path_management.c for path_management in /home/linard_f/42sh/exec_cmd
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Tue Apr  9 15:34:35 2013 fabien linardon
** Last update Sun May 26 19:57:54 2013 fabien linardon
*/

#include "42s.h"

char	**make_path(char **env)
{
  int	rk;

  rk = -1;
  while (env && env[++rk])
    if (!strncmp("PATH", env[rk], strlen("PATH")))
      return (my_str_to_pathtab(my_strdup(&env[rk][5]), -1, -1, 0));
  return (NULL);
}

char	*path_management(char *av, t_shenv *shenv)
{
  char	*nocorrect;
  char	**path;
  char	*tmp;
  char	*ret;
  int	rk;

  path = make_path(shenv->envp);
  rk = -1;
  while (!is_bin(av) && path && path[++rk])
    {
      if (!access((tmp = my_strcat(path[rk], av)), F_OK) && my_free_tab(path))
	return (tmp);
      xfree(1, &tmp);
    }
  if (is_bin(av) && !access(av, F_OK) && my_free_tab(path))
    return (my_strdup(av));
  nocorrect = get_local_var("nocorrect", shenv);
  nocorrect = (nocorrect == NULL) ? strdup("0") : nocorrect;
  if (!strcmp(nocorrect, "0"))
    if ((ret = correct(av, path, LEV, LEV)) && my_free_tab(path))
      return (ret);
  my_free_tab(path);
  fprintf(stderr, "%s: Command not found.\n", av);
  return (NULL);
}

int	is_bin(char *bin)
{
  int	rk;

  rk = -1;
  while (bin[++rk])
    if (bin[rk] == '/')
      return (TRUE);
  return (FALSE);
}
