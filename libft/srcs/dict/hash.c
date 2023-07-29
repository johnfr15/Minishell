/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tondelierjonathan <tondelierjonathan@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:12:41 by apuchill          #+#    #+#             */
/*   Updated: 2023/03/05 21:39:02 by tondelierjo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

/*
** Hash function - implementation of the djb2 hashing algorithm.
**
** -> key: Character string used as unique identifier of a dictionary entry.
** -> dict_len: Dictionary's length, i.e. its maximum number of entries.
**
** RETURN: the computed index that suggests where the entry can be found.
*/

unsigned long int	hash(const char *key, unsigned int dict_len)
{
	unsigned long int	hash;
	unsigned int		i;

	hash = 5381;
	i = 0;
	while (key[i])
		hash = ((hash << 5) + hash) + key[i++];
	return (hash % dict_len);
}
