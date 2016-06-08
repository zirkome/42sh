/*
** catch_cmd.c for catch_cmd in /home/linard_f/42sh/cmd_edition
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat Apr 13 12:40:46 2013 fabien linardon
** Last update Sun May 26 16:29:47 2013 nicolas bridoux
*/

#include "42s.h"
#include "builtins.h"
#include "list.h"

extern int	g_tgetent;

static int	handle_special_key(int buf, char *str, t_shenv *shenv)
{
  char		*cap;

  if ((buf == 0 || buf == 4) && (str == NULL || str[0] == 0))
    {
      shenv->exit = 1;
      return (EXIT_FAILURE);
    }
  if (isatty(0) && buf == 12)
    {
      cap = tgetstr("cl", NULL);
      if (g_tgetent == TRUE)
	tputs(cap, 1, &my_putint);
      xfree(1, &cap);
      return (2);
    }
  if (buf == 10)
    return (2);
  return (EXIT_SUCCESS);
}

static void	init_catch(int *buf, char **str, t_line *line, int prompt)
{
  *buf = 0;
  *str = NULL;
  line->rk = 0;
  line->prompt = prompt;
  line->x = prompt;
  line->y = 0;
  line->history = 0;
  line->actual = NULL;
}

static void		win_size(t_line *line)
{
  struct winsize	win;

  line->win_x = 80;
  line->win_y = 25;
  if (ioctl(0, TIOCGWINSZ, &win) == -1)
    {
      fprintf(stderr, "familial_sh: %s\n", strerror(errno));
      return ;
    }
  line->win_x = win.ws_col;
  line->win_y = win.ws_row;
}

static char	*complete_catch(int buf, t_shenv *shenv,
				char *str, t_line *line)
{
  xfree(1, &line->actual);
  if (!buf)
    {
      shenv->exit = TRUE;
      return ("");
    }
  end_of_line(0, str, line);
  if (isatty(0) && g_tgetent != FALSE)
    printf("\n");
  my_put_off_raw();
  return (str);

}

char		*catch_cmd(char *iterm, int prompt, t_shenv *shenv, int i_raw)
{
  int		ret;
  int		buf;
  char		*str;
  t_line	line;
  static char	*cpy = NULL;

  line.fd = shenv->tty_fd;
  line.cpy = cpy;
  init_catch(&buf, &str, &line, prompt);
  if (isatty(0))
    win_size(&line);
  while (read(0, &buf, (i_raw || !isatty(0) || !iterm)
	      ? 1 : sizeof(int)) > 0 && buf != K_ENTER)
    {
      if ((ret = handle_special_key(buf, str, shenv)) == EXIT_FAILURE)
	return ("");
      if (ret == 2)
      	return (NULL);
      str = cmd_tab(buf, str, &line, shenv);
      buf = 0;
    }
  cpy = line.cpy;
  return (complete_catch(buf, shenv, str, &line));
}
