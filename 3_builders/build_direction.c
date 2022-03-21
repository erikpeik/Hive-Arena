#include "agent_pippuri.h"

static const dir_t north_west[] = {
	NW,
	W,
	SW,
	S,
	SE,
	E,
	NE
};

static const dir_t south_west[] = {
	SW,
	W,
	NW,
	N,
	NE,
	E,
	SE
};

static const dir_t north_east[] = {
	NE,
	E,
	SE,
	S,
	SW,
	W,
	NW
};

static const dir_t south_east[] = {
	SE,
	E,
	NE,
	N,
	NW,
	W,
	SW
};

static const dir_t bee2_enemy0[] = {
	W,
	NW,
	SW,
	N,
	S,
	NE,
	SE
};

static const dir_t bee2_enemy1[] = {
	E,
	SE,
	NE,
	S,
	N,
	SW,
	NW
};

static const coords_t offsets[] = {
	{-1, 0},
	{-1, 1},
	{ 0, 1},
	{ 1, 1},
	{ 1, 0},
	{ 1,-1},
	{ 0,-1},
	{-1,-1}
};

int is_free(agent_info_t info, int dir)
{
	coords_t offset = offsets[dir];
	cell_t cell_info = info.cells[VIEW_DISTANCE + offset.row][VIEW_DISTANCE + offset.col];
	if (cell_info == EMPTY)
		return (dir);
	return (-1);

}

static dir_t	compass(agent_info_t info, const dir_t directions[])
{
	for (int i = 0; i < 7; i++)
	{
		if (is_free(info, directions[i]) >= 0)
			return (directions[i]);
	}
	return (directions[0]);

}

command_t	build_direction(agent_info_t info)
{
	if (info.player == 0)
	{
		if (info.bee == 0) // SW
		{
			return (command_t) {
				.action = BUILD,
				.direction = compass(info, south_west)
			};
		}
		else if (info.bee == 2)
		{
			return (command_t) {
				.action = BUILD,
				.direction = compass(info, bee2_enemy0)
			};
		}
		else 		// NW
		{
			return (command_t) {
				.action = BUILD,
				.direction = compass(info, north_west)
			};
		}
	}

	else
	{
		if (info.bee == 0) // SE
		{
			return (command_t) {
				.action = BUILD,
				.direction = compass(info, south_east)
			};
		}
		else if (info.bee == 2)
		{
			return (command_t) {
				.action = BUILD,
				.direction = compass(info, bee2_enemy1)
			};
		}
		else				// NE
		{
			return (command_t) {
				.action = BUILD,
				.direction = compass(info, north_east)
			};
		}
	}
}
