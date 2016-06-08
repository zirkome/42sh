/*
** load_conf_file.c for load_conf_file.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sat May 25 12:17:58 2013 nicolas bridoux
** Last update Sun May 26 22:09:15 2013 guillaume fillon
*/

#include "42s.h"

static char	**tab_conf(char *file)
{
  int		i;
  char		**tab;

  if (!(tab = malloc(sizeof(char *) * (nb_cmd(file, '\n') ))))
    return (NULL);
  i = 0;
  tab[0] = strtok(file, "\n");
  while ((tab[++i] = strtok(NULL, "\n")));
  return (tab);
}

static char	*file_conf_path(void)
{
  struct passwd	*p;
  char		*ret;

  if (!(p = getpwuid(getuid())))
    return (NULL);
  if (!(ret = malloc(sizeof(char) * strlen(p->pw_dir) + 8)))
    return (NULL);
  strcpy(ret, p->pw_dir);
  strcat(ret, "/");
  strcat(ret, ".fshrc");
  return (ret);
}

void	load_conf_file(t_shenv *shenv)
{
  int	fd;
  char	*file;
  char	*path;
  char	**tab;
  int	i;

  path = file_conf_path();
  if ((fd = open(path, O_RDONLY | O_CREAT, 0644)) == -1)
    return ;
  if (!(file = read_fd(fd)))
    {
      close(fd);
      return ;
    }
  close(fd);
  if (!(tab = tab_conf(file)))
    return ;
  i = -1;
  while (tab[++i])
    if ((tab[i] = epur_string(tab[i], -1, 0, my_strdup(""))))
      parsing(tab[i], shenv, 0);
  my_free_tab(tab);
  xfree(2, &file, &path);
  shenv->interactive = TRUE;
}
