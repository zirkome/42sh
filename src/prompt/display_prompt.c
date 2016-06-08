/*
** display_prompt.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Sun May 19 02:50:57 2013 guillaume fillon
** Last update Sat May 25 14:43:58 2013 nicolas bridoux
*/

#include "42s.h"

static char	*my_gethostname(void)
{
  char		*host;
  char		buf[256];
  int		ret;
  int		fd;

  if ((fd = open("/proc/sys/kernel/hostname", O_RDONLY)) == -1)
    return (my_strdup(""));
  if ((ret = read(fd, buf, 255 * sizeof(char))) <= 0)
    return (my_strdup(""));
  buf[ret - 1] = '\0';
  if (fd > 0)
    close(fd);
  if (!(host = malloc(strlen(buf) + strlen(MAGENTA) + 2)))
    return (my_strdup(""));
  host = strcpy(host, "@");
  host = strcat(host, MAGENTA);
  host = strcat(host, buf);
  host[strlen(buf) + strlen(MAGENTA) + 1] = '\0';
  return (host);
}

static char	is_root(struct passwd *p)
{
  if (p->pw_uid == 0 && p->pw_gid == 0)
    return ('#');
  return ('$');
}

static char	*change_home(char *path, struct passwd *p)
{
  int		i;
  char		*final;

  i = -1;
  while (path && path[++i] && p->pw_dir)
    if (!strncmp(p->pw_dir, &path[i], strlen(p->pw_dir) - 1))
      {
	if (!(final = my_strdup(path)))
	  return (path);
	path[i] = '\0';
	strcpy(final, path);
	strcat(final, "~");
	if (strlen(p->pw_dir))
	  strcat(final, &path[i + strlen(p->pw_dir) - 1]);
	xfree(1, &path);
	return (final);
      }
  return (path);
}

void		display_prompt(char *path, int fd)
{
  char		*host;
  struct passwd	*p;

  host = my_gethostname();
  if ((p = getpwuid(getuid())) != NULL)
    {
      if (isatty(0))
	{
	  if (path)
	    dprintf(fd, "[%s%s%s%s%s:%s%s%s]\n%c ",
		    CYAN, p->pw_name, INIT, host,
		    INIT, YELLOW, (path = change_home(path, p)),
		    INIT, is_root(p));
	  else
	    dprintf(fd, "[%s%s%s%s%s:%s%s%s]\n%c ",
		    CYAN, p->pw_name, INIT, host,
		    INIT, YELLOW, "", INIT, is_root(p));
	}
    }
  else
    fprintf(stderr, "%s\n", strerror(errno));
  xfree(2, &host, &path);
}
