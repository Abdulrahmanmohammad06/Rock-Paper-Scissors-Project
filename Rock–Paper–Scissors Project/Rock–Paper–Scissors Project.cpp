
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip> 
using namespace std;

enum enGameChoices { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    short RoundNumber = 0;
    enGameChoices PlayerChoice;
    enGameChoices ComputerChoice;
    enWinner Winner;
    string WinnerName = "";
};

struct stGameResults {
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

string WinnerName(enWinner Winner) {
    string ArrWinnerName[3] = { "Player","Computer","Draw" };
    return ArrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoices Choice) {
    string ArrChoiceName[3] = { "Rock","Paper","Scissors" };
    return ArrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner) {
    switch (Winner) {
    case enWinner::Player:
        system("color 2F"); 
        break;
    case enWinner::Computer:
        system("color 4F"); 
        cout << "\a";
        break;
    case enWinner::Draw:
        system("color 6F"); 
        break;
    }
}

void PrintRoundResult(stRoundInfo Info) {
    cout << "\n____________ Round [" << Info.RoundNumber << "] ____________\n\n";
    cout << "Player Choice  : " << ChoiceName(Info.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(Info.ComputerChoice) << endl;
    cout << "Round Winner   : [" << Info.WinnerName << "] \n";
    cout << "__________________________________\n" << endl;
}

enWinner WhoWonTheRound(stRoundInfo Info) {
    if (Info.PlayerChoice == Info.ComputerChoice) {
        return enWinner::Draw;
    }

    switch (Info.PlayerChoice) {
    case enGameChoices::Rock:
        if (Info.ComputerChoice == enGameChoices::Paper) {
            return enWinner::Computer;
        }
        break;
    case enGameChoices::Paper:
        if (Info.ComputerChoice == enGameChoices::Scissors) {
            return enWinner::Computer;
        }
        break;
    case enGameChoices::Scissors:
        if (Info.ComputerChoice == enGameChoices::Rock) {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes) {
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

enGameChoices GetComputerChoice() {
    return (enGameChoices)RandomNumber(1, 3);
}

enGameChoices ReadPlayerChoice() {
    short Choice = 0;
    do {
        cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoices)Choice;
}

stGameResults PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

       
        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
        SetWinnerScreenColor(RoundInfo.Winner);
    }

    return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs) {
    string t = "";
    for (int i = 1; i <= NumberOfTabs; i++) {
        t += "\t";
    }
    return t;
}

void ShowFinalGameResults(stGameResults GameResults) {
    cout << "\n\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 *** G A M E  O V E R *** \n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "------------------- [ Game Results ] ---------------------\n\n";

    cout << Tabs(2) << left << setw(25) << "Game Rounds" << ": " << GameResults.GameRounds << endl;
    cout << Tabs(2) << left << setw(25) << "Player Win Times" << ": " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << left << setw(25) << "Computer Win Times" << ": " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << left << setw(25) << "Draw Times" << ": " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << left << setw(25) << "Final Winner" << ": " << GameResults.WinnerName << endl;

    cout << Tabs(2) << "___________________________________________________________\n\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds() {
    short GameRounds = 1;
    do {
        cout << "How Many Rounds 1 to 10 ? ";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}