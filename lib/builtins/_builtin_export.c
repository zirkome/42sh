/*
** _builtin_export.bis.c for export in /home/degreg_e/
**
** Made by enzo degregorio
** Login   <degreg_e@epitech.net>
**
** Started on  Mon May 20 20:58:19 2013 enzo degregorio
** Last update Sun May 26 12:21:33 2013 nicolas bridoux
*/

#include "builtins.h"
#include "list.h"

int		export_var(char *cname, char *name, t_shenv *shenv)
{
  t_list	*tmp;
  char		*var[3];

  var[0] = cname;
  tmp = shenv->lvar;
  while (tmp != NULL)
    {
      if (!strcmp(name, tmp->name))
	{
	  var[1] = tmp->name;
	  var[2] = tmp->value;
	  return (_builtin_setenv(var, shenv));
	}
      tmp = tmp->next;
    }
  return (EXIT_SUCCESS);
}

void	add_to_env(char *cname, char *name, char *value, t_shenv *shenv)
{
  char	*cmd[3];

  cmd[0] = cname;
  cmd[1] = name;
  cmd[2] = value;
  _builtin_setenv(cmd, shenv);
}

int		_builtin_export(char **cmd, t_shenv *shenv)
{
  int		i;
  char		*cmd_name;
  char		*name;
  char		*value;

  i = 1;
  if (cmd[1] == NULL)
    return (_builtin_env(cmd, shenv));
  cmd_name = strdup("export");
  while (cmd[i] != NULL)
    {
      name = strtok(strdup(cmd[i]), "=");
      if ((value = strtok(NULL, "=")) == NULL)
	export_var(cmd_name, name, shenv);
      else
	add_to_env(cmd_name, name, value, shenv);
      ++i;
    }
  xfree(1, &cmd_name);
  return (EXIT_SUCCESS);
}
