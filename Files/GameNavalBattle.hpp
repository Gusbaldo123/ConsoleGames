#include <windows.h>   // WinApi header
#include <iostream>
#include <string>
#include <limits>

#define DEFAULT_COLOR 7 // Default console color
#define WATER_COLOR 23 // When drawing water, use this color
#define EXPLOSION_COLOR 20 // When hit the ship, red explosion on blue water
#define TABLE_SIZE 10
#define TOTAL_SHIPS 25
#define CHEAT_MODE false

using namespace std;

class GameNavalBattle
{
private:
    int temp = 0, shipsRemaining = 0;
    HANDLE hConsole;
    string savedMessage;

    bool** tableAttempted;
    bool** tableResult;
    bool isGameplay;

    void DrawTable()
    {
        //Drawing header
        string emptyText = "    ";
        cout << emptyText;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << i<<" ";
        }
        cout <<"\n"<< emptyText;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << "| ";
        }
        cout<<"\n";
        //Drawing header
         
        //Drawing table
        char unknowShot = '?', hitShot = '#',missShot = ' ';

        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << i << " - ";
            for (int j = 0; j < TABLE_SIZE; j++)
            {
                if(tableAttempted[i][j] && tableResult[i][j])
                {
                    SetConsoleTextAttribute(hConsole,EXPLOSION_COLOR);
                    cout << hitShot << " ";
                }
                else if(tableAttempted[i][j] && !tableResult[i][j])
                {
                    SetConsoleTextAttribute(hConsole,WATER_COLOR);
                    cout << missShot << " ";
                }
                else
                {
                    SetConsoleTextAttribute(hConsole,WATER_COLOR);
                    cout << unknowShot << " ";
                }
            }
            cout << "\n";
            SetConsoleTextAttribute(hConsole,DEFAULT_COLOR);
        }
        //Drawing table
        CheatDrawResults();

        cout << shipsRemaining << " navios sobrando\n";
    }
    void CheatDrawResults()
    {
        if(!CHEAT_MODE) return;

        for (int i = 0; i < TABLE_SIZE; i++)
        {
            for (int j = 0; j < TABLE_SIZE; j++)
            {
                if(tableResult[i][j])
                    cout << "x ";
                else cout <<"o ";
            }
            cout << "\n";
        }
    }
    void ClearArray(bool** &array)
    {
        DeleteArray(array);
        AllocateArray(array);
    }
    void DeleteArray(bool** &array)
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            delete[] array[i];
        }
        delete[] array;
    }
    void AllocateArray(bool** &array)
    {
        array = new bool*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            array[i] = new bool[TABLE_SIZE];
            for (int j = 0; j < TABLE_SIZE; j++)
            {
                array[i][j] = false;
            }
        }
    }
    void RandomizeTableResult()
    {
        int insertedResults = 0;
        shipsRemaining = TOTAL_SHIPS;

        while (insertedResults<TOTAL_SHIPS)
        {
            int row = rand()%TABLE_SIZE;
            int col = rand()%TABLE_SIZE;
            if(!tableResult[row][col])
            {
                tableResult[row][col] = true;
                insertedResults++;
            }
        }
        
    }
    void AttemptPosition()
    {
        bool invalid;
        do
        {
            cout << "\nInsira linha e coluna\nExemplo: 1 5. Linha 1, coluna 5\n";
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

            invalid = row < 0 || row >= TABLE_SIZE || col < 0 || col >= TABLE_SIZE || tableAttempted[row][col];

            if(invalid)
                cout << "Posicao ja preenchida ou fora dos limites. Tente novamente.\n";
            else
                tableAttempted[row][col] = true;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(tableAttempted[row][col] == tableResult[row][col])
            {
                shipsRemaining--;
                savedMessage+="Voce acertou!\n";
            }
            else savedMessage+="Voce errou\n";

            if(shipsRemaining<=0)
                GameOver();

        } while (invalid);
    }
    void GameOver()
    {
        system(CLEAR_SCREEN);
        cout << "\nFim de jogo, voce venceu!";
        isGameplay = false;
    }
    void GameLoop()
    {
        do
        {
            system(CLEAR_SCREEN);
            DrawTable();
            PrintSavedText();
            AttemptPosition();
        } while (isGameplay);
    }
    void PrintSavedText()
    {
        cout << savedMessage << "\n";
        savedMessage = "";
    }
public:
    GameNavalBattle()
    {
        isGameplay = true;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        AllocateArray(tableAttempted);
        AllocateArray(tableResult);
        RandomizeTableResult();
        
        GameLoop();
    }

    ~GameNavalBattle()
    {
        hConsole = nullptr;
        DeleteArray(tableAttempted);
        DeleteArray(tableResult);
    }
};