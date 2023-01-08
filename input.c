/*
//         .             .              .		    
//         |             |              |           .	    
// ,-. ,-. |-. ,-. . ,-. |  ,_, ,-. ,-. |-. ,-,-. . |- ,_,  
// | | ,-| | | |   | |-' |   /  `-. |   | | | | | | |   /   
// `-| `-^ ^-' '   ' `-' `' '"' `-' `-' ' ' ' ' ' ' `' '"'  
//  ,|							    
//  `'							    
// util.c
*/
#include "util.h"
#include "input.h"
#include "update.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

/* Handle user input and app state */
void handleInputs(appData * app){
    app->userInput = getch();

    switch(app->userInput){
        case ENTER:
            if(app->currentMode == 0){
                if(app->menuPos == 1){
                    app->timer = (app->workTime * 60 * 16);
                    app->frameTimer = 0;
                    app->currentMode = 1;
                    app->pomodoroCounter = app->pomodoroCounter + 1;
                    system("notify-send -t 5000 -c cpomo '華 Work!' 'You need to focus'");
                }
                else if(app->menuPos == 2){
                    app->currentMode = -1;
                    app->menuPos = 1;
                }
                else if(app->menuPos == 3){
                    endwin();
                    exit(EXIT_SUCCESS);
                }
                break;
            }
            else if(app->currentMode == -1){
                if(app->menuPos == 5){
                    app->frameTimer = 0;
                    app->logoFrame = 0;
                    app->currentMode = 0;
                    app->menuPos = 1;
                }
                break;
            }else
                break;

        case KEY_UP:
        case 'K':
        case 'k':
            if(app->menuPos != 1)
                app->menuPos--;
            break;

        case KEY_DOWN:
        case 'J':
        case 'j':
            if(app->currentMode == 0){
                if(app->menuPos != 3)
                    app->menuPos++;
                break;
            }
            if(app->currentMode == -1){
                if(app->menuPos != 5)
                    app->menuPos++;
                break;
            }
            break;

        case KEY_LEFT:
        case 'H':
        case 'h':
            if(app->currentMode == -1){
                if(app->menuPos == 1){
                    if(app->pomodoros != 1)
                        app->pomodoros --;
                }
                else if(app->menuPos == 2){
                    if(app->workTimeLevels != 0){
                        app->workTimeLevels--;
                        app->workTime = app->workTime - 5;
                    }
                }
                else if(app->menuPos == 3){
                    if(app->shortPauseLevels != 0){
                        app->shortPauseLevels --;
                        app->shortPause = app->shortPause - 1;
                    }
                }
                else if(app->menuPos == 4){
                    if(app->longPauseLevels != 0){
                        app->longPauseLevels --;
                        app->longPause = app->longPause - 5;
                    }
                }
                else if(app->menuPos == 5){
                    app->frameTimer = 0;
                    app->logoFrame = 0;
                    app->currentMode = 0;
                    app->menuPos = 1;
                }
                break;
            }
            break;

        case KEY_RIGHT:
        case 'L':
        case 'l':
            if(app->currentMode == 0){
                if(app->menuPos == 1){
                    app->timer = (app->workTime * 60 * 16);
                    app->frameTimer = 0;
                    app->currentMode = 1;
                    app->pomodoroCounter = app->pomodoroCounter + 1;
                    system("notify-send -t 5000 -c cpomo '華 Work!' 'You need to focus'");
                }
                else if(app->menuPos == 2){
                    app->currentMode = -1;
                    app->menuPos = 1;
                }
                else if(app->menuPos == 3){
                    endwin();
                    exit(EXIT_SUCCESS);
                }
                break;
            }
            if(app->currentMode == -1){
                if(app->menuPos == 1){
                    if(app->pomodoros != 8)
                        app->pomodoros++;
                }
                else if(app->menuPos == 2){
                    if(app->workTimeLevels != 9){
                        app->workTimeLevels++;
                        app->workTime = app->workTime + 5;
                    }
                }
                else if(app->menuPos == 3){
                    if(app->shortPauseLevels != 9){
                        app->shortPauseLevels ++;
                        app->shortPause = app->shortPause + 1;
                    }
                }
                else if(app->menuPos == 4){
                    if(app->longPauseLevels != 11){
                        app->longPauseLevels ++;
                        app->longPause = app->longPause + 5;
                    }
                }
                else if(app->menuPos == 5){
                    app->frameTimer = 0;
                    app->logoFrame = 0;
                    app->currentMode = 0;
                    app->menuPos = 1;
                }
                break;
            }
            break;

        case CTRLX:
            if(app->currentMode != 0){
                app->frameTimer = 0;
                app->logoFrame = 0;
                app->currentMode = 0;
                app->menuPos = 1;
                app->pomodoroCounter = 0;
            }
            break;

        case ESC:
        case 'Q':
        case 'q':
            endwin();
            exit(EXIT_SUCCESS);
            break;

        case KEY_RESIZE:
            endwin();
            initScreen();
            getWindowSize(app);
            clear();
            refresh();
            break;
    }

}
