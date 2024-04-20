#include <stdio.h>
#include <stdlib.h>

//starts at 0.
int placePiece(int** board, int boardHeight, int boardWidth, int position, int pieceType);
void printBoard(int** board, int boardHeight, int boardWidth, int type1, int type2);
int** createBoard(int height, int width);
int hasConnectedFour(int** board, int boardHeight, int boardWidth, int row, int column);
int isOnBoard(int boardHeight, int boardWidth, int row, int col);

int main()
{
    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_BLUE    "\x1b[34m"
    #define ANSI_COLOR_RESET   "\x1b[0m"

    int boardHeight; 
    int boardWidth;
    printf("enter board height ");
    scanf("%i", &boardHeight);
    printf("enter board width ");
    scanf("%i", &boardWidth);
    printf("\n");


    int** board = createBoard(boardHeight, boardWidth);
    
    //user should see board to judge where to put piece
    printBoard(board, boardHeight, boardWidth, 1, 2);

    int position;

    int hasWon = 0; 
    int redTurn = 0;
    int pieces[] = {1,2};
    const char *color[2] = {"BLUE", "RED"};

    while(!hasWon)
    {
    
        printf("%s where will you put your piece? (%i - %i) ", color[redTurn], 1, boardWidth);
        scanf("%i", &position);
        //player puts for eg 1-10 we want 0-9
        position--;
        int moveLocationRow = placePiece(board, boardHeight, boardWidth, position, pieces[redTurn]);
        if(moveLocationRow != -1)
        {
            printBoard(board, boardHeight, boardWidth, 1, 2);
            hasWon = hasConnectedFour(board, boardHeight, boardWidth, moveLocationRow, position);
            redTurn = !redTurn;
        } else {
            printf("couldn't place piece at specified position\n");
        }
    }

        printf("%s won!\n",color[!redTurn]);

        //don't really need to free
        //does free() reculsively free?
        for(int i = 0; i < boardHeight; i++)
        {
            free(*(board + i));
        }
        free(board);
}

int** createBoard(int height, int width)
{
    int** board = (int**)malloc(height * sizeof(int*));

    for(int i = 0; i < height; i++)
    *(board + i) = (int*)malloc(width * sizeof(int));

    return board;
}

int placePiece(int** board, int boardHeight, int boardWidth, int position, int pieceType)
{
    //tying to place piece off board.
    if(position < 0 || position >= boardWidth)
        return -1;
    

    for(int i = 0; i < boardHeight; i++)
    {
        //can place
        if(*(*(board + boardHeight -  1 - i) + position) == 0)
        {
            *(*(board + boardHeight - 1 - i) + position) = pieceType;
            return boardHeight - 1 - i;
        }
    }
    //piece could not be placed (because it would go off the board vertically)
    return -1;
}

void printBoard(int** board, int boardHeight, int boardWidth, int type1, int type2)
{
    for(int i = 0; i < boardHeight; i++)
    {
        for(int j = 0; j < boardWidth; j++)
        {
            int currentChar = *(*(board + i) + j);

            //get the right color for the pieces
            if(currentChar == type1)
                printf(ANSI_COLOR_BLUE "0 " ANSI_COLOR_RESET);
            else if(currentChar == type2)
                printf(ANSI_COLOR_RED "0 " ANSI_COLOR_RESET );
            else 
                printf("o ");

        }
        printf("\n");
    }

    for(int i = 1; i <= boardWidth; i++)
    {
        printf("%i ", i); 
    }
    printf("\n");
    printf("\n");
}

//this function sucks.
int hasConnectedFour(int** board, int boardHeight, int boardWidth, int row, int col)
{
    //read the type of piece to check against.
    int pieceType = *(*(board + row) + col);
    //for moving straight up, diagonal up, to the right, and down and to the right.
    int rows[] = {-1,-1, 0, 1};
    int cols[] = { 0, 1, 1, 1};

    if(!isOnBoard(boardHeight, boardWidth, row, col))
        return -1;

    for(int i = 0; i < 4; i++)
    {
        int count = 0;
        for(int j = 1; j < 4; j++)
        {
            int colOffset= j * cols[i];
            int rowOffset = j * rows[i];

            if(!isOnBoard(boardHeight, boardWidth, row + rowOffset, col + colOffset)) 
                break;


            if(*(*(board + row + rowOffset) + col + colOffset) == pieceType)
                count++;
            else
                break;
        }

        for(int j = 1; j < 4; j++)
        {
            int colOffset= j * -cols[i];
            int rowOffset = j * -rows[i];

            if(!isOnBoard(boardHeight, boardWidth, row + rowOffset, col + colOffset)) 
                break;

            if(*(*(board + row + rowOffset) + col + colOffset) == pieceType)
                count++;
            else
                break;
        }

        if(count >= 3)
            return 1;


    }
    return 0;

}

int isOnBoard(int boardHeight, int boardWidth, int row, int col)
{
    if(row >= boardHeight || row < 0)
        return 0;
    if(col >= boardWidth || col < 0)
        return 0;

    return 1;
}
