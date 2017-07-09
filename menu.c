/* ncurses menu drawing - functions */
/* Developer: Nagesh Nanjundachari */
#define MENU_DEFINED
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include "menu.h"
#include "common.h"
#include "key.h"
#include "clogin.c"
extern PMENU exit_menu;

int
draw_menu (PMENU * pmenu)
{
  int i, ii, action_set = 0, temp, ch, plane = 0, ht_bs = 0, ret, spl_event =
    0, chk_len;
  char datap[30], ch_type, *p;
  printer_on = 0;		/* only for printer */
  pmenu->bp->w = newwin (pmenu->bp->r, pmenu->bp->c,
			 pmenu->bp->x, pmenu->bp->y);
#	if	1
#	if	1
  if (pmenu->menu != NULL)
    {
      scr_dump (pmenu->menu);
    }
#	endif
  if (!pmenu->clear_scr)
    {
      clear ();
      refresh ();
    }
#	endif
#	if	1
  for (i = 0; (pmenu->flds) != (i - 1); i++)
    {
      (*pmenu->pf + i)->datad[0] = 0;
      (*pmenu->pf + i)->myself = pmenu;
    }
#	endif
#		if	1	/* menu_init function */
  if (pmenu->pok != NULL)
    (pmenu->pok) (pmenu);
#		endif
#			ifndef	MONO
  if (pmenu->clr)
    {
      wcolor_set (pmenu->bp->w, pmenu->clr, NULL);
    }
  else
    {
      wcolor_set (pmenu->bp->w, 2, NULL);
    }
#			endif
  keypad (pmenu->bp->w, TRUE);
  box (pmenu->bp->w, 0, 0);
  wattrset (pmenu->bp->w, A_NORMAL | rgb (4));
  /*wattrset (pmenu->bp->w, A_BOLD|rgb(10)); */
  mvwprintw (pmenu->bp->w, 1, (pmenu->bp->c - strlen (pmenu->title)) / 2,
	     pmenu->title);
  for (i = 0; (pmenu->flds) != (i - 1); i++)
    {
      temp = (*pmenu->pf + i)->datalen;
      if (temp > 1)
	{
	  wattrset (pmenu->bp->w, (*pmenu->pf + i)->attr | rgb (6));
	  mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x, (*pmenu->pf + i)->y,
		     (*pmenu->pf + i)->fname);
	  datap[--temp] = 0;
	  while (temp--)
	    datap[temp] = nch;
	  datap[0] = nch;
	  wattrset (pmenu->bp->w, rgb (2));
	  mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x,
		     (*pmenu->pf + i)->y + strlen ((*pmenu->pf + i)->fname) +
		     2, datap);
	  mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x,
		     (*pmenu->pf + i)->y + strlen ((*pmenu->pf + i)->fname) +
		     2, (*pmenu->pf + i)->datad);
	}
      else
	{
/****   DISP is added ****/
	  if ((*pmenu->pf + i)->type == DISP)
	    {
	      wattrset (pmenu->bp->w, (*pmenu->pf + i)->attr | rgb (6));
	      mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x,
			 (*pmenu->pf + i)->y, (*pmenu->pf + i)->fname);
	    }
	  if ((*pmenu->pf + i)->type == ACTION)
	    {
	      wattrset (pmenu->bp->w, (*pmenu->pf + i)->attr | rgb (3));
	      mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x,
			 (*pmenu->pf + i)->y, (*pmenu->pf + i)->fname);
	    }
	}
    }

  for (i = 0; (pmenu->flds) != (i - 1); i++)
    {
      if ((*pmenu->pf + i)->datalen)
	break;
    }
#	if	1		/* imp for only action fields */
  if (pmenu->flds == i - 1)
    {
      curs_set (0);
      i = 0;
    }
  else
    curs_set (1);
#	else
  curs_set (1);
