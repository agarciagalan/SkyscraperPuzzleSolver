/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejanga <alejanga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:13:27 by alejanga          #+#    #+#             */
/*   Updated: 2026/03/09 13:13:27 by alejanga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_board(int *matrix, int size)
{
	int		index;
	char	field;

	index = 0;
	while (matrix[index] != '\0')
	{
		field = matrix[index] + '0';
		write(1, &field, 1);
		index++;
		if (index % size != 0)
			write(1, " ", 1);
		else
			write(1, "\n", 1);
	}
}

void	set_value_high(int *matrix, int orientation, int index, int size)
{
	if (orientation == 0)
		matrix[index] = size;
	if (orientation == 1)
		matrix[(size - 1) * size + index] = size;
	if (orientation == 2)
		matrix[index * size] = size;
	if (orientation == 3)
		matrix[index * size + (size - 1)] = size;
}

void	set_value_low(int *matrix, int orientation, int index, int size)
{
	int	counter;

	counter = 0;
	while (counter < size)
	{
		if (orientation == 0)
			matrix[counter * size + index] = counter + 1;
		else if (orientation == 1)
			matrix[(size - 1 - counter) * size + index] = counter + 1;
		else if (orientation == 2)
			matrix[index * size + counter] = counter + 1;
		else if (orientation == 3)
			matrix[index * size + (size - 1 - counter)] = counter + 1;
		counter++;
	}
}

void	set_initial_values(int *matrix, int *combination, int size)
{
	int		orientation;
	int		index;

	orientation = 0;
	while (orientation < 4)
	{
		index = 0;
		while (index < size)
		{
			if (combination[orientation * size + index] == 1)
				set_value_high(matrix, orientation, index, size);
			else if (combination[orientation * size + index] == size)
				set_value_low(matrix, orientation, index, size);
			index++;
		}
		orientation++;
	}
}
int	*create_board(int *board, int *combination, int size)
{
	int		index;

	index = 0;
	while (index < (size * size))
	{
		board[index] = -1;
		index++;
	}
	set_initial_values(board, combination, size);
	return (board);
}
