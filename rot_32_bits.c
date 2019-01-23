/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_32_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 00:30:31 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/23 00:30:54 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

uint32_t		rot_32_left(uint32_t base, uint32_t rounds)
{
	return ((base << rounds) | (base >> (32 - rounds)));
}

uint32_t		rot_32_right(uint32_t base, uint32_t rounds)
{
	return ((base >> rounds) | (base << (32 - rounds)));
}
