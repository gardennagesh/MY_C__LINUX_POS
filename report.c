/***********************************/
/*report.c report related functions*/
/* Developer: Nagesh Nanjundachari */
/***********************************/
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"
#include "menu.h"
#include "common.h"
#include "prog.h"

extern FIELD isales_flds[];
extern FIELD istock_flds[];
extern FIELD finan_flds[];
extern FIELD profit_flds[];
extern FIELD billsum_flds[];
extern FIELD taxsum_flds[];
extern FIELD idetail_flds[];

long pbills;
long nbills;
long start_point;
long end_point;
long blstart_point;
long blsame_lastp;
long blend_point;
long no_of_refbill;
long no_of_trans;
long no_of_bills;
long owner_bills;
long ifound = 0;
double tot_owner_amt;
double tot_sale_val = 0;
double tot_sale_qty = 0;
double date_qty = 0;
double tot_card_amt = 0;
double tot_cash_amt = 0;
double tot_credit_amt = 0;
double tot_chq_amt = 0;
double tot_misc_amt = 0;
double tot_serv_amt = 0;
double tot_disc_amt = 0;
double tot_tax1_amt = 0;
double tot_taxon1_amt = 0;
double tot_tax2_amt = 0;
double tot_taxon2_amt = 0;
double tot_tax3_amt = 0;
double tot_taxon3_amt = 0;
double tot_tax4_amt = 0;
double tot_taxon4_amt = 0;
double tot_tax_amt = 0;
double tot_taxon_amt = 0;
double tot_refund_amt = 0;
double tot_drawer_amt = 0;
double grand_tot_amt = 0;
double pay_tot_amt = 0;
double tot_basic_amt = 0;
double tot_prof_val = 0;
BILL_ITEM tbill_item;
BILL_DETAIL tbill_detail;
CARD_DETAIL tcard_detail;
CREDIT_DETAIL tcredit_detail;
CHQ_DETAIL tchq_detail;

int
print_line ()
{
  if (printer_on)
    fprintf (print_file, "\r\n");
  else
    fprintf (print_file, "\n");
}

int
print_str (char *str_buf, int width, int side)
{
  int len = 0, left, tleft;
  char space_buf[81];

  space_buf[0] = 0;
  len = strlen (str_buf);
  if (!len)
    fprintf (print_file, "NST\n");
  if (width < len)
    width = len + 1;		/*u will loose aline here,so take care */
  if (side == RIGHT_SIDE)
    {
      left = width - len;
      if (left > 0)
	while (left--)
	  strcat (space_buf, " ");
      if (strlen (space_buf))
	fprintf (print_file, space_buf);
      fprintf (print_file, str_buf);
    }
  if (side == LEFT_SIDE)
    {
      left = width - len;
      fprintf (print_file, str_buf);
      if (left > 0)
	while (left--)
	  strcat (space_buf, " ");
      fprintf (print_file, space_buf);
    }
  if (side == MIDDLE)
    {
      left = (width - len) / 2;
      if (left > 0)
	while (left--)
	  strcat (space_buf, " ");
      fprintf (print_file, space_buf);
      fprintf (print_file, str_buf);
      fprintf (print_file, space_buf);
    }

}

greport_title ()
{
  char tbuf[81];

  head_file = fopen ("./pos_files/dbase/head_ifile", "r");
  fread (&head, sizeof (HEAD), 1, head_file);
  fclose (head_file);
  if (strlen (head.line1))
    {
      print_str (head.line1, 60, MIDDLE);
      print_line ();
    }
  if (strlen (head.line2))
    {
      print_str (head.line2, 60, MIDDLE);
      print_line ();
    }
  if (strlen (head.line3))
    {
      print_str (head.line3, 60, MIDDLE);
      print_line ();
    }
  if (strlen (head.line4))
    {
      print_str (head.line4, 60, MIDDLE);
      print_line ();
    }
  if (strlen (head.line5))
    {
      print_str (head.line5, 60, MIDDLE);
      print_line ();
    }
  print_str ("-------------------------", 60, MIDDLE);
  print_line ();
  print_str ("Report No. :", 14, LEFT_SIDE);
  print_str ("1", 3, LEFT_SIDE);
  if (strlen (sect_buf))
    {
      print_str ("Section No. :", 14, LEFT_SIDE);
      print_str (sect_buf, 3, LEFT_SIDE);
    }
  print_line ();
  if (strlen (start_date))
    {
      print_str ("From Date:", 11, LEFT_SIDE);
      print_str (start_date, 10, LEFT_SIDE);
      print_str ("   ", 5, LEFT_SIDE);
      print_str ("To Date:", 9, LEFT_SIDE);
      print_str (end_date, 10, LEFT_SIDE);
      print_line ();
    }
  print_str ("Report Date:", 14, LEFT_SIDE);
  print_str (bl_date, 9, LEFT_SIDE);
  print_str ("Time:", 6, LEFT_SIDE);
  print_str (bl_time, 9, LEFT_SIDE);
  print_line ();
  print_line ();

}

int
set_ipoints ()
{
  int got_date = 0;

  rewind (billitem_file);
  got_date = 0;
  while (fread (&tbill_item, sizeof (BILL_ITEM), 1, billitem_file))
    {
      if (!strcmp (start_date, tbill_item.date))
	{
	  got_date = 1;
	  break;
	}
    }
  if (got_date)
    {
      got_date = 0;
      fseek (billitem_file, -sizeof (BILL_ITEM), SEEK_CUR);
      start_point = ftell (billitem_file);
      rewind (billitem_file);
      if (!strcmp (end_date, start_date))
	{
	  while (fread (&tbill_item, sizeof (BILL_ITEM), 1, billitem_file))
	    {
	      if (!strcmp (end_date, tbill_item.date))
		{
		  end_point = ftell (billitem_file);
		  got_date = 1;
		}
	    }
	}
      else
	{
	  while (fread (&tbill_item, sizeof (BILL_ITEM), 1, billitem_file))
	    {
	      if (!strcmp (end_date, tbill_item.date))
		{
		  got_date = 1;
		  end_point = ftell (billitem_file);
		}
	    }
	}
      if (!got_date)
	{
	  fseek (billitem_file, 0, SEEK_END);
	  end_point = ftell (billitem_file);
	}
    }
  else
    {
      fseek (billitem_file, 0, SEEK_END);
      start_point = ftell (billitem_file);
      end_point = ftell (billitem_file);
    }
  rewind (billitem_file);
  refresh ();
}

int
set_bpoints ()
{
  int got_date = 0;

  rewind (bills_file);
  got_date = 0;
  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
    {
      if (!strcmp (start_date, tbill_detail.date))
	{
	  got_date = 1;
	  break;
	}
    }
  if (got_date)
    {
      got_date = 0;
      fseek (bills_file, -sizeof (BILL_DETAIL), SEEK_CUR);
      blstart_point = ftell (bills_file);
      rewind (bills_file);
      if (!strcmp (end_date, start_date))
	{
	  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
	    {
	      if (!strcmp (end_date, tbill_detail.date))
		{
		  blend_point = ftell (bills_file);
		  got_date = 1;
		}
	    }
	}
      else
	{
	  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
	    {
	      if (!strcmp (end_date, tbill_detail.date))
		{
		  got_date = 1;
		  blend_point = ftell (bills_file);
		}
	    }
	}
      if (!got_date)
	{
	  fseek (bills_file, 0, SEEK_END);
	  blend_point = ftell (bills_file);
	}
    }
  else
    {
      fseek (bills_file, 0, SEEK_END);
      blstart_point = ftell (bills_file);
      blend_point = ftell (bills_file);
    }
  rewind (bills_file);
  refresh ();
}

int
check_printer ()
{
}

int
to_printer ()
{
}



int
display_bill_on ()
{
  int i;
  char tbuf[150];
  char ch;

  print_file = fopen ("/var/tmp/print_ifile", "r");
  while (fgets (tbuf, 100, print_file))
    {
      if (strstr (tbuf, "TOTAL"))
	attrset (rgb (6) | A_REVERSE);
      addstr (tbuf);
      refresh ();
    }
  fclose (print_file);
  attrset (rgb (3) | A_REVERSE);
  mvaddstr (24, 0, "ENTER\n");
  refresh ();
}


int
display_on ()
{
  int i;
  char tbuf[400];
  char ch;

  while (fgets (tbuf, 100, print_file))
    {
#define MONO
#ifdef	MONO
      attrset (rgb (6)|A_REVERSE);
#else
      attrset (rgb (13));
#endif
      if (strstr (tbuf, "TOTAL"))
	attrset (rgb (6) | A_REVERSE);
      addstr (tbuf);
      refresh ();
      /* rep_line is only for scr_disply */
      rep_line++;
      if (rep_line == 22)
	{
	  attrset (rgb (3) | A_REVERSE);
	  mvaddstr (24, 0, "Continue<ENTER>, Exit<ESC>\n");
	  refresh ();
	  attrset (rgb (13));
	  while (1)
	    {
	      ch = getch ();
	      if (ch == 27)
		{
		  rep_line = 0;
		  fclose (print_file);
		  return RET_PRIV;
		}
	      if (ch != CR_KEY)
		continue;
	      clear ();
	      refresh ();
	      rep_line = 0;
	      break;
	    }
	}
    }
  fclose (print_file);
  attrset (rgb (3) | A_REVERSE);
  mvaddstr (24, 0, "Exit<ESC>\n");
  rep_line = 0;
  refresh ();
  while (1)
    {
      ch = getch ();
      if (ch == 27)
	break;
    }
}

