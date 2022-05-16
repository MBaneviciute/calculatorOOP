#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "Calculator.h"
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HWND button;  // variable for all the buttons
HWND textBox; // variable for textbox
string savedText;
string answerText; //  this probably should be the answer string or we could just overwrite the savedText string :)

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("KILL ME NOW PLZ"), /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           500,                 /* The programs width */
           500,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        // creating textBoxW
        textBox = CreateWindow ("STATIC",
                                "",
                                WS_BORDER | WS_CHILD | WS_VISIBLE,
                                20,100,400,30,
                                hwnd, NULL, NULL, NULL);

        // creating buttons
        button = CreateWindow ("BUTTON",
                             "0",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,410,130,20,
                             hwnd, (HMENU) 0, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "1",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,380,50,20,
                             hwnd, (HMENU) 1, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "2",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,380,50,20,
                             hwnd, (HMENU) 2, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "3",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,380,50,20,
                             hwnd, (HMENU) 3, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "4",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,350,50,20,
                             hwnd, (HMENU) 4, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "5",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,350,50,20,
                             hwnd, (HMENU) 5, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "6",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,350,50,20,
                             hwnd, (HMENU) 6, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "7",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,320,50,20,
                             hwnd, (HMENU) 7, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "8",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,320,50,20,
                             hwnd, (HMENU) 8, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "9",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,320,50,20,
                             hwnd, (HMENU) 9, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "(",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,290,50,20,
                             hwnd, (HMENU) 10, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             ")",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,290,50,20,
                             hwnd, (HMENU) 11, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "/",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,290,50,20,
                             hwnd, (HMENU) 12, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "*",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,320,50,20,
                             hwnd, (HMENU) 13, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "-",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,350,50,20,
                             hwnd, (HMENU) 14, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "+",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,380,50,20,
                             hwnd, (HMENU) 15, NULL, NULL );
                             //break;
        button = CreateWindow ("BUTTON",
                             "=",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,410,130,20,
                             hwnd, (HMENU) 18, NULL, NULL );
                             
        button = CreateWindow ("BUTTON",
                            "C",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,290,50,20,
                             hwnd, (HMENU) 16, NULL, NULL );
                             
        button = CreateWindow ("BUTTON",
                            "(-)",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             340,290,50,20,
                             hwnd, (HMENU) 17, NULL, NULL );
                             break;

        case WM_COMMAND:
            SetFocus(hwnd);
            switch (LOWORD(wParam))
            {
                case 0:
                    //code for button 0
                    ///::MessageBox(hwnd,"Button 0","was clicked",MB_OK);  // JUST CHECKED IF BUTTON WORKS
                    savedText += "0";
                    SetWindowText(textBox,savedText.c_str());
                    break;



                case 1:
                    //code for button 1
                    savedText += "1";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 2:
                    //code for button 2
                    savedText += "2";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 3:
                    //code for button 3
                    savedText += "3";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 4:
                    //code for button 4
                    savedText += "4";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 5:
                    //code for button 5
                    savedText += "5";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 6:
                    //code for button 6
                    savedText += "6";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 7:
                    //code for button 7
                    savedText += "7";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 8:
                    //code for button 8
                    savedText += "8";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 9:
                    //code for button 9
                    savedText += "9";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 10:
                    //code for button 10 (
                    savedText += "(";
                    SetWindowText(textBox,savedText.c_str());
                    break;


                case 11:
                    //code for button 11 )
                    savedText += ")";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 12:
                    //code for button 12 /
                    savedText += "/";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 13:
                    //code for button 13 x
                    savedText += "*";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 14:
                    //code for button 14 -
                    savedText += " - ";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 15:
                    //code for button 15 +
                    savedText += " + ";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 16:
                    //code for button 16 C
                    // savedText += "+";
                    // SetWindowText(textBox,savedText.c_str());
                    answerText = "";
                    savedText = "";
                    SetWindowText(textBox, answerText.c_str());
                    break;
                 case 17:
                    //code for button 17 (-)
                    savedText += "-";
                    SetWindowText(textBox,savedText.c_str());
                    break;

                case 18:
                    //code for button 18 =
                    //savedText += "=";
                    //SetWindowText(textBox,savedText.c_str());
                    //const char * c = savedText.c_str();
                    shutingYard::RPN rpn = shutingYard::reversePolishNotation(savedText.c_str());
	                shutingYard::Node* tree = shutingYard::parse(rpn);
                    //cout<< savedText << "= " << shutingYard::eval(tree) << endl;
                    double a = shutingYard::eval(tree);
                    answerText = to_string(a);
                    SetWindowText(textBox, answerText.c_str());
                    //(-)
                    //-
                    break;

                    return DefWindowProc (hwnd, message, wParam, lParam);
            }
        break;


        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

