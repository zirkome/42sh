/*
** my_getnbr.c for my_getnbr.c in /home/bridou_n/42sh
** 
** Made by nicolas bridoux
** Login   <bridou_n@epitech.net>
** 
** Started on  Sun May 26 21:57:07 2013 nicolas bridoux
** Last update Sun May 26 22:02:20 2013 nicolas bridoux
*/

#include "42s.h"

int	my_getnbr(char *str)
{
  int	sign;
  int	result;

  sign = 1;
  result = 0;
  while (*str == '-' || *str == '+')
    {
      if (*str == '-')
	sign = - sign;
      str = str + 1;
    }
  while (*str != '\0' && *str >= '0' && *str <= '9')
    {
      if (result > 214748364)
	return (0);
      if (result == 214748364 && *str > 7 && sign == 1)
	return (0);
      if (result == 214748364 && *str > 8 && sign == -1)
	return (0);
      result = result * 10 + *str - 48;
      str = str + 1;
    }
  return ((sign == -1) ? (-result) : (result));
}
