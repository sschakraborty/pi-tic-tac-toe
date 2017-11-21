#include <iostream>
#include <math.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include<wx/app.h>
#include<wx/frame.h>
#include<wx/menu.h>
#include<wx/statusbr.h>
#include<wx/msgdlg.h>
#include<wx/button.h>

#define __GXX_ABI_VERSION 1010

namespace Generic {
    // Generic Algorithm Name-space
    bool tickO = true;
    bool is_bot_game = false;

    bool has_more_moves(wxString arr[3][3]) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(arr[i][j] == "-")
                    return true;
            }
        }
        return false;
    }

    wxString bot = "X", opponent = "O";

    struct pos {
        int x, y;
    };

    int evaluate(wxString b[3][3]) {
        for(int row = 0; row < 3; row++) {
            if(b[row][0] == bot && b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
                return 10;
            }
            if(b[row][0] == opponent && b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
                return -10;
            }
        }

        for(int col = 0; col < 3; col++) {
            if(b[0][col] == bot && b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
                return 10;
            }
            if(b[0][col] == opponent && b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
                return -10;
            }
        }

        if(b[0][0] == bot && b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
            return 10;
        }

        if(b[0][0] == opponent && b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
            return -10;
        }

        if(b[0][2] == bot && b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
            return 10;
        }

        if(b[0][2] == opponent && b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
            return -10;
        }

        return 0;
    }

    int minimax(wxString board[3][3], bool isMax) {
        int score = evaluate(board);
        if (score == 10 || score == -10)
            return score;
        if (has_more_moves(board) == false)
            return 0;
        if (isMax) {
            int best = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if(board[i][j] == "-") {
                        board[i][j] = bot;
                        best = std::max(best, minimax(board, !isMax));
                        board[i][j] = "-";
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if(board[i][j] == "-") {
                        board[i][j] = opponent;
                        best = std::min(best, minimax(board, !isMax));
                        board[i][j] = "-";
                    }
                }
            }
            return best;
        }
    }

    pos findBestMove(wxString board[3][3]) {
        int bestVal = -1000;
        pos bestMove;
        bestMove.x = -1;
        bestMove.y = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == "-") {
                    board[i][j] = bot;
                    int moveVal = minimax(board, false);
                    board[i][j] = "-";
                    if (moveVal > bestVal) {
                        bestMove.x = i;
                        bestMove.y = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        // printf("The value of the best Move is : %d\n", bestVal);
        // printf("The value of the best Move is : %d\n", bestMove.x);
        // printf("The value of the best Move is : %d\n", bestMove.y);
        return bestMove;
    }
};

class MyApp : public wxApp {
    public:
        virtual bool OnInit();
};

class MyFrame : public wxFrame {
    public:
        MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    private:
        wxButton* b[3][3];

        void OnNewManualGame(wxCommandEvent& event);
        void OnNewBotGame(wxCommandEvent& event);
        void ResetGame();
        void makeMove();
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void BotResetGame() {
            Generic::tickO = !Generic::tickO;
            MyFrame::ResetGame();
            Generic::is_bot_game = true;
            if(!Generic::tickO) {
                makeMove();
            }
        }
        void CheckForWin(int, int);

        void Button_11_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[0][0] -> SetLabel("O");
            } else {
                b[0][0] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[0][0] -> Enable(false);
            CheckForWin(0, 0);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_12_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[0][1] -> SetLabel("O");
            } else {
                b[0][1] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[0][1] -> Enable(false);
            CheckForWin(0, 1);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_13_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[0][2] -> SetLabel("O");
            } else {
                b[0][2] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[0][2] -> Enable(false);
            CheckForWin(0, 2);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_21_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[1][0] -> SetLabel("O");
            } else {
                b[1][0] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[1][0] -> Enable(false);
            CheckForWin(1, 0);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_22_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[1][1] -> SetLabel("O");
            } else {
                b[1][1] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[1][1] -> Enable(false);
            CheckForWin(1, 1);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_23_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[1][2] -> SetLabel("O");
            } else {
                b[1][2] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[1][2] -> Enable(false);
            CheckForWin(1, 2);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_31_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[2][0] -> SetLabel("O");
            } else {
                b[2][0] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[2][0] -> Enable(false);
            CheckForWin(2, 0);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_32_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[2][1] -> SetLabel("O");
            } else {
                b[2][1] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[2][1] -> Enable(false);
            CheckForWin(2, 1);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        void Button_33_Event(wxCommandEvent& e) {
            if(Generic::tickO) {
                b[2][2] -> SetLabel("O");
            } else {
                b[2][2] -> SetLabel("X");
            }
            Generic::tickO = !Generic::tickO;
            b[2][2] -> Enable(false);
            CheckForWin(2, 2);

            if(Generic::is_bot_game && !Generic::tickO) {
                makeMove();
            }
        }

        wxDECLARE_EVENT_TABLE();
};

