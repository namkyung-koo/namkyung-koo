/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:03:43 by nakoo             #+#    #+#             */
/*   Updated: 2023/06/29 15:05:15 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list *list, t_node *new)
{
	t_node	*tail;

	if (list->head_node.next == NULL)
	{
		list->head_node.next = new;
		list->node_count++;
		return ;
	}
	tail = ft_lstlast(list->head_node.next);
	tail->next = new;
	list->node_count++;
}
