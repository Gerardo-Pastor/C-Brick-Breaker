#include <ncurses.h>
#include <stdio.h>
#include <math.h>
//#include <stdlib.h>
//#include <unistd.h>

#define DELAY 60000

int main(int argc, char *argv[]) {
	int x = 2, y = 2;
	int max_y = 0, max_x = 0;
	int dirx = 1, diry = 1;

	WINDOW *w;
	char list[6][10] = { "Jugar", "Facil", "Dificil", "Opciones", "Salir" };
	char item[10];

	int ch, i;
	initscr();
	getmaxyx(stdscr, max_y, max_x);
	w = newwin( 10, 15, (max_y/2) - 5, (max_x/2) - 4 ); // create a new window
    box( w, 0, 0 ); // sets default borders for the window
    noecho();
	curs_set(FALSE);
	keypad( w, TRUE ); // enable keyboard input for the window.

    for( i=0; i<5; i++ ) {
        if( i == 0 ) 
            wattron( w, A_STANDOUT ); 
        else
            wattroff( w, A_STANDOUT );

        sprintf(item, "%-10s",  list[i]);
        mvwprintw( w, i+1, 2, "%s", item );
    }
 
    wrefresh( w );
    i = 0;
	while(( ch = wgetch(w)) != '\n'){  
            sprintf(item, "%-10s",  list[i]); 
            mvwprintw( w, i+1, 2, "%s", item ); 
            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? 4 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>4 ) ? 0 : i;
                            break;
            }
            wattron( w, A_STANDOUT );  
            sprintf(item, "%-10s",  list[i]);
            mvwprintw( w, i+1, 2, "%s", item);
            wattroff( w, A_STANDOUT );
    }
    getmaxyx(stdscr, max_y, max_x);
   	while(max_y < 30 || max_x < 90){
   		getmaxyx(stdscr, max_y, max_x);
   		clear();
   		mvprintw(max_y/2,max_x/2-20,"La pantalla es muy pequena para jugar");
   		refresh();
   	}
   	w = newwin( 30, 90, max_y/2-15,max_x/2-45);
	keypad( w, TRUE );
	wtimeout(w,40);
	int px=45 , timing = 0;

 while(( ch = wgetch(w)) != 'q'){ 
	 if(ch == KEY_LEFT && px > 4) 	px--;
	 if(ch == KEY_RIGHT && px < 86)	px++;

	 if(timing % 4 == 0){
	 	 if (x > 87 || x < 2) dirx *= -1;
	 	 if (y > 27 || y < 2) diry *= -1;
	 	 if(y==27 && abs(px-x)<3){
	 	 	dirx-=px-x;
	 	 	diry *= -1;
	 	 }
	 	 if(dirx > 2)	dirx = 2;
	 	 if(dirx < -2)	dirx = -2;

		 x += dirx;
		 y += diry;
		 timing = 0;
	 }
	 if(ch == 'p'){
 	 	wtimeout(w,-1);
 	 	wgetch(w);
 	 	wtimeout(w,50);
 	 }
 	 wclear(w);
 	 wborder( w,'#','#','#','#','#','#','#','#');
 	 mvwprintw(w,1,5," px: %d key: %c x: %d y: %d", px, ch, x, y );
	 mvwprintw(w,13,7,"    ____         _        __      ____                      __              ");            
 	 mvwprintw(w,14,7,"   / __ ) _____ (_)_____ / /__   / __ ) _____ ___   ____ _ / /__ ___   _____");         
	 mvwprintw(w,15,7,"  / __  |/ ___// // ___// //_/  / __  |/ ___// _ \\ / __ `// //_// _ \\ / ___/");
	 mvwprintw(w,16,7," / /_/ // /   / // /__ /  ,<   / /_/ // /   /  __// /_/ // ,<  /  __// /    ");
	 mvwprintw(w,17,7,"/_____//_/   /_/ \\___//_/|_|  /_____//_/    \\___/ \\__,_//_/|_| \\___//_/     ");
	 mvwprintw(w,y, x, "O");
	 mvwprintw(w,28,px-2,"TTTTT");
 	 wrefresh(w);
 	 timing++;
 }
 clear();
 endwin();
 return 0;
}
