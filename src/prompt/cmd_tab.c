/*
** cmd_tab.c for cmd_tab in /home/linard_f/42sh/cmd_edition
**
** Made by fabien linardon
** Login   <linard_f@epitech.net>
**
** Started on  Sat Apr 13 13:13:12 2013 fabien linardon
** Last update Sun May 26 22:06:31 2013 guillaume fillon
*/

#include "42s.h"

extern int	g_tgetent;

static void	go_to_end(char *cpy, t_line *line, char *str, int buf)
{
  int		rk;

  rk = line->rk;
  while (cpy[++line->rk])
    if (++line->x == line->win_x)
      {
	line->x = 0;
	++line->y;
      }
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
    }
  if (!line->x)
    write(line->fd, "\n", 1);
  while (str && rk != line->rk)
    my_left(buf, str, line);
  my_left(buf, str, line);
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
    }
  ++line->rk;
}

static char	*put_buf_to_end(int buf, char *str, t_line *line)
{
  char		*cpy;

  cpy = NULL;
  if (str != NULL)
    cpy = my_strcat2(str, buf);
  else
    cpy = my_strcat2("", buf);
  if (str != NULL)
    xfree(1, &str);
  if (cpy == NULL)
    return (NULL);
  ++line->rk;
  if (isatty(0) && g_tgetent != FALSE)
    write(line->fd, &buf, sizeof(buf));
  if (++line->x == line->win_x)
    {
      line->x = 0;
      ++line->y;
      write(line->fd, "\n", 1);
    }
  return (cpy);
}

static char	*put_buf_into_str(int buf, char *str, t_line *line)
{
  char		*cpy;
  char		*tmp;

  cpy = NULL;
  if ((cpy = strdup(&str[line->rk])) == NULL)
    return (NULL);
  str[line->rk] = 0;
  str = put_buf_to_end(buf, str, line);
  if (g_tgetent == TRUE)
    tputs(tgetstr("vi", NULL), 1, &my_putint);
  write(line->fd, cpy, strlen(cpy));
  tmp = cpy;
  if ((cpy = my_strcat(str, cpy)) == NULL)
    return (NULL);
  xfree(1, &tmp);
  go_to_end(cpy, line, str, buf);
  if (!line->x)
    write(line->fd, "\n", 1);
  else
    go_right();
  xfree(1, &str);
  if (g_tgetent == TRUE)
    tputs(tgetstr("ve", NULL), 1, &my_putint);
  return (cpy);
}

static char	*cmd_management(int buf, char *str, t_line *line, int rk)
{
  char		*new;
  static char	*(*cmd_tab[])(int buf, char *str, t_line *line) =
    {
      &my_up,
      &my_down,
      &my_right,
      &my_left,
      &my_delete,
      &my_back_space,
      &go_to_begin,
      &end_of_line,
      &my_up,
      &my_down,
      &my_cut,
      &my_paste
    };

  new = cmd_tab[rk](buf, str, line);
  if (new && (!rk || rk == 1 || rk == 8 || rk == 9))
    my_aff_histo(new, line, str);
  return (new);
}

char		*cmd_tab(int buf, char *str, t_line *line, t_shenv *shenv)
{
  int		rk;
  static int	t[] = {K_UP, K_DOWN, K_RIGHT, K_LEFT, K_DEL, K_BCKSP, K_BEGIN,
		       K_END, K_PG_UP, K_PG_DOWN, K_CUT, K_PASTE, 0};

  if (!buf)
    return (str);
  rk = -1;
  if (isatty(0) && (buf == K_TAB || buf == 4))
    return (auto_complete(str, line, shenv));
  while (t[++rk] && buf != t[rk]);
  if (t[rk])
    return (cmd_management(buf, str, line, rk));
  if (str == NULL || !str[line->rk])
    str = put_buf_to_end(buf, str, line);
  else
    str = put_buf_into_str(buf, str, line);
  return (str);
}
