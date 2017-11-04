#include <ncurses.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define DELAY 60000
void drawBrick(WINDOW *w,int y,int x){
	mvwprintw(w,y+0,x,"    ____         _        __      ____                      __              ");            
	mvwprintw(w,y+1,x,"   / __ ) _____ (_)_____ / /__   / __ ) _____ ___   ____ _ / /__ ___   _____");         
	mvwprintw(w,y+2,x,"  / __  |/ ___// // ___// //_/  / __  |/ ___// _ \\ / __ `// //_// _ \\ / ___/");
	mvwprintw(w,y+3,x," / /_/ // /   / // /__ /  ,<   / /_/ // /   /  __// /_/ // ,<  /  __// /    ");
	mvwprintw(w,y+4,x,"/_____//_/   /_/ \\___//_/|_|  /_____//_/    \\___/ \\__,_//_/|_| \\___//_/     ");
}
void drawGame(WINDOW *w, int x, int y, int px){
	wborder( w,'#','#','#','#','#','#','#','#');
	drawBrick(w,13,7);
	mvwprintw(w,y, x, "O");
	mvwprintw(w,28,px-2,"TTTTT");
}
void drawPausa(WINDOW *w){
	mvwprintw(w,7,34,"###   #   # #  ###   #");
	mvwprintw(w,8,34,"# #  # #  # #  #    # #");
	mvwprintw(w,9,34,"###  ###  # #  ###  ###");
	mvwprintw(w,10,34,"#    # #  # #    #  # #");
	mvwprintw(w,11,34,"#    # #  ###  ###  # #");
}

int main(int argc, char *argv[]) {

	int x = 2, y = 2;
	int max_y = 0, max_x = 0;
	int dirx = 1, diry = 1;
	int px=45 , timing = 0;
	int ch, i;

	WINDOW *w, *v;
	char list[7][18] = { "Easy", "Medium", "Crazy", "Options*", "Exit","","*out of service" };
	char item[18];

	initscr();

	getmaxyx(stdscr, max_y, max_x);
	if(max_y < 30 || max_x < 90){
		v = newwin( max_y, max_x, 0,0);	
		wtimeout(v,20);
	   	mvwprintw(v,max_y/3,max_x/2-20,"Screen is too small to play please rezize");
	   	wrefresh(v);
	} 
	else {
	    v = newwin(9,82,(max_y/4) - 5, (max_x/2)-41);
	    drawBrick(v,2,3);
	    wborder( v,'#','#','#','#','#','#','#','#');
	    wrefresh(v);
	}
	w = newwin( 9, 20, (2*max_y/3) - 5, (max_x/2) - 10 ); // create a new window
    box( w, 0, 0 ); // sets default borders for the window
    noecho();
	curs_set(FALSE);
	keypad( w, TRUE ); // enable keyboard input for the window.

    for( i=0; i<7; i++ ) {
        if( i == 0 ) wattron( w, A_STANDOUT ); 
        else wattroff( w, A_STANDOUT );
        sprintf(item, "%s",  list[i]);
        mvwprintw( w, i+1, 9-((unsigned)strlen(list[i])/2), "%s", item );
    }
    wrefresh(w);
    i = 0;
	while(( ch = wgetch(w)) != '\n'){  
        sprintf(item, "%s",  list[i]); 
        mvwprintw( w, i+1, 9-((unsigned)strlen(list[i])/2), "%s", item ); 
        if(ch == KEY_UP && i>0 ) i--;
        if(ch == KEY_DOWN && i<4 ) i++;
        wattron( w, A_STANDOUT );  
        sprintf(item, "%s",  list[i]);
        mvwprintw( w, i+1, 9-((unsigned)strlen(list[i])/2), "%s", item );
        wattroff( w, A_STANDOUT );
    }
    wclear(v);
    delwin(v);
    ch = 'p';
	while( ch != 'q'){ 
	 	getmaxyx(stdscr, max_y, max_x);
	 	if(max_y < 30 || max_x < 90){
	 		wclear(w);
			w = newwin( max_y, max_x, 0,0);	
			wtimeout(w,20);
	   		mvwprintw(w,max_y/2,max_x/2-20,"Screen is too small to play please rezize");
	   		wrefresh(w);
		}
		else{
			wclear(stdscr);
			w = newwin( 30, 90, max_y/2-15,max_x/2-45);	
			keypad( w, TRUE );
			wtimeout(w,20);
			if(ch == 'p'){
		   		drawGame(w,x,y,px);
		   		drawPausa(w);
		   		wrefresh(w);
		   		while(( ch = wgetch(w)) != 'p'){}
			}
			else{
				if((ch == KEY_LEFT || ch == 'a')  && px > 4) 	px--;
				if((ch == KEY_RIGHT || ch == 'd') && px < 86)	px++;

				if(timing % 5 == 0){
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
			}
			mvwprintw(w,1,5," px: %d key: %c max_x: %d max_y: %d", px, ch, max_x, max_y );
			drawGame(w,x,y,px);
			timing++;
		}
		ch = wgetch(w);
	}
	clear();
	endwin();
	return 0;
}
