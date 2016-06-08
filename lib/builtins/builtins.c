/*
** builtins.c for 42sh in /home/fillon_g/projets/42sh/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Tue Mar 19 16:13:47 2013 guillaume fillon
** Last update Sun May 26 21:01:34 2013 nicolas bridoux
*/

#include "builtins.h"

static t_builtin	g_builtins[] =
  {
    {"cd", _builtin_cd},
    {"echo", _builtin_echo},
    {"env", _builtin_env},
    {"export", _builtin_export},
    {"setenv", _builtin_setenv},
    {"unsetenv", _builtin_unsetenv},
    {"set", _builtin_set},
    {"unset", _builtin_unset},
    {"history", _builtin_history},
    {"pwd", _builtin_pwd},
    {"alias", _builtin_alias},
    {"unalias", _builtin_unalias},
    {"help", _builtin_help},
    {NULL, NULL}
  };

int	is_builtin(char **cmd, __attribute__((unused)) t_shenv *shenv)
{
  int	i;

  i = 0;
  while (g_builtins[i].name != NULL)
    {
      if (cmd && cmd[0] && strcmp(g_builtins[i].name, cmd[0]) == 0)
	return (TRUE);
      ++i;
    }
  return (FALSE);
}

int	handle_builtins(char **cmd, t_shenv *shenv)
{
  int	i;

  i = 0;
  while (g_builtins[i].name != NULL)
    {
      if (cmd && cmd[0] && strcmp(g_builtins[i].name, cmd[0]) == 0)
	return (g_builtins[i].fptr(cmd, shenv));
      ++i;
    }
  return (EXIT_FAILURE);
}
