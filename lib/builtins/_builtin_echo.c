/*
** _echo.c for 42sh in /home/kokaz/projets/42sh/srcs/builtins
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.eu>
**
** Started on  Tue Mar  19 01:20:33 2013 guillaume fillon
** Last update Sun May 26 20:57:56 2013 nicolas bridoux
*/

#include "builtins.h"

static t_echo	g_tab[] =
  {
    {'a', '\a'},
    {'b', '\b'},
    {'f', '\f'},
    {'r', '\r'},
    {'t', '\t'},
    {'v', '\v'},
    {'n', '\n'},
    {'e', 27},
    {-1, -1}
  };

static void	shift_tab(char **tab, int i)
{
  while (tab && tab[i])
    {
      tab[i] = tab[i + 1];
      ++i;
    }
}

static int	get_opt(char **cmd)
{
  int		opt;

  opt = FALSE;
  if (cmd[1] && (!strcmp(cmd[1], "-ne") || (!strcmp(cmd[1], "-en"))))
    {
      opt |= NO_LINE;
      opt |= NO_CHARS;
      shift_tab(cmd, 1);
      return (opt);
    }
  if (cmd[1] && (!strcmp(cmd[1], "-n") || !strcmp(cmd[1], "-e")))
    {
      opt |= (!strcmp(cmd[1], "-n")) ? (NO_LINE) : (NO_CHARS);
      shift_tab(cmd, 1);
      if (cmd[1] && (!strcmp(cmd[1], "-n") || !strcmp(cmd[1], "-e")))
	{
	  opt |= (!strcmp(cmd[1], "-n")) ? (NO_LINE) : (NO_CHARS);
	  shift_tab(cmd, 1);
	}
    }
  return (opt);
}

static int	my_putstr(char *str, int opt)
{
  int		i;
  int		j;

  i = -1;
  while (str[++i])
    {
      if (str[i] == '\\' && (opt & NO_CHARS))
	{
	  if (str[++i] == 'c')
	    return (EXIT_FAILURE);
	  j = -1;
	  while (g_tab[++j].key != -1)
	    if (g_tab[j].key == str[i])
	      dprintf(1, "%c", g_tab[j].value);
	}
      else
	dprintf(1, "%c", str[i]);
    }
  return (EXIT_SUCCESS);
}

int	_builtin_echo(char **cmd, __attribute__((unused)) t_shenv *shenv)
{
  int	i;
  int	opt;

  i = 0;
  opt = get_opt(cmd);
  while (cmd[++i])
    {
      if (my_putstr(cmd[i], opt))
	return (EXIT_SUCCESS);
      if (cmd[i + 1])
	dprintf(STDOUT_FILENO, " ");
    }
  if (!(opt & NO_LINE))
    printf("\n");
  return (EXIT_SUCCESS);
}
