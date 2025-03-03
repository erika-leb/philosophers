/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:53:30 by ele-borg          #+#    #+#             */
/*   Updated: 2025/02/28 15:45:44 by ele-borg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sizeint(long nb)
{
	int	r;

	r = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		r++;
		nb = nb * -1;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		r++;
	}
	return (r);
}

char	*ft_ltoa(long n)
{
	static char	str[70000];
	int			s;
	long		nb;

	nb = (long)n;
	s = ft_sizeint(nb);
	if (nb < 0)
		nb = nb * -1;
	str[s] = '\0';
	s--;
	while (s >= 0)
	{
		str[s] = (nb % 10) + '0';
		nb = nb / 10;
		s--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

void	ft_putstr_fd(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
