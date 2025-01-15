/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:49:39 by nakoo             #+#    #+#             */
/*   Updated: 2023/06/29 13:25:31 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list *list)
{
	t_node	*temp;

	while (list->head_node.next)
	{
		temp = list->head_node.next;
		list->head_node.next = list->head_node.next->next;
		free(temp);
	}
	list->node_count = 0;
	free(list);
}
