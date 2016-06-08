/*
** _builtin_help.c for _builtin_help.c in /home/bridou_n/42sh/lib/builtins
**
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
**
** Started on  Sun May 26 19:11:11 2013 nicolas bridoux
** Last update Sun May 26 22:26:19 2013 guillaume fillon
*/

#include "builtins.h"

int	_builtin_help(__attribute__((unused)) char **cmd,
		      __attribute__((unused)) t_shenv *shenv)
{
  printf("\n %sBuiltins :%s\n", WHITE_BOLD, INIT);
  printf("\n\t%salias%s\t\t[key value]\t%s\n", BLUE_BOLD,
	 INIT, "print or set an alias");
  printf("\t%sunalias%s\t\tkey [key...]\t\t%s\n",
	 BLUE_BOLD, INIT, "unalias the key");
  printf("\t%senv%s\t\t\t\tprint the environnement\n", BLUE_BOLD, INIT);
  printf("\t%ssetenv%s\t\tkey value\tset the %s variable key to value\n",
	 BLUE_BOLD, INIT, "environnement");
  printf("\t%sunsetenv%s\tvar\t\t%s var\n", BLUE_BOLD,
	 INIT, "unset the environnement variable");
  printf("\t%sset%s\t\t%sset %s or print the local %s\n", BLUE_BOLD, INIT,
	 "[key value]\t", "the local variable key to value,", "variables");
  printf("\t%sunset%s\t\tvar\t\tunset %s\n",
	 BLUE_BOLD, INIT, "the local variable var");
  printf("\t%sexport%s\t\t%s %s env variable\n", BLUE_BOLD,
	 INIT, "[key[=value]]\texport a", "local varaible or set an");
  printf("\t%secho%s\t\t[-en]\t\tprint the parameters\n", BLUE_BOLD, INIT);
  printf("\t%shistory%s\t\t[-c]\t\t%s\n\n",
	 BLUE_BOLD, INIT, "print or delete history");
  return (EXIT_SUCCESS);
}