#	endif
  while (1)
    {
      noecho ();
      if (action_set)
	{
	  wattrset (pmenu->bp->w, (*pmenu->pf + ii)->attr | rgb (3));
	  mvwprintw (pmenu->bp->w, (*pmenu->pf + ii)->x, (*pmenu->pf + ii)->y,
		     (*pmenu->pf + ii)->fname);
	  action_set = 0;
	  ii = i;
	}
#		if	1
/****   DISP is added later check for bugs is reqd ****/
      if ((*pmenu->pf + i)->type == DISP)
	{
	  if (++i == pmenu->flds + 1)
	    i = 0;
	  plane = strlen ((*pmenu->pf + i)->datad);
	  continue;
	}
#		endif
      if ((*pmenu->pf + i)->type == ACTION)
	{
	  curs_set (0);
#		ifdef	MONO
	  wattrset (pmenu->bp->w,
		    (*pmenu->pf + i)->attr | A_REVERSE | A_BLINK);
#		else
	  wattrset (pmenu->bp->w, (*pmenu->pf + i)->attr | rgb (7));
#		endif
	  mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x, (*pmenu->pf + i)->y,
		     (*pmenu->pf + i)->fname);
	  action_set = 1;
	  ii = i;
	}
      else
	{
	  curs_set (1);
	  wattrset (pmenu->bp->w, rgb (2));
#		define CURS_TIME
#		ifdef	CURS_TIME
	  gwind = pmenu->bp->w;
	  gyy = (*pmenu->pf + i)->x;
	  gxx =
	    (*pmenu->pf + i)->y + strlen ((*pmenu->pf + i)->fname) + 2 +
	    plane;
#		endif
#		define	MOVE_CUR_END
#		ifdef	MOVE_CUR_END	/* for first time */
	  if (!i)
	    plane = strlen ((*pmenu->pf + i)->datad);
#		endif
	  wmove (pmenu->bp->w, (*pmenu->pf + i)->x,
		 (*pmenu->pf + i)->y + strlen ((*pmenu->pf + i)->fname) + 2 +
		 plane);
	  if ((*pmenu->pf + i)->type == AMOUNT
	      || (*pmenu->pf + i)->type == BAMOUNT)
	    {
	      if ((*pmenu->pf + i)->type == AMOUNT)
		chk_len = 5;
	      if ((*pmenu->pf + i)->type == BAMOUNT)
		chk_len = 11;
	      if ((strlen ((*pmenu->pf + i)->datad) == chk_len))
		{
		  p = strchr ((*pmenu->pf + i)->datad, '.');
		  if (p == NULL)
		    spl_event = '.';
		}
	      else
		spl_event = 0;
	    }
	  else
	    spl_event = 0;
	  if ((*pmenu->pf + i)->type == DATE)
	    {
	      if ((strlen ((*pmenu->pf + i)->datad) == 2) ||
		  (strlen ((*pmenu->pf + i)->datad) == 5))
		{
		  spl_event = '/';
		}
	      else
		spl_event = 0;
	    }
	}
      if (((ch = wgetch (pmenu->bp->w)) == ESC_KEY))
	{
#	if	1
	  for (i = 0; (pmenu->flds) != (i - 1); i++)
	    {
	      (*pmenu->pf + i)->datad[0] = 0;
	    }
#	endif
#	if	1		/* for multiple menus */
	  if (pmenu->menu != NULL)
	    {
	      scr_restore (pmenu->menu);
	      remove (pmenu->menu);
	      return RET_ESC;
	    }
	  else
	    {
	      clear ();
	      refresh ();
	      curs_set (0);
	      return RET_ESC;
	    }
#	else
	  clear ();
	  refresh ();
	  curs_set (0);
	  return RET_ESC;
#	endif
	}
      ch_type = check_ch ((*pmenu->pf + i)->type, ch, spl_event);
