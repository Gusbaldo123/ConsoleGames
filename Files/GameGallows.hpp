#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <new>

#ifdef _WIN32
#define CLEAR_SCREEN "CLS"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

class GameGallows
{
    private:
    bool isGameplay;
    string chosenText, savedText, usedLetters, mountedLetters;
    int remainingLetters = 0, remainingTries = 0;
    const string Possibilities[30] = {"rosa", "peixe", "pintor","casaco","oito","morango","laranja","flores", "parede","folha","mirtilo","sementes","figo","pera","groselha","morango","melancia","pepino","acelga","cenoura","tatu","cabra","coruja","sardinha","urso","dragao","gorila","formiga","ganso","crocodilo"};

    void UseCharacter(char _chosenChar)
    {
        if(ContainsCharInString(_chosenChar, usedLetters))
        {
            savedText += "Letra ja utilizada !\n";
            return;
        }
        
        usedLetters += _chosenChar;  // Adicione o caractere diretamente

        if(ContainsCharInString(_chosenChar, chosenText))
            MountCharacters(_chosenChar);
        else MissLetter();
    }
    void UseFullWord(string _chosenWord)
    {
        remainingTries = 0;
        GameOver(chosenText==_chosenWord);
    }
    bool ContainsCharInString(char _chosenChar, string _targetString)
    {
        int size = _targetString.size();
        if(size<=0) return false;
        for (int i = 0; i < size; i++)
        {
            if(_targetString[i] == _chosenChar) return true;
        }
        return false;
    }
    void MissLetter()
    {
        remainingTries--;
        if(remainingTries<=0)
        {
            GameOver(false);
        }
        else
        {
            savedText+="Letra errada! Voce ainda tem ";
            savedText+= to_string(remainingTries);
            savedText+= " tentativas\n";
        }
    }
    void MountCharacters(char _chosenChar)
    {
        for (int i = 0; i < chosenText.size(); i++)
        {
            if(chosenText[i] == _chosenChar)
            {
                mountedLetters[i] = chosenText[i];
                remainingLetters--;
                if(remainingLetters<=0)
                    GameOver(true);
            }
        }
    }
    void GameOver(bool _win)
    {
        system(CLEAR_SCREEN);
        cout << "Fim de jogo, ";
        if(_win)
            cout << "voce ganhou! :D";
        else cout << "voce perdeu...";
        cout << "\nA palavra era "<< chosenText;

        isGameplay = false;
    }
    void PrintMountedLetters()
    {
        for (int i = 0; i < mountedLetters.size(); i++)
        {
            cout << mountedLetters[i];
            if(i<mountedLetters.size()) cout<< " ";
        }
        cout <<"\n";
    }
    void PrintUsedLetters()
    {
        cout <<"\n";
        for (int i = 0; i < usedLetters.size(); i++)
        {
            cout << usedLetters[i];
            if(i<usedLetters.size()) cout<< "-";
        }
        cout <<"\n";
    }
    void PrintSavedText()
    {
        cout << savedText << "\n";
        savedText = "";
    }
    void TryGuess()
    {
        cout << "Digite uma letra\nVoce tambem pode tentar sacrificar todas as vidas para tentar uma palavra completa\n";
        string playerTry;
        cin >> playerTry;

        for (int i = 0; i < playerTry.size(); i++)
        {
            playerTry[i] = tolower(playerTry[i]);
        }

        if(playerTry.size() == 1)
            UseCharacter(playerTry[0]);
        else
            UseFullWord(playerTry);
    }
    void GameLoop()
    {
        isGameplay = true;
        do
        {
            system(CLEAR_SCREEN);
            PrintMountedLetters();
            PrintUsedLetters();
            PrintSavedText();
            TryGuess();
        } while (isGameplay);
        
    }
    void Singleplayer() // Singleplayer
    {
        chosenText = Possibilities[rand()%30];
        for (int i = 0; i < chosenText.size(); i++)
        {
            chosenText[i] = tolower(chosenText[i]);
        }
        
        mountedLetters = string(chosenText.size(), '-');
        
        remainingLetters = chosenText.size();
        remainingTries = 5;
        GameLoop();
    }
    void Multiplayer(string _chosenText) // Multiplayer
    {
        chosenText = _chosenText;
        for (int i = 0; i < chosenText.size(); i++)
        {
            chosenText[i] = tolower(chosenText[i]);
        }
        
        mountedLetters = string(chosenText.size(), '-');

        remainingLetters = chosenText.size();
        remainingTries = 5;
        GameLoop();
    }

    public:
    GameGallows() // Constructor
    {
        bool isInvalid;
        int gameMode = -1;
        do
        {
            system(CLEAR_SCREEN);
            cout << "Vamos jogar!\nAperte 1 - Singleplayer\nAperte 2 - Multiplayer\n";
            cin >> gameMode;

            if (gameMode == 1)
            {
                Singleplayer();
                isInvalid = false;
            }
            else if (gameMode == 2)
            {
                system(CLEAR_SCREEN);
                string chosenText;
                cout << "Insira uma palavra para o multiplayer\n";
                cin >> chosenText;
                Multiplayer(chosenText);
                isInvalid = false;
            }
            else
            {
                isInvalid = true;
            }
        } while (isInvalid);
    }
};