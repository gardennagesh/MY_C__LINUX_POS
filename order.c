/* KITCHEN ORDER TOKEN programming module file */
/* Developer : Nagesh Nanjundachari */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <stdlib.h>
#include "key.h"
#include "menu.h"
#include "common.h"
#include "prog.h"
#include "bill.h"
#include "morder.c"

double tot_kot_amt;
int kot_per_tbl;
int has_tbl;
int has_wtr;
int kot_items;
int kot_tbls;
int tbl_pos;
int kkcur_pos;
int gtable;
int too_tbl;
int tbl_disp;
int gwaiter;
int ascend;
int descend;
char tbl_field[10];
char wtr_field[10];
char entity_field[10];
char kot_bills[MAX_KOT_ITEMS][60];
char tbls[101][35];
char display_flag;
char kadjust_flag;
char koverride_flag;
char yes_delete;
char kqty_override;
char kot_ok;
char xfer_ok;
char kot_box;
char tbl_box;
KOT_ITEM kot_item[MAX_KOT_ITEMS];
WTABLE wtable;
TLIST tlist[101];

int
kot_in_time ()
{
  FILE *fptemp;
  char temp1[10];
  char bl_date[12], bl_time[12];

  system ("date +%D > dtime");
  system ("date +%T >> dtime");
  fptemp = fopen ("dtime", "r");
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
  print_str ("Date:", 6, LEFT_SIDE);
  print_str (temp1, 10, LEFT_SIDE);
  print_str ("Time:", 6, LEFT_SIDE);
  print_str (bl_time, 10, LEFT_SIDE);
}

int
xfer_init (PMENU * menu)
{
  char *pch, temp_buf[40];
  strcpy (temp_buf, tbls[tbl_pos - 1]);
  pch = temp_buf;
  ++pch;
  while (*pch != ' ')
    pch++;
  *pch = 0;
  tbl_disp = atoi (temp_buf);
  sprintf (from_tbl, "%d", tbl_disp);

}

int
kot_error (char *err)
{
  scr_dump ("kotscreen");
  set_error (err);
  scr_restore ("kotscreen");
  remove ("kotscreen");
  refresh ();
  return 0;
}

int
set_kot_out ()
{
  ascend = 0;
  descend = 0;
  kot_ok = 0;
  gtable = 0;
  gwaiter = 0;
  tbl_field[0] = 0;
  wtr_field[0] = 0;
  entity_field[0] = 0;
  has_tbl = 0;
  has_wtr = 0;
  kot_items = 0;
  kkcur_pos = 0;
  tbl_box = 0;
  kot_box = 1;
  keypad (wk4, FALSE);
  keypad (stdscr, TRUE);
}

int
disp_instrn ()
{

  wattrset (wk5, A_BOLD | rgb (17));
  dsave_buf[14] = 0;
  mvwaddstr (wk5, 15, 30, dsave_buf);
}

int
disp_kot_no ()
{

  kotno_file = fopen ("./pos_files/dbase/kotno_ifile", "r");
  fread (&kotno, sizeof (KOTNO), 1, kotno_file);
  fclose (kotno_file);
  wattrset (wk4, rgb (13) | A_BOLD);
  mvwaddstr (wk4, 1, 51, "      ");
  mvwaddstr (wk4, 1, 51, kotno.kotno);
  wrefresh (wk4);
}

int
kot_print_out ()
{
  int i = 0;
  char temp_buf[25];

  printer_on = 1;
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  print_line ();
  print_line ();
  print_str ("Kitchen Order Ticket: ", 22, LEFT_SIDE);
  print_str (kotno.kotno, 6, LEFT_SIDE);
  print_line ();
  print_str ("----------------------------------", 35, LEFT_SIDE);
  print_line ();
  kot_in_time ();
  print_line ();
  print_str ("Table:", 8, LEFT_SIDE);
  print_str (tbl_field, 5, LEFT_SIDE);
  print_str ("Waiter:", 9, LEFT_SIDE);
  print_str (wtr_field, 4, LEFT_SIDE);
  print_line ();
  print_str ("----------------------------------", 35, LEFT_SIDE);
  print_line ();
  print_str ("SlNo.", 6, LEFT_SIDE);
  print_str ("Item-Name", 17, LEFT_SIDE);
  print_str ("Qty", 9, RIGHT_SIDE);
  print_line ();
  print_str ("----------------------------------", 35, LEFT_SIDE);
  print_line ();
  for (i = 0; i < kot_items; i++)
    {
      sprintf (temp_buf, "%d", i + 1);
      print_str (temp_buf, 6, LEFT_SIDE);
      print_str (kot_item[i].item_name, 17, LEFT_SIDE);
      sprintf (temp_buf, "%f", kot_item[i].qty);
      put_accurate (temp_buf, QTY_ACT);
      print_str (temp_buf, 10, RIGHT_SIDE);
      print_line ();
    }
  print_str ("----------------------------------", 35, LEFT_SIDE);
  print_line ();
  if (strlen (dsave_buf))
    {
      print_str ("Instr'n1:", 10, LEFT_SIDE);
      print_str (dsave_buf, 20, LEFT_SIDE);
      print_line ();
    }
  if (strlen (tsave_buf))
    {
      print_str ("Instr'n2:", 10, LEFT_SIDE);
      print_str (tsave_buf, 20, LEFT_SIDE);
      print_line ();
    }
  tsave_buf[0] = 0;
  dsave_buf[0] = 0;
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  fclose (print_file);
  printer_on = 0;
}