void MyFrame::CheckForWin(int x, int y) {
    bool win = true;
    for(int i = 0; i < 3; i++) {
        if(!((b[x][i] -> GetLabel()) == (b[x][y] -> GetLabel()))) {
            win = false;
            break;
        }
    }
    if(win) {
        if(Generic::is_bot_game && !Generic::tickO) {
            wxMessageBox("You Win", "Win", wxOK | wxICON_INFORMATION);
            BotResetGame();
        } else if(Generic::is_bot_game && Generic::tickO) {
            wxMessageBox("Bot Wins", "Win", wxOK | wxICON_INFORMATION);
            BotResetGame();
        } else {
            wxMessageBox("Winner", "Win", wxOK | wxICON_INFORMATION);
            ResetGame();
        }
        return;
    }

    win = true;
    for(int i = 0; i < 3; i++) {
        if(!((b[i][y] -> GetLabel()) == (b[x][y] -> GetLabel()))) {
            win = false;
            break;
        }
    }
    if(win) {
        if(Generic::is_bot_game && !Generic::tickO) {
            wxMessageBox("You Win", "Win", wxOK | wxICON_INFORMATION);
            BotResetGame();
        } else if(Generic::is_bot_game && Generic::tickO) {
            wxMessageBox("Bot Wins", "Win", wxOK | wxICON_INFORMATION);
            BotResetGame();
        } else {
            wxMessageBox("Winner", "Win", wxOK | wxICON_INFORMATION);
            ResetGame();
        }
        return;
    }

    if(x == y) {
        win = true;
        for(int i = 0; i < 3; i++) {
            if(!((b[i][i] -> GetLabel()) == (b[x][y] -> GetLabel()))) {
                win = false;
                break;
            }
        }
        if(win) {
            if(Generic::is_bot_game && !Generic::tickO) {
                wxMessageBox("You Win", "Win", wxOK | wxICON_INFORMATION);
                BotResetGame();
            } else if(Generic::is_bot_game && Generic::tickO) {
                wxMessageBox("Bot Wins", "Win", wxOK | wxICON_INFORMATION);
                BotResetGame();
            } else {
                wxMessageBox("Winner", "Win", wxOK | wxICON_INFORMATION);
                ResetGame();
            }
            return;
        }
    }
    if(x == (2 - y)) {
        win = true;
        for(int i = 0; i < 3; i++) {
            if(!((b[i][2 - i] -> GetLabel()) == (b[x][y] -> GetLabel()))) {
                win = false;
                break;
            }
        }
        if(win) {
            if(Generic::is_bot_game && !Generic::tickO) {
                wxMessageBox("You Win", "Win", wxOK | wxICON_INFORMATION);
                BotResetGame();
            } else if(Generic::is_bot_game && Generic::tickO) {
                wxMessageBox("Bot Wins", "Win", wxOK | wxICON_INFORMATION);
                BotResetGame();
            } else {
                wxMessageBox("Winner", "Win", wxOK | wxICON_INFORMATION);
                ResetGame();
            }
            return;
        }
    }
}

void MyFrame::makeMove() {
    wxString bx[3][3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            bx[i][j] = b[i][j] -> GetLabel();
        }
    }
    Generic::pos p = Generic::findBestMove(bx);
    if(p.x < 0 || p.y < 0) return;
    b[p.x][p.y] -> SetLabel(Generic::bot);
    b[p.x][p.y] -> Enable(false);
    Generic::tickO = !Generic::tickO;
    MyFrame::CheckForWin(p.x, p.y);
}

void MyFrame::OnNewBotGame(wxCommandEvent& event) {
    Generic::tickO = !Generic::tickO;
    MyFrame::ResetGame();
    Generic::is_bot_game = true;
    if(!Generic::tickO) {
        makeMove();
    }
}

