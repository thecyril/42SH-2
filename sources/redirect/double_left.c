/*
** double_left.c for 42sh in C:\Users\gambin_l\42SH\sources\redirect
**
** Made by Gambini Lucas
** Login   <Lucas Gambini@epitech.net>
**
** Started on  Mon May 30 10:56:47 2016 Gambini Lucas
** Last update Mon Jun  6 21:30:57 2016 cyril puccio
*/

#include 		"42.h"

char			*my_concate(char *base, char *add)
{
  char			*ret;
  int			i;
  int			j;

  if (base == NULL || add == NULL)
    return (NULL);
  if ((ret = malloc(sizeof(char)
		    * (strlen(base) + strlen(add) + 2))) == NULL)
    return (NULL);
  i = -1;
  while (base[++i] != '\0')
    ret[i] = base[i];
  ret[i++] = '\n';
  j = 0;
  while (add[j] != '\0')
    ret[i++] = add[j++];
  ret[i] = '\0';
  return (ret);
}

char			*get_buffer(t_red var)
{
  char			*buff;
  char			*res;

  res = NULL;
  if (!var.name)
    return (NULL);
  while (write(1, "? ", 2) && (buff = get_next_line(0)))
    {
      if (strcmp(buff, var.name) == 0)
	break;
      if (!res)
	res = strdup(buff);
      else
	res = my_concate(res, buff);
      xfree(buff);
    }
  return (res);
}

int                     check_left(char *buff, t_cmd *cmd, int pipefd[2])
{
  if (buff)
    {
      if (cmd->cmd[0])
        {
          write(1, buff, strlen(buff));
          return (SUCCESS + 0 * write(1, "\n", 1));
        }
      else
        write(pipefd[1], buff, strlen(buff));
    }
  else
    return (FAILURE);
  return (0);
}

int                     double_left(t_cmd *cmd, t_list *list,
                                    char **env, int builtin)
{
  t_red                 var;
  char                  *buff;
  int                   pipefd[2];
  int                   reset;

  init_double_left(cmd, &var);
  if (!(cmd->go_on))
    return (FAILURE);
  pipe(pipefd);
  var.is_builtin = builtin;
  if ((buff = get_buffer(var)) == NULL)
    return (FAILURE);
  reset = dup(0);
  if (check_left(buff, cmd, pipefd) != 0)
    return (check_left(buff, cmd, pipefd));
  close(pipefd[1]);
  dup2(pipefd[0], 0);
  if (exec_left(list, env, cmd) == FAILURE)
    check_go_on(cmd);
  close(pipefd[0]);
  dup2(reset, 0);
  xfree(var.name);
  free_tab(var.cmd);
  return (SUCCESS);
}
