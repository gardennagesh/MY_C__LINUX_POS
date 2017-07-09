/* I ENJOYED C AND LINUX PROGRAMMING */
/* cpos.c. main function is here. draws login menu */ 
/* Developer: Nagesh Nanjundachari */
		
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "key.h"
#include "menu.h"
#include "common.h"
#include "creport.c"
#include "mpos.c"
extern PMENU exit_menu;
extern PMENU login_menu;


int main ()
{
  WINDOW *w1, *w2, *w3, *w4;
  int i, ch = 0;
  char cmd[20], *p;

/**************************************
	data_base file creation & initialization
***************************************/
  initscr ();
#include "clean.h"
  raw ();
  slk_init (1);
  curs_set (0);
  open_close_all_files (1);
  while (1)
    {
      if (draw_menu (&login_menu) == RET_OK)
	while (1)
	  {
	    if (owner)
	      {
		if (set_pos (&main_spos) == RET_OK)
		  break;
	      }
	    else
	      {
		if (toupper (cashman.powner[0]) == 'Y')
		  {
		    if (set_pos (&main_spos) == RET_OK)
		      break;
		  }
		else
		  {
		    billing ();
		  }
	      }
	    /* ESC in main-menu */
	    if (draw_menu (&exit_menu) == RET_OK)
	      break;
	  }
    }
}

void
disp_date_time_comn (int flag)
{
  FILE *fptemp;
  int i, j;
  char temp1[10];

  system ("date +%D > dtemp");
  system ("date +%T >> dtemp");
  fptemp = fopen ("dtemp", "r");
  fgets (bl_date, 10, fptemp);
  fgets (bl_time, 10, fptemp);
  fclose (fptemp);
  bl_date[8] = 0;
  bl_time[8] = 0;
  temp1[0] = bl_date[3];
  temp1[1] = bl_date[4];
  temp1[2] = bl_date[5];
  temp1[3] = bl_date[0];
  temp1[4] = bl_date[1];
  temp1[5] = bl_date[2];
  temp1[6] = bl_date[6];
  temp1[7] = bl_date[7];
  temp1[8] = 0;
  wtime = newwin (3, 78, 21, 1);
  box (wtime, 0, 0);
  wrefresh (wtime);
  wattrset (wtime, A_NORMAL | rgb (6));
  mvwaddstr (wtime, 1, 1, "                                              ");
  mvwaddstr (wtime, 1, 46, "DATE: ");
  mvwaddstr (wtime, 1, 52, bl_date);
  mvwaddstr (wtime, 1, 60, "   TIME: ");
  mvwaddstr (wtime, 1, 69, bl_time);
  mvwaddstr (wtime, 1, 74, "   ");
  alarm (2);
  wrefresh (wtime);
  wmove (gwind, gyy, gxx);
  wrefresh (gwind);
}

int
common_start_alarm ()
{
  signal (SIGALRM, disp_date_time_comn);
  alarm (2);
}

int
common_stop_alarm ()
{
  signal (SIGALRM, SIG_IGN);
}
