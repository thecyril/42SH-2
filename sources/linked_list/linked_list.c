/*
** linked_list.c for  in /home/xx/Rendu/PSU/42SH
**
** Made by boris saint-bonnet
** Login   <saint-_o@epitech.net>
**
** Started on  Thu May 19 18:53:01 2016 boris saint-bonnet
** Last update Mon Jun 06 18:29:13 2016 Philippe Lefevre
*/

#include	"42.h"

t_list		*create_list(t_list *list)
{
  if ((list = malloc(sizeof(*list))) == NULL)
    return (NULL);
  if ((list->path = malloc(sizeof(struct s_path))) == NULL)
    return (NULL);
  if ((list->myEnv = malloc(sizeof(struct s_env))) == NULL)
    return (NULL);
  if ((list->myHist = malloc(sizeof(struct s_history))) == NULL)
    return (NULL);
  if ((list->myRc = malloc(sizeof(struct s_bash))) == NULL)
    return (NULL);
  list->myEnv->head = NULL;
  list->myEnv->tail = NULL;
  list->myHist->head = NULL;
  list->myHist->tail = NULL;
  list->myRc->head = NULL;
  list->myRc->tail = NULL;
  list->head = NULL;
  list->tail = NULL;
  list->path->head = NULL;
  list->path->tail = NULL;
  return (list);
}

t_node		*init_push_env(t_node *node, char *data, char *name)
{
  if ((node->data = strdup(data)) == NULL)
    return (NULL);
  if ((node->name = strdup(name)) == NULL)
    return (NULL);
  node->next = NULL;
  node->p = true;
  return (node);
}

t_list		*push_env(t_list *list, char *data, char *name)
{
  t_node        *node;

  if ((node = malloc(sizeof(*node))) == NULL)
    return (NULL);
  if (list != NULL)
    {
      if (node != NULL)
  	{
	  if (init_push_env(node, data, name) == NULL)
	    return (list);
	  if (list->myEnv->tail == NULL)
	    {
	      node->prev = NULL;
	      list->myEnv->head = node;
	      list->myEnv->tail = node;
	    }
	  else
	    {
	      list->myEnv->tail->next = node;
	      node->prev = list->myEnv->tail;
	      list->myEnv->tail = node;
	    }
	}
    }
  return (list);
}

t_list		*push_path(t_list *list, char *data)
{
  t_node        *node;

  if (data == NULL)
    return (list);
  if ((node = malloc(sizeof(*node))) == NULL)
    return (NULL);
  node->data = strdup(data);
  node->name = NULL;
  node->next = NULL;
  node->p = true;
  if (list->path->tail == NULL)
    {
      node->prev = NULL;
      list->path->head = node;
      list->path->tail = node;
    }
  else
    {
      list->path->tail->next = node;
      node->prev = list->path->tail;
      list->path->tail = node;
    }
  return (list);
}
