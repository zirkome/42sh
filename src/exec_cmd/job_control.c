/*
** job_control.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g/src
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Fri May 24 22:42:43 2013 guillaume fillon
** Last update Sun May 26 14:00:31 2013 nicolas bridoux
*/

#include "42s.h"

void		create_real_son(pid_t pid)
{
  if (setpgid(pid, pid) == -1)
    fprintf(stderr, "familial_sh: %s\n", strerror(errno));
  signal(SIGINT, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
  signal(SIGTSTP, SIG_DFL);
  signal(SIGTTIN, SIG_DFL);
  signal(SIGTTOU, SIG_DFL);
  signal(SIGCHLD, SIG_DFL);
  signal(SIGTTOU, SIG_IGN);
  if (isatty(0))
    tcsetpgrp(0, pid);
  if (isatty(1))
    tcsetpgrp(1, pid);
  if (isatty(2))
    tcsetpgrp(2, pid);
  signal(SIGTTOU, SIG_DFL);
}

void		back_to_shell(pid_t pid)
{
  signal(SIGTTOU, SIG_IGN);
  if (isatty(0))
    tcsetpgrp(0, pid);
  if (isatty(1))
    tcsetpgrp(1, pid);
  if (isatty(2))
    tcsetpgrp(2, pid);
  signal(SIGTTOU, SIG_DFL);
}
