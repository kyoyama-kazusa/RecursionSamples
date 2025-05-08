#pragma once

#include "SudokuGrid.h"
#include <stdlib.h>

void entry(void) {
	const char *const input = "..4.6..9.2..4..3....3..9...3...851...5....6....8..........7..8.9..2364....1.....7";

	SudokuGrid *const grid = parse_grid(input);
	print_grid(grid);

	SudokuGrid solution = { 0 };
	copy_grid(grid, &solution);
	backtrack_solve_grid(grid, &solution);
	print_grid(&solution);

	free(grid);
}
