/*
** utils.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May  5 17:01:19 2016 
** Last update Sun May 15 18:44:57 2016 
*/

#include "utils.h"

static int	count_word(char *str)
{
  int		i;
  int		count;

  count = 0;
  i = 0;
  while (str[i] && str[i] != '\r')
    {
      while (str[i] == ' ' || str[i] == '\t'
	     || str[i] == '\r' || str[i] == '\n')
	i++;
      if (!str[i])
	return (count);
      count++;
      while (str[i]
	     && str[i] != '\r'
	     && str[i] != ' '
	     && str[i] != '\t')
	i++;
    }
  return (count);
}

char		**str_to_wordtab(char *str)
{
  char		**tab;
  char		*tmp;
  int		nb_word;
  int		i;

  i = 0;
  nb_word = count_word(str);
  if ((tab = malloc(sizeof(char *) * (nb_word + 1))) == NULL)
    return (NULL);
  while ((tmp = strsep(&str, " ")) != NULL)
    {
      tab[i] = strdup(tmp);
      if (tab[i][0])
	i++;
    }
  tab[i] = NULL;
  return (tab);
}

int	size_wordtab(char **tab)
{
  int	s;

  s = 0;
  while (tab && tab[s] != NULL)
    {
      s++;
    }
  return (s);
}

int	get_ip_port(char *arg, char **ip, int *port)
{
  int	step;
  char	*tmp;
  char	*get;

  step = -1;
  tmp = strdup(arg);
  while ((get = strsep(&tmp, ",")) != NULL && ++step < 4)
    {
      if (step == 0)
	sprintf(*ip, "%s.", get);
      else if (step < 3)
	*ip = strcat(strcat(*ip, get), ".");
      else
	*ip = strcat(*ip, get);
    }
  if (step != 4)
    return (-1);
  if (get != NULL)
    (*port) += atoi(get) * 256;
  if ((get = strsep(&tmp, ",")) != NULL)
    (*port) += atoi(get);
  if (get == NULL)
    return (-1);
  return (0);
}