int
adjust_table ()
{
  char tbuf[50];
  int more = 0, multi, left;
  int i = 1;			/* dont change i val */

  i = 1;
  if (tbl_pos <= 17 || kadjust_flag)
    {
      while (i <= 17)
	{
	  wattrset (wk7, A_REVERSE | rgb (7));
	  mvwaddstr (wk7, i, 1, tbls[i - 1]);
	  i++;
	}
      if (!kadjust_flag)
	{
	  wattrset (wk7, A_NORMAL | rgb (7));
	  mvwaddstr (wk7, tbl_pos, 1, tbls[tbl_pos - 1]);
	}
    }
  else
    {
      int i = 1;
      more = tbl_pos - 17;
      while (i <= 16)
	{
	  wattrset (wk7, A_REVERSE | rgb (7));
	  mvwaddstr (wk7, i++, 1, tbls[more++]);
	}
      wattrset (wk7, A_NORMAL | rgb (7));
      mvwaddstr (wk7, i, 1, tbls[more]);
    }
  wattrset (wk7, rgb (6));
  mvwaddstr (wk7, 18, 1, "                                 ");
  mvwaddstr (wk7, 18, 1, "Bar:");
  sprintf (tbuf, "%d", tbl_pos);
  mvwaddstr (wk7, 18, 5, tbuf);
  mvwaddstr (wk7, 18, 9, "Tbls:");
  sprintf (tbuf, "%d", kot_tbls);
  mvwaddstr (wk7, 18, 14, tbuf);
  mvwaddstr (wk7, 18, 18, "Amt:");
  sprintf (tbuf, "%f", tot_kot_amt);
  put_accurate (tbuf, PRICE_ACT);
  mvwaddstr (wk7, 18, 23, tbuf);
  wrefresh (wk7);
}

int
display_kot_items ()
{
  int ii = 0, jj = 0;
  char *pch, temp_buf[40];

  kot_items = 0;
  display_set = 0;
  for (ii = 0; ii < MAX_KOT_ITEMS; ii++)
    {
      for (jj = 0; jj <= 43; jj++)
	{
	  kot_bills[ii][jj] = ' ';
	  if (jj == 43)
	    kot_bills[ii][jj] = 0;
	}
    }
  for (ii = 0; ii != MAX_KOT_ITEMS; ii++)
    {
      memset (&kot_item[ii], 0, sizeof (KOT_ITEM));
    }
  for (ii = 0; ii != MAX_KOT_ITEMS; ii++)
    {
      kot_item[ii].valid = 'N';
    }
  adjust_kot_item ();
  strcpy (temp_buf, tbls[tbl_pos - 1]);
  pch = temp_buf;
  ++pch;
  while (*pch != ' ')
    pch++;
  *pch = 0;
  tbl_disp = atoi (temp_buf);
  sprintf (from_tbl, "%d", tbl_disp);
  display_flag = 1;
  kot_file = fopen ("./pos_files/dbase/kot_ifile", "r");
}

int
display_table ()
{
  int it = 0, left = 0, ii = 0, jj = 0;
  char tbuf[60];

  tbl_pos = 1;
  it = 0;
  kot_tbls = 0;
  tot_kot_amt = 0;
  for (ii = 0; ii < 99; ii++)
    {
      for (jj = 0; jj <= 34; jj++)
	{
	  tbls[ii][jj] = ' ';
	  if (jj == 33)
	    tbls[ii][jj] = 0;
	}
      memset (&tlist[ii], 0, sizeof (TLIST));
    }
  table_file = fopen ("./pos_files/dbase/table_ifile", "r");
  rewind (table_file);
  while (fread (&wtable, sizeof (WTABLE), 1, table_file))
    {
      if (wtable.valid == 'Y')
	{
	  tlist[kot_tbls].tbl = wtable.tbl;
	  tlist[kot_tbls].wtr = wtable.wtr;
	  kot_tbls++;
	  tot_kot_amt += wtable.amt;
	  sprintf (tbuf, "%d", wtable.tbl);
	  strcpy (tbls[it], " ");
	  strcat (tbls[it], tbuf);
	  left = strlen (tbls[it]);
	  left = 6 - left;
	  while (left--)
	    strcat (tbls[it], " ");
	  sprintf (tbuf, "%d", wtable.wtr);
	  strcat (tbls[it], tbuf);
	  left = strlen (tbls[it]);
	  left = 9 - left;
	  while (left--)
	    strcat (tbls[it], " ");
	  sprintf (tbuf, "%f", wtable.amt);
	  put_accurate (tbuf, PRICE_ACT);
	  left = strlen (tbuf);
	  left = 11 - left;
	  while (left--)
	    strcat (tbls[it], " ");
	  strcat (tbls[it], tbuf);
	  left = 5;
	  while (left--)
	    strcat (tbls[it], " ");
	  strcat (tbls[it], bla_time);
	  tbls[it][strlen (tbls[it])] = 0;
	  it++;

	}
    }
  fclose (table_file);
  adjust_table ();
}

