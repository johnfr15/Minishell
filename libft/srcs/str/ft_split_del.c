/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tondelierjonathan <tondelierjonathan@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 23:49:55 by apuchill          #+#    #+#             */
/*   Updated: 2023/03/18 14:19:20 by tondelierjo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: N/A
** SYNOPSIS: split string, with specified character as delimiter, into an array
**			of strings
**
** DESCRIPTION:
** 		Allocates (with malloc(3)) and returns an array of strings obtained by
**	splitting ’s’ using the character ’c’ as a delimiter. The array must be
**	ended by a NULL pointer.
*/

#include "libft.h"

static int trim_del(const char *str, char *del)
{
    int i;

    i = 0;
    while ( ft_strchr(del, str[i]) != 0 )
        i++;
    return (i);
}

static int	count_words(const char *str, char *del)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(del, str[i]) == 0)
		{
			count++;
			while (ft_strchr(del, str[i]) == 0)
				i++;
		}
        else
		    i++;
	}
	return (count);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split_del(char const *s, char *del)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**split;

	if (!s) return (0);
    
	split = (char **) malloc((count_words(s, del) + 1) * sizeof(char *));
	if (!split) return (NULL);

	i = trim_del(s, del);
    j = 0;
	while (s[i])
	{
		if ( ft_strchr(del, s[i]) == 0 )
        {
			len = 0;
            while (ft_strchr(del, s[i + len]) == 0)
                len++;
				
			split[j++] = word_dup(s, i, i + len);
			split[j] = NULL;

            i += len;
        }
		else
            i++;
	}

	return (split);
}
