/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrasamim <jrasamim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:20:38 by jrasamim          #+#    #+#             */
/*   Updated: 2024/10/11 15:42:45 by jrasamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			i += get_len(s + i, c);
		}
	}
	return (count);
}

static char	*dup_word(const char *s, char c)
{
	char	*cpy;
	int		i;

	cpy = malloc(get_len(s, c) * sizeof(char) + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static void	*free_words(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		j;
	int		i;

	words = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			words[j] = dup_word(s + i, c);
			if (!words[j])
				return (free_words(words));
			i += get_len(s + i, c);
			j++;
		}
	}
	words[j] = NULL;
	return (words);
}