int
start_next_kot ()
{
  int ii = 0, jj = 0;

  kot_box = 1;
  kot_ok = 0;
  kot_items = 0;
  gtable = 0;
  gwaiter = 0;
  tbl_field[0] = 0;
  wtr_field[0] = 0;
  entity_field[0] = 0;
  has_tbl = 0;
  has_wtr = 0;
  kkcur_pos = 1;
  tbl_pos = 1;
  for (ii = 0; ii < 99; ii++)
    {
      for (jj = 0; jj <= 34; jj++)
	{
	  tbls[ii][jj] = ' ';
	  if (jj == 33)
	    tbls[ii][jj] = 0;
	  kot_tbls++;
	}
    }
  for (ii = 0; ii < MAX_KOT_ITEMS; ii++)
    {
      for (jj = 0; jj <= 43; jj++)
	{
	  kot_bills[ii][jj] = ' ';
	  if (jj == 43)
	    kot_bills[ii][jj] = 0;
	}
    }
  for (ii = 0; ii != MAX_KOT_ITEMS; ii++)
    {
      memset (&kot_item[ii], 0, sizeof (KOT_ITEM));
    }
  for (ii = 0; ii != MAX_KOT_ITEMS; ii++)
    {
      kot_item[ii].valid = 'N';
    }
  adjust_kot_item ();
  put_tbl_status ();
  put_wtr_status ();
  wrefresh (wk5);
  wrefresh (wk4);
  display_table ();
  curs_set (1);
}

int
store_kot ()
{
  int i, item_found = 0;
  double tval = 0, dval = 0;

  i = 0;
  kot_file = fopen ("./pos_files/dbase/kot_ifile", "r+");
  fseek (kot_file, 0, SEEK_END);
  for (i = 0; i <= kot_items; i++)
    {
      kot_item[i].tbl = gtable;
      kot_item[i].wtr = gwaiter;
#		if	1	/* disc-calc */
      tval = kot_item[i].sell_price * kot_item[i].per_disc;
      tval = tval / 100.00;
      tval = kot_item[i].sell_price - tval;
#		endif
      dval += (tval * kot_item[i].qty);
      fwrite (&kot_item[i], sizeof (KOT_ITEM), 1, kot_file);
    }
  fflush (kot_file);
  fclose (kot_file);
  table_file = fopen ("./pos_files/dbase/table_ifile", "r+");
  rewind (table_file);
  item_found = 0;
  while (fread (&wtable, sizeof (WTABLE), 1, table_file))
    {
      if (wtable.tbl == gtable)
	{
	  item_found = 1;
	  break;
	}
    }
  wtable.tbl = gtable;
  if (!item_found)
    {
      wtable.wtr = gwaiter;
      wtable.amt = dval;
      //wtable.time = dval;
    }
  wtable.valid = 'Y';
  if (item_found)
    {
      wtable.amt += dval;
      item_found = 0;
      fseek (table_file, -sizeof (WTABLE), SEEK_CUR);
      fwrite (&wtable, sizeof (WTABLE), 1, table_file);
    }
  else
    {
      fwrite (&wtable, sizeof (WTABLE), 1, table_file);
    }
  fclose (table_file);
}

int
instrn_do_ok (void *key_menu)
{
  return RET_PRIV;
}

int
instrn_cancel_ok (void *key_menu)
{
  refresh_menu ((PMENU *) key_menu, 0, 0, 0);
}

int
xfer_do_ok (void *key_menu)
{
  xfer_ok = 1;
  too_tbl = atoi (to_tbl);
  if (too_tbl < 1)
    {
      kot_error (" Enter Correct Table ");
      return;
    }
  else
    {
      xfer_ok = 1;
    }
  return RET_PRIV;
}

int
xfer_cancel_ok (void *key_menu)
{
  return RET_PRIV;
}

int
kotexit_do_ok (void *key_menu)
{
  system ("rm -rf kotscreen");
  return RET_OK;
}

int
kotexitno_do_ok (void *key_menu)
{
  return RET_PRIV;
}

int
yeskot_do_ok (void *key_menu)
{

  kot_ok = 1;
  return RET_PRIV;
}

int
nokot_do_ok (void *key_menu)
{
  return RET_PRIV;
}

int
update_kot_item ()
{

  if (kqty_override)
    {
      koverride_flag = 1;
      kot_item[kkcur_pos - 1].qty = atof (entity_field);
    }
  format_kot_item ();
  adjust_kot_item ();
}

int
fill_kot_item_hole ()
{
  int i, j;

  for (i = 0; i <= kot_items; i++)
    if (kot_item[i].valid != 'Y')
      break;
  for (j = i; j < kot_items; j++)
    {
      kot_item[j] = kot_item[j + 1];
      strcpy (kot_bills[j], kot_bills[j + 1]);
    }
  if (kot_items)
    --kot_items;
  if (!kkcur_pos)
    kkcur_pos = 1;
}


int
tbl_key_up ()
{
  int pos;

  tbl_pos--;
  if (tbl_pos <= 1)
    {
      tbl_pos = 1;
      ascend++;
    }
}

int
tbl_key_down ()
{
  int pos;

  tbl_pos++;
  if (tbl_pos >= kot_tbls)
    {
      tbl_pos = kot_tbls;
      descend++;
    }
}

int
kot_key_up ()
{
  int pos;

  kkcur_pos--;
  if (kkcur_pos <= 1)
    kkcur_pos = 1;
}

int
kot_key_down ()
{
  int pos;

  kkcur_pos++;
  if (kkcur_pos >= MAX_KOT_ITEMS - 1)
    kkcur_pos = MAX_KOT_ITEMS - 1;
}


int
put_tbl_status ()
{
  wattrset (wk4, rgb (13));
  mvwaddstr (wk4, 1, 6, "    ");
  wrefresh (wk4);
}

int
put_wtr_status ()
{
  wattrset (wk4, rgb (13));
  mvwaddstr (wk4, 1, 16, "   ");
  wrefresh (wk4);
}

