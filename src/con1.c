 #include <stdio.h> 
 #include <stdlib.h> 
 #include <ncurses.h>
 #include <errno.h>
 #include <sys/types.h>
 #include <unistd.h> 
 #include <signal.h>
 #include <string.h>



 WINDOW *big_window;
 
// nasza funkcja dostosowujeca rozmiar

void handle_winch(int sig){
  signal(SIGWINCH, SIG_IGN);

  endwin();
  initscr();
  refresh();
  clear();

  signal(SIGWINCH, handle_winch);
}



 void clean(void)
  {
   endwin();
   system("clear");
  }

// incjalizuje bibloteke ncurses
 void init_ncurses()
  {
   initscr();
   clear();
   start_color();
   init_pair(1, COLOR_WHITE, COLOR_BLUE);
   init_pair(2, COLOR_BLUE, COLOR_WHITE);
   init_pair(3, COLOR_GREEN, COLOR_BLUE);
   init_pair(4, COLOR_CYAN, COLOR_BLUE);
   cbreak();
   keypad(stdscr,TRUE);
   noecho();
   refresh();
   
   curs_set(0);
   big_window = newwin(LINES, COLS, 0, 0);      

   wattron(big_window, COLOR_PAIR(1));

   wbkgdset(big_window, COLOR_PAIR(1));

   wclear(big_window);
   wrefresh(big_window);

   on_exit(clean, NULL);
  }
  
   

 void main( /* argc, argv[] */ )
  {
   int key;

    // tworzymy okno
   init_ncurses();

   // wyswietlenie ramki
   box(big_window, 0, 0);

    // odpowiednik printf
   //mvwprintw(big_window, 10, 20, "wart=%d", 10);

   wattron(big_window, COLOR_PAIR(4));
   wattron(big_window, A_BOLD);
   
   //mvwprintw(big_window, 5, 2, "napis");
   wattroff(big_window, A_BOLD);


   wattroff(big_window, COLOR_PAIR(1));
   wattron(big_window, COLOR_PAIR(2));
     
   //mvwprintw(big_window, 12, 5, "action 1");
   
   wattroff(big_window, COLOR_PAIR(2));
   wattron(big_window, COLOR_PAIR(1));

   //mvwprintw(big_window, 14, 5, "action 2");

   // wrefresh odsiwza zawartosc terminala
   wrefresh(big_window);

    // dopobieraniu znaku bez wyswietlaniu dsipaling char in terminal
   // key must be integrer

   // KEY_DOWN
   // mvwaddch

   // * wsakznik do terminala
   // wspolzedna y
   // wspolrzena x
   // znak wpsiansy
   // ace_
   //ACS_DIAMOND()

   int x = 5;
   int y = 5;
   mvwaddch(big_window, y, x, ACS_DIAMOND);
   while( (key = getch()) != 27 ) // ESC == 27 code
    {
        wclear(big_window);
        box(big_window, 0, 0);
        switch (key)
        {
            case KEY_DOWN:
                y +=1;
                if( y > LINES -2 ) y = LINES - 2;
                break;
            case KEY_UP:
                y -=1;
                if( y < 1 ) y = 1;
                break;
            case KEY_LEFT:
                x -=1;
                if( x < 1 ) x = 1;
                break;
            case KEY_RIGHT:
                x +=1;
                if( x > COLS - 2 ) x = COLS - 2;
                break;
        }

        mvwaddch(big_window, y, x, ACS_DIAMOND);
        wrefresh(big_window);


    }


   endwin();
   system("clear");
  }





// nie uzywac printf i scantd