int
isale_init (PMENU * key_menu)
{
  sect_buf[0] = '1';
  sect_buf[1] = 0;
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
isale_title ()
{
  print_str ("CODE     ITEM-NAME            SALES-QTY     SALES-VALUE ",
	     79, LEFT_SIDE);
  print_line ();
  print_str ("-------------------------------------------------------",
	     79, LEFT_SIDE);
  print_line ();
}

int
print_item ()
{
  char tbuf[40];
  int item_found = 0;
  double dval, taxper, taxonper;

  dval = 0;
  taxper = 0;
  taxonper = 0;
  item_found = 0;
  tax_file = fopen ("./pos_files/dbase/tax_ifile", "r");
  while (fread (&tax, sizeof (TAX), 1, tax_file))
    {
      if (!strcmp (tax.tax_no, item.tax_link))
	{
	  if (tax.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (tax_file);
  if (item_found)
    {
      taxper = atof (tax.tamt);
      taxonper = atof (tax.toamt);
    }
  print_str (item.item_code, 9, LEFT_SIDE);
  print_str (item.item_name, 20, LEFT_SIDE);
  tot_sale_qty += item.today_sale_qty;
  sprintf (tbuf, "%f", item.today_sale_qty);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  dval = atof (item.sell_price);
  taxper = taxper * dval / 100;
  taxonper = taxper * taxonper / 100;
  dval = dval + taxper + taxonper;
  dval = dval * (item.today_sale_qty);
  tot_sale_val += dval;
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();
}

int
print_item_date ()
{
  char tbuf[40];
  int item_found = 0;
  double dval, taxper, taxonper;

  dval = 0;
  taxper = 0;
  taxonper = 0;
  item_found = 0;
  tax_file = fopen ("./pos_files/dbase/tax_ifile", "r");
  while (fread (&tax, sizeof (TAX), 1, tax_file))
    {
      if (!strcmp (tax.tax_no, item.tax_link))
	{
	  if (tax.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (tax_file);
  if (item_found)
    {
      taxper = atof (tax.tamt);
      taxonper = atof (tax.toamt);
    }

  print_str (item.item_code, 9, LEFT_SIDE);
  print_str (item.item_name, 20, LEFT_SIDE);
  tot_sale_qty += date_qty;
  sprintf (tbuf, "%f", date_qty);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  dval = atof (item.sell_price);
  taxper = taxper * dval / 100;
  taxonper = taxper * taxonper / 100;
  dval = dval + taxper + taxonper;
  dval = dval * (item.today_sale_qty);
  dval = dval * (date_qty);
  tot_sale_val += dval;
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();
}

int
print_item_total ()
{
  char tbuf[40];
  double dval;

  print_line ();
  print_str ("-------------------------------------------------------",
	     79, LEFT_SIDE);
  print_line ();
  print_str ("               ", 21, RIGHT_SIDE);
  print_str ("TOTAL :", 8, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_sale_qty);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_sale_val);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();
  print_line ();
}

int
isales_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  if (kstate == 2)
    {
      if (store_buf[0] == 0)
	{
	  set_error (" Store Not Entered ");
	  return RET_STAY;
	}
    }
  if (kstate == 3)
    {
      if (code_buf[0] == 0)
	{
	  set_error (" Item Code Not Entered ");
	  return RET_STAY;
	}
    }

  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  tot_sale_val = 0;
  tot_sale_qty = 0;
  date_qty = 0;
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  greport_title ();
  isale_title ();
  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
  billitem_file = fopen ("./pos_files/dbase/billitem_ifile", "r");
  if (rep_buf[0] == 'Y')
    {
      while (fread (&item, sizeof (ITEM), 1, item_file))
	{
	  if (item.today_sale_qty > 0 && item.valid == 'Y')
	    {
	      if (kstate == 3)
		{
		  if (!strcmp (code_buf, item.item_code))
		    {
		      print_item ();
		      break;
		    }
		}
	      if (kstate == 2)
		{
		  if (!strcmp (store_buf, item.dept_link))
		    {
		      print_item ();
		    }
		}
	      if (kstate == 1)
		print_item ();
	    }
	}
    }
  else
    {
      tot_sale_qty = 0;
      tot_sale_val = 0;
      set_ipoints ();
      rewind (item_file);
      rewind (billitem_file);
      while (fread (&item, sizeof (ITEM), 1, item_file))
	{
	  rewind (billitem_file);
	  fseek (billitem_file, start_point, SEEK_CUR);
	  date_qty = 0.00;
	  while (fread (&tbill_item, sizeof (BILL_ITEM), 1, billitem_file))
	    {
	      if (end_point == ftell (billitem_file))
		{
		  break;
		}
	      if (kstate == 1)
		if (!strcmp (tbill_item.stricode, item.item_code))
		  {
		    date_qty += tbill_item.qty;
		  }
	      if (kstate == 2)
		if (!strcmp (tbill_item.stricode, item.item_code))
		  {
		    if (!strcmp (tbill_item.dept_link, store_buf))
		      {
			date_qty += tbill_item.qty;
		      }
		  }
	      if (kstate == 3)
		if (!strcmp (tbill_item.stricode, code_buf))
		  {
		    date_qty += tbill_item.qty;
		  }
	    }
	  if (kstate == 1 || kstate == 2)
	    print_item_date ();
	  if (kstate == 3)
	    {
	      print_item_date ();
	      break;
	    }
	}
    }
  print_item_total ();
  fclose (item_file);
  fclose (billitem_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
start_jump (void *key_menu)
{

  if ((strlen (start_date) < 8) && (strlen (start_date) >= 1))
    {
      refresh_menu ((PMENU *) key_menu, 1, 6, 0);
      set_error (" Date Format Is Not OK ");
      return RET_STAY;
    }
  refresh_menu ((PMENU *) key_menu, 6, 6, 0);
}

int
end_jump (void *key_menu)
{

  if (((strlen (start_date) == 8) && (strlen (end_date) < 8)) ||
      ((!strlen (start_date)) && (strlen (end_date))))
    {
      refresh_menu ((PMENU *) key_menu, 1, 6, 0);
      set_error (" Date Format Is Not OK ");
      return RET_STAY;
    }
  if ((strlen (start_date) == 8) && (strlen (end_date) == 8))
    {
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 6, 6, 0);
}

int
sect_jump (void *key_menu)
{
  pfield = &isales_flds;
  if (kstate == 1)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[3].type = DISP;
    }
  if (kstate == 2)
    {
      (*pfield)[2].type = DIGIT;
      (*pfield)[3].type = DISP;
    }
  if (kstate == 3)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[3].type = DIGIT;
    }
  refresh_menu ((PMENU *) key_menu, 6, 6, 0);
}

int
istock_init (PMENU * key_menu)
{
  if (kstate == 1)
    {
      rep_buf[0] = 'Y';
      rep_buf[1] = 0;
    }
  else
    {
      rep_buf[0] = 0;
    }
}

int
istock_title ()
{
  print_str
    ("CODE  ITEM-NAME        OPEN-STOCK   STOCK-IN  STOCK-OUT   SOLD-QTY  CURRENT-STOK",
     80, LEFT_SIDE);
  print_line ();
  print_str
    ("--------------------------------------------------------------------------------",
     80, LEFT_SIDE);
  print_line ();
}

int
stock_jump (void *key_menu)
{
  pfield = &istock_flds;
  if (kstate == 1)
    {
      (*pfield)[1].type = DISP;
      (*pfield)[2].type = DISP;
    }
  if (kstate == 2)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[1].type = DIGIT;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  if (kstate == 3)
    {
      (*pfield)[1].type = DISP;
      (*pfield)[2].type = DIGIT;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 1, 0, 0);
}

int
print_item_stock ()
{
  char tbuf[40];
  double dval;

  tot_sale_val = 0;
  print_str (item.item_code, 5, LEFT_SIDE);
  print_str (item.item_name, 17, LEFT_SIDE);
  sprintf (tbuf, "%f", item.open_stock);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", item.stock_in);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", item.stock_out);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", item.today_sale_qty);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", item.curr_stock);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  print_line ();
  print_str ("Stock Value :", 14, RIGHT_SIDE);
  dval = atof (item.sell_price);
  dval = dval * (item.curr_stock);
  tot_sale_val += dval;
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 18, RIGHT_SIDE);
  print_line ();
  print_line ();
}

int
istock_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  char *tmp;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  if (kstate == 2)
    {
      if (store_buf[0] == 0)
	{
	  set_error (" Store Not Entered ");
	  return RET_STAY;
	}
    }
  if (kstate == 3)
    {
      if (code_buf[0] == 0)
	{
	  set_error (" Item Code Not Entered ");
	  return RET_STAY;
	}
    }
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  tot_sale_val = 0;
  tot_sale_qty = 0;
  date_qty = 0;
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  greport_title ();
  istock_title ();
  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
  while (fread (&item, sizeof (ITEM), 1, item_file))
    {
      if (item.valid == 'Y')
	{
	  if (kstate == 3)
	    {
	      if (!strcmp (code_buf, item.item_code))
		{
		  print_item_stock ();
		  break;
		}
	    }
	  if (kstate == 2)
	    {
	      if (!strcmp (store_buf, item.dept_link))
		{
		  print_item_stock ();
		}
	    }
	  if (kstate == 1)
	    print_item_stock ();
	}
    }
  fclose (item_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
profit_init (PMENU * key_menu)
{
  sect_buf[0] = '1';
  sect_buf[1] = 0;
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
profit_title ()
{
  print_str
    ("CODE  ITEM-NAME            SELL-PRICE    COST-PRICE     SOLD-QTY        PROFIT",
     79, LEFT_SIDE);
  print_line ();
  print_str
    ("------------------------------------------------------------------------------",
     79, LEFT_SIDE);
  print_line ();
}

int
print_profit_item ()
{
  char tbuf[40];
  double dtval, ddval, dsval, dcval;

  print_str (item.item_code, 6, LEFT_SIDE);
  print_str (item.item_name, 17, LEFT_SIDE);

  dsval = atof (item.sell_price);
  sprintf (tbuf, "%f", dsval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);

  dcval = atof (item.cost_price);
  sprintf (tbuf, "%f", dcval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);

  dtval = item.today_sale_qty;
  sprintf (tbuf, "%f", dtval);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);

  ddval = dsval - dcval;
  dtval *= ddval;
  tot_prof_val += dtval;
  sprintf (tbuf, "%f", dtval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 15, RIGHT_SIDE);
  print_line ();

}

int
print_profit_item_date ()
{
  char tbuf[40];
  double dtval, ddval, dsval, dcval;

  print_str (item.item_code, 6, LEFT_SIDE);
  print_str (item.item_name, 17, LEFT_SIDE);

  dsval = atof (item.sell_price);
  sprintf (tbuf, "%f", dsval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);

  dcval = atof (item.cost_price);
  sprintf (tbuf, "%f", dcval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);

  dtval = date_qty;
  sprintf (tbuf, "%f", dtval);
  put_accurate (tbuf, QTY_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);

  ddval = dsval - dcval;
  dtval *= ddval;
  tot_prof_val += dtval;
  sprintf (tbuf, "%f", dtval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 15, RIGHT_SIDE);
  print_line ();
}

int
print_profit_item_total ()
{
  char tbuf[40];

  print_str
    ("-------------------------------------------------------------------------------",
     79, RIGHT_SIDE);
  print_line ();
  print_str ("TOTAL PROFIT AMOUNT :", 40, LEFT_SIDE);
  sprintf (tbuf, "%f", tot_prof_val);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 39, RIGHT_SIDE);
  print_line ();
  print_line ();
}

int
profit_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);

  if (kstate == 2)
    {
      if (store_buf[0] == 0)
	{
	  set_error (" Store Not Entered ");
	  return RET_STAY;
	}
    }
  if (kstate == 3)
    {
      if (code_buf[0] == 0)
	{
	  set_error (" Item Code Not Entered ");
	  return RET_STAY;
	}
    }

  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  tot_sale_val = 0;
  tot_sale_qty = 0;
  date_qty = 0;
  tot_prof_val = 0;
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  greport_title ();
  profit_title ();
  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
  billitem_file = fopen ("./pos_files/dbase/billitem_ifile", "r");
  if (rep_buf[0] == 'Y')
    {
      while (fread (&item, sizeof (ITEM), 1, item_file))
	{
	  if (item.today_sale_qty > 0 && item.valid == 'Y')
	    {
	      if (kstate == 3)
		{
		  if (!strcmp (code_buf, item.item_code))
		    {
		      print_profit_item ();
		      break;
		    }
		}
	      if (kstate == 2)
		{
		  if (!strcmp (store_buf, item.dept_link))
		    {
		      print_profit_item ();
		    }
		}
	      if (kstate == 1)
		print_profit_item ();
	    }
	}
    }
  else
    {
      tot_sale_qty = 0;
      tot_sale_val = 0;
      set_ipoints ();
      rewind (item_file);
      rewind (billitem_file);
      while (fread (&item, sizeof (ITEM), 1, item_file))
	{
	  rewind (billitem_file);
	  fseek (billitem_file, start_point, SEEK_CUR);
	  date_qty = 0.00;
	  while (fread (&tbill_item, sizeof (BILL_ITEM), 1, billitem_file))
	    {
	      if (end_point == ftell (billitem_file))
		{
		  break;
		}
	      if (kstate == 1)
		if (!strcmp (tbill_item.stricode, item.item_code))
		  {
		    date_qty += tbill_item.qty;
		  }
	      if (kstate == 2)
		if (!strcmp (tbill_item.stricode, item.item_code))
		  {
		    if (!strcmp (tbill_item.dept_link, store_buf))
		      {
			date_qty += tbill_item.qty;
		      }
		  }
	      if (kstate == 3)
		if (!strcmp (tbill_item.stricode, code_buf))
		  {
		    date_qty += tbill_item.qty;
		  }
	    }
	  if (kstate == 1 || kstate == 2)
	    print_profit_item_date ();
	  if (kstate == 3)
	    {
	      print_profit_item_date ();
	      break;
	    }
	}
    }
  print_profit_item_total ();
  fclose (item_file);
  fclose (billitem_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
isman_init (PMENU * key_menu)
{
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
isman_title ()
{

  print_str
    ("No.     Name      Bills       BillsAmt     Commison    SalesManAmt", 70,
     LEFT_SIDE);
  print_line ();
  print_str
    ("------------------------------------------------------------------", 70,
     LEFT_SIDE);
  print_line ();
}

int
calc_sman ()
{
  ++no_of_bills;
  pay_tot_amt += tbill_detail.bill_payble;
}

int
print_sman ()
{
  char tbuf[40];
  double tval = 0, dval = 0;

  print_str (sman.smanno, 6, LEFT_SIDE);
  print_str (sman.smaname, 12, LEFT_SIDE);
  sprintf (tbuf, "%d", no_of_bills);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", pay_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);
  tval = atof (sman.scomison);
  sprintf (tbuf, "%f", tval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);
  tval = atof (sman.scomison);
  dval = tval * pay_tot_amt / 100;
  grand_tot_amt += dval;
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 15, RIGHT_SIDE);
  no_of_bills = 0;
  pay_tot_amt = 0;
  print_line ();
}

int
print_sman_total ()
{
  char tbuf[30];

  print_str
    ("------------------------------------------------------------------", 70,
     LEFT_SIDE);
  print_line ();
  print_str ("TOTAL COMMISION PAYBLE:", 25, RIGHT_SIDE);
  sprintf (tbuf, "%f", grand_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);

}

int
isman_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch, cman = 0;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  pbills = 0;
  nbills = 0;
  greport_title ();
  isman_title ();
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
  sman_file = fopen ("./pos_files/dbase/sman_ifile", "r");
  if ((rep_buf[0] != 'Y'))
    {
      strcpy (end_date, start_date);
      set_bpoints ();
    }
  zero_bill_detail ();
  while (fread (&sman, sizeof (WAITER), 1, sman_file))
    {
      if (sman.valid == 'Y')
	{
	  cman = atoi (sman.smanno);
	  rewind (bills_file);
	  if ((rep_buf[0] != 'Y'))
	    {
	      fseek (bills_file, blstart_point, SEEK_SET);
	    }
	  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
	    {
	      if (tbill_detail.valid == 'Y' && rep_buf[0] == 'Y')
		{
		  if (tbill_detail.sman_no == cman)
		    {
		      calc_sman ();
		    }
		}
	      if (tbill_detail.valid != 'Y' && rep_buf[0] != 'Y')
		{
		  if (tbill_detail.sman_no == cman)
		    {
		      calc_sman ();
		    }
		  if (blend_point == ftell (bills_file))
		    {
		      break;
		    }
		}
	    }
	  print_sman ();
	}
    }
  print_sman_total ();
  fclose (bills_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
isman_date_jump (void *key_menu)
{
  refresh_menu ((PMENU *) key_menu, 1, 0, 0);
}

int
waiter_init (PMENU * key_menu)
{
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
waiter_title ()
{

  print_str
    ("No.     Name      Bills       BillsAmt     Commison     Waiter-Amt", 70,
     LEFT_SIDE);
  print_line ();
  print_str
    ("------------------------------------------------------------------", 70,
     LEFT_SIDE);
  print_line ();
}

int
calc_waiter ()
{
  ++no_of_bills;
  pay_tot_amt += tbill_detail.bill_payble;
}

int
print_waiter ()
{
  char tbuf[40];
  double tval = 0, dval = 0;

  print_str (waiter.wtrno, 6, LEFT_SIDE);
  print_str (waiter.wtrname, 12, LEFT_SIDE);
  sprintf (tbuf, "%d", no_of_bills);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", pay_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);
  tval = atof (waiter.wtrcomison);
  sprintf (tbuf, "%f", tval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);
  tval = atof (waiter.wtrcomison);
  dval = tval * pay_tot_amt / 100;
  grand_tot_amt += dval;
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 15, RIGHT_SIDE);
  no_of_bills = 0;
  pay_tot_amt = 0;
  print_line ();
}

int
print_waiter_total ()
{
  char tbuf[30];

  print_str
    ("------------------------------------------------------------------", 70,
     LEFT_SIDE);
  print_line ();
  print_str ("TOTAL COMMISION PAYBLE:", 25, RIGHT_SIDE);
  sprintf (tbuf, "%f", grand_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);

}

int
iwaiter_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch, cman = 0;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  pbills = 0;
  nbills = 0;
  greport_title ();
  waiter_title ();
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
  waiter_file = fopen ("./pos_files/dbase/waiter_ifile", "r");
  if ((rep_buf[0] != 'Y'))
    {
      strcpy (end_date, start_date);
      set_bpoints ();
    }
  zero_bill_detail ();
  tot_owner_amt = 0;
  owner_bills = 0;
  while (fread (&waiter, sizeof (WAITER), 1, waiter_file))
    {
      if (waiter.valid == 'Y')
	{
	  cman = atoi (waiter.wtrno);
	  rewind (bills_file);
	  if ((rep_buf[0] != 'Y'))
	    {
	      fseek (bills_file, blstart_point, SEEK_SET);
	    }
	  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
	    {
	      if (tbill_detail.valid == 'Y' && rep_buf[0] == 'Y')
		{
		  if (tbill_detail.wtr_no == cman)
		    {
		      calc_waiter ();
		    }
		}
	      if (tbill_detail.valid != 'Y' && rep_buf[0] != 'Y')
		{
		  if (tbill_detail.wtr_no == cman)
		    {
		      calc_waiter ();
		    }
		  if (blend_point == ftell (bills_file))
		    {
		      break;
		    }
		}
	    }
	  print_waiter ();
	}
    }
  print_waiter_total ();
  fclose (bills_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
waiter_date_jump (void *key_menu)
{
  refresh_menu ((PMENU *) key_menu, 1, 0, 0);
}


int
cashman_init (PMENU * key_menu)
{
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
cashman_title ()
{

  print_str
    ("No.     Name      Bills       BillsAmt     Commison    Cash-ManAmt", 70,
     LEFT_SIDE);
  print_line ();
  print_str
    ("------------------------------------------------------------------", 70,
     LEFT_SIDE);
  print_line ();
}

int
calc_cashman ()
{
  ++no_of_bills;
  pay_tot_amt += tbill_detail.bill_payble;
}

int
print_cashman ()
{
  char tbuf[40];
  double tval = 0, dval = 0;

  print_str (cashman.cmanno, 6, LEFT_SIDE);
  print_str (cashman.cname, 12, LEFT_SIDE);
  sprintf (tbuf, "%d", no_of_bills);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", pay_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);
  tval = atof (cashman.commision);
  sprintf (tbuf, "%f", tval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);
  tval = atof (cashman.commision);
  dval = tval * pay_tot_amt / 100;
  grand_tot_amt += dval;
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 15, RIGHT_SIDE);
  no_of_bills = 0;
  pay_tot_amt = 0;
  print_line ();
}

int
print_owner ()
{
  char tbuf[40];
  double tval = 0, dval = 0;

  print_str ("0", 6, LEFT_SIDE);
  print_str ("OWNER", 12, LEFT_SIDE);
  sprintf (tbuf, "%d", owner_bills);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", tot_owner_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 14, RIGHT_SIDE);
#		if	0
  tval = 0;
  sprintf (tbuf, "%f", tval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);
  tval = atof (cashman.commision);
  dval = tval * pay_tot_amt / 100;
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 15, RIGHT_SIDE);
#	endif
  print_line ();
}

int
print_cashman_total ()
{
  char tbuf[30];

  print_str
    ("------------------------------------------------------------------", 70,
     LEFT_SIDE);
  print_line ();
  print_str ("TOTAL COMMISION PAYBLE:", 25, RIGHT_SIDE);
  sprintf (tbuf, "%f", grand_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);

}

int
icashman_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch, cman = 0;
  int owner_calc = 0;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  pbills = 0;
  nbills = 0;
  greport_title ();
  cashman_title ();
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
  cashman_file = fopen ("./pos_files/dbase/cashman_ifile", "r");
  if ((rep_buf[0] != 'Y'))
    {
      strcpy (end_date, start_date);
      set_bpoints ();
    }
  zero_bill_detail ();
  tot_owner_amt = 0;
  owner_bills = 0;
  owner_calc = 0;
  while (fread (&cashman, sizeof (CASHMAN), 1, cashman_file))
    {
      if (cashman.valid == 'Y')
	{
	  cman = atoi (cashman.cmanno);
	  rewind (bills_file);
	  if ((rep_buf[0] != 'Y'))
	    {
	      fseek (bills_file, blstart_point, SEEK_SET);
	    }
	  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
	    {
	      if (tbill_detail.valid == 'Y' && rep_buf[0] == 'Y')
		{
		  if (!tbill_detail.cashman_no)
		    {
		      if (!owner_calc)
			{
			  ++owner_bills;
			  tot_owner_amt += tbill_detail.bill_payble;
			}
		    }
		  if (tbill_detail.cashman_no == cman)
		    {
		      calc_cashman ();
		    }
		}
	      if (tbill_detail.valid != 'Y' && rep_buf[0] != 'Y')
		{
		  if (!tbill_detail.cashman_no)
		    {
		      if (!owner_calc)
			{
			  ++owner_bills;
			  tot_owner_amt += tbill_detail.bill_payble;
			}
		    }
		  if (tbill_detail.cashman_no == cman)
		    {
		      calc_cashman ();
		    }
		  if (blend_point == ftell (bills_file))
		    {
		      break;
		    }
		}
	    }
	  print_cashman ();
	}
      owner_calc = 1;
    }
  print_owner ();
  print_cashman_total ();
  fclose (bills_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
cashman_date_jump (void *key_menu)
{
  refresh_menu ((PMENU *) key_menu, 1, 0, 0);
}

int
billsum_init (PMENU * key_menu)
{
  sect_buf[0] = '1';
  sect_buf[1] = 0;
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
billsum_title ()
{
  print_str
    ("BillNo     Basic-Amt   Tax-Amt   Misc-Amt    Service    Discount      Total CMAN",
     80, LEFT_SIDE);
  print_line ();
  print_str
    ("--------------------------------------------------------------------------------",
     80, LEFT_SIDE);
  print_line ();
}

int
calc_billsum ()
{
  tot_basic_amt += tbill_detail.bill_total;
  tot_misc_amt += tbill_detail.bill_pmisc;
  tot_misc_amt += tbill_detail.bill_nmisc;
  tot_serv_amt += tbill_detail.bill_serv;
  tot_disc_amt += tbill_detail.bill_perdamt;
  tot_disc_amt += tbill_detail.bill_amtdisc;
  tot_tax_amt += tbill_detail.bill_tax;
  tot_tax_amt += tbill_detail.bill_taxon;
  /* tot_refund_amt; */
  pay_tot_amt += tbill_detail.bill_payble;
  if (tbill_detail.bill_payble < 0)
    nbills++;
  else
    pbills++;
}

int
print_billsum ()
{
  char tbuf[50];

  sprintf (tbuf, "%d", tbill_detail.bill_no);
  print_str (tbuf, 6, LEFT_SIDE);

  sprintf (tbuf, "%f", tbill_detail.bill_total);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);

  sprintf (tbuf, "%f", tbill_detail.bill_tax + tbill_detail.bill_taxon);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);

  sprintf (tbuf, "%f", tbill_detail.bill_pmisc + tbill_detail.bill_nmisc);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);

  sprintf (tbuf, "%f", tbill_detail.bill_serv);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);

  sprintf (tbuf, "%f", tbill_detail.bill_perdamt + tbill_detail.bill_amtdisc);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);

  sprintf (tbuf, "%f", tbill_detail.bill_payble);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);

  print_str ("man", 4, RIGHT_SIDE);
  print_line ();
}

