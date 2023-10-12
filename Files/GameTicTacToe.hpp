#include <iostream>
#include <stdlib.h>
#include <string>

#define BOARD_SIZE 3
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"

class GameTicTacToe
{
    private:

    typedef struct Player
    {
        string name;
        int id;
        int points;
        char visual;
    }Player;

    bool isGameplay;
    Player player1, player2;

    int** board;
    int remainingMovements;

    void PlayerSetter(Player* pl, int id,char visual)
    {
        pl->id=id;
        pl->points = 0;
        pl->visual = visual;
        cout << "Insira o nome do jogador "<<id<<"\n";
        cin >> pl->name;
        pl->name[0] = toupper(pl->name[0]);
    }
    void AddToBoard(Player pl)
    {
        bool invalid = false;
        do
        {
            cout << "\n"<< pl.name<<", ";
            cout << "insira linha e coluna\nExemplo: 1 2. Linha 1, coluna 2\n";
            int row=-1, col=-1;
            cin >> row >> col;

            if(cin.fail())
            {
                cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                invalid = true;
                cout << "Input invalido. Por favor, insira dois numeros.\n";
                continue;
            }

            invalid = row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col]!=0;

            if(invalid)
                cout << "Posicao ja preenchida ou fora dos limites. Tente novamente.\n";
            else
                board[row][col] = pl.id;
        } while (invalid);
        remainingMovements--;
    }
    void ClearBoard()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board[i][j] = 0;
            }
        }
        remainingMovements = BOARD_SIZE*BOARD_SIZE;
    }
    void DrawBoard()
    {
        string emptyText = "    ";
        cout << emptyText;
        //header
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            cout << i<< "   ";
        }
        cout <<"\n"<< emptyText;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            cout << "|   ";
        }
        cout <<"\n";
        
        //header

        string txtToDraw = "";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            txtToDraw+=to_string(x);
            txtToDraw+="--";
            txtToDraw+= UNDERLINE;
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                txtToDraw+=" ";
                if(board[x][y] == player1.id)
                    txtToDraw+=player1.visual;
                else if(board[x][y] == player2.id)
                    txtToDraw+=player2.visual;
                else 
                    txtToDraw+=" ";

                if (y < BOARD_SIZE)
                {
                    txtToDraw+=" |";
                }
                
            }
            txtToDraw+= CLOSEUNDERLINE;
            txtToDraw+="\n";
        }
        cout << txtToDraw;
        
    }
    void VerifyVictory(Player pl)
    {
        //horizontal checker
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            int counter = 0;
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                if(board[x][y]!=pl.id)
                    break;
                else counter++;

                if(counter==BOARD_SIZE)
                {
                    GameOver(pl);
                    return;
                }
            }
        }
        //horizontal checker

        //vertical checker
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            int counter = 0;
            for (int x = 0; x < BOARD_SIZE; x++)
            {
                if(board[x][y]!=pl.id)
                    break;
                else counter++;

                if(counter==BOARD_SIZE)
                {
                    GameOver(pl);
                    return;
                }
            }
        }
        //vertical checker

        if(board[0][0] == pl.id && board[1][1] == pl.id && board[2][2] == pl.id)
        {
            GameOver(pl);
            return;
        }
        else if(board[2][0] == pl.id && board[1][1] == pl.id && board[0][2] == pl.id)
        {
            GameOver(pl);
            return;
        }
        else
        {
            //welp, the game continues
            //nothing here
        }
        
    }
    void GameOver()
    {
        system(CLEAR_SCREEN);
        DrawBoard();
        cout << "\nGameOver! Deu velha";
        isGameplay = false;
    }
    void GameOver(Player winner)
    {
        system(CLEAR_SCREEN);
        DrawBoard();
        cout << "\nGameOver! ";
        cout << winner.name << " venceu!";
        isGameplay = false;
    }
    void Gameloop()
    {
        bool player1Turn=true;
        while (isGameplay)
        {
            if(remainingMovements<=0)
            {
                GameOver();
                return;
            }

            Player tgPlayer = player1Turn? player1: player2;
            
            AddToBoard(tgPlayer);
            VerifyVictory(tgPlayer);

            if(!isGameplay)return;

            player1Turn = !player1Turn;

            system(CLEAR_SCREEN);
            DrawBoard();
        }
    }

    public:
    GameTicTacToe()
    {
        isGameplay = true;

        board = new int*[BOARD_SIZE];
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            board[i] = new int[BOARD_SIZE];
        }
        
        PlayerSetter(&player1,1,'X');
        PlayerSetter(&player2,2,'O');
        
        system(CLEAR_SCREEN);
        ClearBoard();
        DrawBoard();
        Gameloop();
    }
    ~GameTicTacToe()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            delete board[i];
        }
        delete board;
    }
};