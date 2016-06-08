/*
** builtin_history.c for builtin_history.c in /home/bridou_n/42sh/src/builtins
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sat May 11 18:19:02 2013 nicolas bridoux
** Last update Sun May 26 13:36:36 2013 nicolas bridoux
*/

#include "builtins.h"

static int	display_history(char *path)
{
  int		fd;
  char		*file;

  if ((fd = open(path, O_RDONLY | O_CREAT)) == -1)
    {
      xfree(1, &path);
      my_error("");
      return (EXIT_FAILURE);
    }
  file = read_fd(fd);
  close(fd);
  dprintf(STDOUT_FILENO, "%s", file);
  xfree(2, &file, &path);
  return (EXIT_SUCCESS);
}

int	_builtin_history(char **cmd, __attribute__((unused)) t_shenv *shenv)
{
  char	*path;
  int	fd;

  if (!(path = get_history_file_path()))
    return (EXIT_FAILURE);
  if (cmd[1] && !strcmp(cmd[1], "-c"))
    {
      if ((fd = open(path, O_RDONLY | O_TRUNC)) == -1)
	{
	  my_error("");
	  xfree(1, &path);
	  return (EXIT_FAILURE);
	}
      close(fd);
    }
  else
    return (display_history(path));
  xfree(1, &path);
  return (EXIT_SUCCESS);
}
