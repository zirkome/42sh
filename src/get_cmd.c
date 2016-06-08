/*
** get_cmd.c for get_cmd.c in /home/bridou_n/42sh
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Tue Mar 19 12:09:54 2013 nicolas bridoux
** Last update Sun May 26 16:16:48 2013 nicolas bridoux
*/

#include "42s.h"
#include "builtins.h"

int		get_cmd(t_shenv *shenv)
{
  static int	flag = 1;
  char		*cmd;

  while (flag)
    {
      shenv->status = 0;
      cmd = catch_cmd(_builtin_getenv("TERM", shenv), 2, shenv,
		      my_put_in_raw(_builtin_getenv("TERM", shenv)));
      if (cmd && cmd[0] == 0 && shenv->exit != 65535 && printf("\n"))
	return (EXIT_SUCCESS);
      cmd = epur_string(cmd, -1, 0, my_strdup(""));
      if (cmd && parsing(cmd, shenv, 0) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      my_free_tab(shenv->envp);
      shenv->envp = NULL;
      xfree(1, &cmd);
      if (shenv->status == SIGINT)
	putchar('\n');
      display_prompt(my_getcwd(), shenv->tty_fd);
      if (!isatty(0))
	flag = 0;
    }
  return (EXIT_SUCCESS);
}
