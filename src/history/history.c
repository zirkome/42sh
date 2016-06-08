/*
** history.c for history.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Mon May 13 18:38:14 2013 nicolas bridoux
** Last update Sat May 25 22:04:36 2013 nicolas bridoux
*/

#include "42s.h"

static char	**history_tab(char *file, int i, int j, int k)
{
  char		**tab;

  if (!(tab = malloc(sizeof(char *) * (nb_cmd(file, '\n')))))
    {
      xfree(1, &file);
      return (NULL);
    }
  while (file[++i])
    if (file[i] == '\n')
      {
	file[i] = '\0';
	if (!(tab[++j] = my_strdup(&file[k])))
	  return (NULL);
	k = i + 1;
      }
  tab[++j] = NULL;
  xfree(1, &file);
  return (tab);
}

int	len_tab(char **tab)
{
  int	i;

  i = -1;
  while (tab[++i])
    ;
  return (i);
}

char	**get_history_line(void)
{
  char	*path;
  char	*file;
  char	**tab;
  int	fd;

  if (!(path = get_history_file_path()))
    return (NULL);
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if (!(file = read_fd(fd)))
    return (NULL);
  close(fd);
  if (!(tab = history_tab(file, -1, -1, 0)))
    return (NULL);
  return (tab);
}

char	*my_up(__attribute__((unused)) int buf, char *str, t_line *line)
{
  char	*ret;
  char	**tab;
  int	i;

  if (!(tab = get_history_line()))
    return (NULL);
  if (!line->actual)
    line->actual = (!str) ? (my_strdup("")) : (my_strdup(str));
  if (line->history < len_tab(tab))
    line->history++;
  i = len_tab(tab) - line->history;
  ret = my_strdup(tab[i]);
  my_free_tab(tab);
  return (ret);
}

char	*my_down(__attribute__((unused)) int buf, char *str, t_line *line)
{
  char	*ret;
  char	**tab;
  int	i;

  if (!(tab = get_history_line()))
    return (NULL);
  if (line->history > 0)
    line->history--;
  if (!line->history)
    {
      if (!line->actual)
	line->actual = (!str) ? (NULL) : (my_strdup(str));
      ret = my_strdup(line->actual);
      my_free_tab(tab);
      return (ret);
    }
  i = len_tab(tab) - line->history;
  ret = my_strdup(tab[i]);
  my_free_tab(tab);
  return (ret);
}
