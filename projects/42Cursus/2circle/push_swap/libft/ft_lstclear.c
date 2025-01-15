/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:49:39 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/31 19:59:41 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{	
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		del(tmp->content);
		*lst = (*lst)->next;
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}
