/*login-functions are defined here in common.c*/
/* Developer: Nagesh Nanjundachari */

#define COMMON_DECLARES

#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"
#include "menu.h"
#include "common.h"

int
cancel_do_ok (void *menu_key)
{
  refresh_menu ((PMENU *) menu_key, 1, 0, 1);
  return RET_CANCEL;
}

int
common_do_ok (void *menu_key)
{
  return RET_OK;
}

int
restore_do_ok (void *menu_key)
{
  char cmd[50];

  if (!fork ())
    {
      exit (1);
    }
  else
    {
      wait (1);
    }
  return RET_OK;
}

int
save_do_ok (void *menu_key)
{
  char cmd[50];

  if (!fork ())
    {
      sleep (2);
      exit (1);
    }
  else
    {
      wait (1);
    }
  return RET_OK;
}

int
common_do_cancel (void *menu_key)
{
  return RET_NEXT;
}

int
login_do_ok (void *menu_key)
{
  char my_passwd[10] = { 'n', 'a', 'g', 'e', 's', 'h', 0 };
  int item_found = 0;
  owner = 0;
  if (owner_check ())
    {
      owner = 1;
      gcashman_no = 0;
      return RET_OK;
    }
  cashman_file = fopen ("./pos_files/dbase/cashman_ifile", "r");
  while (fread (&cashman, sizeof (CASHMAN), 1, cashman_file))
    {
      if (cashman.valid == 'Y')
	{
	  if (!strcmp (cashman.cname, loginp)
	      && !strcmp (cashman.cpasswd, passp))
	    {
	      item_found = 1;
	      gcashman_no = atoi (cashman.cmanno);
	      owner = 0;
	      break;
	    }
	}
    }
  fclose (cashman_file);
  if (item_found)
    {
      item_found = 0;
      return RET_OK;
    }
  if (!item_found)
    {
      if (!strcmp (loginp, "nagesh") && !strcmp (passp, my_passwd))
	{
	  owner = 1;
	  return RET_OK;
	}
      else
	{
	  set_error ("   Login Failure   ");
	  return RET_STAY;
	}
    }
}

int
login_exit_ok (void *menu_key)
{
#			if	1
  system ("rm -rf *scre*");
  remove ("./dtemp");
  remove ("./dtime");
#			endif
  endwin ();
  exit (1);
}

int
login_shut_ok (void *menu_key)
{
  system ("rm -rf *scre*");
  remove ("./dtemp");
  remove ("./dtime");
  endwin ();
  system ("init 0");
}

int
login_init (PMENU * cmenu)
{
  passp[0] = 0;
  loginp[0] = 0;
}

int
save_init (PMENU * cmenu)
{
  int no_reports = 0;
  FILE *fptemp;
  BILL_DETAIL tbill_detail;

  no_reports = 0;
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
  if (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file) != 1)
    {
      no_reports = 1;
    };
  fclose (bills_file);
  system ("date +%D > dtime");
  system ("date +%T >> dtime");
  fptemp = fopen ("dtime", "r");
  fgets (bl_date, 10, fptemp);
  fgets (bl_time, 10, fptemp);
  fclose (fptemp);
  bl_date[8] = 0;
  bl_time[8] = 0;
  if (no_reports)
    {
      strcpy (tbill_detail.date, bl_date);
      strcpy (tbill_detail.time, bl_time);
      no_reports = 0;
    }
  strcpy (dsave_buf, " Date   From:");
  strcat (dsave_buf, tbill_detail.date);
  strcat (dsave_buf, "  To:");
  strcat (dsave_buf, bl_date);
  strcat (dsave_buf, " ");

  strcpy (tsave_buf, " Time   From:");
  strcat (tsave_buf, tbill_detail.time);
  strcat (tsave_buf, "  To:");
  strcat (tsave_buf, bl_time);
  strcat (tsave_buf, " ");
}