int
put_entity_status ()
{
  wattrset (wk4, rgb (13));
  mvwaddstr (wk4, 1, 34, "        ");
  wrefresh (wk4);
}

int
format_kot_item ()
{
  ITEM titem;
  char tbuf[50], *p;
  int i, tkkcur_pos, left = 0;

  tkkcur_pos = kot_items;
  if (koverride_flag)
    tkkcur_pos = kkcur_pos - 1;
/**** add item_code to cursor-bar-string **************/
  strcpy (kot_bills[tkkcur_pos], kot_item[tkkcur_pos].code);
  left = 4 - strlen (kot_bills[tkkcur_pos]);
  left += 6;
  kot_string (&kot_bills, left, RIGHT_SIDE, NULL);

/**** add item_name to cursor-bar-string **************/
  strcat (kot_bills[tkkcur_pos], kot_item[tkkcur_pos].item_name);
  left = 16 - strlen (kot_item[tkkcur_pos].item_name);
  left += 6;
  kot_string (&kot_bills, left, RIGHT_SIDE, NULL);

/**** add item_quntity to cursor-bar-string **************/
  if (koverride_flag)
    {
      sprintf (tbuf, "%f", kot_item[tkkcur_pos].qty);
      put_accurate (tbuf, QTY_ACT);
    }
  else
    {
      if (display_flag)
	{
	  sprintf (tbuf, "%f", xkot_item.qty);
	  put_accurate (tbuf, QTY_ACT);
	}
      else
	strcpy (tbuf, "1.000");
    }
  //left = 9-strlen(tbuf);
  left = 8 - strlen (tbuf);
  while (left--)
    strcat (kot_bills[tkkcur_pos], " ");
  strcat (kot_bills[tkkcur_pos], tbuf);
  if (strlen (item.unit))
    {
      strcat (kot_bills[tkkcur_pos], item.unit);
      left = 3 - strlen (item.unit);
      while (left--)
	strcat (kot_bills[tkkcur_pos], " ");
    }
  else
    {
      left = 3;
      while (left--)
	strcat (kot_bills[tkkcur_pos], " ");
    }
  kot_string (&kot_bills, 2, RIGHT_SIDE, NULL);
  left = strlen (kot_bills[tkkcur_pos]);
  left = 43 - left;
  if (left > 0)
    while (left--)
      strcat (kot_bills[tkkcur_pos], " ");
  kot_bills[tkkcur_pos][43] = 0;
}



int
progitem_to_kotitem ()
{

  strcpy (kot_item[kot_items].code, item.item_code);
  strcpy (kot_item[kot_items].item_name, item.item_name);
  if (display_flag)
    {
      kot_item[kot_items].qty = xkot_item.qty;
    }
  else
    kot_item[kot_items].qty = 1;
  kot_item[kot_items].per_disc = atof (item.item_disc);
  kot_item[kot_items].valid = 'Y';
  kot_item[kot_items].tbl = atoi (tbl_field);
  kot_item[kot_items].wtr = atoi (wtr_field);
  kot_item[kot_items].sell_price = atof (item.sell_price);
  format_kot_item ();
  kot_items++;
}


int
entry_to_kfifo (char *entity_field)
{
  int left = 0, item_found = 0;

  if (strlen (entity_field))
    {
      item_file = fopen ("./pos_files/dbase/item_ifile", "r");
      item_found = 0;
      while (fread (&item, sizeof (ITEM), 1, item_file))
	{
	  if (!strcmp (item.item_code, entity_field))
	    {
	      if (item.valid == 'Y')
		{
		  item_found = 1;
		  break;
		}
	    }
	}
      fclose (item_file);
      if (!item_found)
	{
	  kot_error (" Item Not Programmed ");
	  return 0;
	}
      if (item_found == 1)
	{
	  progitem_to_kotitem ();
	  return 1;
	}
    }
  else
    {
      attron (A_NORMAL | rgb (4));
      return 0;
    }
}

int
display_tot_kot ()
{
  char tbuf[50];

  wattrset (wk5, rgb (6));
  mvwaddstr (wk5, 15, 1, "                                           ");
  mvwaddstr (wk5, 15, 1, "CurBar:");
  sprintf (tbuf, "%d", kkcur_pos);
  mvwaddstr (wk5, 15, 8, tbuf);
  mvwaddstr (wk5, 15, 12, "Items:");
  sprintf (tbuf, "%d", kot_items);
  mvwaddstr (wk5, 15, 18, tbuf);
  mvwaddstr (wk5, 15, 22, "Instr'n:");
  disp_instrn ();
  wrefresh (wk5);
}

int
adjust_kot_item ()
{
  int more = 0, multi, left;
  int i = 1;			/* dont change i val */

  i = 1;
  if (kkcur_pos <= 14 || kadjust_flag)
    {
      while (i <= 14)
	{
	  wattrset (wk5, A_REVERSE | rgb (7));
	  mvwaddstr (wk5, i, 1, kot_bills[i - 1]);
	  i++;
	}
      if (!kadjust_flag)
	{
	  wattrset (wk5, A_NORMAL | rgb (7));
	  mvwaddstr (wk5, kkcur_pos, 1, kot_bills[kkcur_pos - 1]);
	}
    }
  else
    {
      int i = 1;
      more = kkcur_pos - 14;
      while (i <= 13)
	{
	  wattrset (wk5, A_REVERSE | rgb (7));
	  mvwaddstr (wk5, i++, 1, kot_bills[more++]);
	}
      wattrset (wk5, A_NORMAL | rgb (7));
      mvwaddstr (wk5, i, 1, kot_bills[more]);
    }

  display_tot_kot ();
}

