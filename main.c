#include "../include/cub3d.h"

#define BUFFER_SIZE 1024

char	*take_the_map(char *argv)
{
	char	*data;
	char	*bu;
	int		buff;
	int		fd;

	buff = 0;
	fd = 0;
	bu = NULL;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (NULL);
	}
	bu = malloc(sizeof(char) * BUFFER_SIZE);
	if (!bu)
	{
		perror("Erreur lors de l'allocation de mémoire");
		close(fd);
		return (NULL);
	}
	buff = read(fd, bu, BUFFER_SIZE);
	if (buff < 0)
	{
		perror("Erreur lors de la lecture du fichier");
		close(fd);
		free(bu);
		return (NULL);
	}
	data = malloc(sizeof(char) * (buff + 1));
	if (!data)
	{
		perror("Erreur lors de l'allocation de mémoire");
		close(fd);
		free(bu);
		return (NULL);
	}
	memcpy(data, bu, buff);
	data[buff] = '\0';
	close(fd);
	free(bu);
	return (data);
}

void	verif_cub(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '.')
		{
			if (argv[i + 1] == 'c' && argv[i + 2]
				== 'u' && argv[i + 3] == 'b' && argv[i + 4] == '\0')
				return ;
			else
				exit (0);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	void		*mlx;
	void		*win;
	char		*bu;

	if (argc == 2)
	{
		verif_cub(argv[1]);
		bu = take_the_map(argv[1]);
		mlx = mlx_init();
		win = mlx_new_window(mlx, 10 * PIXEL_WIN, 10 * PIXEL_WIN, "CUB3D");
		mlx_loop(mlx);
	}
	else
		printf ("NEED NAME OF MAP\n");
}
