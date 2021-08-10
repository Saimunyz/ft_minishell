/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:41:13 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/10 17:38:47 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static int	ft_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*get_word(char const **s, char c)
{
	size_t	i;
	size_t	word_len;
	char	*word;

	i = 0;
	while (**s == c)
		(*s)++;
	word_len = ft_len(*s, c);
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	while (i < word_len)
	{
		word[i] = s[0][i];
		i++;
	}
	word[i] = '\0';
	(*s) += word_len;
	while (**s != c && **s)
		(*s)++;
	return (word);
}

void	free_text(char **text, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(text[j]);
		text[j] = NULL;
		j++;
	}
	free(text);
	text = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	num_words;
	size_t	i;
	char	**text;
	char	*word;

	i = 0;
	if (!s)
		return (NULL);
	num_words = count_words(s, c);
	text = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!text)
		return (NULL);
	while (i < num_words)
	{
		word = get_word(&s, c);
		if (!word)
		{
			free_text(text, i);
			return (NULL);
		}
		text[i] = word;
		i++;
	}
	text[i] = NULL;
	return (text);
}