int
kot_item_entry (char *entity_field)
{
  char tbuf[40];
  int left = 0, more = 0;

  if ((kot_items <= 14) && (kkcur_pos > kot_items))
    {
      kadjust_flag = 1;
      adjust_kot_item ();
      kkcur_pos = kot_items;
      kadjust_flag = 0;
    }

  if (entry_to_kfifo (entity_field))
    {
      if (kkcur_pos <= 14)
	{
	  wattrset (wk5, A_REVERSE | rgb (7));
	  mvwaddstr (wk5, kkcur_pos, 1, kot_bills[kkcur_pos - 1]);
	}
      kkcur_pos = kot_items;
      if (kkcur_pos <= 14)
	{
	  wattrset (wk5, A_NORMAL | rgb (7));
	  mvwaddstr (wk5, kkcur_pos, 1, kot_bills[kot_items - 1]);
	  if (kot_items > 1)
	    {
	      wattrset (wk5, A_REVERSE | rgb (7));
	      mvwaddstr (wk5, kkcur_pos - 1, 1, kot_bills[kot_items - 2]);
	    }
	}
      else
	{
	  int i = 1;
	  more = kot_items - 14;
	  while (i <= 13)
	    {
	      wattrset (wk5, A_REVERSE | rgb (7));
	      mvwaddstr (wk5, i++, 1, kot_bills[more++]);
	    }
	  wattrset (wk5, A_NORMAL | rgb (7));
	  mvwaddstr (wk5, i, 1, kot_bills[more]);
	}
    }
  wrefresh (wk5);
}

