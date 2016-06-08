/*
** termcap.c for termcap.c in /home/linard_f/42sh/cmd_edition
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat Apr 13 14:25:55 2013 fabien linardon
** Last update Wed May 22 20:56:21 2013 guillaume fillon
*/

#include "42s.h"

extern int	g_tgetent;

int	my_putint(int c)
{
  write(1, &c, 1);
  return (0);
}

void	go_up(void)
{
  char	*cap;

  cap = NULL;
  if (g_tgetent == TRUE)
    {
      cap = tgetstr("up", NULL);
      tputs(cap, 1, &my_putint);
    }
  xfree(1, &cap);
}

void	go_left(void)
{
  char	*cap;

  cap = NULL;
  if (g_tgetent == TRUE)
    {
      cap = tgetstr("le", NULL);
      tputs(cap, 1, &my_putint);
    }
  xfree(1, &cap);
}

void	go_right(void)
{
  char	*cap;

  cap = NULL;
  if (g_tgetent == TRUE)
    {
      cap = tgetstr("nd", NULL);
      tputs(cap, 1, &my_putint);
    }
  xfree(1, &cap);
}
