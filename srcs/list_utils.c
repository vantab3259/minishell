/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 03:51:20 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/05 09:05:08 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(int type, char *content)
{
	t_node	*new_node;

	new_node = (t_node *) malloc (sizeof(t_node));
	if (new_node == NULL)
	{
		ft_print_error(2, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	new_node->type = type;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	push_midle(t_node **head, int type, char *content )
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_node(type, content);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	new_node->next = current->next;
	current->next = new_node;
}

void	p_bk(t_node **head, int type, char *content)
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_node(type, content);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
}

void	push_front(t_node **head, int type, char *content)
{
	t_node	*new_node;

	new_node = create_node(type, content);
	new_node->next = *head;
	*head = new_node;
}

void	display_list(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		printf("[T = %d; C = \"%s\"] ->\n", current->type, current->content);
		current = current->next;
	}
}