int
kot_menu (int flag)
{
  int ii, jj, ic, jc, ch, post = 0, item_found = 0;
  int wtr_post = 0, entity_post = 0, yes_tbl = 0;
  double tflot = 0;
  char *pch, temp_buf[40], temp1_buf[40];
  KOT_ITEM tkot_item;

  curs_set (1);
  tsave_buf[0] = 0;
  dsave_buf[0] = 0;
  kkcur_pos = 1;
  kot_box = 1;
  for (ii = 0; ii < MAX_KOT_ITEMS; ii++)
    {
      for (jj = 0; jj <= 43; jj++)
	{
	  kot_bills[ii][jj] = ' ';
	  if (jj == 43)
	    kot_bills[ii][jj] = 0;
	}
    }
  for (ii = 0; ii != MAX_KOT_ITEMS; ii++)
    {
      memset (&kot_item[ii], 0, sizeof (KOT_ITEM));
    }
  for (ii = 0; ii != MAX_KOT_ITEMS; ii++)
    {
      kot_item[ii].valid = 'N';
    }
  tbl_field[0] = 0;
  wtr_field[0] = 0;
  entity_field[0] = 0;
  clear ();
  refresh ();
  attrset (rgb (4) | A_NORMAL);
  mvaddstr (1, 1,
	    "  KOT-BILLING                                                                  ");
  refresh ();
#			if	0
  wk6 = newwin (4, 79, 21, 1);
  wk4 = newwin (4, 79, 2, 1);
  wk5 = newwin (17, 45, 5, 1);
  wk7 = newwin (17, 35, 5, 45);
#			else
  wk6 = newwin (4, 45, 21, 1);
  wk4 = newwin (4, 79, 2, 1);
  wk5 = newwin (17, 45, 5, 1);
  wk7 = newwin (20, 35, 5, 45);
#			endif
  wcolor_set (wk4, 1, NULL);
  wcolor_set (wk5, 1, NULL);
  wcolor_set (wk6, 1, NULL);
  wcolor_set (wk7, 1, NULL);
  box (wk4, 0, 0);
  box (wk5, 0, 0);
  box (wk6, 0, 0);
  box (wk7, 0, 0);
  mvwaddstr (wk4, 1, 1, " Tbl:");
  mvwaddstr (wk4, 1, 11, " Wtr:");
  mvwaddstr (wk4, 1, 19, "  Enter Entity:");
  mvwaddstr (wk4, 1, 42, "  Kot No:");
  mvwaddstr (wk4, 1, 58, "  Type:");
  mvwaddstr (wk4, 2, 1,
	     " Code    Item-Name                Quantity  Tbl  Wtr      Basic-Amt   In-Time");
  wattrset (wk6, rgb (4) | A_NORMAL);
  mvwaddstr (wk6, 1, 1, "F1:KotOn   F2:Bill-Tbl  F3:ScrlKot F4:Txfer");
  mvwaddstr (wk6, 2, 1, "F6:Instr'n                                 ");
  wattrset (wk4, rgb (13) | A_BOLD | A_BLINK);
  mvwaddstr (wk4, 1, 65, "           ");
  mvwaddstr (wk4, 1, 65, "kot-entry");
  wrefresh (wk5);
  wrefresh (wk6);
  wrefresh (wk7);
  wmove (wk4, 1, 6);
  wrefresh (wk4);
  keypad (stdscr, FALSE);
  keypad (wk4, TRUE);
  display_table ();
  while (1)
    {
      disp_kot_no ();
      noecho ();
      if (!select_flag && !display_flag)
	{
	  if (!has_tbl)
	    {
	      ch = mvwgetch (wk4, 1, 6 + post);
	    }
	  if (has_tbl && !has_wtr)
	    {
	      ch = mvwgetch (wk4, 1, 16 + wtr_post);
	    }
	  if (has_tbl && has_wtr)
	    {
	      gwaiter = atoi (wtr_field);
	      ch = mvwgetch (wk4, 1, 34 + entity_post);
	    }
	  if (!echo_chk (ch))
	    continue;
	}
      else
	{
#		if	1
	  if (display_flag)
	    {
	      while (1)
		{
		  if (fread (&tkot_item, sizeof (KOT_ITEM), 1, kot_file) != 1)
		    {
		      fclose (kot_file);
		      display_flag = 0;
		      display_set = 1;
		      break;
		    }
		  if (tkot_item.tbl == tbl_disp)
		    {
		      if (tkot_item.valid == 'Y')
			{
			  xkot_item = tkot_item;
			  jj = atoi (tkot_item.code);
			  sprintf (select_buf, "%d", jj);
			  break;
			}
		    }
		}
	    }
#			endif
	  kcase = KEY_PPAGE;
	}
      switch (kcase)
	{

	case ESC_KEY:
	  if (!has_tbl)
	    {
	      set_kot_out ();
	      return;
	    }
	  else
	    {
	      if (draw_menu (&kot_exit_menu) == RET_OK)
		{
		  set_kot_out ();
		  return;
		}
	      curs_set (1);
	    }

	case ALPHA:
	  continue;

	case DIGIT:
	  if (tbl_box)
	    {
	      continue;
	    }
	  echo ();
	  if (post <= 2 && wtr_post <= 1 && entity_post <= 4)
	    {
	      wattrset (wk4, rgb (13) | A_BOLD);
	      if (!has_tbl && !has_wtr)
		{
		  mvwaddch (wk4, 1, 6 + post, ch);
		  tbl_field[post] = ch;
		  post++;
		}
	      if (has_tbl && !has_wtr)
		{
		  mvwaddch (wk4, 1, 16 + wtr_post, ch);
		  wtr_field[wtr_post] = ch;
		  wtr_post++;
		}
	      if (has_tbl && has_wtr)
		{
		  mvwaddch (wk4, 1, 34 + entity_post, ch);
		  entity_field[entity_post] = ch;
		  entity_post++;
		}
	      wrefresh (wk4);
	    }
	  continue;

	case KEY_BACKSPACE:
	  if (display_set)
	    continue;
	  echo ();
	  wattrset (wk4, rgb (13));
	  if (!has_tbl)
	    {
	      post--;
	      if (post <= 0)
		post = 0;
	      tbl_field[post] = 0;
	      mvwaddch (wk4, 1, 6 + post, ' ');
	      wrefresh (wk4);
	    }
	  if (has_tbl && !has_wtr)
	    {
	      wtr_post--;
	      if (wtr_post <= 0)
		wtr_post = 0;
	      wtr_field[wtr_post] = 0;
	      mvwaddch (wk4, 1, 16 + wtr_post, ' ');
	      wrefresh (wk4);
	      if (!wtr_post)
		{
		  has_tbl = 0;
		  post = 4;
		}
	    }
	  if (has_tbl && has_wtr)
	    {
	      entity_post--;
	      if (entity_post <= 0)
		entity_post = 0;
	      entity_field[entity_post] = 0;
	      mvwaddch (wk4, 1, 34 + entity_post, ' ');
	      wrefresh (wk4);
	      if (!entity_post)
		{
		  has_wtr = 0;
		  wtr_post = 2;
		}
	    }
	  break;

	case KEY_TAB:
	  if (display_set)
	    continue;
	  if (!has_tbl)
	    {
	      if (!strlen (tbl_field))
		{
		  continue;
		}
	      else
		{
		  tbl_field[post] = 0;
		  /* for tbl if alredy exist */
#										if	1
		  gtable = atoi (tbl_field);
		  for (ic = 0; ic < kot_tbls; ic++)
		    {
		      if (tlist[ic].tbl == gtable)
			{
			  sprintf (wtr_field, "%d", tlist[ic].wtr);
			  wtr_post = strlen (wtr_field);
			  mvwaddstr (wk4, 1, 16, wtr_field);
			  wrefresh (wk4);
			  break;
			}
		    }
#										endif
		  has_tbl = 1;
		  post = 0;
		}
	    }
	  if (has_tbl && !has_wtr)
	    {
	      if (!strlen (wtr_field))
		{
		  continue;
		}
	      else
		{
		  gtable = atoi (tbl_field);
		  wtr_field[wtr_post] = 0;
#				if	1
		  waiter_file = fopen ("./pos_files/dbase/waiter_ifile", "r");
		  item_found = 0;
		  while (fread (&waiter, sizeof (WAITER), 1, waiter_file))
		    {
		      if (!strcmp (waiter.wtrno, wtr_field))
			{
			  if (item.valid == 'Y')
			    {
			      item_found = 1;
			      break;
			    }
			}
		    }
		  fclose (waiter_file);
		  if (!item_found)
		    {
		      kot_error (" Add this Waiter in SETUP-MODE ");
		      continue;
		    }
#				endif
		  has_wtr = 1;
		  wtr_post = 0;
		}
	    }
	  break;

	case KEY_F (1):
	  tbl_box = 0;
	  kot_box = 1;
	  yes_delete = 0;
	  post = 0;
	  wtr_post = 0;
	  entity_post = 0;
	  entity_field[0] = 0;
	  tbl_field[0] = 0;
	  wtr_field[0] = 0;
	  wattrset (wk4, rgb (13) | A_BOLD | A_BLINK);
	  mvwaddstr (wk4, 1, 65, "             ");
	  mvwaddstr (wk4, 1, 65, "Kot-Entry");
	  wrefresh (wk4);
	  if (display_set)
	    {
	      start_next_kot ();
	      display_set = 0;
	    }
	  break;

	case KEY_F (2):
	  entity_field[entity_post] = 0;
	  if ((has_tbl && has_wtr && kot_items)
	      || (has_tbl && has_wtr && strlen (entity_field)))
	    {
	      kot_error (" Finish KOT Opertion ");
	      refresh ();
	      continue;
	    }
	  kot_box = 0;
	  tbl_box = 1;
	  yes_delete = 0;
	  wattrset (wk4, rgb (11) | A_REVERSE | A_BLINK | A_BOLD);
	  mvwaddstr (wk4, 1, 65, "             ");
	  mvwaddstr (wk4, 1, 65, "Bill-Table");
	  wrefresh (wk4);
	  display_kot_items ();
	  break;

	case KEY_F (3):
	  if (tbl_box)
	    {
	      kot_box = 1;
	      tbl_box = 0;
	      wattrset (wk4, rgb (12) | A_BLINK | A_BOLD);
	      mvwaddstr (wk4, 1, 65, "             ");
	      mvwaddstr (wk4, 1, 65, "Scrl-Kot-Item");
	      wrefresh (wk4);
	    }
	  break;

	case KEY_F (5):
	  if (has_tbl && has_wtr && kot_items)
	    {
	      kot_error (" Finish KOT Opertion ");
	      continue;
	    }
	  kot_box = 0;
	  tbl_box = 1;
	  wattrset (wk4, rgb (16) | A_BOLD | A_BLINK);
	  mvwaddstr (wk4, 1, 65, "             ");
	  mvwaddstr (wk4, 1, 65, "Kot-Cancel");
	  wrefresh (wk4);
	  display_kot_items ();
	  yes_delete = 1;
	  break;

	case KEY_F (6):
	  if (kot_box)
	    {
	      draw_menu (&instrn_menu);
	    }
	  display_tot_kot ();
	  break;

	case KEY_F (4):
	  wattrset (wk4, rgb (10) | A_BOLD | A_BLINK);
	  mvwaddstr (wk4, 1, 65, "             ");
	  mvwaddstr (wk4, 1, 65, "Tbl-Trasfer");
	  yes_delete = 0;
	  kot_box = 0;
	  tbl_box = 1;
	  wrefresh (wk4);
	  if (draw_menu (&xfer_menu) == RET_PRIV && xfer_ok)
	    {
	      xfer_ok = 0;
	      kot_file = fopen ("./pos_files/dbase/kot_ifile", "r+");
	      while (fread (&tkot_item, sizeof (KOT_ITEM), 1, kot_file))
		{
		  if (tkot_item.tbl == tbl_disp)
		    {
		      if (tkot_item.valid == 'Y')
			{
			  tkot_item.tbl = too_tbl;
			  fseek (kot_file, -sizeof (KOT_ITEM), SEEK_CUR);
			  fwrite (&tkot_item, sizeof (KOT_ITEM), 1, kot_file);
			}
		    }
		}
	      fflush (kot_file);
	      fclose (kot_file);
	      table_file = fopen ("./pos_files/dbase/table_ifile", "r+");
	      while (fread (&wtable, sizeof (WTABLE), 1, table_file))
		{
		  if (wtable.tbl == tbl_disp)
		    {
		      if (wtable.valid == 'Y')
			{
			  wtable.tbl = too_tbl;
			  fseek (table_file, -sizeof (WTABLE), SEEK_CUR);
			  fwrite (&wtable, sizeof (WTABLE), 1, table_file);
			}
		    }
		}
	      fflush (table_file);
	      fclose (table_file);
	    }
	  display_table ();
	  display_kot_items ();
	  break;

	case KEY_UP:
	  if (kot_box)
	    {
	      kot_key_up ();
	      adjust_kot_item ();
	    }
	  if (tbl_box)
	    {
	      descend = 0;
	      tbl_key_up ();
	      adjust_table ();
	      if (ascend <= 1)
		display_kot_items ();
	    }
	  break;

	case KEY_DOWN:
	  if (kot_box)
	    {
	      kot_key_down ();
	      adjust_kot_item ();
	    }
	  if (tbl_box)
	    {
	      ascend = 0;
	      tbl_key_down ();
	      adjust_table ();
	      if (descend <= 1)
		display_kot_items ();
	    }
	  break;

	case KEY_DC:
	  if (!yes_delete)
	    {
	      if (!kot_items || (kkcur_pos > kot_items)
		  || strlen (entity_field))
		{
		  put_entity_status ();
		  entity_field[0] = 0;
		  continue;
		}
	      if (display_set)
		continue;
	    }
	  kot_item[kkcur_pos - 1].valid = 'N';
	  fill_kot_item_hole ();
	  adjust_kot_item ();
	  break;

	case KEY_HOME:
	  entity_field[entity_post] = 0;
	  if (!strlen (entity_field) || kkcur_pos > kot_items)
	    {
	      entity_post = 0;
	      entity_field[0] = 0;
	      put_entity_status ();
	      continue;
	    }
	  if (display_set)
	    continue;
	  tflot = atof (entity_field);
	  if (tflot > 99999)
	    {
	      kot_error (" Max Qty Is [99999.00] ");
	      entity_post = 0;
	      entity_field[0] = 0;
	      put_entity_status ();
	      continue;
	    }
	  kqty_override = 1;
	  update_kot_item ();
	  kqty_override = 0;
	  koverride_flag = 0;
	  entity_post = 0;
	  entity_field[0] = 0;
	  put_entity_status ();
	  break;
	case KEY_NPAGE:
	  if (display_set)
	    continue;
	  scr_dump ("kotscreen");
	  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
	  search_items (1);
	  fclose (item_file);
	  scr_restore ("kotscreen");
	  remove ("kotscreen");
	  mvaddstr (1, 1,
		    "  KOT-BILLING                                                                  ");
	  refresh ();
	  keypad (stdscr, FALSE);
	  keypad (wk4, TRUE);
	  refresh ();
	  break;

	case KEY_PPAGE:
	  if (display_set)
	    continue;
	  if (select_flag || display_flag)
	    {
	      strcpy (entity_field, select_buf);
	      select_flag = 0;
	    }
	  else
	    {
	      entity_field[entity_post] = 0;
	    }
	  if (!strlen (entity_field))
	    continue;
	  if (kot_items >= MAX_KOT_ITEMS - 1)
	    {
	      kot_error (" Items Per Kot Limit Eceeded ");
	      entity_field[0] = 0;
	      entity_post = 0;
	      continue;
	    }
	  kot_item_entry (entity_field);
	  display_tot_kot ();
	  entity_post = 0;
	  entity_field[0] = 0;
	  put_entity_status ();
	  break;

	case CR_KEY:
	  if (kot_box && has_tbl && has_wtr)
	    {
	      if (!kot_items)
		continue;
	      if (draw_menu (&kot_print_menu) == RET_PRIV && kot_ok)
		{
		  refresh ();
		  disp_kot_no ();
		  jj = check_printer ();
		  if (jj == OUT_OF_ORDER)
		    {
		      kot_error (" Printer is out of order ");
		      continue;
		    }
		  if (jj == PAPER_OUT)
		    {
		      kot_error (" Printer Paper Out ");
		      continue;
		    }
		  sprintf (temp1_buf, "%d", atol (kotno.kotno) + 1);
		  kotno_file = fopen ("./pos_files/dbase/kotno_ifile", "r+");
		  strcpy (kotno.kotno, temp1_buf);
		  fwrite (&kotno, sizeof (KOTNO), 1, kotno_file);
		  fflush (kotno_file);
		  fclose (kotno_file);
		  store_kot ();
		  kot_print_out ();
		  system ("cat /var/tmp/print_ifile > /dev/lp0");
		  start_next_kot ();
		}
	      curs_set (1);
	      break;
	    }

	  if (yes_delete)
	    {
	      if (!kot_items)
		continue;
	      if (draw_menu (&del_kot_menu) == RET_PRIV && kot_ok)
		{
		  jj = check_printer ();
		  if (jj == OUT_OF_ORDER)
		    {
		      kot_error (" Printer is out of order ");
		      continue;
		    }
		  if (jj == PAPER_OUT)
		    {
		      kot_error (" Printer Paper Out ");
		      continue;
		    }
		  /*
		     strcpy (temp_buf, tbls [tbl_pos-1]);
		     pch = temp_buf;
		     ++pch;
		     while (*pch != ' ')pch++;
		     *pch = 0;
		     bill_tbl = atoi (temp_buf);  
		     kot_file = fopen ("./pos_files/dbase/kot_ifile", "r");
		     for (i=0; i<kot_items; i++) {
		     if (kot_items [i].tbl == bill_tbl) {
		     }
		     }
		   */
		  kot_print_out ();
		  system ("cat /var/tmp/print_ifile > /dev/lp0");
		  start_next_kot ();
		}
	      curs_set (1);
	      break;
	    }

	  if (display_set)
	    {
	      if (draw_menu (&bill_tbl_menu) == RET_PRIV && kot_ok)
		{
		  display_set = 0;
		  strcpy (temp_buf, tbls[tbl_pos - 1]);
		  pch = temp_buf;
		  ++pch;
		  while (*pch != ' ')
		    pch++;
		  *pch = 0;
		  bill_tbl = atoi (temp_buf);
		  kot_kho = 1;
		  kot_file = fopen ("./pos_files/dbase/kot_ifile", "r");
		  set_kot_out ();
		  return;
		}
	      curs_set (1);
	    }

	}
    }
}

void
kot_string (char (*src)[][60], char no, char side, char *brc)
{
  char tbuf[50];
  int tcur_pos;

  tcur_pos = kot_items;
  if (koverride_flag)
    tcur_pos = kkcur_pos - 1;
  tbuf[0] = ' ';
  tbuf[1] = 0;
  if ((src != NULL) && (brc == NULL))
    {
      if (side == RIGHT_SIDE)
	{
	  while (no--)
	    strcat ((*src)[tcur_pos], " ");
	}
      if (side == LEFT_SIDE)
	{			/* not tested bug may exist */
	  while (no-- == 1)
	    strcat (tbuf, " ");
	  strcat (tbuf, (*src)[tcur_pos]);
	  strcpy ((*src)[tcur_pos], tbuf);
	}
    }
  if ((brc != NULL) && (src == NULL))
    {
      if (side == RIGHT_SIDE)
	{
	  while (no--)
	    strcat (brc, " ");
	}
      if (side == LEFT_SIDE)
	{			/* not tested bug may exist */
	  while (no-- == 1)
	    strcat (tbuf, " ");
	  strcat (tbuf, brc);
	  strcpy (brc, tbuf);
	}
    }
}