/* follow state is only to print_reports by setting flag at PRINTER-button */
      if (pmenu->flds == i)
	{
	  printer_on = 1;
	}
      else
	{
	  printer_on = 0;
	}
      switch (ch_type)
	{

	case EMERGE:
	  endwin ();
	  exit (0);

	case ENCRYPT:
	  if (plane + 2 < (*pmenu->pf + i)->datalen)
	    {
	      waddch (pmenu->bp->w, '*');
	      (*pmenu->pf + i)->datad[plane] = ch;
	      (*pmenu->pf + i)->datad[plane + 1] = 0;
	      plane++;
	    }
	  break;

	case FLD_CHAR:
	  if (plane + 2 < (*pmenu->pf + i)->datalen)
	    {
	      if ((*pmenu->pf + i)->type == CHECK)
		{
		  waddch (pmenu->bp->w, toupper (ch));
		  (*pmenu->pf + i)->datad[plane] = toupper (ch);
		}
	      else
		{
		  waddch (pmenu->bp->w, ch);
		  (*pmenu->pf + i)->datad[plane] = ch;
		}
	      (*pmenu->pf + i)->datad[plane + 1] = 0;
	      plane++;
	    }
	  break;

	case HOT_KEY:
	  break;

	case AFLD_CHAR:
	  break;

	case OK_KEY:
	  if ((*pmenu->pf + i)->pfn != NULL)
	    {
	      ret = ((*pmenu->pf + i)->pfn) ((*pmenu->pf + i)->myself);
	      if (ret == RET_OK)
		{
		  clear ();
		  refresh ();
		  return RET_OK;
		}
	      if (ret == RET_PRIV)
		{
		  if (pmenu->menu != NULL)
		    {
		      scr_restore (pmenu->menu);
#								if	1
		      refresh ();
#								endif
		      remove (pmenu->menu);
		      return RET_PRIV;
		    }
		  return RET_OK;
		}
	      if (ret == RET_CANCEL)
		{
		  break;
		}
	      if (ret == RET_NEXT)
		{
		  clear ();
		  refresh ();
		  return RET_CANCEL;
		}
	      if (ret == RET_STAY)
		{
		  clear ();
		  scr_restore ("screen2");
		  remove ("screen2");
		  break;
		}
	      if (ret == RET_DELETE)
		{
		  clear ();
		  refresh ();
		  return RET_CANCEL;
		}
	    }
	  break;

	case TAB_KEY:
#			if	1
/****   DISP is added later check for bugs is reqd ****/
	  if ((*pmenu->pf + (i + 1))->type == DISP)
	    {
	      if ((*pmenu->pf + i)->pfnt != NULL)
		((*pmenu->pf + i)->pfnt) ((*pmenu->pf + i)->myself);
	      if (++i == pmenu->flds + 1)
		i = 0;
	      plane = strlen ((*pmenu->pf + i)->datad);
	      continue;
	    }
#			endif
	  if ((*pmenu->pf + i)->pfnt != NULL)
	    {
	      ret = ((*pmenu->pf + i)->pfnt) ((*pmenu->pf + i)->myself);
	      if (ret)
		{
		  clear ();
		  scr_restore ("screen2");
		  remove ("screen2");
		  break;
		}
	    }
	  if (++i == pmenu->flds + 1)
	    i = 0;
	  plane = strlen ((*pmenu->pf + i)->datad);
	  break;

	case DOWN_KEY:
	  if ((*pmenu->pf + i)->pfnt != NULL)
	    {
	      ret = ((*pmenu->pf + i)->pfnt) ((*pmenu->pf + i)->myself);
	      if (ret)
		{
		  clear ();
		  scr_restore ("screen2");
		  remove ("screen2");
		  break;
		}
	    }
	  if (++i == pmenu->flds + 1)
	    i = 0;
	  plane = strlen ((*pmenu->pf + i)->datad);
	  break;

	case UP_KEY:
	  if (i == 0)
	    i = pmenu->flds;
	  else
	    i--;
	  plane = strlen ((*pmenu->pf + i)->datad);
	  break;

	case BSP_KEY:
	  plane--;
	  if (plane >= 0)
	    {
	      wmove (pmenu->bp->w, (*pmenu->pf + i)->x,
		     (*pmenu->pf + i)->y + strlen ((*pmenu->pf + i)->fname) +
		     2 + plane);
	      waddch (pmenu->bp->w, ' ');
	      (*pmenu->pf + i)->datad[plane] = 0;
	      break;
	    }
	  if (plane < 0)
	    plane = 0;

	}
    }
  wrefresh (pmenu->bp->w);
}

int
check_ch (int type, int ch, int spl_event)
{

  if (ch == 407)
    return AFLD_CHAR;
  switch (type)
    {

    case PASSWD:
      if (isalnum (ch))
	return ENCRYPT;
      else
	return which_key (ch);

    case MATH:
      if (ch == '+' || ch == '-')
	return 1;
      else
	return which_key (ch);

    case ALPHA:
      if (isalpha (ch) || ch == ' ')
	return 1;
      else
	return which_key (ch);

    case ALNUM:
      if (isalnum (ch) || ch == ' ')
	return 1;
      else
	return which_key (ch);

    case DIGIT:
      if (isdigit (ch))
	return 1;
      else
	return which_key (ch);

    case CHECK:
      if (ch == 'Y' || ch == 'y' || ch == 'n' || ch == 'N')
	return 1;
      else
	return which_key (ch);

    case UPPER:
      if (isupper (ch))
	return 1;
      else
	return which_key (ch);

    case LOWER:
      if (islower (ch))
	return 1;
      else
	return which_key (ch);

    case DASH:
      if (ch == '$' || ch == '#')
	return 1;
      else
	return which_key (ch);

    case BAMOUNT:
    case AMOUNT:
      if (!spl_event)
	{
	  if (isdigit (ch) || ch == '.')
	    return 1;
	  else
	    return which_key (ch);
	}
      else if (ch == '.')
	return 1;
      else
	return which_key (ch);

    case DATE:
      if (!spl_event)
	{
	  if (isdigit (ch))
	    return 1;
	  else
	    return which_key (ch);
	}
      else if (ch == '/')
	return 1;
      else
	return which_key (ch);

    case ACTION:
      if (ch == KEY_UP)
	return UP_KEY;
      if (ch == KEY_DOWN)
	return DOWN_KEY;
      if (ch == CR_KEY)
	return OK_KEY;
      if (ch == KEY_TAB)
	return TAB_KEY;
      else
	return which_key (ch);

    }
}

