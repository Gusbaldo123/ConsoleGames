#include <iostream>
#include <string>
#include <new>
#include <stdlib.h>
#include "GameGallows.hpp"

#ifdef _WIN32
#define CLEAR_SCREEN "CLS"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

void ClearScreen();
void About();
void WaitForEnter();

void Menu();

int main()
{
    srand(time(NULL));
    Menu();
    return 0;
}
void ClearScreen()
{
    system(CLEAR_SCREEN);
}
void PlayGallows()
{
    GameGallows game;
    WaitForEnter();
}
void PlayNavalBattle()
{
    //TODO: Implement Naval Battle game
}
void PlayTicTacToe()
{
    //TODO: Implement TicTacToe game
}
void About()
{
    cout << "Criado por Gusbaldo\n";
    cout << "Github:\nhttps://github.com/Gusbaldo123";
    WaitForEnter();
}
void WaitForEnter()
{
    cout << "\nPressione ENTER para continuar...";
    cin.ignore();  // Descarta o '\n' anterior
    cin.get();     // Aguarda até ENTER ser pressionado
}
void Menu()
{
    bool willLoop = true;

    do
    {
        ClearScreen();

        cout << "Selecione uma opcao\n1- Jogar Forca\n2- Jogar Batalha Naval\n3- Jogo da velha\n4- Sobre\n5- Sair";
        cout << "\n";
        int selOpt = -1;
        cin >> selOpt;

        switch (selOpt)
        {
            case 1:
                PlayGallows();
                break;
            case 2:
                PlayNavalBattle();
                break;
            case 3:
                PlayTicTacToe();
                break;
            case 4:
                About();
                break;
            case 5:
                willLoop = false;
                ClearScreen();
                cout << "Fechando o programa...";
                break;
            
            default:
                cout << "Opcao Invalida\n";
                break;
        }
    } while (willLoop);
    
}