int
print_billsum_total ()
{
  char tbuf[40];

  print_str
    ("--------------------------------------------------------------------------------",
     80, LEFT_SIDE);
  print_line ();
  print_str ("TOTAL:", 6, LEFT_SIDE);

  sprintf (tbuf, "%f", tot_basic_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);

  sprintf (tbuf, "%f", tot_tax_amt + tot_taxon_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);

  sprintf (tbuf, "%f", tot_misc_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);

  sprintf (tbuf, "%f", tot_serv_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);

  sprintf (tbuf, "%f", tot_disc_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);

  sprintf (tbuf, "%f", pay_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 13, RIGHT_SIDE);

  print_str ("   ", 4, RIGHT_SIDE);
  print_line ();
  print_line ();

  sprintf (tbuf, "%d", pbills);
  print_str ("No Of Regular Bills :", 22, LEFT_SIDE);
  print_str (tbuf, 5, RIGHT_SIDE);
  print_line ();
  sprintf (tbuf, "%d", nbills);
  print_str ("No Of Refund Bills  :", 22, LEFT_SIDE);
  print_str (tbuf, 5, RIGHT_SIDE);
  print_line ();
  print_line ();
  print_line ();
}

int
billsum_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  char temp[20];
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  pbills = 0;
  nbills = 0;
  greport_title ();
  billsum_title ();
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
  if ((rep_buf[0] != 'Y'))
    {
      strcpy (end_date, start_date);
      set_bpoints ();
    }
  zero_bill_detail ();
  rewind (bills_file);
  if ((rep_buf[0] != 'Y'))
    {
      fseek (bills_file, blstart_point, SEEK_SET);
    }
  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
    {
      if (tbill_detail.valid == 'Y' && rep_buf[0] == 'Y')
	{
	  calc_billsum ();
	  print_billsum ();
	}
      if (tbill_detail.valid != 'Y' && rep_buf[0] != 'Y')
	{
	  calc_billsum ();
	  print_billsum ();
	  if (blend_point == ftell (bills_file))
	    {
	      break;
	    }
	}
    }
  print_billsum_total ();
  fclose (bills_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
billsum_sect_jump (void *key_menu)
{
  pfield = &billsum_flds;
  if (kstate == 1)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[1].type = CHECK;
      rep_buf[0] = 'Y';
      rep_buf[1] = 0;
    }
  if (kstate == 2)
    {
      (*pfield)[2].type = DATE;
      (*pfield)[1].type = DISP;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 2, 0, 0);
}

