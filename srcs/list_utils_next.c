/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 05:34:17 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/05 06:12:58 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_list(t_node **head, t_node *node_to_remove)
{
	t_node	*current;

	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = (*head)->next;
		free(node_to_remove->content);
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
	free(node_to_remove);
}

void	free_list(t_node *head)
{
	t_node	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
}

int	list_len(t_node *head)
{
	int		i;
	t_node	*current;

	i = 0;
	current = head;
	while (current != NULL)
		i++;
	return (i);
}

void	display_list_env(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		printf("[K = %s; C = \"%s\"] ->\n", current->key, current->content);
		current = current->next;
	}
}

void	free_list_env(t_env *head)
{
	t_env	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp->key);
		free(temp);
	}
}
