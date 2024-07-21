/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefabreg <lefabreg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:11:41 by lefabreg          #+#    #+#             */
/*   Updated: 2024/07/17 16:01:26 by lefabreg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}

static const char	*ft_white_space(const char *str)
{
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	return (str);
}

static const char	*is_number(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
		count++;
	}
	return (str - count);
}

int	ft_atol(const char *str)
{
	size_t	sign;
	int		nb;

	nb = 0;
	sign = 1;
	str = ft_white_space(str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (!is_number(str))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		if (((nb * 10) + (*str - 48)) / 10 != nb)
			return (-1);
		nb = (nb * 10) + (*str++ - 48);
	}
	return (sign * nb);
}