int
billsum_date_jump (void *key_menu)
{
  rep_buf[0] = 'N';
  rep_buf[1] = 0;
  refresh_menu ((PMENU *) key_menu, 3, 0, 0);
}

int
taxsum_init (PMENU * key_menu)
{
  sect_buf[0] = '1';
  sect_buf[1] = 0;
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
taxsum_title ()
{
  TAX ttax;

  tax_file = fopen ("./pos_files/dbase/tax_ifile", "r");
  fread (&ttax, sizeof (TAX), 1, tax_file);
  if (ttax.valid)
    {
      if (atoi (ttax.tax_no) == 1)
	{
	  print_str ("Tax1 =", 8, LEFT_SIDE);
	  print_str (ttax.tname, 12, LEFT_SIDE);
	  print_str ("Cess1 =", 9, LEFT_SIDE);
	  print_str (ttax.toname, 12, LEFT_SIDE);
	  print_line ();
	  print_line ();
	}
      fread (&ttax, sizeof (TAX), 1, tax_file);
      if (atoi (ttax.tax_no) == 2)
	{
	  print_str ("Tax2 =", 8, LEFT_SIDE);
	  print_str (ttax.tname, 12, LEFT_SIDE);
	  print_str ("Cess2 =", 9, LEFT_SIDE);
	  print_str (ttax.toname, 12, LEFT_SIDE);
	  print_line ();
	  print_line ();
	}
      fread (&ttax, sizeof (TAX), 1, tax_file);
      if (atoi (ttax.tax_no) == 3)
	{
	  print_str ("Tax3 =", 8, LEFT_SIDE);
	  print_str (ttax.tname, 12, LEFT_SIDE);
	  print_str ("Cess3 =", 9, LEFT_SIDE);
	  print_str (ttax.toname, 12, LEFT_SIDE);
	  print_line ();
	  print_line ();
	}
      fread (&ttax, sizeof (TAX), 1, tax_file);
      if (atoi (ttax.tax_no) == 4)
	{
	  print_str ("Tax4 =", 8, LEFT_SIDE);
	  print_str (ttax.tname, 12, LEFT_SIDE);
	  print_str ("Cess4 =", 9, LEFT_SIDE);
	  print_str (ttax.toname, 12, LEFT_SIDE);
	  print_line ();
	  print_line ();
	}
    }

  print_str
    ("BNo.        Tax1   Cess1       Tax2   Cess2      Tax3   Cess3      Tax4   Cess4",
     80, LEFT_SIDE);
  print_str
    ("--------------------------------------------------------------------------------",
     80, LEFT_SIDE);
}

int
calc_taxsum ()
{
  tot_tax1_amt += tbill_detail.bill_tax1;
  tot_taxon1_amt += tbill_detail.bill_taxon1;
  tot_tax2_amt += tbill_detail.bill_tax2;
  tot_taxon2_amt += tbill_detail.bill_taxon2;
  tot_tax3_amt += tbill_detail.bill_tax3;
  tot_taxon3_amt += tbill_detail.bill_taxon3;
  tot_tax4_amt += tbill_detail.bill_tax4;
  tot_taxon4_amt += tbill_detail.bill_taxon4;
  pay_tot_amt += tbill_detail.bill_payble;
  if (tbill_detail.bill_payble < 0)
    nbills++;
  else
    pbills++;
}

int
print_taxsum ()
{
  char tbuf[40];
  sprintf (tbuf, "%d", tbill_detail.bill_no);
  print_str (tbuf, 5, LEFT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_tax1);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_taxon1);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_tax2);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_taxon2);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_tax3);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_taxon3);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_tax4);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_taxon4);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  print_line ();
}

