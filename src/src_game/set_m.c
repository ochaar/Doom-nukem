/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_m.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:52:41 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/25 11:54:50 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		reset_player(t_env *w, t_map *m)
{
	m->player.bullet[0] = 0;
	m->player.bullet[1] = 0;
	m->player.take[0] = 0;
	m->player.take[1] = 0;
	m->player.take[2] = 0;
	m->player.take[3] = 0;
	m->player.intactu_ammo = 0;
	m->player.firing = 0;
	m->player.shooting = 0;
	m->player.field_of_vision_h = w->mem_field_of_vision_h;
	m->player.field_of_vision_v = w->mem_field_of_vision_v;
	m->player.aiming = 0;
	m->elevator = 0;
	m->weap[0].actu_ammo = m->weap[0].magazine;
	m->weap[1].actu_ammo = m->weap[1].magazine;
	m->weap[2].actu_ammo = m->weap[2].magazine;
}

void		set_count(t_map *m)
{
	m->i = 0;
	m->dotsc = 0;
	m->s = 0;
	m->spmc = 0;
	m->ennemyc = 0;
	m->door = 0;
	m->w = 0;
	m->section_number = 0;
	m->dots_count = 0;
	m->sector_count = 0;
	m->nb_d = 0;
	m->nb_a = 0;
}

void		set_m(t_map *m)
{
	m->sprite_count = -1;
	m->weapon_count = -1;
	m->trippymod = 0;
	m->fd = 0;
	m->fd2 = 0;
	m->stop = 0;
	m->launchwmap = 0;
	m->newgame = 1;
	m->endsector = -1;
	m->change_lvl = 0;
	m->maxrenderedsector = 32;
	m->yaw = 0;
	m->gravity = BASE_GRAVITY;
	m->line = NULL;
	m->linklvl = NULL;
	m->dot = NULL;
	m->sector = NULL;
	m->weap = NULL;
	m->ennemy = NULL;
	m->sprite = NULL;
	m->sprt = NULL;
	m->tab = NULL;
	m->god_mod = 0;
	m->hud = pre_init_texture(0, 0);
	set_count(m);
}

void		set_player_math(t_map *m)
{
	m->player.coor.x = 0;
	m->player.coor.y = 0;
	m->player.coor.z = 0;
	m->player.memz = 0;
	m->player.movespeed = 0;
	m->player.move_speed.x = 0;
	m->player.move_speed.y = 0;
	m->player.move_speed.z = 0;
	m->player.move_speedless.x = 0;
	m->player.move_speedless.y = 0;
	m->player.move_speedless.z = 0;
	m->player.angle = 0;
	m->player.anglecos = 0;
	m->player.anglesin = 0;
	m->player.yaw = 0;
	m->player.stance = 0;
	m->player.fall = 1;
	m->player.jump = 0;
	m->player.ground = 0;
	m->player.moving = 0;
	m->player.height = 0;
	m->player.hole_low = 0;
	m->player.hole_high = 0;
	m->player.press = 0;
	m->player.accel = 0;
}

void		set_m_player(t_map *m)
{
	m->player.bal = 0;
	if (!(m->player.fps = (char *)malloc(sizeof(char) * 12)))
		set_error((t_env *)m->world, m, 0, strdup_check(m->world, "pl.fps"));
	ft_light_itoa(0, m->player.fps);
	if (!(m->player.stractu_ammo = (char *)malloc(sizeof(char) * 12)))
		set_error((t_env *)m->world, m, 0, strdup_check(m->world, "pl.ammo"));
	ft_light_itoa(0, m->player.stractu_ammo);
	if (!(m->player.strhp = (char *)malloc(sizeof(char) * 12)))
		set_error((t_env *)m->world, m, 0, strdup_check(m->world, "pl.ammo"));
	ft_light_itoa(0, m->player.strhp);
	if (!(m->player.strbullet = (char *)malloc(sizeof(char) * 12)))
		set_error((t_env *)m->world, m, 0, strdup_check(m->world, "pl.bullet"));
	m->player.handed = 0;
	m->player.aiming = 0;
	m->player.shooting = 0;
	m->player.firing = 0;
	m->player.refresh = 0;
	m->player.switching = 0;
	m->player.recoil = 0;
	m->player.sector = 0;
	m->player.hud = 1;
	m->player.max_hp = 100;
	set_player_math(m);
	m->player.display = 0;
	m->player.minimap = 0;
}
