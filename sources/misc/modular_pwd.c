/*
** modular_pwd.c for 42sh in C:\Users\gambin_l\42SH\sources\misc
**
** Made by Gambini Lucas
** Login   <Lucas Gambini@epitech.net>
**
** Started on  Sun Jun 05 17:29:44 2016 Gambini Lucas
** Last update Mon Jun  6 04:52:40 2016 boris saint-bonnet
*/

# include		"42.h"

char			*modular_pwd(char boolean, char *new_pwd)
{
  static char		*pwd = NULL;

  if (boolean && new_pwd)
    {
      if (pwd != NULL)
	free(pwd);
      pwd = strdup(new_pwd);
    }
  return (pwd);
}

char		*get_pwd(void)
{
  return (modular_pwd(0, NULL));
}

void 		set_pwd(char *pwd)
{
  modular_pwd(1, pwd);
}
