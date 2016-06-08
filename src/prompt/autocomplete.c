/*
** autocomplete.c for autocomplete.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Fri May 24 15:39:50 2013 nicolas bridoux
** Last update Sun May 26 12:30:06 2013 fabien linardon
*/

#include "42s.h"

static char	*complete_ret(int len, char **tab_cmd,
			      char *common, char *str)
{
  char		*ret;

  if (!(ret = malloc(sizeof(char) * len + 2)))
    return (str);
  strcpy(ret, tab_cmd[0]);
  strcat(ret, common);
  strcat(ret, tab_cmd[2]);
  if ((len = strlen(tab_cmd[1])) < 0)
    tab_cmd[1][len + 1] = '\0';
  else
    tab_cmd[1][len] = '\0';
  return (ret);
}

char	*complete_if_possible(char *str, char **tab,
			      char **tab_cmd, t_line *line)
{
  char	*ret;
  char	*common;
  int	n;
  int	len;

  n = 0;
  ret = my_strdup(str);
  while (first_n_char_are_the_same(tab, ++n));
  --n;
  if (!(common = strndup(tab[0], n)))
    return (str);
  len = strlen(tab_cmd[0]) + strlen(common) + strlen(tab_cmd[2]);
  if (!(ret = complete_ret(len, tab_cmd, common, str)))
    return (str);
  dprintf(line->fd, "%s", ret);
  if (strlen(common))
    len = line->rk += (strlen(common) - strlen(tab_cmd[1]));
  line->x = line->rk + line->prompt;
  n = strlen(ret) - line->rk;
  while (n > 0 && n--)
    go_left();
  xfree(2, &common, &str);
  return (ret);
}

char	*display_matches(t_line *line, char **tab, char *str, char **tab_cmd)
{
  int	max;
  int	i;
  int	count;

  i = -1;
  count = 0;
  max = find_max(tab) + 1;
  putchar('\n');
  while (tab[++i])
    {
      ++count;
      dprintf(line->fd, "%s%-*s%s", (tab[i][strlen(tab[i]) - 1] == '/') ?
	      (BLUE_BOLD) : (""), max, tab[i],
	      (tab[i][strlen(tab[i]) - 1] == '/') ? (INIT) : (""));
      if (count == line->win_x / max)
	{
	  printf("\n");
	  count = 0;
	}
    }
  dprintf(line->fd, "%s\n", INIT);
  display_prompt(my_getcwd(), line->fd);
  str = complete_if_possible(str, tab, tab_cmd, line);
  free_cmd_tab(tab_cmd);
  return (str);
}

static char	*complete_path(char *str, t_line *line, char **tab)
{
  glob_t	elem;
  char		*ret;

  if (strlen(tab[1]) && tab[1][strlen(tab[1]) - 1] != '*')
    strcat(tab[1], "*");
  if (glob(tab[1], GLOB_TILDE | GLOB_MARK | GLOB_NOCHECK, NULL, &elem))
    return (str);
  if (elem.gl_pathv[0] && !strcmp(elem.gl_pathv[0], tab[1]))
    ret = str;
  else if (elem.gl_pathc == 1)
    ret = one_completion(line, elem.gl_pathv[0], str, tab);
  else
    {
      ret = display_matches(line, elem.gl_pathv, str, tab);
      my_right(0, ret, line);
    }
  globfree(&elem);
  return (ret);
}

char		*auto_complete(char *str, t_line *line, t_shenv *shenv)
{
  char		*tab[4];
  char		*cmd;

  if (cut_completion(tab, str, line->rk) || !tab[0] || !tab[1] || !tab[2])
    return (str);
  (!strcmp(tab[0], "")) ? (cmd = tab[1]) : (cmd = tab[0]);
  if (!actual_path(cmd))
    return (complete_binary(str, line, shenv, tab));
  else
    return (complete_path(str, line, tab));
  free_cmd_tab(tab);
  return (str);
}
