/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:59:13 by zmourid           #+#    #+#             */
/*   Updated: 2023/11/17 23:34:35 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*tmp_data;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		tmp_data = (*f)(lst->content);
		new = ft_lstnew(tmp_data);
		if (!new)
		{
			ft_lstclear(&head, del);
			free(tmp_data);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