int
print_taxsum_total ()
{
  char tbuf[40];
  double dval;
  print_str
    ("-------------------------------------------------------------------------------",
     79, RIGHT_SIDE);
  print_line ();
  print_str ("TOTAL", 5, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax1_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon1_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax2_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon2_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax3_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon3_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax4_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon4_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 8, RIGHT_SIDE);
  print_line ();
  print_line ();
  dval = tot_tax1_amt + tot_taxon1_amt + tot_tax2_amt + tot_taxon2_amt;
  dval += tot_tax3_amt + tot_taxon3_amt + tot_tax4_amt + tot_taxon4_amt;
  print_str ("Total Tax Payble    :", 22, LEFT_SIDE);
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);
  print_line ();
  sprintf (tbuf, "%d", pbills);
  print_str ("No Of Regular Bills :", 22, LEFT_SIDE);
  print_str (tbuf, 12, RIGHT_SIDE);
  print_line ();
  sprintf (tbuf, "%d", nbills);
  print_str ("No Of Refund Bills  :", 22, LEFT_SIDE);
  print_str (tbuf, 12, RIGHT_SIDE);
  print_line ();
  print_line ();
  print_line ();
}

int
taxsum_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  pbills = 0;
  nbills = 0;
  greport_title ();
  taxsum_title ();
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
  if ((rep_buf[0] != 'Y'))
    {
      strcpy (end_date, start_date);
      set_bpoints ();
    }
  zero_bill_detail ();
  rewind (bills_file);
  if ((rep_buf[0] != 'Y'))
    {
      fseek (bills_file, blstart_point, SEEK_SET);
    }
  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
    {
      if (tbill_detail.valid == 'Y' && rep_buf[0] == 'Y')
	{
	  calc_taxsum ();
	  print_taxsum ();
	}
      if (tbill_detail.valid != 'Y' && rep_buf[0] != 'Y')
	{
	  calc_taxsum ();
	  print_taxsum ();
	  if (blend_point == ftell (bills_file))
	    {
	      break;
	    }
	}
    }
  print_taxsum_total ();
  fclose (bills_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
taxsum_sect_jump (void *key_menu)
{
  pfield = &taxsum_flds;
  if (kstate == 1)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[1].type = CHECK;
      rep_buf[0] = 'Y';
      rep_buf[1] = 0;
    }
  if (kstate == 2)
    {
      (*pfield)[2].type = DATE;
      (*pfield)[1].type = DISP;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 2, 0, 0);
}

int
taxsum_date_jump (void *key_menu)
{
  rep_buf[0] = 'N';
  rep_buf[1] = 0;
  refresh_menu ((PMENU *) key_menu, 3, 0, 0);
}

