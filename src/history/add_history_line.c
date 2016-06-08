/*
** add_history_line.c for add_history_line.c in /home/bridou_n/42sh/src
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sat May 11 17:31:35 2013 nicolas bridoux
** Last update Sun May 26 14:34:43 2013 nicolas bridoux
*/

#include "42s.h"

char		*get_history_file_path(void)
{
  char		*home;
  struct passwd	*p;
  static char	*path;
  static int	i = 0;

  if (!i++)
    {
      if (!(p = getpwuid(getuid())))
	return (NULL);
      home = my_strdup(p->pw_dir);
      if (!(path = malloc(sizeof(char) * (strlen(home) + 15))))
	{
	  my_error("");
	  return (NULL);
	}
      strcpy(path, home);
      strcat(path, "/");
      strcat(path, ".fsh_history");
      xfree(1, &home);
    }
  return (my_strdup(path));
}

int	add_history_line(char *cmd, t_shenv *shenv)
{
  char	*path;
  int	fd;

  if (!shenv->interactive)
    return (EXIT_SUCCESS);
  if (!strcmp(cmd, ""))
    return (EXIT_SUCCESS);
  if (!(path = get_history_file_path()))
    return (EXIT_FAILURE);
  if ((fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1)
    {
      my_error("");
      xfree(1, &path);
      return (EXIT_FAILURE);
    }
  xfree(1, &path);
  dprintf(fd, "%s\n", cmd);
  close(fd);
  return (EXIT_SUCCESS);
}
