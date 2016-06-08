/*
** _cd.c for 42sh in /home/kokaz/projets/42sh/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.eu>
**
** Started on  Tue Mar  19 01:20:33 2013 guillaume fillon
** Last update Sun May 26 12:32:37 2013 fabien linardon
*/

#include "builtins.h"

static int	my_chdir(const char *path)
{
  if (path != NULL && chdir(path) == -1)
    {
      fprintf(stderr, "familial_sh: cd: %s: %s\n", path, strerror(errno));
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static int		chdir_home()
{
  static struct passwd *p = NULL;

  if (p == NULL)
    p = getpwuid(getuid());
  if (p == NULL)
    return (EXIT_FAILURE);
  else if (my_chdir(p->pw_dir) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static void	update_env(char *oldpwd, t_shenv *shenv)
{
  char		*cmd[3];

  cmd[0] = strdup("setenv");
  cmd[1] = strdup("PWD");
  cmd[2] = my_getcwd();
  _builtin_setenv(cmd, shenv);
  xfree(1, &cmd[1]);
  cmd[1] = strdup("OLDPWD");
  cmd[2] = oldpwd ? oldpwd : my_getcwd();
  _builtin_setenv(cmd, shenv);
  xfree(2, &cmd[0], &cmd[1]);
}

int		_builtin_cd(char **cmd, t_shenv *shenv)
{
  int		ret;
  char		*cwd;
  static char	*oldpwd = NULL;

  cwd = my_getcwd();
  if (cmd[1] == NULL)
    ret = chdir_home();
  else if (!strcmp(cmd[1], "-"))
    {
      if ((ret = my_chdir(oldpwd)) == EXIT_SUCCESS)
	{
	  printf("%s\n", (oldpwd == NULL) ? my_getcwd() : oldpwd);
	  xfree(1, &oldpwd);
	  oldpwd = cwd;
	  update_env(oldpwd, shenv);
	  return (EXIT_SUCCESS);
	}
      return (EXIT_FAILURE);
    }
  else
    ret = my_chdir(cmd[1]);
  update_env(cwd, shenv);
  if (ret == EXIT_SUCCESS && xfree(1, &oldpwd))
    oldpwd = cwd;
  return ((ret) ? (EXIT_FAILURE) : (EXIT_SUCCESS));
}
