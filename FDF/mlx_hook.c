/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:08:14 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 22:48:02 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_(void *param)
{
	(void)param;
	exit(0);
}

void	engine(t_vars *var)
{
	mlx_hook(var->mlx_win, 2, 1L << 0, key_press, var);
	mlx_hook(var->mlx_win, 3, 1L << 1, key_release, var);
	mlx_hook(var->mlx_win, 17, 0, close_, var);
	mlx_hook(var->mlx_win, 4, 1L << 2, mouse_press, var);
	mlx_hook(var->mlx_win, 5, 1L << 3, mouse_release, var);
	mlx_hook(var->mlx_win, 6, 1L << 7, mouse_motion, var);
	mlx_loop_hook(var->mlx, loop_hook, var);
}
