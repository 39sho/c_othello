#include <stdio.h>
#include <string.h>

void print_board();
int calc_pos(int, int);
int can_place(int);
int flip_line(int, int, int);
int place_and_flip(int, int);

char cell_type[] = {' ', '@', 'O', '#'};

/*
int board[100] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 2, 1, 0, 0, 0, 3,
    3, 0, 0, 0, 1, 2, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};
*/
int board[100] = {
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    3,
    3,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    3,
    3,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    3,
    3,
    0,
    0,
    0,
    2,
    1,
    0,
    0,
    0,
    3,
    3,
    0,
    0,
    0,
    1,
    2,
    0,
    0,
    0,
    3,
    3,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    3,
    3,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    3,
    3,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
};

int main()
{
    int x, y;
    int pos;
    char message[100] = "\n";
    int player = 1; /* 1 or 2 */
    int count = 0;
    int blankCount = 0;
    int player1count = 0;
    int player2count = 0;
    int isEnd = 0;
    int i;

    while (1)
    {
        printf("\033[2J\033[1;1H");
        print_board(board);
        printf("%s", message);
        printf("player%d(%c): \n", player, cell_type[player]);
        printf("input position(x y): ");

        strcpy(message, "\n");

        isEnd = 0;
        blankCount = 0;
        for (i = 0; i < 100; i++)
        {
            if (board[i] == 0)
                blankCount += 1;
        }

        player1count = 0;
        for (i = 0; i < 100; i++)
        {
            if (board[i] == 1)
                player1count += 1;
        }

        player2count = 0;
        for (i = 0; i < 100; i++)
        {
            if (board[i] == 2)
                player2count += 1;
        }

        isEnd = blankCount == 0 || player1count == 0 || player2count == 0;

        if (isEnd)
            break;

        if (scanf("%d%d", &x, &y) == EOF)
        {
            break;
        }

        pos = calc_pos(x, y);

        /* if pos is 99, close game */
        if (pos == 99)
            break;

        /* if pos is 0, skip */
        if (pos != 0)
        {
            if (!(1 <= x && x <= 8 && 1 <= y && y <= 8))
            {
                strcpy(message, "\033[31moutside of board\033[39m\n");
                continue;
            }

            count = 0;

            if (can_place(pos))
                count = place_and_flip(player, pos);

            if (count == 0)
            {
                strcpy(message, "\033[31mcannot place\033[39m\n");
                continue;
            }
        }

        if (player == 1)
        {
            player = 2;
        }
        else
        {
            player = 1;
        }
    }

    /* isEnd = true */
    printf("\033[32m");
    if (player1count > player2count)
    {
        printf("--- player1 WIN! ---\n");
    }
    else if (player1count < player2count)
    {
        printf("--- player2!! WIN!---\n");
    }
    else
    {
        printf("--- DRAW ---\n");
    }
    printf("\033[39m");
}

void print_board()
{
    int i, j;

    printf("  ");
    for (i = 0; i < 10; i++)
    {
        if (i == 0 || i == 9)
            printf("  ");
        else
            printf("%2d", i);
    }
    printf("\n");

    for (i = 0; i < 10; i++)
    {
        if (i == 0 || i == 9)
            printf("  ");
        else
            printf("%2d", i);

        for (j = 0; j < 10; j++)
        {

            printf("%2c", cell_type[board[calc_pos(j, i)]]);
        }

        printf("\n");
    }
}

int calc_pos(int x, int y)
{
    return y * 10 + x;
}

int can_place(int pos)
{
    if (board[pos] == 0)
        return 1;

    return 0;
}

int flip_line(int player, int pos, int dir)
{
    int tmp_pos = pos;
    int count = 0;

    while (1)
    {
        tmp_pos += dir;

        if (board[tmp_pos] == 0 || board[tmp_pos] == 3)
            return 0;
        else if (board[tmp_pos] == player)
        {
            break;
        }
    }

    while (1)
    {
        tmp_pos -= dir;
        if (tmp_pos == pos)
        {
            break;
        }

        count += 1;
        board[tmp_pos] = player;
    }

    return count;
}

int place_and_flip(int player, int pos)
{
    int count = 0;

    count += flip_line(player, pos, -11);
    count += flip_line(player, pos, -10);
    count += flip_line(player, pos, -9);
    count += flip_line(player, pos, -1);
    count += flip_line(player, pos, 1);
    count += flip_line(player, pos, 9);
    count += flip_line(player, pos, 10);
    count += flip_line(player, pos, 11);

    if (count != 0)
        board[pos] = player;

    return count;
}