int
finan_init (PMENU * key_menu)
{

  sect_buf[0] = '1';
  sect_buf[1] = 0;
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
zero_bill_detail ()
{
  tot_tax_amt = 0;
  tot_taxon_amt = 0;
  tot_basic_amt = 0;
  pay_tot_amt = 0;
  tot_card_amt = 0;
  tot_cash_amt = 0;
  tot_credit_amt = 0;
  tot_chq_amt = 0;
  tot_misc_amt = 0;
  tot_misc_amt = 0;
  tot_serv_amt = 0;
  tot_disc_amt = 0;
  tot_disc_amt = 0;
  tot_tax1_amt = 0;
  tot_taxon1_amt = 0;
  tot_tax2_amt = 0;
  tot_taxon2_amt = 0;
  tot_tax3_amt = 0;
  tot_taxon3_amt = 0;
  tot_tax4_amt = 0;
  tot_taxon4_amt = 0;
  /* tot_refund_amt; */
  tot_drawer_amt = 0;
  grand_tot_amt = 0;
  pay_tot_amt = 0;
}

int
calc_bill_detail ()
{
  tot_card_amt += tbill_detail.card_amt;
  tot_cash_amt += tbill_detail.cash_amt;
  tot_credit_amt += tbill_detail.credit_amt;
  tot_chq_amt += tbill_detail.chq_amt;
  tot_misc_amt += tbill_detail.bill_pmisc;
  tot_misc_amt += tbill_detail.bill_nmisc;
  tot_serv_amt += tbill_detail.bill_serv;
  tot_disc_amt += tbill_detail.bill_perdamt;
  tot_disc_amt += tbill_detail.bill_amtdisc;
  tot_tax1_amt += tbill_detail.bill_tax1;
  tot_taxon1_amt += tbill_detail.bill_taxon1;
  tot_tax2_amt += tbill_detail.bill_tax2;
  tot_taxon2_amt += tbill_detail.bill_taxon2;
  tot_tax3_amt += tbill_detail.bill_tax3;
  tot_taxon3_amt += tbill_detail.bill_taxon3;
  tot_tax4_amt += tbill_detail.bill_tax4;
  tot_taxon4_amt += tbill_detail.bill_taxon4;
  /* tot_refund_amt; */
  tot_drawer_amt += tbill_detail.cash_amt;
  grand_tot_amt += tbill_detail.cash_amt;
  grand_tot_amt += tbill_detail.chq_amt;
  grand_tot_amt += tbill_detail.card_amt;
  grand_tot_amt += tbill_detail.credit_amt;
}

int
print_finance ()
{
  char tbuf[100];
  print_str ("FINANCIAL SUMMRAY ", 20, RIGHT_SIDE);
  print_line ();
  print_str ("----------------- ", 20, RIGHT_SIDE);
  print_line ();
  print_line ();

  print_str ("cash Sales Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_cash_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("card Sales Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_card_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("credit Sales Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_credit_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("chque Sales Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_chq_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("miscelenious Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_misc_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("service  Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_serv_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("discount Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_disc_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("Tax1 Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax1_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str (" Tax1 On Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon1_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str (" Tax2  Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax2_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str (" Tax2 On Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon2_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str (" Tax3  Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax3_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str (" Tax3 On Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon3_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str (" Tax4 Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_tax4_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str (" Tax4 On Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_taxon4_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  /* tot_refund_amt; */

  print_str ("cash drawer Amt :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_drawer_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

  print_str ("GRAND TOTAL AMT :", 20, RIGHT_SIDE);
  sprintf (tbuf, "%f", grand_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();

}

int
finan_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;
  char temp[20];

  rep_buf[0] = toupper (rep_buf[0]);
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  greport_title ();
  pbills = 0;
  nbills = 0;
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
  if ((rep_buf[0] != 'Y'))
    {
      set_bpoints ();
    }
  zero_bill_detail ();
  rewind (bills_file);
  if ((rep_buf[0] != 'Y'))
    {
      fseek (bills_file, blstart_point, SEEK_SET);
    }
  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
    {
      if (tbill_detail.valid == 'Y' && rep_buf[0] == 'Y')
	{
	  calc_billsum ();
	}
      if (tbill_detail.valid != 'Y' && rep_buf[0] != 'Y')
	{
	  calc_billsum ();
	  if (blend_point == ftell (bills_file))
	    {
	      break;
	    }
	}
    }
  print_finance ();
  fclose (bills_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
finan_sect_jump (void *key_menu)
{
  pfield = &finan_flds;
  if (kstate == 1)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[1].type = CHECK;
      rep_buf[0] = 'Y';
      rep_buf[1] = 0;
    }
  if (kstate == 2)
    {
      (*pfield)[2].type = DATE;
      (*pfield)[1].type = DISP;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 2, 0, 0);
}

int
finan_date_jump (void *key_menu)
{
  if ((strlen (start_date) == 8) && (strlen (end_date) == 8))
    {
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 4, 1, 0);
}

int
detail_init (PMENU * key_menu)
{
  if (kstate == 1)
    {
      rep_buf[0] = 'Y';
      rep_buf[1] = 0;
    }
  else
    {
      rep_buf[1] = 0;
    }
}

int
print_idetail_title ()
{
  print_str
    ("CODE     NAME           UNIT  HKEY  SELL-PRICE  COST-PRICE STORE  KIT TAX",
     79, LEFT_SIDE);
  print_line ();
  print_str
    ("-------------------------------------------------------------------------",
     79, LEFT_SIDE);
  print_line ();
}

int
print_item_detail ()
{
  char tbuf[40];
  double dval;

  ++ifound;
  print_str (item.item_code, 7, LEFT_SIDE);
  print_str (item.item_name, 18, LEFT_SIDE);
  if (strlen (item.unit))
    {
      print_str (item.unit, 5, LEFT_SIDE);
    }
  else
    {
      print_str (" ", 5, LEFT_SIDE);
    }
  if (strlen (item.hkey))
    {
      print_str (item.hkey, 3, RIGHT_SIDE);
    }
  else
    {
      print_str (" ", 3, RIGHT_SIDE);
    }
  dval = atof (item.sell_price);
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);
  print_str ("  ", 3, RIGHT_SIDE);
  dval = atof (item.cost_price);
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 10, RIGHT_SIDE);
  print_str (" ", 2, LEFT_SIDE);
  if (strlen (item.dept_link))
    {
      print_str (item.dept_link, 3, LEFT_SIDE);
    }
  else
    {
      print_str ("  ", 3, RIGHT_SIDE);
    }
  if (strlen (item.kit_link))
    {
      print_str (item.kit_link, 6, RIGHT_SIDE);
    }
  else
    {
      print_str ("  ", 6, RIGHT_SIDE);
    }
  if (strlen (item.tax_link))
    {
      print_str (item.tax_link, 3, RIGHT_SIDE);
    }
  else
    {
      print_str (" ", 3, RIGHT_SIDE);
    }
  print_line ();
}

int
print_idetail_total ()
{
  char tbuf[40];

  print_str
    ("------------------------------------------------------------------------",
     79, LEFT_SIDE);
  print_line ();
  sprintf (tbuf, "%d", ifound);
  print_str ("TOTAL ITEMS FOUND :", 22, LEFT_SIDE);
  print_str (tbuf, 5, RIGHT_SIDE);
  print_line ();
}

int
idetail_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  if (kstate == 2)
    {
      if (store_buf[0] == 0)
	{
	  set_error (" Store Not Entered ");
	  return RET_STAY;
	}
    }
  if (kstate == 3)
    {
      if (code_buf[0] == 0)
	{
	  set_error (" Item Code Not Entered ");
	  return RET_STAY;
	}
    }

  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  ifound = 0;
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  greport_title ();
  print_idetail_title ();
  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
  while (fread (&item, sizeof (ITEM), 1, item_file))
    {
      if (item.valid == 'Y')
	{
	  if (kstate == 1)
	    print_item_detail ();
	  if (kstate == 2)
	    {
	      if (!strcmp (store_buf, item.dept_link))
		{
		  print_item_detail ();
		}
	    }
	  if (kstate == 3)
	    {
	      if (!strcmp (code_buf, item.kit_link))
		{
		  print_item_detail ();
		}
	    }
	}
    }
  print_idetail_total ();
  fclose (item_file);
  rewind (print_file);
  if (printer_on)
    {
      if (!to_printer ())
	{
	  curs_set (0);
	  return RET_PRIV;
	}
    }
  else
    {
      display_on ();
    }
  return RET_PRIV;
}

int
detail_jump (void *key_menu)
{
  pfield = &idetail_flds;
  if (kstate == 1)
    {
      (*pfield)[1].type = DISP;
      (*pfield)[2].type = DISP;
    }
  if (kstate == 2)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[1].type = DIGIT;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  if (kstate == 3)
    {
      (*pfield)[1].type = DISP;
      (*pfield)[2].type = DIGIT;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 1, 0, 0);
}

int
reset_cancel_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;

  return RET_PRIV;
}

int
reset_stock ()
{
  item_file = fopen ("./pos_files/dbase/item_ifile", "r+");
  while (fread (&item, sizeof (ITEM), 1, item_file))
    {
      if (item.valid == 'Y')
	{
	  item.today_sale_qty = 0;
	  item.curr_stock = 0;
	  item.stock_in = 0;
	  item.stock_out = 0;
	  item.open_stock = 0;
	  fseek (item_file, -sizeof (ITEM), SEEK_CUR);
	  fwrite (&item, sizeof (ITEM), 1, item_file);
	}
    }
  fflush (item_file);
  fclose (item_file);
}

int
reset_billtax_sum ()
{

  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r+");
  while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
    {
      tbill_detail.valid = 'N';
      fseek (bills_file, -sizeof (BILL_DETAIL), SEEK_CUR);
      fwrite (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file);
    }
  fflush (bills_file);
  fclose (bills_file);
}

int
reset_sales ()
{

  item_file = fopen ("./pos_files/dbase/item_ifile", "r+");
  while (fread (&item, sizeof (ITEM), 1, item_file))
    {
      item.today_sale_qty = 0;
      fseek (item_file, -sizeof (ITEM), SEEK_CUR);
      fwrite (&item, sizeof (ITEM), 1, item_file);
    }
  fflush (item_file);
  fclose (item_file);
  billitem_file = fopen ("./pos_files/dbase/billitem_ifile", "r+");
  while (fread (&tbill_item, sizeof (BILL_ITEM), 1, billitem_file))
    {
      tbill_item.valid = 'N';
      fseek (billitem_file, -sizeof (BILL_ITEM), SEEK_CUR);
      fwrite (&tbill_item, sizeof (BILL_ITEM), 1, billitem_file);
    }
  fflush (billitem_file);
  fclose (billitem_file);
}

int
reset_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  if (kstate == 1)
    {
      reset_sales ();
      reset_billtax_sum ();
    }
  if (kstate == 2)
    {
      reset_stock ();
    }
  return RET_PRIV;
}

int
custmr_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  return RET_PRIV;
}

int
custmr_jump (void *key_menu)
{
  refresh_menu ((PMENU *) key_menu, 1, 0, 0);
}

int
custmr_init (PMENU * key_menu)
{
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
set_cardpoints ()
{
  int got_date = 0;

  rewind (card_file);
  got_date = 0;
  while (fread (&tcard_detail, sizeof (CARD_DETAIL), 1, card_file))
    {
      if (!strcmp (start_date, tcard_detail.date))
	{
	  got_date = 1;
	  break;
	}
    }
  if (got_date)
    {
      got_date = 0;
      fseek (card_file, -sizeof (CARD_DETAIL), SEEK_CUR);
      blstart_point = ftell (card_file);
      rewind (card_file);
      if (!strcmp (end_date, start_date))
	{
	  while (fread (&tcard_detail, sizeof (CARD_DETAIL), 1, card_file))
	    {
	      if (!strcmp (end_date, tcard_detail.date))
		{
		  blend_point = ftell (card_file);
		  got_date = 1;
		}
	    }
	}
      else
	{
	  while (fread (&tcard_detail, sizeof (CARD_DETAIL), 1, card_file))
	    {
	      if (!strcmp (end_date, tcard_detail.date))
		{
		  got_date = 1;
		  blend_point = ftell (card_file);
		}
	    }
	}
      if (!got_date)
	{
	  fseek (card_file, 0, SEEK_END);
	  blend_point = ftell (card_file);
	}
    }
  else
    {
      fseek (card_file, 0, SEEK_END);
      blstart_point = ftell (card_file);
      blend_point = ftell (card_file);
    }
  rewind (card_file);
  refresh ();
}

int
set_chqpoints ()
{
  int got_date = 0;

  rewind (chq_file);
  got_date = 0;
  while (fread (&tchq_detail, sizeof (CHQ_DETAIL), 1, chq_file))
    {
      if (!strcmp (start_date, tchq_detail.date))
	{
	  got_date = 1;
	  break;
	}
    }
  if (got_date)
    {
      got_date = 0;
      fseek (chq_file, -sizeof (CHQ_DETAIL), SEEK_CUR);
      blstart_point = ftell (chq_file);
      rewind (chq_file);
      if (!strcmp (end_date, start_date))
	{
	  while (fread (&tchq_detail, sizeof (CHQ_DETAIL), 1, chq_file))
	    {
	      if (!strcmp (end_date, tchq_detail.date))
		{
		  blend_point = ftell (chq_file);
		  got_date = 1;
		}
	    }
	}
      else
	{
	  while (fread (&tchq_detail, sizeof (CHQ_DETAIL), 1, chq_file))
	    {
	      if (!strcmp (end_date, tchq_detail.date))
		{
		  got_date = 1;
		  blend_point = ftell (chq_file);
		}
	    }
	}
      if (!got_date)
	{
	  fseek (chq_file, 0, SEEK_END);
	  blend_point = ftell (chq_file);
	}
    }
  else
    {
      fseek (chq_file, 0, SEEK_END);
      blstart_point = ftell (chq_file);
      blend_point = ftell (chq_file);
    }
  rewind (chq_file);
  refresh ();
}

int
set_creditpoints ()
{
  int got_date = 0;

  rewind (credit_file);
  got_date = 0;
  while (fread (&tcredit_detail, sizeof (CREDIT_DETAIL), 1, credit_file))
    {
      if (!strcmp (start_date, tcredit_detail.date))
	{
	  got_date = 1;
	  break;
	}
    }
  if (got_date)
    {
      got_date = 0;
      fseek (credit_file, -sizeof (CREDIT_DETAIL), SEEK_CUR);
      blstart_point = ftell (credit_file);
      rewind (credit_file);
      if (!strcmp (end_date, start_date))
	{
	  while (fread
		 (&tcredit_detail, sizeof (CREDIT_DETAIL), 1, credit_file))
	    {
	      if (!strcmp (end_date, tcredit_detail.date))
		{
		  blend_point = ftell (credit_file);
		  got_date = 1;
		}
	    }
	}
      else
	{
	  while (fread
		 (&tcredit_detail, sizeof (CREDIT_DETAIL), 1, credit_file))
	    {
	      if (!strcmp (end_date, tcredit_detail.date))
		{
		  got_date = 1;
		  blend_point = ftell (credit_file);
		}
	    }
	}
      if (!got_date)
	{
	  fseek (credit_file, 0, SEEK_END);
	  blend_point = ftell (credit_file);
	}
    }
  else
    {
      fseek (credit_file, 0, SEEK_END);
      blstart_point = ftell (credit_file);
      blend_point = ftell (credit_file);
    }
  rewind (credit_file);
  refresh ();
}

int
general_init (PMENU * key_menu)
{
  sect_buf[0] = '1';
  sect_buf[1] = 0;
  rep_buf[0] = 'Y';
  rep_buf[1] = 0;
}

int
general_title ()
{
  print_str
    ("BillNo     Cash-Amt   Card-Amt    Chq-Amt  Credit-Amt  Total-Amt   Date   Time",
     80, LEFT_SIDE);
  print_line ();
  print_str
    ("--------------------------------------------------------------------------------",
     80, LEFT_SIDE);
  print_line ();
}

int
calc_general ()
{
  tot_cash_amt += tbill_detail.cash_amt;
  tot_card_amt += tbill_detail.card_amt;
  tot_credit_amt += tbill_detail.credit_amt;
  tot_chq_amt += tbill_detail.chq_amt;
  pay_tot_amt += tbill_detail.bill_payble;
  if (tbill_detail.bill_payble < 0)
    nbills++;
  else
    pbills++;
}

int
print_general ()
{
  char tbuf[50];

  sprintf (tbuf, "%d", tbill_detail.bill_no);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.cash_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.card_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.chq_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.credit_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", tbill_detail.bill_payble);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);

  print_str (tbill_detail.date, 9, RIGHT_SIDE);
  strcpy (tbuf, tbill_detail.time);
  tbuf[5] = 0;
  print_str (tbuf, 6, RIGHT_SIDE);
  print_line ();
}

int
print_general_total ()
{
  char tbuf[40];

  print_str
    ("--------------------------------------------------------------------------------",
     80, LEFT_SIDE);
  print_line ();
  print_str ("TOTAL:", 6, LEFT_SIDE);
  sprintf (tbuf, "%f", tot_cash_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_card_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_chq_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_credit_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 11, RIGHT_SIDE);
  sprintf (tbuf, "%f", pay_tot_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 12, RIGHT_SIDE);
  print_line ();
  print_line ();
  sprintf (tbuf, "%d", pbills);
  print_str ("No Of Regular Bills :", 22, LEFT_SIDE);
  print_str (tbuf, 5, RIGHT_SIDE);
  print_line ();
  sprintf (tbuf, "%d", nbills);
  print_str ("No Of Refund Bills  :", 22, LEFT_SIDE);
  print_str (tbuf, 5, RIGHT_SIDE);
  print_line ();
  print_line ();
  print_line ();
}

int
card_title ()
{
  print_str
    ("BillNo       Card-Amt           Card-No   Card-Name    Date     Time  ",
     79, LEFT_SIDE);
  print_line ();
  print_str
    ("---------------------------------------------------------------------------",
     79, LEFT_SIDE);
  print_line ();
}

int
calc_card ()
{
  no_of_trans++;
  tot_card_amt += tcard_detail.card_amt;
}

int
print_card ()
{
  char tbuf[40];

  sprintf (tbuf, "%d", tcard_detail.bill_no);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", tcard_detail.card_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_str (tcard_detail.card_no, 18, RIGHT_SIDE);
  print_str (tcard_detail.card_name, 11, RIGHT_SIDE);
  print_str (tcard_detail.date, 11, RIGHT_SIDE);
  print_str (tcard_detail.time, 11, RIGHT_SIDE);
  print_line ();
}

int
print_card_total ()
{
  char tbuf[40];

  print_str
    ("---------------------------------------------------------------------------",
     79, LEFT_SIDE);
  print_line ();
  print_str ("TOTAL:", 6, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_card_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();
  print_line ();
  print_str ("Total Cards swiped :", 22, LEFT_SIDE);
  sprintf (tbuf, "%d", no_of_trans);
  print_str (tbuf, 5, RIGHT_SIDE);
}

int
chq_title ()
{
  print_str
    ("BillNo       Cheq-Amt   Cheq-No           Cust-Name       Date     Time  ",
     79, LEFT_SIDE);
  print_line ();
  print_str
    ("---------------------------------------------------------------------------",
     79, LEFT_SIDE);
  print_line ();
}

int
calc_chq ()
{
  no_of_trans++;
  tot_chq_amt += tchq_detail.chq_amt;
}

int
print_chq ()
{
  char tbuf[40];

  sprintf (tbuf, "%d", tchq_detail.bill_no);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", tchq_detail.chq_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_str (tchq_detail.chq_no, 9, RIGHT_SIDE);
  print_str (tchq_detail.cust_name, 22, RIGHT_SIDE);
  print_str (tchq_detail.date, 11, RIGHT_SIDE);
  print_str (tchq_detail.time, 11, RIGHT_SIDE);
  print_line ();
}

int
print_chq_total ()
{
  char tbuf[40];

  print_str
    ("---------------------------------------------------------------------------",
     79, LEFT_SIDE);
  print_line ();
  print_str ("TOTAL:", 6, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_chq_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();
  print_line ();
  print_str ("Total Chqe Transactions :", 25, LEFT_SIDE);
  sprintf (tbuf, "%d", no_of_trans);
  print_str (tbuf, 5, RIGHT_SIDE);
}

int
credit_title ()
{
  print_str ("BillNo       Credit-Amt    Customer-No    Date     Time  ", 67,
	     LEFT_SIDE);
  print_line ();
  print_str ("---------------------------------------------------------", 67,
	     LEFT_SIDE);
  print_line ();
}

calc_credit ()
{
  no_of_trans++;
  tot_credit_amt += tcredit_detail.credit_amt;
}

print_credit ()
{
  char tbuf[40];

  sprintf (tbuf, "%d", tcredit_detail.bill_no);
  print_str (tbuf, 6, LEFT_SIDE);
  sprintf (tbuf, "%f", tcredit_detail.credit_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  sprintf (tbuf, "%d", tcredit_detail.cust_no);
  print_str (tbuf, 9, RIGHT_SIDE);
  print_str (tcredit_detail.date, 16, RIGHT_SIDE);
  print_str (tcredit_detail.time, 11, RIGHT_SIDE);
  print_line ();
}

int
print_credit_total ()
{
  char tbuf[40];

  print_str ("---------------------------------------------------------", 67,
	     LEFT_SIDE);
  print_line ();
  print_str ("TOTAL:", 6, RIGHT_SIDE);
  sprintf (tbuf, "%f", tot_credit_amt);
  put_accurate (tbuf, PRICE_ACT);
  print_str (tbuf, 16, RIGHT_SIDE);
  print_line ();
  print_line ();
  print_str ("Total Credit Transactions :", 29, LEFT_SIDE);
  sprintf (tbuf, "%d", no_of_trans);
  print_str (tbuf, 5, RIGHT_SIDE);

}

int
general_do_ok (void *key_menu)
{
  int lines_count, i, left = 0, ch;
  char temp[20];
  PMENU *menu;

  rep_buf[0] = toupper (rep_buf[0]);
  menu = (PMENU *) key_menu;
  keypad (stdscr, TRUE);
  curs_set (0);
  clear ();
  refresh ();
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  pbills = 0;
  nbills = 0;
  greport_title ();
  if (kstate == 1)
    {
      general_title ();
      bills_file = fopen ("./pos_files/dbase/bills_ifile", "r");
      if ((rep_buf[0] != 'Y'))
	{
	  strcpy (end_date, start_date);
	  set_bpoints ();
	}
      zero_bill_detail ();
      rewind (bills_file);
      if ((rep_buf[0] != 'Y'))
	{
	  fseek (bills_file, blstart_point, SEEK_SET);
	}
      while (fread (&tbill_detail, sizeof (BILL_DETAIL), 1, bills_file))
	{
	  if (((rep_buf[0] == 'Y')) && (tbill_detail.valid == 'Y'))
	    {
	      calc_general ();
	      print_general ();
	    }
	  else
	    {
	      calc_general ();
	      print_general ();
	    }
	  if ((rep_buf[0] != 'Y'))
	    {
	      if (blend_point == ftell (bills_file))
		{
		  break;
		}
	    }
	}
      print_general_total ();
      fclose (bills_file);
      rewind (print_file);
      if (printer_on)
	{
	  if (!to_printer ())
	    {
	      curs_set (0);
	      return RET_PRIV;
	    }
	}
      else
	{
	  display_on ();
	}
    }
  if (kstate == 2)
    {
      card_title ();
      card_file = fopen ("./pos_files/dbase/card_ifile", "r");
      if ((rep_buf[0] != 'Y'))
	{
	  strcpy (end_date, start_date);
	  set_cardpoints ();
	}
      zero_bill_detail ();
      rewind (card_file);
      if ((rep_buf[0] != 'Y'))
	{
	  fseek (card_file, blstart_point, SEEK_SET);
	}
      while (fread (&tcard_detail, sizeof (CARD_DETAIL), 1, card_file))
	{
	  if (tcard_detail.valid == 'Y' && rep_buf[0] == 'Y')
	    {
	      calc_card ();
	      print_card ();
	    }
	  if (tcard_detail.valid != 'Y' && rep_buf[0] != 'Y')
	    {
	      calc_card ();
	      print_card ();
	      if (blend_point == ftell (card_file))
		{
		  break;
		}
	    }
	}
      print_card_total ();
      fclose (card_file);
      rewind (print_file);
      if (printer_on)
	{
	  if (!to_printer ())
	    {
	      curs_set (0);
	      return RET_PRIV;
	    }
	}
      else
	{
	  display_on ();
	}
    }
  if (kstate == 3)
    {
      chq_title ();
      chq_file = fopen ("./pos_files/dbase/chq_ifile", "r");
      if ((rep_buf[0] != 'Y'))
	{
	  strcpy (end_date, start_date);
	  set_chqpoints ();
	}
      zero_bill_detail ();
      rewind (chq_file);
      if ((rep_buf[0] != 'Y'))
	{
	  fseek (chq_file, blstart_point, SEEK_SET);
	}
      while (fread (&tchq_detail, sizeof (CHQ_DETAIL), 1, chq_file))
	{
	  if (tchq_detail.valid == 'Y' && rep_buf[0] == 'Y')
	    {
	      calc_chq ();
	      print_chq ();
	    }
	  if (tchq_detail.valid != 'Y' && rep_buf[0] != 'Y')
	    {
	      calc_chq ();
	      print_chq ();
	      if (blend_point == ftell (chq_file))
		{
		  break;
		}
	    }
	}
      print_chq_total ();
      fclose (chq_file);
      rewind (print_file);
      if (printer_on)
	{
	  if (!to_printer ())
	    {
	      curs_set (0);
	      return RET_PRIV;
	    }
	}
      else
	{
	  display_on ();
	}
    }
  if (kstate == 4)
    {
      credit_title ();
      credit_file = fopen ("./pos_files/dbase/credit_ifile", "r");
      if ((rep_buf[0] != 'Y'))
	{
	  strcpy (end_date, start_date);
	  set_bpoints ();
	}
      zero_bill_detail ();
      rewind (credit_file);
      if ((rep_buf[0] != 'Y'))
	{
	  fseek (credit_file, blstart_point, SEEK_SET);
	}
      while (fread (&tcredit_detail, sizeof (CREDIT_DETAIL), 1, credit_file))
	{
	  if (tcredit_detail.valid == 'Y' && rep_buf[0] == 'Y')
	    {
	      calc_credit ();
	      print_credit ();
	    }
	  if (tcredit_detail.valid != 'Y' && rep_buf[0] != 'Y')
	    {
	      calc_credit ();
	      print_credit ();
	      if (blend_point == ftell (credit_file))
		{
		  break;
		}
	    }
	}
      print_credit_total ();
      fclose (credit_file);
      rewind (print_file);
      if (printer_on)
	{
	  if (!to_printer ())
	    {
	      curs_set (0);
	      return RET_PRIV;
	    }
	}
      else
	{
	  display_on ();
	}
    }
  return RET_PRIV;
}

int
general_sect_jump (void *key_menu)
{
  pfield = &billsum_flds;
  if (kstate == 1)
    {
      (*pfield)[2].type = DISP;
      (*pfield)[1].type = CHECK;
      rep_buf[0] = 'Y';
      rep_buf[1] = 0;
    }
  if (kstate == 2)
    {
      (*pfield)[2].type = DATE;
      (*pfield)[1].type = DISP;
      rep_buf[0] = 'N';
      rep_buf[1] = 0;
    }
  refresh_menu ((PMENU *) key_menu, 2, 0, 0);
}

int
general_date_jump (void *key_menu)
{
  rep_buf[0] = 'N';
  rep_buf[1] = 0;
  refresh_menu ((PMENU *) key_menu, 3, 0, 0);
}

int
set_dblwidth ()
{
  fputc (0x1b, print_file);
  fputc (0x21, print_file);
  fputc (0x40, print_file);
}