enum {
    ID_New_Manual,
    ID_New_Bot,
    Button_11,
    Button_12,
    Button_13,
    Button_21,
    Button_22,
    Button_23,
    Button_31,
    Button_32,
    Button_33
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_New_Manual, MyFrame::OnNewManualGame)
    EVT_MENU(ID_New_Bot, MyFrame::OnNewBotGame)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_BUTTON(Button_11, MyFrame::Button_11_Event)
    EVT_BUTTON(Button_12, MyFrame::Button_12_Event)
    EVT_BUTTON(Button_13, MyFrame::Button_13_Event)
    EVT_BUTTON(Button_21, MyFrame::Button_21_Event)
    EVT_BUTTON(Button_22, MyFrame::Button_22_Event)
    EVT_BUTTON(Button_23, MyFrame::Button_23_Event)
    EVT_BUTTON(Button_31, MyFrame::Button_31_Event)
    EVT_BUTTON(Button_32, MyFrame::Button_32_Event)
    EVT_BUTTON(Button_33, MyFrame::Button_33_Event)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("pi-tic-tac-toe", wxPoint(400, 150), wxSize(320, 380));
    frame -> Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size) {
    // Disable resizing
    SetMinSize(GetSize());
    SetMaxSize(GetSize());

    wxMenu *menuGame = new wxMenu;
    menuGame->Append(ID_New_Manual, "New Manual Game",
                     "A normal 2-player game");
    menuGame->AppendSeparator();
    menuGame->Append(ID_New_Bot, "New Bot Game",
                     "A game with pi bot");
    menuGame->AppendSeparator();
    menuGame->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuGame, "&Game Menu");
    menuBar->Append(menuHelp, "&Help");

    // Create a new button and add it to frame
    wxFont font(32, wxFONTFAMILY_DEFAULT, wxNORMAL, wxNORMAL);

    b[0][0] = new wxButton(this, Button_11, "-", wxPoint(10, 10), wxSize(100, 100));
    b[0][0] -> SetFont(font);

    b[0][1] = new wxButton(this, Button_12, "-", wxPoint(110, 10), wxSize(100, 100));
    b[0][1] -> SetFont(font);

    b[0][2] = new wxButton(this, Button_13, "-", wxPoint(210, 10), wxSize(100, 100));
    b[0][2] -> SetFont(font);

    b[1][0] = new wxButton(this, Button_21, "-", wxPoint(10, 110), wxSize(100, 100));
    b[1][0] -> SetFont(font);

    b[1][1] = new wxButton(this, Button_22, "-", wxPoint(110, 110), wxSize(100, 100));
    b[1][1] -> SetFont(font);

    b[1][2] = new wxButton(this, Button_23, "-", wxPoint(210, 110), wxSize(100, 100));
    b[1][2] -> SetFont(font);

    b[2][0] = new wxButton(this, Button_31, "-", wxPoint(10, 210), wxSize(100, 100));
    b[2][0] -> SetFont(font);

    b[2][1] = new wxButton(this, Button_32, "-", wxPoint(110, 210), wxSize(100, 100));
    b[2][1] -> SetFont(font);

    b[2][2] = new wxButton(this, Button_33, "-", wxPoint(210, 210), wxSize(100, 100));
    b[2][2] -> SetFont(font);

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("pi-tic-tac-toe / Start with O");
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(" Dev: Subhadra S. Chakraborty \n Dev-alias: pi (2017) \n Version: pi-tic-tac-toe 0.1.1 \n License: Apache/2 Open Source",
                  "About", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnNewManualGame(wxCommandEvent& event)
{
    ResetGame();
}

void MyFrame::ResetGame() {
    b[0][0] -> SetLabel("-");
    b[0][0] -> Enable(true);

    b[0][1] -> SetLabel("-");
    b[0][1] -> Enable(true);

    b[0][2] -> SetLabel("-");
    b[0][2] -> Enable(true);

    b[1][0] -> SetLabel("-");
    b[1][0] -> Enable(true);

    b[1][1] -> SetLabel("-");
    b[1][1] -> Enable(true);

    b[1][2] -> SetLabel("-");
    b[1][2] -> Enable(true);

    b[2][0] -> SetLabel("-");
    b[2][0] -> Enable(true);

    b[2][1] -> SetLabel("-");
    b[2][1] -> Enable(true);

    b[2][2] -> SetLabel("-");
    b[2][2] -> Enable(true);

    if(Generic::tickO) {
        SetStatusText("pi-tic-tac-toe / Start with O");
    } else {
        SetStatusText("pi-tic-tac-toe / Start with X");
    }

    Generic::is_bot_game = false;
}
