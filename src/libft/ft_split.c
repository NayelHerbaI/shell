
#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_tab(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;
	size_t	i;
	size_t	start;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = ft_calloc(words + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		start = 0;
		while (s[start] && s[start] != c)
			start++;
		tab[i] = ft_substr(s, 0, start);
		if (!tab[i])
			return (free_tab(tab, i), NULL);
		s += start;
		i++;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	char	buf[12];
	int		i;
	int		neg;
	long	nb;

	nb = n;
	i = 10;
	neg = 0;
	buf[11] = '\0';
	if (nb < 0)
	{
		neg = 1;
		nb = -nb;
	}
	if (nb == 0)
		buf[i--] = '0';
	while (nb > 0)
	{
		buf[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (neg)
		buf[i--] = '-';
	return (ft_strdup(&buf[i + 1]));
}
