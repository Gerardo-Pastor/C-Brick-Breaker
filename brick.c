#include <ncurses.h>
#include <unistd.h>

#define DELAY 10000

int main(int argc, char *argv[]) {
 int x = 0, y = 5;
 int max_y = 0, max_x = 0;
 int next_x = 0;
 int direction = 1;

 initscr();
 getmaxyx(stdscr, max_y, max_x);
 noecho();
 curs_set(FALSE);

 while(1) {
 clear();
 mvprintw(y, x, "o");
 refresh();

 usleep(DELAY);

 next_x = x + direction;

 if (next_x >= max_x || next_x < 0) {
 direction*= -1;
 } else {
 x+= direction;
 }
 }

 endwin();
}
