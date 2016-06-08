/*
** put_in_raw.c for put_in_raw in /home/linard_f/42sh/cmd_edition
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat Apr 13 11:57:57 2013 fabien linardon
** Last update Sun May 26 22:02:07 2013 guillaume fillon
*/

#include "42s.h"

int	g_tgetent = TRUE;

int			my_put_in_raw(char *iterm)
{
  struct termios	term;

  if (!isatty(0) || iterm == NULL)
    {
      g_tgetent = FALSE;
      return (EXIT_FAILURE);
    }
  if (tcgetattr(0, &term) == -1)
    return (my_error(""));
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
  term.c_lflag &= ~ICANON;
  term.c_lflag &= ~ECHO;
  if (tcsetattr(0, TCSANOW, &term) == -1)
    return (my_error(""));
  if (tgetent(NULL, iterm) < 1)
    {
      g_tgetent = FALSE;
      return (EXIT_FAILURE);
    }
  else
    g_tgetent = TRUE;
  return (EXIT_SUCCESS);
}

void			my_put_off_raw(void)
{
  struct termios	term;

  if (!isatty(0))
    return ;
  if (tcgetattr(0, &term) == -1)
    my_error("");
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
  term.c_lflag |= (ICANON | ECHO);
  if (tcsetattr(0, TCSANOW, &term) == -1)
    my_error("");
}
