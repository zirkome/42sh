/*
** termcaps.c for termcaps.c in /home/bridou_n//minishell1/Bonus
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Dec 11 21:23:22 2012 nicolas bridoux
** Last update Sun May 19 04:34:46 2013 guillaume fillon
*/

#include "42s.h"

static int	modif_term(struct termios *t)
{
  if (tcsetattr(STDIN_FILENO, TCSANOW, t) == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		my_putc(int c)
{
  if ((write(1, &c, 1)) == -1)
    return (EXIT_FAILURE);
  return (FALSE);
}

int		raw_mode(struct termios *t)
{
  t->c_lflag &= ~(ICANON | ECHO);
  t->c_cc[VMIN] = 1;
  t->c_cc[VTIME] = 0;
  return (modif_term(t));
}

int		raw_mode_off(struct termios *t)
{
  t->c_lflag |= (ICANON | ECHO);
  return (modif_term(t));
}
