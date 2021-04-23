/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:50:33 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/10 17:38:01 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && (s[i + 1] == ' '
				|| s[i + 1] == '\t' || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static int	ft_len(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

static char	*get_word(char const **s)
{
	size_t	i;
	size_t	word_len;
	char	*word;

	i = 0;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	word_len = ft_len(*s);
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
	while (**s && (**s == ' ' || **s == '\t'))
		(*s)++;
	return (word);
}

char	**ft_split_whitespace(char const *s)
{
	size_t	num_words;
	size_t	i;
	char	**text;
	char	*word;

	i = 0;
	if (!s)
		return (NULL);
	num_words = count_words(s);
	text = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!text)
		return (NULL);
	while (i < num_words)
	{
		word = get_word(&s);
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