int
which_key (int ch)
{

  switch (ch)
    {
    case KEY_BACKSPACE:
      return BSP_KEY;
    case KEY_UP:
      return UP_KEY;
    case KEY_DOWN:
      return DOWN_KEY;
    case KEY_TAB:
      return TAB_KEY;
    case CR_KEY:
      return OK_KEY;
    case QKEY:
      return EMERGE;
    default:
      return AFLD_CHAR;
    }
}

int
set_error (char *err)
{
  WINDOW *w;
  scr_dump ("screen2");
  curs_set (0);
  w = newwin (5, 40, 8, 20);
  box (w, 0, 0);
  wattrset (w, A_BLINK | rgb (3));
  mvwprintw (w, 1, 12, " ERROR MESSAGE ");
  wattrset (w, rgb (7));
  mvwprintw (w, 3, (40 - strlen (err)) / 2, err);
  wrefresh (w);
  wgetch (w);
  flushinp ();
  curs_set (1);
  return 1;
}


int
set_pos (SETPOS * mnu)
{
  WINDOW *w;
  int i, k = 1, ch, ret;

  time_box ();
  if (mnu->ascreen != NULL)
    scr_dump (mnu->ascreen);
  w = newwin (mnu->r, mnu->c, mnu->x, mnu->y);
#		ifndef	MONO
  wcolor_set (w, 3, NULL);
#		endif
  keypad (w, TRUE);
  box (w, 0, 0);
  for (i = 1; (mnu->pos) && (i != (mnu->pos)); i++)
    {
      //      wattrset (w, A_NORMAL | rgb(1));
      wattrset (w, A_NORMAL | rgb (8));
      if (!((~i + k) + 1))
	wattron (w, A_NORMAL | rgb (2));
      mvwaddstr (w, i, 1, *(*mnu->pp + (i - 1)));
      // wattrset (w, A_NORMAL | rgb(1));
      wattrset (w, A_NORMAL | rgb (8));
    }
  wrefresh (w);
  while (1)
    {
      noecho ();
      if (((ch = wgetch (w)) == '\t') || ch == KEY_DOWN)
	{
	  if (++k == mnu->pos)
	    {
	      wattrset (w, A_NORMAL | rgb (1));
	      mvwaddstr (w, k - 1, 1, *(*mnu->pp + (k - 2)));
	      wattrset (w, A_NORMAL | rgb (2));
	      mvwaddstr (w, 1, 1, **mnu->pp);
	      k = 1;
	      continue;
	    }
	  wattrset (w, A_NORMAL | rgb (1));
	  mvwaddstr (w, k - 1, 1, *(*mnu->pp + (k - 2)));
	  wattrset (w, A_NORMAL | rgb (2));
	  mvwaddstr (w, k, 1, *(*mnu->pp + (k - 1)));
	  continue;
	}
      if (ch == KEY_UP)
	{
	  if (--k == 0)
	    {
	      wattrset (w, A_NORMAL | rgb (1));
	      mvwaddstr (w, 1, 1, **mnu->pp);
	      wattrset (w, A_NORMAL | rgb (2));
	      mvwaddstr (w, mnu->pos - 1, 1, *(*mnu->pp + (mnu->pos - 2)));
	      k = mnu->pos - 1;
	      continue;
	    }
	  wattrset (w, A_NORMAL | rgb (2));
	  mvwaddstr (w, k, 1, *(*mnu->pp + (k - 1)));
	  wattrset (w, A_NORMAL | rgb (1));
	  mvwaddstr (w, k + 1, 1, *(*mnu->pp + (k)));
	  continue;
	}
      if (ch == 27 || ch == KEY_LEFT)
	{
	  clear ();
	  wrefresh (w);
	  if (mnu->ascreen != NULL)
	    {
	      scr_restore (mnu->ascreen);
	      remove (mnu->ascreen);
	    }
	  wrefresh (w);
	  return;
	}
      if (ch == KEY_RIGHT || ch == CR_KEY)
	{
	  if (!mnu->tmenu)
	    {
	      if (k == 1 || k == 2 || k == 7)
		{
		  set_pos ((*mnu->nxt)[k - 1]);
		}
	      if (k == 3)
		{
		  scr_dump ("screen1");
		  billing ();
		  slk_init (1);
		  curs_set (0);
		  clear ();
		  refresh ();
		  scr_restore ("screen1");
		  refresh ();
		  remove ("screen1");
		}
	      if (k == 4)
		{
		  scr_dump ("screen1");
		  ret = draw_menu (&exit_menu);
		  if (ret == RET_OK)
		    {
		      return RET_OK;
		    }
		  else
		    {
		      slk_init (1);
		      curs_set (0);
		      clear ();
		      refresh ();
		      scr_restore ("screen1");
		      remove ("screen1");
		      refresh ();
		    }
		}
	      if (k == 5)
		{
		  scr_dump ("screen1");
		  draw_menu (&save_menu);
		  slk_init (1);
		  curs_set (0);
		  clear ();
		  refresh ();
		  scr_restore ("screen1");
		  remove ("screen1");
		  refresh ();
		}
	      else if (k == 6)
		{
		  scr_dump ("screen1");
		  draw_menu (&restore_menu);
		  slk_init (1);
		  curs_set (0);
		  clear ();
		  refresh ();
		  scr_restore ("screen1");
		  remove ("screen1");
		  refresh ();
		}
	    }
	  if (mnu->tmenu == 2)
	    {
	      if ((*mnu->nxt) != NULL)
		set_pos ((*mnu->nxt)[k - 1]);
	      scr_dump ("backscreen");
	      if (mnu->gmenu != NULL)
		{
		  kstate = k;
		  if ((*mnu->gmenu)[k - 1] != NULL)
		    {
		      common_stop_alarm ();
		      draw_menu ((*mnu->gmenu)[k - 1]);
		      common_start_alarm ();
		    }
		}
	      clear ();
	      scr_restore ("backscreen");
	      remove ("backscreen");
	      wrefresh (w);
	    }
	  if (mnu->tmenu == 1)
	    {
	      common_stop_alarm ();
	      scr_dump ("backscreen");
	      draw_menu (prog_menu[k - 1]);
	      clear ();
	      scr_restore ("backscreen");
	      remove ("backscreen");
	      wrefresh (w);
	      common_start_alarm ();
	    }
	}
    }
}

