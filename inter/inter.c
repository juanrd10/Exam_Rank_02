#include <unistd.h>

int main(int argc, char **argv)
{
	int ascii[255] = {0};
	int move_arg;
	int move_char;

	if (argc == 3)
	{
		move_arg = 2;
		while(move_arg > 0)
		{
			move_char = 0;
			while(argv[move_arg][move_char])
			{
				if (move_arg == 2 && ascii[(unsigned char)argv[move_arg][move_char]] == 0)
						ascii[(unsigned char)argv[move_arg][move_char]] = 1;
				else if (move_arg == 1 && ascii[(unsigned char)argv[move_arg][move_char]] == 1)
						{
						write(1, &argv[move_arg][move_char], 1);
						ascii[(unsigned char)argv[move_arg][move_char]] = 2;
						}
				move_char++;
			}
			move_arg--;
		}
	}
	write (1, "\n", 1);
	return (0);
}
