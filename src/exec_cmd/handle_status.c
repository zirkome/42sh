/*
** handle_status.c for 42sh in /home/fillon_g/projets/42sh-2017-fillon_g
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Sun May 26 14:58:27 2013 guillaume fillon
** Last update Sun May 26 15:10:52 2013 guillaume fillon
*/

#include "42s.h"
#include "builtins.h"
#include "list.h"

static t_status g_st[] =
  {
    {SIGHUP, "[%d] hangup %s\n"},
    {SIGQUIT, "[%d] quit %s\n"},
    {SIGILL, "[%d] illegal hardware instruction %s\n"},
    {SIGTRAP, "[%d] trace trap %s\n"},
    {SIGABRT, "[%d] abort %s\n"},
    {SIGIOT, "[%d] abort %s\n"},
    {SIGBUS, "[%d] bus error %s\n"},
    {SIGFPE, "[%d] floating point exception %s\n"},
    {SIGKILL, "[%d] killed %s\n"},
    {SIGUSR1, "[%d] user-defined signal 1 %s\n"},
    {SIGUSR2, "[%d] user-defined signal 2 %s\n"},
    {SIGSEGV, "[%d] segmentation fault %s\n"},
    {SIGALRM, "[%d] alarm %s\n"},
    {SIGTERM, "[%d] terminated %s\n"},
    {SIGSTKFLT, "[%d] stack fault on coprocessor %s\n"},
    {SIGTSTP, "[%d] suspended (signal) %s\n"},
    {SIGTTIN, "[%d] suspended (tty input) %s\n"},
    {SIGTTOU, "[%d] suspended (tty output) %s\n"},
    {SIGXCPU, "[%d] cpu limit exceeded %s\n"},
    {SIGXFSZ, "[%d] file size limit exceeded %s\n"},
    {SIGVTALRM, "[%d] virtual time alarm %s\n"},
    {SIGPROF, "[%d] profile signal %s\n"},
    {SIGIO, "[%d] pollable event occurred %s\n"},
    {SIGPOLL, "[%d] pollable event occurred %s\n"},
    {SIGPWR, "[%d] power fail %s\n"},
    {SIGSYS, "[%d] invalid system call %s\n"},
    {-1, NULL}
  };

void		add_status(t_shenv *shenv)
{
  char		status[10];
  t_list	*tmp;

  tmp = shenv->lvar;
  snprintf(status, 10, "%d", WEXITSTATUS(shenv->status));
  while (tmp != NULL)
    {
      if (strcmp("?", tmp->name) == 0)
	{
	  tmp->value = strdup(status);
	  return ;
	}
      tmp = tmp->next;
    }
  my_put_in_end(&shenv->lvar, strdup("?"), strdup(status));
}

int	handle_status(pid_t pid, char *cmd, t_shenv *shenv)
{
  int	i;

  i = 0;
  if (WIFSIGNALED(shenv->status))
    while (g_st[i].sig != -1)
      {
	if (g_st[i].sig == WTERMSIG(shenv->status))
	  {
	    printf(g_st[i].message, pid, cmd);
	    return (EXIT_FAILURE);
	  }
	++i;
      }
  if (WIFEXITED(shenv->status))
    add_status(shenv);
  return (EXIT_SUCCESS);
}
