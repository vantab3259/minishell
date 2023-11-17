/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 04:46:20 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 10:49:36 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node_env(char *key, char *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		ft_print_error(2, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	new_node->key = key;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	push_back_env(t_env **head, char *key, char *content)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_node_env(key, content);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			break ;
		current = current->next;
	}
	current->next = new_node;
}

void	push_front_env(t_env **head, char *key, char *content)
{
	t_env	*new_node;

	new_node = create_node_env(key, content);
	new_node->next = *head;
	*head = new_node;
}

void	remove_list_env(t_env **head, t_env *node_to_remove)
{
	t_env	*current;

	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = (*head)->next;
		free(node_to_remove->content);
		free(node_to_remove->key);
		free(node_to_remove);
		return ;
	}
	current = *head;
	while (current->next != NULL && current->next != node_to_remove)
		current = current->next;
	if (current->next == NULL)
		return ;
	current->next = node_to_remove->next;
	free(node_to_remove->content);
	free(node_to_remove->key);
	free(node_to_remove);
}