int
refresh_menu (PMENU * pmenu, int i, char found_flag, char finit)
{
  char datap[30], temp;

/*  check out for i=0 */

  if (!found_flag)
    {
      for (; (pmenu->flds) != (i - 1); i++)
	{
	  (*pmenu->pf + i)->datad[0] = 0;
	}
      if (pmenu->pok != NULL)
	{
	  if (finit)
	    (pmenu->pok) (pmenu);
	}
    }
  for (i = 0; (pmenu->flds) != (i - 1); i++)
    {
      temp = (*pmenu->pf + i)->datalen;
      if (temp > 1)
	{
	  datap[--temp] = 0;
	  while (temp--)
	    datap[temp] = nch;
	  datap[0] = nch;
	  mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x,
		     (*pmenu->pf + i)->y + strlen ((*pmenu->pf + i)->fname) +
		     2, datap);
	  mvwprintw (pmenu->bp->w, (*pmenu->pf + i)->x,
		     (*pmenu->pf + i)->y + strlen ((*pmenu->pf + i)->fname) +
		     2, (*pmenu->pf + i)->datad);
	}
    }
  wrefresh (pmenu->bp->w);
}

int
time_box ()
{
  wtime = newwin (3, 78, 21, 1);
  box (wtime, 0, 0);
  wrefresh (wtime);
  wattrset (wtime, A_NORMAL | rgb (6));
  mvwaddstr (wtime, 1, 1,
	     "                                                                            ");
  wrefresh (wtime);
}
