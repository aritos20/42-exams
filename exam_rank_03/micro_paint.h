/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:09:40 by agianico          #+#    #+#             */
/*   Updated: 2020/10/11 17:12:44 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_zone
{
	int			width;
	int			height;
	char		background;
}				t_zone;

typedef struct	s_shape
{
	char		type;
	float		x;
	float		y;
	float		width;
	float		height;
	char		color;
}				t_shape;

