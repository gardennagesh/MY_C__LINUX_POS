/* biil.c bill related functions ***/
/* Developer: Nagesh Nanjundachari */


#define BILL_DECLARES
#define UNI_COLOR
#define DISPLAY_ON
#define KOT_MODE_SCR

#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include "key.h"
#include "menu.h"
#include "common.h"
#include "prog.h"
#include "bill.h"
#include	"cbill.c"
extern FIELD misc_flds[];
extern PMENU misc_menu;
extern BOX_INFO misc_box;
#		if	0
char *ptitle[4] = {
  "F1:HELP     F2:SEGRGATE   F3:TABLE    F4:WAITER   F5:STOCK-CHECK     F6:MISC",
  "F7:AMT-DISC  F8: %DISCOUNT    F9:CUSTOMER  F10:CASH  F11:CREDIT     F12:CARD",
};
#	else
char *ptitle[4] = {
  "F1:Pieces    F2:Item-Disc    F3:Re-CALC    F4:Refresh     F5:Stock   F6:Misc",
  "F7:Amt-Disc  F8: %Discount    F9:Cheque   F10:Cash    F11:Credit    F12:Card",
  " BillNo:      Cash-Man:           Tbl:      Wtr:    Type:        Sman:   S: ",
  " Code  Item-Name           Quantity      Price  Pieces  %Disc       Amount  ",
};
#	endif


void
disp_sect ()
{
  char tbuf[3];
  bill_detail.sect_no = atoi (sect_str);
  sprintf (tbuf, "%d", bill_detail.sect_no);
  strcpy (bl_section, tbuf);
  wattrset (w, A_NORMAL | rgb (15));
  mvwaddstr (w, 1, 76, bl_section);
  wrefresh (w);
}

void
disp_billno ()
{

  billno_file = fopen ("./pos_files/dbase/billno_ifile", "r");
  while (fread (&billno, sizeof (BILLNO), 1, billno_file))
    {
      if (!strcmp (billno.sectno, sect_str))
	{
	  if (billno.valid == 'Y')
	    {
	      break;
	    }
	}
    }
  fclose (billno_file);
  bill_detail.bill_no = atol (billno.billno);
  strcpy (bl_billno, billno.billno);
  wattrset (w, A_NORMAL | rgb (15));
  mvwaddstr (w, 1, 9, "      ");
  mvwaddstr (w, 1, 9, bl_billno);
  wrefresh (w);
}

void
disp_cashman ()
{
  bill_detail.cashman_no = gcashman_no;
  wattrset (w, A_NORMAL | rgb (15));
  mvwaddstr (w, 1, 24, "          ");
  mvwaddstr (w, 1, 24, loginp);
  wrefresh (w);
}

void
disp_tbl ()
{
  char tbuf[6];

  sprintf (tbuf, "%d", bill_detail.table);
  strcpy (bl_tbl, tbuf);
  wattrset (w, A_NORMAL | rgb (15));
  mvwaddstr (w, 1, 39, "     ");
  mvwaddstr (w, 1, 39, bl_tbl);
  wrefresh (w);
}

void
disp_wtr ()
{
  char tbuf[4];
  sprintf (tbuf, "%d", bill_detail.wtr_no);
  strcpy (bl_wtr, tbuf);
  wattrset (w, A_NORMAL | rgb (15));
  mvwaddstr (w, 1, 49, "    ");
  mvwaddstr (w, 1, 49, bl_wtr);
  wrefresh (w);
}

void
disp_save ()
{
  wattrset (w, A_BOLD | A_BLINK | rgb (16));
  mvwaddstr (w, 1, 58, "        ");
  mvwaddstr (w, 1, 58, "save-on");
  wrefresh (w);
}

void
disp_type ()
{

  if (bill_detail.bill_type == REGULAR)
    {
      wattrset (w, A_NORMAL | rgb (15));
      mvwaddstr (w, 1, 58, "        ");
      mvwaddstr (w, 1, 58, "regular");
    }

  if (bill_detail.bill_type == SETTLE)
    {
      wattrset (w, A_BOLD | A_BLINK | rgb (17));
      mvwaddstr (w, 1, 58, "        ");
      mvwaddstr (w, 1, 58, "settle");
    }

  if (bill_detail.bill_type == REFUND)
    {
      wattrset (w, A_BLINK | A_BOLD | rgb (15));
      mvwaddstr (w, 1, 58, "        ");
      mvwaddstr (w, 1, 58, " refund ");
    }
  if (bill_detail.bill_type == DUPLICATE)
    {
      wattrset (w, A_NORMAL | rgb (15));
      mvwaddstr (w, 1, 58, "        ");
      mvwaddstr (w, 1, 58, "duplicat");
    }
  wrefresh (w);
}

int
disp_sman ()
{
  char tbuf[10];

  wattrset (w, A_NORMAL | rgb (15));
  sprintf (tbuf, "%d", bill_detail.sman_no);
  mvwaddstr (w, 1, 71, "   ");
  mvwaddstr (w, 1, 71, tbuf);
  wrefresh (w);
}

int
start_next_bill ()
{
  int i = 0, j = 0;

  set_help = 0;
  adjust_flag = 0;
  no_of_items = 0;
  no_of_miscs = 0;
  deleted_items = 0;
  cur_pos = 1;
  lno_of_items = 0;
  lcur_pos = 0;
  isearch = 0;
  memset (&bill_detail, 0, sizeof (BILL_DETAIL));
  bill_detail.bill_type = REGULAR;
  for (i = 0; i < MAX_BILL_ITEMS; i++)
    {
      for (j = 0; j <= 74; j++)
	{
	  bills[i][j] = ' ';
	  if (j == 74)
	    bills[i][j] = 0;
	}
    }
  for (i = 0; i != MAX_BILL_ITEMS; i++)
    {
      memset (&bill_item[i], 0, sizeof (BILL_ITEM));
    }
  for (i = 0; i != MAX_BILL_ITEMS; i++)
    {
      bill_item[i].valid = 'N';
    }
  cash_ok = 0;
  chq_ok = 0;
  card_ok = 0;
  credit_ok = 0;
  card_used = 0;
  cash_used = 0;
  credit_used = 0;
  chq_used = 0;
  paid_amt = 0;
  change_amt = 0;
  balance_amt = 0;
  no_of_miscs = 0;
  tax1_exist = 0;
  tax2_exist = 0;
  tax3_exist = 0;
  tax4_exist = 0;
  tax1_name[0] = 0;
  taxon1_name[0] = 0;
  tax2_name[0] = 0;
  taxon2_name[0] = 0;
  tax3_name[0] = 0;
  taxon3_name[0] = 0;
  tax4_name[0] = 0;
  taxon4_name[0] = 0;
  misc1_amt = 0.00;
  misc2_amt = 0.00;
  misc3_amt = 0.00;
  misc4_amt = 0.00;
  misc1_per = 0.00;
  misc2_per = 0.00;
  misc3_per = 0.00;
  misc4_per = 0.00;
  misc1_per_exist = 0;
  misc1_amt_exist = 0;
  misc2_amt_exist = 0;
  misc2_per_exist = 0;
  misc3_amt_exist = 0;
  misc3_per_exist = 0;
  misc4_amt_exist = 0;
  misc4_per_exist = 0;
  misc_no = 0;
  enter_status ();
  disp_sect ();
  disp_billno ();
  disp_tbl ();
  disp_wtr ();
  disp_sman ();
  disp_type ();
  adjust_item ();
  calc_bill_total ();
  display_total_items_amt ();
  display_bill_detail ();
  start_misc ();
  gcard_no[0] = 0;
  gchq_no[0] = 0;
  gcust_name[0] = 0;
  gcard_name[0] = 0;
  gbank_name[0] = 0;
  bill_detail.cashman_no = gcashman_no;
}

int
stock_code_jump (void *key_menu)
{
  int item_found;

  if (strlen (code_buf))
    {
      item_file = fopen ("./pos_files/dbase/item_ifile", "r");
      item_found = 0;
      while (fread (&item, sizeof (ITEM), 1, item_file))
	{
	  if (!strcmp (item.item_code, code_buf))
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
	}
      if (item_found)
	{
	  strcpy (name_buf, item.item_name);
	  sprintf (stock_curr, "%f", item.curr_stock);
	  put_accurate (stock_curr, QTY_ACT);
	}
    }
  refresh_menu ((PMENU *) key_menu, 5, 0, 0);
}

int
stock_do_ok (void *key_menu)
{
  stock_ok = 1;
  return RET_PRIV;
}

int
stockexit_do_ok (void *key_menu)
{
  return RET_PRIV;
}

int
commit_do_ok (void *key_menu)
{
  bill_detail.cash_amt = atof (print_bill.cash_amt);
  bill_detail.card_amt = atof (print_bill.card_amt);
  if (bill_detail.card_amt > 0 && !card_used)
    {
      yes_move = 1;
      bill_error (" F11 Hot key Not Used ");
      bill_detail.card_amt = 0;
      yes_move = 0;
      return;
    }
  bill_detail.chq_amt = atof (print_bill.chq_amt);
  if (bill_detail.chq_amt > 0 && !chq_used)
    {
      yes_move = 1;
      bill_error (" F9 Hot key Not Used ");
      bill_detail.chq_amt = 0;
      yes_move = 0;
      return;
    }
  bill_detail.credit_amt = atof (print_bill.credit_amt);
  if (bill_detail.credit_amt > 0 && !credit_used)
    {
      yes_move = 1;
      bill_error (" F12 Hot key Not Used ");
      bill_detail.credit_amt = 0;
      yes_move = 0;
      return;
    }
  paid_amt = bill_detail.chq_amt + bill_detail.cash_amt +
    bill_detail.credit_amt + bill_detail.card_amt;
  balance_amt = bill_detail.bill_payble - paid_amt;
  change_amt = paid_amt - bill_detail.bill_payble;
  if ((change_amt > 0.1) && !card_used && !chq_used && !credit_used)
    {
      bill_detail.cash_amt -= change_amt;
    }
  refresh_menu ((PMENU *) key_menu, 0, 0, 1);
  if ((change_amt > 0.1) && (card_used || chq_used || credit_used))
    {
      yes_move = 1;
      bill_error (" Enter Exact Payble Amount ");
      yes_move = 0;
      commit_ok = 0;
      return;
    }
  if (balance_amt > 0.0099999)
    {
      yes_move = 1;
      bill_error (" Paid Amt Is Less Than Payble ");
      yes_move = 0;
      commit_ok = 0;
      return;
    }
  commit_ok = 1;
  return RET_PRIV;
}

int
jump_cash (void *key_menu)
{
  cash_do_ok (NULL);
  refresh_menu ((PMENU *) key_menu, 0, 0, 1);
}

int
jump_card (void *key_menu)
{
  card_do_ok (NULL);
  refresh_menu ((PMENU *) key_menu, 0, 0, 1);
}

int
jump_credit (void *key_menu)
{
  credit_do_ok (NULL);
  refresh_menu ((PMENU *) key_menu, 0, 0, 1);
}

int
jump_chq (void *key_menu)
{
  chq_do_ok (NULL);
  refresh_menu ((PMENU *) key_menu, 0, 0, 1);
}

int
cash_do_ok (void *key_menu)
{
  bill_detail.cash_amt = atof (print_bill.cash_amt);
  paid_amt = bill_detail.chq_amt +
    bill_detail.cash_amt + bill_detail.credit_amt + bill_detail.card_amt;
  balance_amt = bill_detail.bill_payble - paid_amt;
  change_amt = paid_amt - bill_detail.bill_payble;
  cash_ok = 1;
  return RET_PRIV;
}

int
card_do_ok (void *key_menu)
{
  bill_detail.card_amt = atof (print_bill.card_amt);
  paid_amt = bill_detail.chq_amt +
    bill_detail.cash_amt + bill_detail.credit_amt + bill_detail.card_amt;
  balance_amt = bill_detail.bill_payble - paid_amt;
  change_amt = paid_amt - bill_detail.bill_payble;
  card_ok = 1;
  if ((strlen (print_bill.card_no) != 16) || (!strlen (print_bill.card_amt)))
    {
      yes_move = 1;
      bill_error (" Enter Card Details ");
      yes_move = 0;
      card_ok = 0;
      return;
    }
  return RET_PRIV;
}

int
cust_no_jump (void *key_menu)
{
  int item_found = 0;

  print_bill.cust_no;
  customer_file = fopen ("./pos_files/dbase/customer_ifile", "r+");
  item_found = 0;
  while (fread (&customer, sizeof (CUSTOMER), 1, customer_file))
    {
      if (!strcmp (customer.custno, print_bill.cust_no))
	{
	  if (customer.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      strcpy (print_bill.cust_name, customer.custname);
    }
  else
    {
      bill_error (" Customer Not Found ");
      return;
    }
  refresh_menu ((PMENU *) key_menu, 4, 0, 0);
}

int
credit_do_ok (void *key_menu)
{
  bill_detail.credit_amt = atof (print_bill.credit_amt);
  paid_amt = bill_detail.chq_amt +
    bill_detail.cash_amt + bill_detail.credit_amt + bill_detail.card_amt;
  balance_amt = bill_detail.bill_payble - paid_amt;
  change_amt = paid_amt - bill_detail.bill_payble;
  credit_ok = 1;
  if ((!strlen (print_bill.cust_name)) || (!strlen (print_bill.credit_amt)))
    {
      yes_move = 1;
      bill_error (" Enter Credit Details ");
      yes_move = 0;
      card_ok = 0;
      return;
    }
  return RET_PRIV;
}

int
chq_do_ok (void *key_menu)
{
  bill_detail.chq_amt = atof (print_bill.chq_amt);
  paid_amt = bill_detail.chq_amt +
    bill_detail.cash_amt + bill_detail.credit_amt + bill_detail.card_amt;
  balance_amt = bill_detail.bill_payble - paid_amt;
  change_amt = paid_amt - bill_detail.bill_payble;
  chq_ok = 1;
  if ((!strlen (print_bill.cust_name)) || (!strlen (print_bill.chq_amt)))
    {
      yes_move = 1;
      bill_error (" Enter Chque Details ");
      yes_move = 0;
      card_ok = 0;
      return;
    }
  return RET_PRIV;
}

int
trance_init ()
{
  sprintf (print_bill.payble, "%f", bill_detail.bill_payble);
  put_accurate (print_bill.payble, PRICE_ACT);
  sprintf (print_bill.paid, "%f", paid_amt);
  put_accurate (print_bill.paid, PRICE_ACT);
  sprintf (print_bill.balance, "%f", balance_amt);
  put_accurate (print_bill.balance, PRICE_ACT);
  if (print_bill.balance[0] == '-')
    {
      strcpy (print_bill.balance, "0.00");
    }
  sprintf (print_bill.change, "%f", change_amt);
  put_accurate (print_bill.change, PRICE_ACT);
  if (print_bill.change[0] == '-')
    {
      strcpy (print_bill.change, "0.00");
    }
}

int
cash_init (PMENU * menu)
{
  trance_init ();
}

int
card_init (PMENU * menu)
{
  trance_init ();
  strcpy (print_bill.card_no, gcard_no);
  strcpy (print_bill.cust_name, gcust_name);
  strcpy (print_bill.card_name, gcard_name);
}

int
credit_init (PMENU * menu)
{
  trance_init ();
  strcpy (print_bill.cust_name, gcust_name);
}

int
chq_init (PMENU * menu)
{
  trance_init ();
  strcpy (print_bill.chq_no, gchq_no);
  strcpy (print_bill.cust_name, gcust_name);
  strcpy (print_bill.bank_name, gbank_name);
}

int
bill_print_init (PMENU * menu)
{

  trance_init ();
  sprintf (print_bill.cash_amt, "%f", bill_detail.cash_amt);
  put_accurate (print_bill.cash_amt, PRICE_ACT);
  sprintf (print_bill.card_amt, "%f", bill_detail.card_amt);
  put_accurate (print_bill.card_amt, PRICE_ACT);
  sprintf (print_bill.credit_amt, "%f", bill_detail.credit_amt);
  put_accurate (print_bill.credit_amt, PRICE_ACT);
  sprintf (print_bill.chq_amt, "%f", bill_detail.chq_amt);
  put_accurate (print_bill.chq_amt, PRICE_ACT);
}

void
disp_date_time_bill (int flag)
{
  FILE *fptemp;
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
  attrset (A_NORMAL | rgb (4));
  mvaddstr (1, 48, "DATE: ");
  mvaddstr (1, 54, temp1);
  mvaddstr (1, 62, "   TIME: ");
  mvaddstr (1, 71, bl_time);
  strcpy (bla_date, temp1);	/* to avoid critical arry access */
  strcpy (bla_time, bl_time);
#				define NO_SEC
#							ifdef	NO_SEC
  mvaddstr (1, 76, "   ");
#							endif
  alarm (60);			/* dont keep less invoke@60sec */
  move (1, 18 + stat_cur_pos);
  refresh ();
}

void
billscreen_init ()
{
  disp_sect ();
  disp_billno ();
  disp_cashman ();
  disp_tbl ();
  disp_wtr ();
  disp_sman ();
  disp_type ();
  disp_date_time_bill (1);
}

int
make_neg ()
{
  bill_detail.cash_amt *= -1;
  bill_detail.bill_perdamt *= -1;
  bill_detail.bill_amtdisc *= -1;
  bill_detail.bill_payble *= -1;
  bill_detail.bill_total *= -1;
  bill_detail.bill_serv *= -1;
  bill_detail.bill_pmisc *= -1;
  bill_detail.bill_nmisc *= -1;
  bill_detail.bill_tax1 *= -1;
  bill_detail.bill_tax2 *= -1;
  bill_detail.bill_tax3 *= -1;
  bill_detail.bill_tax4 *= -1;
  bill_detail.bill_taxon1 *= -1;
  bill_detail.bill_taxon2 *= -1;
  bill_detail.bill_taxon3 *= -1;
  bill_detail.bill_taxon4 *= -1;
  bill_detail.bill_tax *= -1;
  bill_detail.bill_taxon *= -1;
}

int
bill_print_out ()
{
  double tbill_qty, tbill_amt;
  int i = 0;
  char temp_buf[50];

  printer_on = 0;
  print_file = fopen ("/var/tmp/print_ifile", "w+");
  head_file = fopen ("./pos_files/dbase/head_ifile", "r");
  fread (&head, sizeof (HEAD), 1, head_file);
  fclose (head_file);
  print_line ();
  print_line ();
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
  print_str ("Bill No:", 9, LEFT_SIDE);
  sprintf (temp_buf, "%d", bill_detail.bill_no);
  print_str (temp_buf, 12, LEFT_SIDE);
  print_str ("Date:", 6, LEFT_SIDE);
  sprintf (temp_buf, "%s", bill_detail.date);
  print_str (temp_buf, 16, LEFT_SIDE);
  print_str ("Time:", 6, LEFT_SIDE);
  sprintf (temp_buf, "%s", bill_detail.time);
  print_str (temp_buf, 10, LEFT_SIDE);
  print_line ();
  print_str ("Cash-Man:", 10, LEFT_SIDE);
  sprintf (temp_buf, "%d", bill_detail.cashman_no);
  print_str (temp_buf, 5, LEFT_SIDE);
  print_str ("Type:", 6, LEFT_SIDE);
/* check type */
  if (bill_detail.bill_type == REGULAR)
    print_str ("regular", 12, LEFT_SIDE);
  if (bill_detail.bill_type == REFUND)
    print_str ("refund", 12, LEFT_SIDE);
  if (bill_detail.bill_type == SETTLE)
    print_str ("settle", 12, LEFT_SIDE);
  if (bill_detail.bill_type == DUPLICATE)
    print_str ("duplicate", 12, LEFT_SIDE);
  print_str ("Table:", 7, LEFT_SIDE);
  sprintf (temp_buf, "%d", bill_detail.table);
  print_str (temp_buf, 8, LEFT_SIDE);
  print_str ("Waiter:", 8, LEFT_SIDE);
  sprintf (temp_buf, "%d", bill_detail.wtr_no);
  print_str (temp_buf, 5, LEFT_SIDE);
  print_line ();
  print_str
    ("-------------------------------------------------------------------",
     70, LEFT_SIDE);
  print_line ();
  print_str ("SlNo", 4, LEFT_SIDE);
  print_str (" Item-Name", 17, LEFT_SIDE);
  print_str ("Qty", 10, RIGHT_SIDE);
  if (toupper (oprtion.fsoft[0]) == 'Y')
    {
      print_str ("Pcs", 5, RIGHT_SIDE);
    }
  print_str ("Price", 9, RIGHT_SIDE);
  print_str ("%Disc", 6, RIGHT_SIDE);
  print_str ("Amount", 14, RIGHT_SIDE);
  print_line ();
  print_str
    ("-------------------------------------------------------------------",
     70, LEFT_SIDE);
  print_line ();
  tbill_amt = 0;
  tbill_qty = 0;
  for (i = 0; i < no_of_items; i++)
    {
      tbill_qty += bill_item[i].qty;
      tbill_amt += bill_item[i].item_amt;
      sprintf (temp_buf, "%d", i + 1);
      print_str (temp_buf, 4, LEFT_SIDE);
      print_str (bill_item[i].item_name, 17, LEFT_SIDE);
      sprintf (temp_buf, "%f", bill_item[i].qty);
      put_accurate (temp_buf, QTY_ACT);
      print_str (temp_buf, 10, RIGHT_SIDE);
      if (toupper (oprtion.fsoft[0]) == 'Y')
	{
	  sprintf (temp_buf, "%d", bill_item[i].pieces);
	  print_str (temp_buf, 5, RIGHT_SIDE);
	}
      sprintf (temp_buf, "%f", bill_item[i].price);
      put_accurate (temp_buf, PRICE_ACT);
      print_str (temp_buf, 9, RIGHT_SIDE);
      sprintf (temp_buf, "%f", bill_item[i].per_disc);
      put_accurate (temp_buf, PRICE_ACT);
      print_str (temp_buf, 6, RIGHT_SIDE);
      sprintf (temp_buf, "%f", bill_item[i].item_amt);
      put_accurate (temp_buf, PRICE_ACT);
      print_str (temp_buf, 14, RIGHT_SIDE);
      print_line ();
    }
  print_line ();
  print_str
    ("-------------------------------------------------------------------",
     70, LEFT_SIDE);
  print_line ();
  //set_dblwidth ();
  print_str ("Total: ", 21, LEFT_SIDE);
  sprintf (temp_buf, "%f", tbill_qty);
  put_accurate (temp_buf, QTY_ACT);
  print_str (temp_buf, 10, RIGHT_SIDE);
  if (toupper (oprtion.fsoft[0]) == 'Y')
    {
      print_str (" ", 20, LEFT_SIDE);
    }
  else
    {
      print_str (" ", 15, LEFT_SIDE);
    }
  sprintf (temp_buf, "%f", tbill_amt);
  put_accurate (temp_buf, PRICE_ACT);
  print_str (temp_buf, 14, RIGHT_SIDE);
  print_line ();
  if (toupper (oprtion.fsoft[0]) == 'Y')
    {
#				if	0
      if (bill_detail.bill_tax1)
	{
	  print_str (tax1_name, 10, LEFT_SIDE);
	  print_str (": ", 2, LEFT_SIDE);
	  sprintf (temp_buf, "%f", bill_detail.bill_tax1);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 12, LEFT_SIDE);
	  if (bill_detail.bill_taxon1)
	    {
	      print_str (taxon1_name, 8, LEFT_SIDE);
	      print_str (": ", 2, LEFT_SIDE);
	      sprintf (temp_buf, "%f", bill_detail.bill_taxon1);
	      put_accurate (temp_buf, PRICE_ACT);
	      print_str (temp_buf, 8, LEFT_SIDE);
	    }
	}
#				endif
      if (bill_detail.bill_tax)
	{
	  print_str ("Tax Amt", 50, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f",
		   bill_detail.bill_tax + bill_detail.bill_taxon);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	  print_line ();
	}
      if (bill_detail.bill_pmisc || bill_detail.bill_nmisc)
	{
	  print_str ("Misc Amt", 50, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f",
		   bill_detail.bill_pmisc + bill_detail.bill_nmisc);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	  print_line ();
	}
      if (bill_detail.bill_serv)
	{
	  print_str ("Service Amt", 50, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f", bill_detail.bill_serv);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	  print_line ();
	}
      if (bill_detail.bill_perdamt || bill_detail.bill_perdamt)
	{
	  print_str ("Total Discount", 50, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f",
		   bill_detail.bill_perdamt + bill_detail.bill_amtdisc);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	  print_line ();
	}
      print_str ("PAYBLE AMOUNT", 50, RIGHT_SIDE);
      print_str (":", 1, LEFT_SIDE);
      sprintf (temp_buf, "%f", bill_detail.bill_payble);
      put_accurate (temp_buf, PRICE_ACT);
      print_str (temp_buf, 14, RIGHT_SIDE);
      print_line ();
    }
  else
    {
#			if	0
      if (bill_detail.bill_tax1)
	{
	  print_str (tax1_name, 10, LEFT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f", bill_detail.bill_tax1);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 11, LEFT_SIDE);
	  if (bill_detail.bill_taxon1)
	    {
	      print_str (taxon1_name, 8, LEFT_SIDE);
	      print_str (":", 1, LEFT_SIDE);
	      sprintf (temp_buf, "%f", bill_detail.bill_taxon1);
	      put_accurate (temp_buf, PRICE_ACT);
	      print_str (temp_buf, 7, LEFT_SIDE);
	    }
	}
      else
	{
	  print_str (" ", 1, LEFT_SIDE);
	}
#				endif
      if (bill_detail.bill_tax)
	{
	  print_str ("Tax Amt", 45, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f",
		   bill_detail.bill_tax + bill_detail.bill_taxon);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	}
      if (bill_detail.bill_pmisc || bill_detail.bill_nmisc)
	{
	  print_str ("Misc Amt", 45, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f",
		   bill_detail.bill_pmisc + bill_detail.bill_nmisc);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	  print_line ();
	}
      if (bill_detail.bill_serv)
	{
	  print_str ("Service Amt", 45, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f", bill_detail.bill_serv);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	  print_line ();
	}
      if (bill_detail.bill_perdamt || bill_detail.bill_perdamt)
	{
	  print_str ("Total Discount", 45, RIGHT_SIDE);
	  print_str (":", 1, LEFT_SIDE);
	  sprintf (temp_buf, "%f",
		   bill_detail.bill_perdamt + bill_detail.bill_amtdisc);
	  put_accurate (temp_buf, PRICE_ACT);
	  print_str (temp_buf, 14, RIGHT_SIDE);
	  print_line ();
	}
      print_str ("PAYBLE AMOUNT", 50, RIGHT_SIDE);
      print_str (":", 1, LEFT_SIDE);
      sprintf (temp_buf, "%f", bill_detail.bill_payble);
      put_accurate (temp_buf, PRICE_ACT);
      print_str (temp_buf, 14, RIGHT_SIDE);
      print_line ();
    }
  foot_file = fopen ("./pos_files/dbase/foot_ifile", "r");
  fread (&foot, sizeof (FOOT), 1, foot_file);
  fclose (foot_file);
  if (strlen (foot.line1))
    {
      print_str (foot.line1, 60, MIDDLE);
      print_line ();
    }
  if (strlen (foot.line2))
    {
      print_str (foot.line2, 60, MIDDLE);
      print_line ();
    }
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  print_line ();
  fclose (print_file);
  printer_on = 0;
}

int
store_bill ()
{
  KOT_ITEM tkot_item;
  WTABLE wtable;
  int i = 0;
  if (chq_used)
    {
      chq_detail.valid = 'Y';
      chq_detail.bill_no = bill_detail.bill_no;
      chq_detail.chq_amt = bill_detail.chq_amt;
      chq_detail.sect_no = bill_detail.sect_no;
      strcpy (chq_detail.date, bill_detail.date);
      strcpy (chq_detail.time, bill_detail.time);
      strcpy (chq_detail.chq_no, print_bill.chq_no);
      strcpy (chq_detail.cust_name, print_bill.cust_name);
      strcpy (chq_detail.bank_name, print_bill.bank_name);
      chq_file = fopen ("./pos_files/dbase/chq_ifile", "r+");
      fseek (chq_file, 0, SEEK_END);
      fwrite (&chq_detail, sizeof (CHQ_DETAIL), 1, chq_file);
      fflush (chq_file);
      fclose (chq_file);
    }
  if (credit_used)
    {
      credit_detail.valid = 'Y';
      credit_detail.bill_no = bill_detail.bill_no;
      credit_detail.credit_amt = bill_detail.credit_amt;
      credit_detail.sect_no = bill_detail.sect_no;
      strcpy (credit_detail.date, bill_detail.date);
      strcpy (credit_detail.time, bill_detail.time);
      credit_detail.cust_no = atoi (print_bill.cust_no);
      credit_file = fopen ("./pos_files/dbase/credit_ifile", "r+");
      fseek (credit_file, 0, SEEK_END);
      fwrite (&credit_detail, sizeof (CREDIT_DETAIL), 1, credit_file);
      fflush (credit_file);
      fclose (credit_file);
    }
  if (card_used)
    {
      card_detail.bill_no = bill_detail.bill_no;
      card_detail.valid = 'Y';
      card_detail.card_amt = bill_detail.card_amt;
      card_detail.sect_no = bill_detail.sect_no;
      strcpy (card_detail.date, bill_detail.date);
      strcpy (card_detail.time, bill_detail.time);
      strcpy (card_detail.card_no, gcard_no);
      strcpy (card_detail.cust_name, gcust_name);
      strcpy (card_detail.card_name, gcard_name);
      card_file = fopen ("./pos_files/dbase/card_ifile", "r+");
      fseek (card_file, 0, SEEK_END);
      fwrite (&card_detail, sizeof (CARD_DETAIL), 1, card_file);
      fflush (card_file);
      fclose (card_file);
    }
  bills_file = fopen ("./pos_files/dbase/bills_ifile", "r+");
  fseek (bills_file, 0, SEEK_END);
  fwrite (&bill_detail, sizeof (BILL_DETAIL), 1, bills_file);
  fflush (bills_file);
  fclose (bills_file);

  billitem_file = fopen ("./pos_files/dbase/billitem_ifile", "r+");
  fseek (billitem_file, 0, SEEK_END);
  for (i = 1; i <= no_of_items; i++)
    {
      fwrite (&bill_item[i], sizeof (BILL_ITEM), 1, billitem_file);
    }
  fflush (billitem_file);
  fclose (billitem_file);

  kot_file = fopen ("./pos_files/dbase/kot_ifile", "r+");
  while (fread (&tkot_item, sizeof (KOT_ITEM), 1, kot_file))
    {
      if (tkot_item.tbl == bill_tbl)
	{
	  tkot_item.valid = 'N';
	  fseek (kot_file, -sizeof (KOT_ITEM), SEEK_CUR);
	  fwrite (&tkot_item, sizeof (KOT_ITEM), 1, kot_file);
	}
    }
  fflush (kot_file);
  fclose (kot_file);
  table_file = fopen ("./pos_files/dbase/table_ifile", "r+");
  while (fread (&wtable, sizeof (WTABLE), 1, table_file))
    {
      if (wtable.tbl == bill_tbl)
	{
	  wtable.valid = 'N';
	  fseek (table_file, -sizeof (WTABLE), SEEK_CUR);
	  fwrite (&wtable, sizeof (WTABLE), 1, table_file);
	}
    }
  fflush (table_file);
  fclose (table_file);
}

int
my_refresh ()
{
  wrefresh (w1);
  wrefresh (w2);
}

void
billing ()
{

  if ((option_file = fopen ("./pos_files/dbase/option_ifile", "r")) != NULL)
    {
      fread (&oprtion, sizeof (OPRTION), 1, option_file);
      fclose (option_file);
    }
  repays = 2;
  adjust_flag = 0;
  no_of_items = 0;
  no_of_miscs = 0;
  deleted_items = 0;
  cur_pos = 1;
  lno_of_items = 0;
  lcur_pos = 0;
  isearch = 0;
  common_stop_alarm ();
  attrset (A_NORMAL | rgb (4));
  enter_status ();
  move (1, 18);
  slk_init (1);
  curs_set (0);
  refresh ();
  w = newwin (10, 76, 4, 2);
#				ifndef	MONO
  wcolor_set (w, 1, NULL);
#				endif
  box (w, 0, 0);
  wrefresh (w);
  w = newwin (23, 78, 2, 1);
#				ifndef	MONO
  wcolor_set (w, 1, NULL);
#				endif
  box (w, 0, 0);
  wattron (w, A_NORMAL | rgb (1));
  mvwaddstr (w, 1, 1, ptitle[2]);
  wattron (w, A_NORMAL | rgb (1));
  mvwaddstr (w, 2, 1, ptitle[3]);
  wattron (w, A_NORMAL | rgb (1));
  mvwaddstr (w, 20, 1, ptitle[0]);
  wattron (w, A_NORMAL | rgb (1));
  mvwaddstr (w, 21, 1, ptitle[1]);
  wrefresh (w);
  start_alarm ();
  w1 = newwin (10, 76, 5, 2);
#				ifndef	MONO
  wcolor_set (w1, 12, NULL);
#				endif
  box (w1, 0, 0);
  wattrset (w1, A_NORMAL | rgb (7));
  mvwaddstr (w1, cur_pos, 1,
	     "                                                                          ");
  wrefresh (w1);
  w2 = newwin (8, 76, 14, 2);
#				ifndef	MONO
  wcolor_set (w2, 12, NULL);
#				endif
  box (w2, 0, 0);
  wrefresh (w2);
  /*w6 = newwin (3,24,19,54);
     #                            ifndef  MONO
     wcolor_set (w6, 12, NULL);
     #                            endif
     box (w6, 0, 0);
     wattrset (w6, rgb(6)|A_BOLD);
     mvwaddstr (w6, 1,1,"PAYBLE :         0000.00");      
     wrefresh (w6);
   */
  wattrset (w2, rgb (20) | A_BOLD);
  mvwaddstr (w2, 6, 52, " PAYBLE :       0000.00");
  wrefresh (w2);
  curs_set (1);
  start_billing ();
}

int
start_billing ()
{
  int ch, iall = 0, i = 0, j = 0, ic = 0, jc = 0;
  int tstat, all_items = 0, item_found = 0, retval = 0;
  double tdble;
  float tflot;
  char tbuf[50], tempd[6];
  KOT_ITEM kot_item;

  keypad (stdscr, TRUE);
  strcpy (sect_str, "1");
  memset (&bill_detail, 0, sizeof (BILL_DETAIL));
  bill_detail.bill_type = REGULAR;
  for (i = 0; i < MAX_BILL_ITEMS; i++)
    {
      for (j = 0; j <= 74; j++)
	{
	  bills[i][j] = ' ';
	  if (j == 74)
	    bills[i][j] = 0;
	}
    }
  for (i = 0; i != MAX_BILL_ITEMS; i++)
    {
      memset (&bill_item[i], 0, sizeof (BILL_ITEM));
    }
  for (i = 0; i != MAX_BILL_ITEMS; i++)
    {
      bill_item[i].valid = 'N';
    }
  cash_ok = 0;
  chq_ok = 0;
  card_ok = 0;
  credit_ok = 0;
  card_used = 0;
  cash_used = 0;
  credit_used = 0;
  chq_used = 0;
  paid_amt = 0;
  change_amt = 0;
  balance_amt = 0;
  no_of_miscs = 0;
  tax1_exist = 0;
  tax2_exist = 0;
  tax3_exist = 0;
  tax4_exist = 0;
  tax1_name[0] = 0;
  taxon1_name[0] = 0;
  tax2_name[0] = 0;
  taxon2_name[0] = 0;
  tax3_name[0] = 0;
  taxon3_name[0] = 0;
  tax4_name[0] = 0;
  taxon4_name[0] = 0;
  misc1_amt = 0.00;
  misc2_amt = 0.00;
  misc3_amt = 0.00;
  misc4_amt = 0.00;
  misc1_per = 0.00;
  misc2_per = 0.00;
  misc3_per = 0.00;
  misc4_per = 0.00;
  misc1_per_exist = 0;
  misc1_amt_exist = 0;
  misc2_amt_exist = 0;
  misc2_per_exist = 0;
  misc3_amt_exist = 0;
  misc3_per_exist = 0;
  misc4_amt_exist = 0;
  misc4_per_exist = 0;
  misc1_amt_exist = 0;
  misc_no = 0;
  start_misc ();
  billscreen_init ();
  i = 0;

  while (1)
    {
      noecho ();
#			if	1
      if (select_flag || kot_kho)
	{
	  if (kot_kho)
	    {
	      while (1)
		{
		  if (fread (&kot_item, sizeof (KOT_ITEM), 1, kot_file) != 1)
		    {
		      disp_wtr ();
		      disp_tbl ();
		      bill_detail.bill_type = SETTLE;
		      disp_type ();
		      kot_kho = 0;
		      fclose (kot_file);
		      break;
		    }
		  if (kot_item.tbl == bill_tbl)
		    {
		      if (kot_item.valid == 'Y')
			{
			  xkot_item = kot_item;
			  strcpy (status_field, kot_item.code);
			  bill_detail.table = bill_tbl;
			  bill_detail.wtr_no = kot_item.wtr;
			  break;
			}
		    }
		}
	    }
	  kcase = KEY_PPAGE;
	}
      else
	{
	  if (!select_flag)
	    {
	      ch = mvgetch (1, 18 + i);
	      stat_cur_pos = i;
	      if (!echo_chk (ch))
		continue;
	    }
	}
#			else
      if (!select_flag)
	{
	  ch = mvgetch (1, 18 + i);
	  stat_cur_pos = i;
	  if (!echo_chk (ch))
	    continue;
	}
      else
	{
	  kcase = KEY_PPAGE;
	}
#				endif
      switch (kcase)
	{

	case ALPHA:
	  continue;

	case DIGIT:
	  echo ();
	  if (i <= 10)
	    {
	      mvaddch (1, 18 + i, ch);
	      status_field[i] = ch;
	      i++;
	      stat_cur_pos = i;
	    }
	  continue;

	case KEY_BACKSPACE:
	  echo ();
	  i--;
	  stat_cur_pos = i;
	  if (i <= 0)
	    i = 0;
	  mvaddch (1, 18 + i, ' ');
	  break;

	case KEY_PPAGE:
	  if (set_help)
	    continue;
	  stop_alarm ();
	  if (select_flag)
	    {
	      strcpy (status_field, select_buf);
	      select_flag = 0;
	      select_buf[0] = 0;
	    }
	  else
	    {
	      if (kot_kho)
		{
		}
	      else
		status_field[i] = 0;
	    }
	  if (!strlen (status_field))
	    continue;
	  if (no_of_items >= MAX_BILL_ITEMS - 1)
	    {
	      bill_error (" Items Per Bill Limit Eceeded ");
	      status_field[0] = 0;
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_tax);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 12)
	    {
	      bill_error (" Tax Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_total);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 14)
	    {
	      bill_error (" Amt Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  item_entry (status_field);
	  i = 0;
	  stat_cur_pos = i;
	  start_alarm ();
	  break;

	case CR_KEY:
	  if (!no_of_items)
	    continue;
	  stop_alarm ();
	  if (!card_used && !credit_used && !chq_used && !cash_used)
	    {
	      paid_amt = bill_detail.bill_payble;
	      bill_detail.cash_amt = bill_detail.bill_payble;
	      change_amt = 0;
	    }
	  if ((draw_menu (&bill_print_menu) == RET_PRIV) && commit_ok)
	    {
	      disp_billno ();
	      commit_ok = 0;
	      all_items = 0;
	      item_file = fopen ("./pos_files/dbase/item_ifile", "r+");
	      while (all_items != no_of_items)
		{
		  item_found = 0;
		  while (fread (&item, sizeof (ITEM), 1, item_file))
		    {
		      if (!strcmp
			  (item.item_code, bill_item[all_items].stricode))
			{
			  if (item.valid == 'Y')
			    {
			      item_found = 1;
			      break;
			    }
			}
		    }
		  if (item_found)
		    {
		      item.today_sale_qty += bill_item[all_items].qty;
		      item.curr_stock -= bill_item[all_items].qty;
		      fseek (item_file, -sizeof (ITEM), SEEK_CUR);
		      fwrite (&item, sizeof (ITEM), 1, item_file);
		      rewind (item_file);
		      item_found = 0;
		    }
		  all_items++;
		}
	      fflush (item_file);
	      fclose (item_file);
	      sprintf (tbuf, "%d", bill_detail.bill_no + 1);
	      billno_file = fopen ("./pos_files/dbase/billno_ifile", "r+");
	      while (fread (&billno, sizeof (BILLNO), 1, billno_file))
		{
		  if (!strcmp (billno.sectno, sect_str))
		    {
		      if (billno.valid == 'Y')
			{
			  break;
			}
		    }
		}
	      strcpy (billno.billno, tbuf);
	      fseek (billno_file, -sizeof (BILLNO), SEEK_CUR);
	      fwrite (&billno, sizeof (BILLNO), 1, billno_file);
	      fflush (billno_file);
	      fclose (billno_file);
	      strcpy (bill_detail.date, bla_date);
	      strcpy (bill_detail.time, bla_time);
	      bill_detail.sect_no = atoi (sect_str);
	      for (iall = 0; iall <= no_of_items; iall++)
		{
		  strcpy (bill_item[iall].date, bla_date);
		  bill_item[iall].bill_no = bill_detail.bill_no;
		}
	      bill_detail.no_of_items = no_of_items;
	      bill_detail.valid = 'Y';
	      if (bill_detail.bill_type == REFUND)
		make_neg ();
	      store_bill ();
	      bill_print_out ();
#ifndef DISPLAY_ON
/* Printer Code Here  USB printer or DOT matrix.*/
#endif
#ifdef DISPLAY_ON
stop_alarm ();
scr_dump ("billscreen");
clear();
display_bill_on();
getch ();
scr_restore ("billscreen");
refresh ();
remove ("billscreen");
start_alarm ();
#endif
	      start_next_bill ();
	    }
	  if (!card_used && !credit_used && !chq_used && !cash_used)
	    {
	      paid_amt = 0;
	      bill_detail.cash_amt = 0;
	    }
	  bill_detail.bill_pmisc = 0.00;
	  bill_detail.bill_nmisc = 0.00;
	  calc_bill_total ();
	  display_total_items_amt ();
	  start_alarm ();
	  break;

	case KEY_F (1):
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  if (!strlen (status_field) || !no_of_items || cur_pos > no_of_items)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tflot = atof (status_field);
	  if (tflot > 9999)
	    {
	      bill_error (" Max Pieces Is [9999] ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  if (!calc_over_flow (tflot, DPIECE))
	    {
	      bill_error (" Qty/Pieces Limit Exceeds ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_tax);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 12)
	    {
	      bill_error (" Tax Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_total);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 14)
	    {
	      bill_error (" Amt Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  piece_override = 1;
	  update_item_data ();
	  piece_override = 0;
	  override_flag = 0;
	  i = 0;
	  stat_cur_pos = i;
	  break;

	case KEY_F (4):
	  start_next_bill ();
	  break;

	case KEY_F (5):
	  if (set_help)
	    continue;
	  if (draw_menu (&stock_menu) == RET_PRIV && stock_ok)
	    {
	      if (strlen (code_buf))
		{
		  item_file = fopen ("./pos_files/dbase/item_ifile", "r+");
		  item_found = 0;
		  while (fread (&item, sizeof (ITEM), 1, item_file))
		    {
		      if (!strcmp (item.item_code, code_buf))
			{
			  if (item.valid == 'Y')
			    {
			      tflot = atof (stock_in);
			      if (tflot > 1)
				{
				  item.stock_in += tflot;
				  item.curr_stock += tflot;
				}
			      tflot = atof (stock_out);
			      if (tflot > 1)
				{
				  item.stock_out -= tflot;
				  item.curr_stock -= tflot;
				}
			      fseek (item_file, -sizeof (ITEM), SEEK_CUR);
			      fwrite (&item, sizeof (ITEM), 1, item_file);
			      fflush (item_file);
			      fclose (item_file);
			      break;
			    }
			}
		    }
		}
	    }
	  break;

	case KEY_F (3):
	  if (set_help)
	    continue;
	  bill_detail.dpercent = 0.00;
	  bill_detail.bill_amtdisc = 0.00;
	  bill_detail.bill_serv = 0.00;
	  bill_detail.serv_cent = 0.00;
	  bill_detail.bill_pmisc = 0.00;
	  bill_detail.bill_nmisc = 0.00;
	  bill_detail.bill_tax1 = 0.00;
	  bill_detail.bill_tax2 = 0.00;
	  bill_detail.bill_tax3 = 0.00;
	  bill_detail.bill_tax4 = 0.00;
	  bill_detail.bill_taxon1 = 0.00;
	  bill_detail.bill_taxon2 = 0.00;
	  bill_detail.bill_taxon3 = 0.00;
	  bill_detail.bill_taxon4 = 0.00;
	  misc1_amt = 0.00;
	  misc2_amt = 0.00;
	  misc3_amt = 0.00;
	  misc4_amt = 0.00;
	  misc1_per = 0.00;
	  misc2_per = 0.00;
	  misc3_per = 0.00;
	  misc4_per = 0.00;
	  bill_detail.cash_amt = 0.00;
	  bill_detail.card_amt = 0.00;
	  bill_detail.credit_amt = 0.00;
	  gcard_no[0] = 0;
	  gchq_no[0] = 0;
	  gcust_name[0] = 0;
	  gcard_name[0] = 0;
	  gbank_name[0] = 0;
	  start_misc ();
	  commit_ok = 0;
	  cash_ok = 0;
	  chq_ok = 0;
	  card_ok = 0;
	  credit_ok = 0;
	  card_used = 0;
	  cash_used = 0;
	  credit_used = 0;
	  chq_used = 0;
	  paid_amt = 0;
	  change_amt = 0;
	  balance_amt = 0;
	  calc_bill_total ();
	  display_total_items_amt ();
	  display_bill_detail ();
	  break;

	case CTRL_DD:
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  tstat = strlen (status_field);
	  if (!tstat)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tflot = atof (status_field);
	  if (tflot > 99.99)
	    {
	      bill_error (" Max Discount Is [99.99] ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  if (!calc_over_flow (tflot, DDISC))
	    {
	      bill_error (" Qty/Pieces Limit Exceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  strcpy (tempd, status_field);
	  for (i = 1; i <= no_of_items; i++)
	    {
	      disc_override = 1;
	      cur_pos = i;
	      strcpy (status_field, tempd);
	      update_item_data ();
	    }
	  disc_override = 0;
	  override_flag = 0;
	  i = 0;
	  stat_cur_pos = i;
	  break;

	case CTRL_HH:
#					if		0
	  if (no_of_items)
	    continue;
	  fp1 = fopen ("/CRYPT", "rb");
	  if (fp1 == NULL)
	    {
	      bill_error (" CRYPT file status changed ");
	      fclose (fp1);
	      status_field[0] = 0;
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  help_file = fopen ("/junka", "w+");
	  while (fread (&ch, sizeof (ch), 1, fp1) == 1)
	    {
	      fputc (ch, help_file);
	    }
	  fclose (fp1);
	  rewind (help_file);
	  if (no_of_items)
	    continue;
	  help_file = fopen ("/junka", "r");
	  /* no of bills > no of help lines is must */
	  i = 0;
	  while (fgets (bills[i++], 80, help_file))
	    bills[i - 1][74] = 0;
	  fclose (help_file);
	  remove ("/junka");
	  i = 0;
	  set_help = 1;
	  adjust_item ();
#						endif
	  break;

	case CTRL_AA:
	  disp_save ();
	  if (!fork ())
	    {
#							if		0
	      system ("rat Pcvzf ./pos_files/bdft/fsave.tar ./pos_files/dbase > x");
#							else
	      dsave_buf[0] = 'r';
	      dsave_buf[1] = 'a';
	      dsave_buf[2] = 't';
	      dsave_buf[3] = ' ';
	      dsave_buf[4] = 'P';
	      dsave_buf[5] = 'c';
	      dsave_buf[6] = 'v';
	      dsave_buf[7] = 'z';
	      dsave_buf[8] = 'f';
	      dsave_buf[9] = ' ';
	      dsave_buf[10] = '/';
	      dsave_buf[11] = 'u';
	      dsave_buf[12] = 's';
	      dsave_buf[13] = 'r';
	      dsave_buf[14] = '/';
	      dsave_buf[15] = 'b';
	      dsave_buf[16] = 'd';
	      dsave_buf[17] = 'f';
	      dsave_buf[18] = 't';
	      dsave_buf[19] = '/';
	      dsave_buf[20] = 'f';
	      dsave_buf[21] = 's';
	      dsave_buf[22] = 'a';
	      dsave_buf[23] = 'v';
	      dsave_buf[24] = 'e';
	      dsave_buf[25] = '.';
	      dsave_buf[26] = 't';
	      dsave_buf[27] = 'a';
	      dsave_buf[28] = 'r';
	      dsave_buf[29] = ' ';
	      dsave_buf[30] = '/';
	      dsave_buf[31] = 'u';
	      dsave_buf[32] = 's';
	      dsave_buf[33] = 'r';
	      dsave_buf[34] = '/';
	      dsave_buf[35] = 'd';
	      dsave_buf[36] = 'b';
	      dsave_buf[37] = 'a';
	      dsave_buf[38] = 's';
	      dsave_buf[39] = 'e';
	      dsave_buf[40] = ' ';
	      dsave_buf[41] = '>';
	      dsave_buf[42] = ' ';
	      dsave_buf[43] = 'x';
	      dsave_buf[44] = 0;
	      system (dsave_buf);
#							endif
	      remove ("x");
	      system ("sync");
	      exit (1);
	    }
	  else
	    {
	      wait (1);
	    }
	  sleep (2);
	  disp_type ();
	  break;

	case CTRL_RR:
	  if (set_help)
	    continue;
	  bill_detail.bill_type = REFUND;;
	  disp_type ();
	  break;

	case CTRL_SS:
	  if (!no_of_items)
	    continue;
	  status_field[i] = 0;
	  i = atoi (status_field);
	  if (i)
	    {
	      item_found = 0;
	      sman_file = fopen ("./pos_files/dbase/sman_ifile", "r");
	      item_found = 0;
	      while (fread (&sman, sizeof (SMAN), 1, sman_file))
		{
		  if (!strcmp (sman.smanno, status_field))
		    {
		      if (sman.valid == 'Y')
			{
			  item_found = 1;
			  break;
			}
		    }
		}
	      fclose (sman_file);
	      if (!item_found)
		{
		  bill_error (" Sales Man Not Found ");
		  status_field[0] = 0;
		  i = 0;
		  stat_cur_pos = i;
		  continue;
		}
	      item_found = 0;
	      bill_detail.sman_no = atoi (status_field);
	      disp_sman ();
	    }
	  enter_status ();
	  move (1, 18);
	  status_field[0] = 0;
	  i = 0;
	  break;

	case CTRL_VV:
	  if (set_help)
	    continue;
	  tbox = misc_box;
	  tmenu = misc_menu;
	  pfield = &misc_flds;
	  for (i = 0; i <= (misc_menu.flds - 3); i++)
	    (*pfield)[i].type = DISP;
	  misc_box.r = 14;
	  misc_menu.menu = "billscreen";
	  misc_menu.flds -= 2;
	  misc_menu.clear_scr = 1;
	  misc_menu.clr = 14;
	  draw_menu (&misc_menu);
	  (*pfield)[0].type = ALPHA;
	  (*pfield)[1].type = DIGIT;
	  (*pfield)[2].type = DIGIT;
	  (*pfield)[3].type = MATH;
	  (*pfield)[4].type = ALPHA;
	  (*pfield)[5].type = DIGIT;
	  (*pfield)[6].type = DIGIT;
	  (*pfield)[7].type = MATH;
	  (*pfield)[8].type = ALPHA;
	  (*pfield)[9].type = DIGIT;
	  (*pfield)[10].type = DIGIT;
	  (*pfield)[11].type = MATH;
	  (*pfield)[12].type = ALPHA;
	  (*pfield)[13].type = DIGIT;
	  (*pfield)[14].type = DIGIT;
	  (*pfield)[15].type = MATH;
	  misc_box = tbox;
	  misc_menu = tmenu;
	  curs_set (1);
	  status_field[0] = 0;
	  i = 0;
	  refresh ();
	  break;


	case KEY_F (8):
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  tstat = strlen (status_field);
	  if (!tstat || !no_of_items)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tflot = atof (status_field);
	  if (tflot > 99.99)
	    {
	      bill_error (" Max Discount Is [99.99] ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  bill_detail.dpercent = tflot;
	  calc_bill_total ();
	  display_total_items_amt ();
	  display_bill_detail ();
	  disc_override = 0;
	  override_flag = 0;
	  enter_status ();
	  move (1, 18);
	  i = 0;
	  stat_cur_pos = i;
	  break;

	case KEY_END:
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  tstat = strlen (status_field);
	  if (!tstat || !no_of_items)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tflot = atof (status_field);
	  if (tflot > 99.99)
	    {
	      bill_error (" Max Service Is [99.99%] ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  bill_detail.serv_cent = tflot;
	  calc_bill_total ();
	  display_total_items_amt ();
	  display_bill_detail ();
	  disc_override = 0;
	  override_flag = 0;
	  enter_status ();
	  move (1, 18);
	  i = 0;
	  stat_cur_pos = i;
	  break;

	case KEY_F (9):
	  if (set_help)
	    continue;
	  if (!no_of_items)
	    continue;
	  stop_alarm ();
	  if ((draw_menu (&chq_menu) == RET_PRIV) && chq_ok)
	    {
	      strcpy (gcust_name, print_bill.cust_name);
	      strcpy (gchq_no, print_bill.chq_no);
	      strcpy (gbank_name, print_bill.bank_name);
	      chq_ok = 0;
	      chq_used = 1;
	      display_total_items_amt ();
	    };
	  start_alarm ();
	  break;

	case KEY_F (10):
	  if (set_help)
	    continue;
	  if (!no_of_items)
	    continue;
	  stop_alarm ();
	  calc_bill_total ();
	  if ((draw_menu (&cash_menu) == RET_PRIV) && cash_ok)
	    {
	      cash_ok = 0;
	      cash_used = 1;
	      display_total_items_amt ();
	    };
	  start_alarm ();
	  break;

	case KEY_F (11):
	  if (set_help)
	    continue;
	  if (!no_of_items)
	    continue;
	  stop_alarm ();
	  if ((draw_menu (&card_menu) == RET_PRIV) && card_ok)
	    {
	      strcpy (gcust_name, print_bill.cust_name);
	      strcpy (gcard_no, print_bill.card_no);
	      strcpy (gcard_name, print_bill.card_name);
	      card_ok = 0;
	      card_used = 1;
	      display_total_items_amt ();
	    };
	  start_alarm ();
	  break;

	case KEY_F (12):
	  if (set_help)
	    continue;
	  if (!no_of_items)
	    continue;
	  stop_alarm ();
	  if ((draw_menu (&credit_menu) == RET_PRIV) && credit_ok)
	    {
	      strcpy (gcust_name, print_bill.cust_name);
	      credit_ok = 0;
	      credit_used = 1;
	      display_total_items_amt ();
	    };
	  start_alarm ();
	  break;

	case KEY_F (6):
	  if (set_help)
	    continue;
	  if (toupper (oprtion.fmisc_amt[0]) == 'Y')
	    {
	      bill_error (" Default Misc Is Selected ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  else
	    {
	      if (no_of_miscs == 2)
		{
		  bill_error (" Two Miscs Are Selected ");
		  i = 0;
		  stat_cur_pos = i;
		  continue;
		}
	      misc_no = atoi (status_field);
	      if (no_of_miscs && (misc1_per_exist
				  || misc1_amt_exist) && misc_no == 1)
		{
		  bill_error (" This MISC1 Exist ");
		  i = 0;
		  stat_cur_pos = i;
		  continue;
		}
	      if (no_of_miscs && (misc2_per_exist
				  || misc2_amt_exist) && misc_no == 2)
		{
		  bill_error (" This MISC2 Exist ");
		  i = 0;
		  stat_cur_pos = i;
		  continue;
		}
	      if (no_of_miscs && (misc3_per_exist
				  || misc3_amt_exist) && misc_no == 3)
		{
		  bill_error (" This MISC3 Exist ");
		  i = 0;
		  stat_cur_pos = i;
		  continue;
		}
	      if (no_of_miscs && (misc4_per_exist
				  || misc4_amt_exist) && misc_no == 4)
		{
		  bill_error (" This MISC4 Exist ");
		  i = 0;
		  stat_cur_pos = i;
		  continue;
		}
	      calc_entered_misc (misc_no);
	      ++no_of_miscs;
	      enter_status ();
	      move (1, 18);
	      i = 0;
	      stat_cur_pos = i;
	    }
	  break;

	case KEY_F (7):
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  tstat = strlen (status_field);
	  if (!tstat || !no_of_items)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tdble = atof (status_field);
	  if (tdble > bill_detail.bill_payble)
	    {
	      bill_error (" Discount Exceeds Payble ");
	      i = 0;
	      stat_cur_pos = i;
	      status_field[0] = 0;
	      continue;
	    }
	  bill_detail.bill_amtdisc = tdble;
	  calc_bill_total ();
	  display_total_items_amt ();
	  display_bill_detail ();
	  disc_override = 0;
	  override_flag = 0;
	  i = 0;
	  stat_cur_pos = i;
	  enter_status ();
	  move (1, 18);
	  break;

	case KEY_F (2):
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  tstat = strlen (status_field);
	  if (!tstat || !no_of_items || cur_pos > no_of_items)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tflot = atof (status_field);
	  if (tflot > 99.99)
	    {
	      bill_error (" Max Discount Is [99.99] ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  if (!calc_over_flow (tflot, DDISC))
	    {
	      bill_error (" Qty/Pieces Limit Exceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  disc_override = 1;
	  update_item_data ();
	  disc_override = 0;
	  override_flag = 0;
	  i = 0;
	  stat_cur_pos = i;
	  break;

	case KEY_DC:
	  if (set_help)
	    continue;
	  if (!no_of_items || (cur_pos > no_of_items)
	      || strlen (status_field))
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      status_field[0] = 0;
	      continue;
	    }
	  bill_item[cur_pos - 1].valid = 'N';
	  fill_item_hole ();
	  if (!no_of_items)
	    {
	      disp_wtr ();
	      disp_sman ();
	      disp_tbl ();
	      disp_type ();
	    }
	  adjust_item ();
	  calc_bill_total ();
	  display_total_items_amt ();
	  display_bill_detail ();
	  break;

	case KEY_IC:
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  if (!strlen (status_field) || !no_of_items || cur_pos > no_of_items)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tflot = atof (status_field);
	  if (tflot > 99999)
	    {
	      bill_error (" Max Price Is [99999.00] ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  if (!calc_over_flow (tflot, DPRICE))
	    {
	      bill_error (" Qty/Pieces Limit Exceeds ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_tax);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 12)
	    {
	      bill_error (" Tax Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_total);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 14)
	    {
	      bill_error (" Amt Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  price_override = 1;
	  update_item_data ();
	  price_override = 0;
	  override_flag = 0;
	  i = 0;
	  stat_cur_pos = i;
	  break;

	case KEY_HOME:
	  if (set_help)
	    continue;
	  status_field[i] = 0;
	  if (!strlen (status_field) || !no_of_items || cur_pos > no_of_items)
	    {
	      i = 0;
	      stat_cur_pos = i;
	      enter_status ();
	      move (1, 18);
	      continue;
	    }
	  tflot = atof (status_field);
	  if (tflot > 99999)
	    {
	      bill_error (" Max Qty Is [99999.00] ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  if (!calc_over_flow (tflot, DQTY))
	    {
	      bill_error (" Qty/Pieces Limit Exceeds ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_tax);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 12)
	    {
	      bill_error (" Tax Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  sprintf (tbuf, "%f", bill_detail.bill_total);
	  put_accurate (tbuf, PRICE_ACT);
	  if (strlen (tbuf) >= 14)
	    {
	      bill_error (" Amt Limit Is Eceeded ");
	      i = 0;
	      stat_cur_pos = i;
	      continue;
	    }
	  qty_override = 1;
	  update_item_data ();
	  qty_override = 0;
	  override_flag = 0;
	  i = 0;
	  stat_cur_pos = i;
	  break;

	case KEY_TAB:
/* ENTER INTO KOT SCREEN . THIS IS OPTINAL. */
#ifdef KOT_MODE_SCR 
	  if (set_help)
	    continue;
	  if (no_of_items)
	    continue;
	  if (toupper (oprtion.fsoft[0]) != 'Y')
	    continue;
	  kot_kho = 0;
	  display_set = 0;
	  stop_alarm ();
	  scr_dump ("billscreen");
	  kot_menu (1);
	  scr_restore ("billscreen");
	  remove ("billscreen");
	  refresh ();
	  start_alarm ();
#endif
	  break;

	case KEY_NPAGE:
	  if (set_help)
	    continue;
	  stop_alarm ();
	  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
	  scr_dump ("billscreen");
	  search_items (1);
	  fclose (item_file);
	  scr_restore ("billscreen");
	  remove ("billscreen");
	  refresh ();
	  start_alarm ();
	  break;

	case KEY_UP:
	  key_up ();
	  adjust_item ();
	  break;

	case KEY_DOWN:
	  key_down ();
	  adjust_item ();
	  break;

	case CTRL_FF:
	  if (set_help)
	    continue;
	  cur_pos += 7;
	  if (cur_pos >= MAX_BILL_ITEMS - 1)
	    cur_pos = MAX_BILL_ITEMS - 1;
	  if (cur_pos <= 1)
	    cur_pos = 1;
	  adjust_item ();
	  break;

	case CTRL_BB:
	  if (set_help)
	    continue;
	  cur_pos -= 7;
	  if (cur_pos >= MAX_BILL_ITEMS - 1)
	    cur_pos = MAX_BILL_ITEMS - 1;
	  if (cur_pos <= 1)
	    cur_pos = 1;
	  adjust_item ();
	  break;

	case ESC_KEY:
	  if (set_help)
	    continue;
	  if (draw_menu (&bill_exit_menu) == RET_OK)
	    {
	      system ("rm -rf ./billscreen");
	      stop_alarm ();
	      common_start_alarm ();
	      cur_pos = 1;
	      misc_no = 0;
	      return;
	    }
	  curs_set (1);
	  adjust_item ();
	  display_bill_detail ();
	default:
	  break;
	}
    }
}

int
echo_chk (int ch)
{

  if (isalpha (ch))
    {
      kcase = ALPHA;
      return 1;
    }
  if (isdigit (ch))
    {
      kcase = DIGIT;
      return 2;
    }
  if (ch == '.')
    {
      kcase = DIGIT;
      return 2;
    }
  if (ch == KEY_BACKSPACE)
    {
      kcase = KEY_BACKSPACE;
      return 1;
    }
  if (ch == KEY_TAB)
    {
      kcase = KEY_TAB;
      return 1;
    }
  if (ch == KEY_F (1))
    {
      kcase = KEY_F (1);
      return 1;
    }
  if (ch == KEY_F (2))
    {
      kcase = KEY_F (2);
      return 1;
    }
  if (ch == KEY_F (3))
    {
      kcase = KEY_F (3);
      return 1;
    }
  if (ch == KEY_F (4))
    {
      kcase = KEY_F (4);
      return 1;
    }
  if (ch == KEY_F (5))
    {
      kcase = KEY_F (5);
      return 1;
    }
  if (ch == KEY_F (6))
    {
      kcase = KEY_F (6);
      return 1;
    }
  if (ch == KEY_F (7))
    {
      kcase = KEY_F (7);
      return 1;
    }
  if (ch == KEY_F (8))
    {
      kcase = KEY_F (8);
      return 1;
    }
  if (ch == KEY_F (9))
    {
      kcase = KEY_F (9);
      return 1;
    }
  if (ch == KEY_F (10))
    {
      kcase = KEY_F (10);
      return 1;
    }
  if (ch == KEY_F (11))
    {
      kcase = KEY_F (11);
      return 1;
    }
  if (ch == KEY_F (12))
    {
      kcase = KEY_F (12);
      return 1;
    }
  if (ch == CR_KEY)
    {
      kcase = CR_KEY;
      return 1;
    }
  if (ch == CTRL_BB)
    {
      kcase = CTRL_BB;
      return 1;
    }
  if (ch == CTRL_FF)
    {
      kcase = CTRL_FF;
      return 1;
    }
  if (ch == CTRL_AA)
    {
      kcase = CTRL_AA;
      return 1;
    }
  if (ch == CTRL_HH)
    {
      kcase = CTRL_HH;
      return 1;
    }
  if (ch == CTRL_VV)
    {
      kcase = CTRL_VV;
      return 1;
    }
  if (ch == CTRL_SS)
    {
      kcase = CTRL_SS;
      return 1;
    }
  if (ch == CTRL_DD)
    {
      kcase = CTRL_DD;
      return 1;
    }
  if (ch == CTRL_MM)
    {
      kcase = CTRL_MM;
      return 1;
    }
  if (ch == CTRL_RR)
    {
      kcase = CTRL_RR;
      return 1;
    }
  if (ch == KEY_PPAGE)
    {
      kcase = KEY_PPAGE;
      return 1;
    }
  if (ch == KEY_NPAGE)
    {
      kcase = KEY_NPAGE;
      return 1;
    }
  if (ch == KEY_HOME)
    {
      kcase = KEY_HOME;
      return 1;
    }
  if (ch == KEY_END)
    {
      kcase = KEY_END;
      return 1;
    }
  if (ch == KEY_DC)
    {
      kcase = KEY_DC;
      return 1;
    }
  if (ch == KEY_IC)
    {
      kcase = KEY_IC;
      return 1;
    }
  if (ch == KEY_UP)
    {
      kcase = KEY_UP;
      return 1;
    }
  if (ch == KEY_DOWN)
    {
      kcase = KEY_DOWN;
      return 1;
    }
  if (ch == ESC_KEY)
    {
      kcase = ESC_KEY;
      return 1;
    }
  else
    return 0;
}

int
item_entry (char *status_field)
{
  char position[78], ttotal[40], tbuf[40];
  int left = 0, more = 0;

  if ((no_of_items <= 8) && (cur_pos > no_of_items))
    {
      adjust_flag = 1;
      adjust_item ();
      cur_pos = no_of_items;
      adjust_flag = 0;
    }

  if (bill_item_entry (status_field))
    {
      if (cur_pos <= 8)
	{
	  wattrset (w1, A_REVERSE | rgb (7));
	  mvwaddstr (w1, cur_pos, 1, bills[cur_pos - 1]);
	}
      cur_pos = no_of_items;
      if (cur_pos <= 8)
	{
	  wattrset (w1, A_NORMAL | rgb (7));
	  mvwaddstr (w1, cur_pos, 1, bills[no_of_items - 1]);
	  if (no_of_items > 1)
	    {
	      wattrset (w1, A_REVERSE | rgb (7));
	      mvwaddstr (w1, cur_pos - 1, 1, bills[no_of_items - 2]);
	    }
	}
      else
	{
	  int i = 1;
	  more = no_of_items - 8;
	  while (i <= 7)
	    {
	      wattrset (w1, A_REVERSE | rgb (7));
	      mvwaddstr (w1, i++, 1, bills[more++]);
	    }
	  wattrset (w1, A_NORMAL | rgb (7));
	  mvwaddstr (w1, i, 1, bills[more]);
	}
      display_total_items_amt ();
    }
  wrefresh (w1);
  wrefresh (w2);
}

int
key_up ()
{
  int pos;

  cur_pos--;
  if (cur_pos <= 1)
    cur_pos = 1;
}

int
key_down ()
{
  int pos;

  cur_pos++;
  if (cur_pos >= MAX_BILL_ITEMS - 1)
    cur_pos = MAX_BILL_ITEMS - 1;
}

int
bill_item_entry (char *status_field)
{
  int left = 0, item_found = 0;

  if (strlen (status_field))
    {
      item_file = fopen ("./pos_files/dbase/item_ifile", "r");
      item_found = 0;
      while (fread (&item, sizeof (ITEM), 1, item_file))
	{
	  if (!strcmp (item.item_code, status_field))
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
	  bill_error (" Item Not Programmed ");
	  adjust_item ();
	  return 0;
	}
      if (item_found == 1)
	{
	  progitem_to_billitem ();
	  calc_bill_total ();
	  display_bill_detail ();
	  return 1;
	}
    }
  else
    {
      attron (A_NORMAL | rgb (4));
      enter_status ();
      move (1, 18);
      return 0;
    }
}

int
adjust_item ()
{
  char position[78], ttotal[50], tbuf[50];
  int more = 0, multi, left;
  int i = 1;			/* dont change i val */

  if (cur_pos <= 8 || adjust_flag)
    {
      while (i <= 8)
	{
	  wattrset (w1, A_REVERSE | rgb (7));
	  mvwaddstr (w1, i, 1, bills[i - 1]);
	  i++;
	}
      if (!adjust_flag)
	{
	  if (set_help)
	    {
	      if (cur_pos == 1)
		wattrset (w1, A_BOLD | rgb (16));
	      else
		wattrset (w1, A_BOLD | rgb (13));
	    }
	  else
	    wattrset (w1, A_NORMAL | rgb (7));
	  mvwaddstr (w1, cur_pos, 1, bills[cur_pos - 1]);
	}
    }
  else
    {
      int i = 1;
      more = cur_pos - 8;
      while (i <= 7)
	{
	  wattrset (w1, A_REVERSE | rgb (7));
	  mvwaddstr (w1, i++, 1, bills[more++]);
	}
      if (set_help)
	wattrset (w1, A_BOLD | rgb (13));
      else
	wattrset (w1, A_NORMAL | rgb (7));
      mvwaddstr (w1, i, 1, bills[more]);
    }
  display_total_items_amt ();
}

int
display_total_items_amt ()
{
  char position[78], ttotal[40], tbuf[40];
  int left;
  double dval;
#			ifdef	MONO
  wattrset (w2, rgb (1));
#			else
  wattrset (w2, rgb (6));
#			endif
  strcpy (position, " No Of Items: ");
  left = no_of_items;
  sprintf (position + strlen (position), "%d", left);
  strcat (position + strlen (position), "         CurBar Position: ");
  sprintf (position + strlen (position), "%d", cur_pos);

  sprintf (tbuf, "%f", bill_detail.bill_total);
  put_accurate (tbuf, PRICE_ACT);
#			if	1
  strcat (position + strlen (position), "        ");
  position[50] = 0;
  mvwaddstr (w2, 1, 1, position);
  mvwaddstr (w2, 1, 51, "Basic Amt:");
  left = 14 - strlen (tbuf);
  strcpy (ttotal, " ");
  --left;
  while (left--)
    strcat (ttotal, " ");
  strcat (ttotal, tbuf);
  mvwaddstr (w2, 1, 61, ttotal);
#			else
  strcpy (ttotal, " Basic Amt: ");
  strcat (ttotal, tbuf);
  left = 75 - (strlen (position) + strlen (ttotal));
  wrefresh (w1);
  while (left--)
    {
      sprintf (position + strlen (position), "%s", " ");
    }
  sprintf (position + strlen (position) - 1, "%s", ttotal);
  position[74] = 0;
  mvwaddstr (w2, 1, 1, position);
#			endif

/**** print tax details on screen */
  //wattrset (w2, rgb(13));
  wattrset (w2, rgb (8));
  mvwaddstr (w2, 2, 1,
	     "                                                       ");
  strcpy (tbuf, tax1_name);
  if (strlen (taxon1_name))
    {
      strcat (tbuf, "+");
      strcat (tbuf, taxon1_name);
    }
  strcat (tbuf, "=");
  if (tax1_exist)
    mvwaddstr (w2, 2, 1, tbuf);
  sprintf (position, "%f", bill_detail.bill_tax1 + bill_detail.bill_taxon1);
  put_accurate (position, PRICE_ACT);
  left = strlen (tbuf) + 1;
  mvwaddstr (w2, 2, left, position);

  left += strlen (position) + 3;
  strcpy (tbuf, tax2_name);
  if (strlen (taxon2_name))
    {
      strcat (tbuf, "+");
      strcat (tbuf, taxon2_name);
    }
  strcat (tbuf, "=");
  if (tax2_exist)
    mvwaddstr (w2, 2, left, tbuf);
  sprintf (position, "%f", bill_detail.bill_tax2 + bill_detail.bill_taxon2);
  put_accurate (position, PRICE_ACT);
  left += strlen (tbuf);
  mvwaddstr (w2, 2, left, position);

  //wattrset (w2, rgb(13));
  wattrset (w2, rgb (8));
  mvwaddstr (w2, 3, 1,
	     "                                                       ");
  strcpy (tbuf, tax3_name);
  if (strlen (taxon3_name))
    {
      strcat (tbuf, "+");
      strcat (tbuf, taxon3_name);
    }
  strcat (tbuf, "=");
  if (tax3_exist)
    mvwaddstr (w2, 3, 1, tbuf);
  sprintf (position, "%f", bill_detail.bill_tax3 + bill_detail.bill_taxon3);
  put_accurate (position, PRICE_ACT);
  left = strlen (tbuf) + 1;
  mvwaddstr (w2, 3, left, position);

  left += strlen (position) + 3;
  strcpy (tbuf, tax4_name);
  if (strlen (taxon4_name))
    {
      strcat (tbuf, "+");
      strcat (tbuf, taxon4_name);
    }
  strcat (tbuf, "=");
  if (tax4_exist)
    mvwaddstr (w2, 3, left, tbuf);
  sprintf (position, "%f", bill_detail.bill_tax4 + bill_detail.bill_taxon4);
  put_accurate (position, PRICE_ACT);
  left += strlen (tbuf);
  mvwaddstr (w2, 3, left, position);
#					ifdef	UNI_COLOR
  wattrset (w2, rgb (7));
#					else
  wattrset (w2, rgb (1));
#					endif
  mvwaddstr (w2, 2, 52, " TaxAmt :");
  sprintf (position, "%f", bill_detail.bill_tax + bill_detail.bill_taxon);
  put_accurate (position, PRICE_ACT);
  mvwaddstr (w2, 2, 62, "             ");
  mvwaddstr (w2, 2, 75 - strlen (position), position);

/**** print misc details on screen */
  //wattrset (w2, rgb(13));
  wattrset (w2, rgb (8));
  mvwaddstr (w2, 4, 1,
	     "                                                      ");
  left = 1;
  if (misc1_per_exist)
    {
      sprintf (tbuf, "%f", misc1_per);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext1);
      strcat (position, " @:");
      strcat (position, tbuf);
      strcat (position, "%");
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 5;
    }
  if (misc1_amt_exist)
    {
      sprintf (tbuf, "%f", misc1_amt);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext1);
      strcat (position, ": ");
      strcat (position, tbuf);
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 5;
    }
  if (misc2_per_exist)
    {
      sprintf (tbuf, "%f", misc2_per);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext2);
      strcat (position, " @:");
      strcat (position, tbuf);
      strcat (position, "%");
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 5;
    }
  if (misc2_amt_exist)
    {
      sprintf (tbuf, "%f", misc2_amt);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext2);
      strcat (position, ": ");
      strcat (position, tbuf);
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 5;
    }
  if (misc3_per_exist)
    {
      sprintf (tbuf, "%f", misc1_per);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext3);
      strcat (position, " @:");
      strcat (position, tbuf);
      strcat (position, "%");
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 3;
    }
  if (misc3_amt_exist)
    {
      sprintf (tbuf, "%f", misc3_amt);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext3);
      strcat (position, ": ");
      strcat (position, tbuf);
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 5;
    }
  if (misc4_per_exist)
    {
      sprintf (tbuf, "%f", misc1_per);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext4);
      strcat (position, " @:");
      strcat (position, tbuf);
      strcat (position, "%");
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 3;
    }
  if (misc4_amt_exist)
    {
      sprintf (tbuf, "%f", misc4_amt);
      put_accurate (tbuf, PRICE_ACT);
      strcpy (position, misc.mtext4);
      strcat (position, ": ");
      strcat (position, tbuf);
      mvwaddstr (w2, 4, left, position);
      left = strlen (position) + 5;
    }
#			ifdef	UNI_COLOR
  wattrset (w2, rgb (7));
#			else
  wattrset (w2, rgb (2));
#			endif
  mvwaddstr (w2, 3, 52, " MiscAmt:");
  sprintf (position, "%f", bill_detail.bill_pmisc + bill_detail.bill_nmisc);
  put_accurate (position, PRICE_ACT);
  mvwaddstr (w2, 3, 62, "             ");
  mvwaddstr (w2, 3, 75 - strlen (position), position);

/**** print service details on screen */
  //wattrset (w2, rgb(13));
  wattrset (w2, rgb (8));
  mvwaddstr (w2, 6, 1, "CHANGE:");
  sprintf (position, "%f", change_amt);
  put_accurate (position, PRICE_ACT);
  mvwaddstr (w2, 6, 8, "                ");
  if (position[0] == '-')
    {
      mvwaddstr (w2, 6, 8, "0.00");
    }
  else
    {
      mvwaddstr (w2, 6, 8, position);
    }
  mvwaddstr (w2, 6, 25, "Service@  ");
  mvwaddstr (w2, 6, 25 + 10, "              ");
  sprintf (position, "%f", bill_detail.serv_cent);
  put_accurate (position, PRICE_ACT);
  strcat (position, "%");
  mvwaddstr (w2, 6, 25 + 10, position);
#					ifdef	UNI_COLOR
  wattrset (w2, rgb (7));
#					else
  wattrset (w2, rgb (3));
#					endif
  mvwaddstr (w2, 4, 52, " ServAmt:");
  sprintf (position, "%f", bill_detail.bill_serv);
  put_accurate (position, PRICE_ACT);
  mvwaddstr (w2, 4, 62, "             ");
  mvwaddstr (w2, 4, 75 - strlen (position), position);

/**** print service details on screen */
  //wattrset (w2, rgb(13));
  wattrset (w2, rgb (8));
  mvwaddstr (w2, 5, 1, "Amount Disc: ");
  dval = bill_detail.bill_amtdisc;
  sprintf (position, "%f", dval);
  put_accurate (position, PRICE_ACT);
  mvwaddstr (w2, 5, 15, "         ");
  mvwaddstr (w2, 5, 14, position);
  mvwaddstr (w2, 5, 25, "Discount@");
  mvwaddstr (w2, 5, 35, "       ");
  sprintf (position, "%f", bill_detail.dpercent);
  put_accurate (position, PRICE_ACT);
  strcat (position, "%=");
  mvwaddstr (w2, 5, 35, position);
  sprintf (position, "%f", bill_detail.bill_perdamt);
  put_accurate (position, PRICE_ACT);
  mvwaddstr (w2, 5, 42, "             ");
  mvwaddstr (w2, 5, 42, position);
#				ifdef	UNI_COLOR
  wattrset (w2, rgb (7));
#				else
  wattrset (w2, rgb (4));
#				endif
  mvwaddstr (w2, 5, 52, " TotDisc:");
  dval = 0.00 - (bill_detail.bill_perdamt + bill_detail.bill_amtdisc);
  sprintf (position, "%f", dval);
  put_accurate (position, PRICE_ACT);
  mvwaddstr (w2, 5, 62, "             ");
  mvwaddstr (w2, 5, 75 - strlen (position), position);

  wrefresh (w1);
  wrefresh (w2);
}

#		if	0
int
adjust_item_look ()
{
  int more = 0, left;
  int i = 1;
  char position[60];

  if (lcur_pos <= 11 || adjust_flag)
    {
      while (i <= 11)
	{
	  wattrset (w5, A_REVERSE | rgb (7));
	  mvwaddstr (w5, i, 1, lbills[i - 1]);
	  i++;
	}
      if (!adjust_flag)
	{
	  wattrset (w5, A_REVERSE | rgb (6));
	  mvwaddstr (w5, lcur_pos, 1, lbills[lcur_pos - 1]);
	}
    }
  else
    {
      int i = 1;
      more = lcur_pos - 11;
      while (i <= 10)
	{
	  wattrset (w5, A_REVERSE | rgb (7));
	  mvwaddstr (w5, i++, 1, lbills[more++]);
	}
      wattrset (w5, A_REVERSE | rgb (6));
      mvwaddstr (w5, i, 1, lbills[more]);
    }
  wattrset (w5, A_NORMAL | rgb (11));
  strcpy (position, " No Of Items Searched :");
  sprintf (position + strlen (position), "%d", lno_of_items);
  strcat (position + strlen (position), "         CurBar Position :");
  sprintf (position + strlen (position), "%d", lcur_pos);
  left = strlen (position);
  while (left < 58)
    position[left++] = ' ';
  position[58] = 0;
  mvwaddstr (w5, 12, 1, position);
  wrefresh (w5);
}
#		else
int
adjust_item_look ()
{
  int more = 0, left;
  int i = 1;
  char position[60];

  if (lcur_pos <= 11 || adjust_flag)
    {
      while (i <= 11)
	{
	  wattrset (w5, A_REVERSE | rgb (7));
	  mvwaddstr (w5, i, 1, lbills[i - 1]);
	  i++;
	}
      if (!adjust_flag)
	{
	  wattrset (w5, A_REVERSE | rgb (3));
	  mvwaddstr (w5, lcur_pos, 1, lbills[lcur_pos - 1]);
	}
    }
  else
    {
      int i = 1;
      more = lcur_pos - 11;
      while (i <= 10)
	{
	  wattrset (w5, A_REVERSE | rgb (7));
	  mvwaddstr (w5, i++, 1, lbills[more++]);
	}
      wattrset (w5, A_REVERSE | rgb (3));
      mvwaddstr (w5, i, 1, lbills[more]);
    }
  wattrset (w5, A_NORMAL | rgb (11));
  //wattrset (w5, A_NORMAL|rgb(6));
  strcpy (position, " No Of Items Searched :");
  sprintf (position + strlen (position), "%d", lno_of_items);
  strcat (position + strlen (position), "         CurBar Position :");
  sprintf (position + strlen (position), "%d", lcur_pos);
  left = strlen (position);
  while (left < 58)
    position[left++] = ' ';
  position[58] = 0;
  mvwaddstr (w5, 12, 1, position);
  wrefresh (w5);
}
#			endif

int
to_item_list_look (ITEM * sbuf)
{
  int left;
  double dval;
  char tbuf[40];

  left = 0;
  strcpy (lbills[lno_of_items], "  ");
  strcat (lbills[lno_of_items], sbuf->item_code);
  left = strlen (lbills[lno_of_items]);
  left = 7 - left;
  left += 5;
  while (left--)
    strcat (lbills[lno_of_items], " ");
  strcat (lbills[lno_of_items], sbuf->item_name);
  left = 30 - strlen (lbills[lno_of_items]);
  while (left--)
    strcat (lbills[lno_of_items], " ");
  dval = atof (sbuf->sell_price);
  sprintf (tbuf, "%f", dval);
  put_accurate (tbuf, PRICE_ACT);
  left = 9 - strlen (tbuf);
  while (left--)
    strcat (lbills[lno_of_items], " ");
  strcat (lbills[lno_of_items], tbuf);
  left = 48 - strlen (lbills[lno_of_items]);
  while (left--)
    strcat (lbills[lno_of_items], " ");
  sprintf (tbuf, "%f", sbuf->curr_stock);
  put_accurate (tbuf, PIECE_ACT);
  left = 8 - strlen (tbuf);
  while (left--)
    strcat (lbills[lno_of_items], " ");
  strcat (lbills[lno_of_items], tbuf);
  left = strlen (lbills[lno_of_items]);
  while (left < 58)
    lbills[lno_of_items][left++] = ' ';
  lbills[lno_of_items][58] = 0;
  lno_of_items++;
  attron (A_NORMAL | rgb (4));
  enter_status ();
  move (1, 18);
  return 1;
}

int
search_items (int flag)
{
  int ic, jc, ch, only_num, only_alpha;

  for (ic = 0; ic < MAX_MATCH; ic++)
    for (jc = 0; jc <= 58; jc++)
      {
	lbills[ic][jc] = ' ';
	if (jc == 58)
	  lbills[ic][jc] = 0;
      }
  /*              
     scr_restore ("billscreen"); 
     remove ("billscreen");
   */
  lno_of_items = 0;
  only_alpha = 0;
  only_num = 0;
  w4 = newwin (4, 60, 5, 10);
  w5 = newwin (14, 60, 8, 10);
  keypad (stdscr, FALSE);
  keypad (w4, TRUE);
#				ifndef	MONO
  wcolor_set (w4, 1, NULL);
  wcolor_set (w5, 1, NULL);
#				endif
  box (w4, 0, 0);
  box (w5, 0, 0);
  mvwaddstr (w4, 1, 1, " Item  Selection  By  Code  Or  Name :");
  mvwaddstr (w4, 2, 1,
	     " Code            Name            Price              Stock ");
  wrefresh (w5);
  wmove (w4, 1, 40);
  wrefresh (w4);
  lcur_pos = 0;
  isearch = 0;
  search_box = 0;
  while (1)
    {
      noecho ();
      if (search_box)
	{
	  ch = mvwgetch (w5, 1, 40 + isearch);
	  if (ch != CR_KEY && ch != KEY_UP && ch != KEY_DOWN
	      && ch != ESC_KEY && ch != CTRL_FF && ch != CTRL_BB)
	    continue;
	}
      else
	{
	  ch = mvwgetch (w4, 1, 40 + isearch);
	}
      if (isalnum (ch))
	{
	  if (!strlen (sbuf))
	    {
	      for (ic = 0; ic < MAX_MATCH; ic++)
		for (jc = 0; jc <= 58; jc++)
		  {
		    lbills[ic][jc] = ' ';
		    if (jc == 58)
		      lbills[ic][jc] = 0;
		  }
	      only_alpha = 0;
	      only_num = 0;
	    }
	  if (only_alpha)
	    {
	      if (isdigit (ch))
		continue;
	    }
	  if (only_num)
	    {
	      if (isalpha (ch))
		continue;
	    }
	  echo ();
	  if (isalpha (ch))
	    only_alpha = 1;
	  if (isdigit (ch))
	    only_num = 1;
	  wattrset (w4, A_REVERSE | rgb (9));
	  if (isearch == 18)
	    {
	      mvwaddch (w4, 1, 40 + isearch, sbuf[isearch - 1]);
	      continue;
	    }
	  mvwaddch (w4, 1, 40 + isearch, ch);
	  sbuf[isearch++] = ch;
	  sbuf[isearch] = 0;
	  wrefresh (w4);
				/**** match with item name or string ********/
	  for (ic = 0; ic < MAX_MATCH; ic++)
	    for (jc = 0; jc <= 58; jc++)
	      {
		lbills[ic][jc] = ' ';
		if (jc == 58)
		  lbills[ic][jc] = 0;
	      }
	  lno_of_items = 0;
	  adjust_item_look ();
	  while (fread (&item, sizeof (ITEM), 1, item_file))
	    {
	      if (strstr (item.item_code, sbuf) != NULL ||
		  strstr (item.item_name, sbuf) != NULL)
		{
		  if (item.valid == 'Y')
		    {
		      if (lno_of_items == MAX_MATCH)
			break;
		      lcur_pos = lno_of_items + 1;
		      to_item_list_look (&item);
		      adjust_item_look ();
		    }
		}
	    }
	  rewind (item_file);
	}
      if (search_box)
	{
	  if (ch == CTRL_FF)
	    {
	      echo ();
	      lcur_pos += 10;
	      if (lcur_pos >= MAX_MATCH)
		lcur_pos = MAX_MATCH;
	      adjust_item_look ();
	      continue;
	    }
	  if (ch == KEY_DOWN)
	    {
	      echo ();
	      lcur_pos++;
	      if (lcur_pos >= MAX_MATCH)
		lcur_pos = MAX_MATCH;
	      adjust_item_look ();
	      continue;
	    }
	  if (ch == CTRL_BB)
	    {
	      echo ();
	      lcur_pos -= 10;
	      if (lcur_pos <= 1)
		lcur_pos = 1;
	      adjust_item_look ();
	      if (lcur_pos == 1)
		{
		  keypad (stdscr, TRUE);
		  keypad (w5, FALSE);
		  search_box = 0;
		}
	      continue;
	    }
	  if (ch == KEY_UP)
	    {
	      echo ();
	      lcur_pos--;
	      if (lcur_pos <= 1)
		lcur_pos = 1;
	      adjust_item_look ();
	      if (lcur_pos == 1)
		{
		  keypad (stdscr, TRUE);
		  keypad (w5, FALSE);
		  search_box = 0;
		}
	      continue;
	    }
	  if (ch == CR_KEY)
	    {
	      lbills[lcur_pos - 1][9] = 0;
	      strcpy (select_buf, lbills[lcur_pos - 1] + 2);
	      gptr = select_buf;
	      while (*gptr != ' ')
		gptr++;
	      *gptr = 0;
	      select_flag = 1;
	      keypad (stdscr, TRUE);
	      keypad (w5, FALSE);
	      keypad (w4, FALSE);
	      break;
	    }
	  if (ch == ESC_KEY)
	    {
	      keypad (stdscr, TRUE);
	      keypad (w5, FALSE);
	      keypad (w4, FALSE);
	      break;
	    }
	}
      if (ch == KEY_UP && lno_of_items > 1 && lcur_pos != 1)
	{
	  keypad (stdscr, FALSE);
	  keypad (w5, TRUE);
	  search_box = 1;
	  continue;
	}
      if (ch == CTRL_BB)
	{
	  echo ();
	  lcur_pos -= 10;
	  if (lcur_pos <= 1)
	    lcur_pos = 1;
	  adjust_item_look ();
	  continue;
	}
      if (ch == CTRL_FF)
	{
	  echo ();
	  lcur_pos += 10;
	  if (lcur_pos >= MAX_MATCH)
	    lcur_pos = MAX_MATCH;
	  adjust_item_look ();
	  continue;
	}
      if (ch == KEY_DOWN)
	{
	  keypad (stdscr, FALSE);
	  keypad (w5, TRUE);
	  search_box = 1;
	  continue;
	}
      if (ch == KEY_BACKSPACE)
	{
	  if (isearch == 18)
	    mvwaddch (w4, 1, 40 + isearch, ' ');
	  isearch--;
	  if (isearch <= 0)
	    isearch = 0;
	  mvwaddch (w4, 1, 40 + isearch, ' ');
	  sbuf[strlen (sbuf) - 1] = 0;
	  wrefresh (w4);
	  for (ic = 0; ic < MAX_MATCH; ic++)
	    for (jc = 0; jc <= 58; jc++)
	      {
		lbills[ic][jc] = ' ';
		if (jc == 58)
		  lbills[ic][jc] = 0;
	      }
	  lno_of_items = 0;
	  if (!strlen (sbuf))
	    {
	      adjust_item_look ();
	      continue;
	    }
	  adjust_item_look ();
	  while (fread (&item, sizeof (ITEM), 1, item_file))
	    {
	      if (strstr (item.item_code, sbuf) != NULL ||
		  strstr (item.item_name, sbuf) != NULL)
		{
		  if (item.valid == 'Y')
		    {
		      if (lno_of_items == MAX_MATCH)
			break;
		      lcur_pos = lno_of_items + 1;
		      to_item_list_look (&item);
		      adjust_item_look ();
		    }
		}
	    }
	  rewind (item_file);
	  continue;
	}
      if (ch == CR_KEY)
	{
	  lbills[lcur_pos - 1][9] = 0;
	  strcpy (select_buf, lbills[lcur_pos - 1] + 2);
	  gptr = select_buf;
	  while (*gptr != ' ')
	    gptr++;
	  *gptr = 0;
	  select_flag = 1;
	  keypad (stdscr, TRUE);
	  keypad (w5, FALSE);
	  keypad (w4, FALSE);
	  break;
	}
      if (ch == ESC_KEY)
	{
	  keypad (stdscr, TRUE);
	  keypad (w5, FALSE);
	  keypad (w4, FALSE);
	  break;
	}
    }
}

int
progitem_to_billitem ()
{
  char item_found = 0, tbuf[50], *p;
  float tval;
  int i, left = 0;
  float sprice;
  double final_amt;

  bill_item[no_of_items].bill_no = 1;
  bill_item[no_of_items].item_code = atoi (item.item_code);
  strcpy (bill_item[no_of_items].stricode, item.item_code);
  strcpy (bill_item[no_of_items].item_name, item.item_name);
  strcpy (bill_item[no_of_items].dept_link, item.dept_link);
  bill_item[no_of_items].price = atof (item.sell_price);
  bill_item[no_of_items].per_disc = atof (item.item_disc);
  if (kot_kho)
    {
      bill_item[no_of_items].qty = xkot_item.qty;
    }
  else
    {
      bill_item[no_of_items].qty = 1;
    }
  bill_item[no_of_items].pieces = 1;
  bill_item[no_of_items].pieces_flag = 0;
  bill_item[no_of_items].tax_flag = 0;
  strcpy (bill_item[no_of_items].tax_link, item.tax_link);
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
      bill_item[no_of_items].per_tax = atof (tax.tamt);
      if (bill_item[no_of_items].per_tax > 0.00)
	bill_item[no_of_items].tax_flag = (char) atoi (tax.tax_no);
      bill_item[no_of_items].per_taxon = atof (tax.toamt);
      if (bill_item[no_of_items].tax_flag == 1)
	{
	  if (!tax1_exist)
	    {
	      strcpy (tax1_name, tax.tname);
	      strcpy (taxon1_name, tax.toname);
	      tax1_exist = 1;
	    }
	}
      if (bill_item[no_of_items].tax_flag == 2)
	{
	  if (!tax2_exist)
	    {
	      strcpy (tax2_name, tax.tname);
	      strcpy (taxon2_name, tax.toname);
	      tax2_exist = 1;
	    }
	}
      if (bill_item[no_of_items].tax_flag == 3)
	{
	  if (!tax3_exist)
	    {
	      strcpy (tax3_name, tax.tname);
	      strcpy (taxon3_name, tax.toname);
	      tax3_exist = 1;
	    }
	}
      if (bill_item[no_of_items].tax_flag == 4)
	{
	  if (!tax4_exist)
	    {
	      strcpy (tax4_name, tax.tname);
	      strcpy (taxon4_name, tax.toname);
	      tax4_exist = 1;
	    }
	}
    }
  item_found = 0;
  bill_item[no_of_items].tax_amt = 0;
  bill_item[no_of_items].taxon_amt = 0;
  bill_item[no_of_items].disc_amt = 0;
  bill_item[no_of_items].disc_flag = 1;
  bill_item[no_of_items].valid = 'Y';
  bill_item[no_of_items].item_amt = 0;
  calc_bill_item ();
  format_bill_item ();
  no_of_items++;
}

int
calc_over_flow (float data, char flag)
{
  float tval, store_orig;
  double dtval;
  int tcur_pos;
  char tbuf[40];

  tcur_pos = cur_pos - 1;
  if (flag == DQTY)
    {
      store_orig = bill_item[tcur_pos].qty;
      bill_item[tcur_pos].qty = data;
    }
  if (flag == DPRICE)
    {
      store_orig = bill_item[tcur_pos].price;
      bill_item[tcur_pos].price = data;
    }
  if (flag == DPIECE)
    {
      store_orig = bill_item[tcur_pos].pieces;
      bill_item[tcur_pos].pieces = data;
    }
  if (flag == DDISC)
    {
      store_orig = bill_item[tcur_pos].per_disc;
      bill_item[tcur_pos].per_disc = data;
    }
  tval = bill_item[tcur_pos].price * bill_item[tcur_pos].per_disc;
  tval = tval / 100.00;
  dtval = ((double) bill_item[tcur_pos].qty *
	   (double) bill_item[tcur_pos].pieces) *
    ((double) bill_item[tcur_pos].price - (double) tval);
  bill_item[tcur_pos].item_amt = dtval;
  sprintf (tbuf, "%f", dtval);
  put_accurate (tbuf, PRICE_ACT);
  if (flag == DQTY)
    {
      bill_item[tcur_pos].qty = store_orig;
    }
  if (flag == DPRICE)
    {
      bill_item[tcur_pos].price = store_orig;
    }
  if (flag == DDISC)
    {
      bill_item[tcur_pos].per_disc = store_orig;
    }
  if (flag == DPIECE)
    {
      bill_item[tcur_pos].pieces = store_orig;
    }
  if (strlen (tbuf) > 13)
    return 0;
  else
    return 1;
}

int
calc_bill_item ()
{
  float tval, xval, dtval;
  double xdtval;
  int tcur_pos;

  tcur_pos = no_of_items;
  if (override_flag)
    tcur_pos = cur_pos - 1;
#			if	ONLY_DISC
  tval = bill_item[tcur_pos].price * bill_item[tcur_pos].per_disc;
  tval = tval / 100.00;
  dtval = ((double) bill_item[tcur_pos].qty *
	   (double) bill_item[tcur_pos].pieces) *
    ((double) bill_item[tcur_pos].price - (double) tval);
  bill_item[tcur_pos].item_amt = dtval;
#			else
/*** disc on sell_price ****/
  tval = bill_item[tcur_pos].price * bill_item[tcur_pos].per_disc;
  tval = tval / 100.00;
  tval = bill_item[tcur_pos].price - tval;
  dtval = tval;
/**** tax on (sell_price - disc_amt) ******/
  tval = tval * bill_item[tcur_pos].per_tax;
  tval = tval / 100.00;
  if (tval > 0)
    {
      xval = ((double) bill_item[tcur_pos].qty *
	      (double) bill_item[tcur_pos].pieces) * tval;
      bill_item[tcur_pos].tax_amt = xval;
    }
/**** tax on tax_amt ******/
  xval = tval * bill_item[tcur_pos].per_taxon;
  xval = xval / 100.00;
  if (xval > 0)
    {
      xval = ((double) bill_item[tcur_pos].qty *
	      (double) bill_item[tcur_pos].pieces) * xval;
      bill_item[tcur_pos].taxon_amt = xval;
    }
  xdtval = ((double) bill_item[tcur_pos].qty *
	    (double) bill_item[tcur_pos].pieces) * (double) dtval;
  bill_item[tcur_pos].item_amt = xdtval;
#			endif
}

int
calc_bill_total ()
{
  int i, j;
  double tval, dtval;

  lmisc1_amt = 0.00;
  lmisc2_amt = 0.00;
  lmisc3_amt = 0.00;
  lmisc4_amt = 0.00;
  lmisc1_per = 0.00;
  lmisc2_per = 0.00;
  lmisc3_per = 0.00;
  lmisc4_per = 0.00;

  bill_detail.bill_total = 0.00;
  bill_detail.bill_payble = 0.00;
  bill_detail.bill_tax = 0.00;
  bill_detail.bill_taxon = 0.00;
  bill_detail.bill_tax1 = 0.00;
  bill_detail.bill_tax2 = 0.00;
  bill_detail.bill_tax3 = 0.00;
  bill_detail.bill_tax4 = 0.00;
  bill_detail.bill_taxon1 = 0.00;
  bill_detail.bill_taxon2 = 0.00;
  bill_detail.bill_taxon3 = 0.00;
  bill_detail.bill_taxon4 = 0.00;
  bill_detail.bill_pmisc = 0.00;
  bill_detail.bill_nmisc = 0.00;
  for (i = 0; i != MAX_BILL_ITEMS; i++)
    {
      if (bill_item[i].valid == 'Y')
	{
	  bill_detail.bill_total += bill_item[i].item_amt;
	  if (bill_item[i].tax_flag)
	    {
	      bill_detail.bill_tax += bill_item[i].tax_amt;
	      bill_detail.bill_taxon += bill_item[i].taxon_amt;
	      if (bill_item[i].tax_flag == 1)
		{
		  bill_detail.bill_tax1 += bill_item[i].tax_amt;
		  bill_detail.bill_taxon1 += bill_item[i].taxon_amt;
		}
	      if (bill_item[i].tax_flag == 2)
		{
		  bill_detail.bill_tax2 += bill_item[i].tax_amt;
		  bill_detail.bill_taxon2 += bill_item[i].taxon_amt;
		}
	      if (bill_item[i].tax_flag == 3)
		{
		  bill_detail.bill_tax3 += bill_item[i].tax_amt;
		  bill_detail.bill_taxon3 += bill_item[i].taxon_amt;
		}
	      if (bill_item[i].tax_flag == 4)
		{
		  bill_detail.bill_tax4 += bill_item[i].tax_amt;
		  bill_detail.bill_taxon4 += bill_item[i].taxon_amt;
		}
	    }
	}
    }
  bill_detail.bill_payble += bill_detail.bill_total;
  bill_detail.bill_payble = (double) bill_detail.bill_tax +
    bill_detail.bill_payble;
  bill_detail.bill_payble = (double) bill_detail.bill_taxon +
    bill_detail.bill_payble;

  dtval = bill_detail.bill_total * (double) bill_detail.serv_cent;
  bill_detail.bill_serv = dtval / 100.00;
  bill_detail.bill_payble += bill_detail.bill_serv;

  dtval = bill_detail.bill_total * (double) bill_detail.dpercent;
  bill_detail.bill_perdamt = dtval / 100.00;
  bill_detail.bill_payble -= bill_detail.bill_perdamt;

  if (toupper (oprtion.fmisc_amt[0]) == 'Y')
    {
      if (misc.mvalid1[0] == 'Y')
	{
	  if (strlen (misc.mper1))
	    {
	      dtval = bill_detail.bill_total * (double) misc1_per;
	      misc1_per_exist = 1;
	      if (misc.math1[0] == '+')
		{
		  lmisc1_per = dtval / 100.00;
		}
	      if (misc.math1[0] == '-')
		{
		  lmisc1_per = (dtval / 100.00) * (-1);
		}
	    }
	  else
	    {
	      misc1_amt_exist = 1;
	      if (misc.math1[0] == '+')
		{
		  lmisc1_amt = misc1_amt;
		}
	      if (misc.math1[0] == '-')
		{
		  lmisc1_amt = misc1_amt * (-1);
		}
	    }
	}
      if (misc.mvalid2[0] == 'Y')
	{
	  if (strlen (misc.mper2))
	    {
	      dtval = bill_detail.bill_total * (double) misc2_per;
	      misc2_per_exist = 2;
	      if (misc.math2[0] == '+')
		{
		  lmisc2_per = dtval / 100.00;
		}
	      if (misc.math2[0] == '-')
		{
		  lmisc2_per = (dtval / 100.00) * (-1);
		}
	    }
	  else
	    {
	      misc2_amt_exist = 2;
	      if (misc.math2[0] == '+')
		{
		  lmisc2_amt = misc2_amt;
		}
	      if (misc.math2[0] == '-')
		{
		  lmisc2_amt = misc2_amt * (-1);
		}
	    }
	}
      if (misc.mvalid3[0] == 'Y')
	{
	  if (strlen (misc.mper3))
	    {
	      misc3_per_exist = 2;
	      dtval = bill_detail.bill_total * (double) misc3_per;
	      if (misc.math3[0] == '+')
		{
		  lmisc3_per = dtval / 100.00;
		}
	      if (misc.math3[0] == '-')
		{
		  lmisc3_per = (dtval / 100.00) * (-1);
		}
	    }
	  else
	    {
	      misc3_amt_exist = 1;
	      if (misc.math3[0] == '+')
		{
		  lmisc3_amt = misc3_amt;
		}
	      if (misc.math3[0] == '-')
		{
		  lmisc3_amt = misc3_amt * (-1);
		}
	    }
	}
      if (misc.mvalid4[0] == 'Y')
	{
	  if (strlen (misc.mper4))
	    {
	      misc4_per_exist = 1;
	      dtval = bill_detail.bill_total * (double) misc4_per;
	      if (misc.math4[0] == '+')
		{
		  lmisc4_per = dtval / 100.00;
		}
	      if (misc.math4[0] == '-')
		{
		  lmisc4_per = (dtval / 100.00) * (-1);
		}
	    }
	  else
	    {
	      misc4_amt_exist = 1;
	      if (misc.math4[0] == '+')
		{
		  lmisc4_amt = misc4_amt;
		}
	      if (misc.math4[0] == '-')
		{
		  lmisc4_amt = misc4_amt * (-1);
		}
	    }
	}
      bill_detail.bill_pmisc +=
	(lmisc1_per + lmisc2_per + lmisc3_per + lmisc4_per);
      bill_detail.bill_nmisc +=
	(lmisc1_amt + lmisc2_amt + lmisc3_amt + lmisc4_amt);
      bill_detail.bill_payble += bill_detail.bill_pmisc;
      bill_detail.bill_payble += bill_detail.bill_nmisc;
    }
  else
    {
      if (misc_no == 1)
	{
	  if (strlen (misc.mper1))
	    {
	      misc1_per_exist = 1;
	      dtval = bill_detail.bill_total * (double) misc1_per;
	      if (misc.math1[0] == '+')
		{
		  lmisc1_per = dtval / 100.00;
		}
	      if (misc.math1[0] == '-')
		{
		  lmisc1_per = (dtval / 100.00) * (-1.00);
		}
	    }
	  else
	    {
	      misc1_amt_exist = 1;
	      if (misc.math1[0] == '+')
		{
		  lmisc1_amt = misc1_amt * (1);
		}
	      if (misc.math1[0] == '-')
		{
		  lmisc1_amt = misc1_amt * (-1);
		}
	    }
	}
      if (misc_no == 2)
	{
	  if (strlen (misc.mper2))
	    {
	      misc2_per_exist = 1;
	      dtval = bill_detail.bill_total * (double) misc2_per;
	      if (misc.math2[0] == '+')
		{
		  lmisc2_per = dtval / 100.00;
		}
	      if (misc.math2[0] == '-')
		{
		  lmisc2_per = dtval / 100.00 * (-1);
		}
	    }
	  else
	    {
	      misc2_amt_exist = 1;
	      if (misc.math2[0] == '+')
		{
		  lmisc2_amt = misc2_amt * (1.00);
		}
	      if (misc.math2[0] == '-')
		{
		  lmisc2_amt = misc2_amt * (-1.00);
		}
	    }
	}
      if (misc_no == 3)
	{
	  if (strlen (misc.mper3))
	    {
	      misc3_per_exist = 1;
	      dtval = bill_detail.bill_total * (double) misc3_per;
	      if (misc.math3[0] == '+')
		{
		  lmisc3_per = dtval / 100.00;
		}
	      if (misc.math3[0] == '-')
		{
		  lmisc3_per = dtval / 100.00 * (-1);
		}
	    }
	  else
	    {
	      misc3_amt_exist = 1;
	      if (misc.math3[0] == '+')
		{
		  lmisc3_amt = misc3_amt * (1);
		}
	      if (misc.math3[0] == '-')
		{
		  lmisc3_amt = misc3_amt * (-1);
		}
	    }
	}
      if (misc_no == 4)
	{
	  if (strlen (misc.mper4))
	    {
	      dtval = bill_detail.bill_total * (double) misc4_per;
	      misc4_per_exist = 1;
	      if (misc.math4[0] == '+')
		{
		  lmisc4_per = dtval / 100.00;
		}
	      if (misc.math4[0] == '-')
		{
		  lmisc4_per = dtval / 100.00 * (-1);
		}
	    }
	  else
	    {
	      misc4_amt_exist = 1;
	      if (misc.math4[0] == '+')
		{
		  lmisc4_amt = misc4_amt * (1);
		}
	      if (misc.math4[0] == '-')
		{
		  lmisc4_amt = misc4_amt * (-1);
		}
	    }
	}

      bill_detail.bill_pmisc +=
	(lmisc1_per + lmisc2_per + lmisc3_per + lmisc4_per);
      bill_detail.bill_nmisc +=
	(lmisc1_amt + lmisc2_amt + lmisc3_amt + lmisc4_amt);
      bill_detail.bill_payble += bill_detail.bill_pmisc;
      bill_detail.bill_payble += bill_detail.bill_nmisc;
    }
  bill_detail.bill_payble -= bill_detail.bill_amtdisc;
#			if	1
  if (card_used || credit_used || chq_used || cash_used)
    {
      balance_amt = bill_detail.bill_payble - paid_amt;
    }
  change_amt = paid_amt - bill_detail.bill_payble;
#			endif
}

int
display_bill_detail ()
{
  char tbuf[40], tpbuf[40];
  int left;
  sprintf (tbuf, "%f", bill_detail.bill_payble);
  put_accurate (tbuf, PRICE_ACT);
  strcpy (tpbuf, " PAYBLE :");
  left = 14 - strlen (tbuf);
  while (left--)
    strcat (tpbuf, " ");
  strcat (tpbuf, tbuf);
  /*
     wattrset (w6, rgb(13));
     mvwaddstr (w6, 1,1, "                      ");       
     mvwaddstr (w6, 1,1, tpbuf);  
     wrefresh (w6);
   */
  //wattrset (w2, rgb(13)|A_REVERSE);
  wattrset (w2, rgb (20) | A_BOLD);
  mvwaddstr (w2, 6, 52, tpbuf);
  wrefresh (w2);
}

int
update_item_data ()
{

  if (qty_override)
    {
      override_flag = 1;
      bill_item[cur_pos - 1].qty = atof (status_field);
    }
  if (price_override)
    {
      override_flag = 1;
      bill_item[cur_pos - 1].price = atof (status_field);
    }
  if (disc_override)
    {
      override_flag = 1;
      bill_item[cur_pos - 1].per_disc = atof (status_field);
      bill_item[cur_pos - 1].disc_flag = 2;
    }
  if (piece_override)
    {
      override_flag = 1;
      bill_item[cur_pos - 1].pieces = atof (status_field);
      bill_item[cur_pos - 1].pieces_flag = 1;
    }
  calc_bill_item ();
  format_bill_item ();
  adjust_item ();
  calc_bill_total ();
  display_total_items_amt ();
  display_bill_detail ();
}

int
format_bill_item ()
{
  ITEM titem;
  char tbuf[50], *p;
  float tval;
  int i, tcur_pos, left = 0;
  float sprice;
  double final_amt;

  tcur_pos = no_of_items;
  if (override_flag)
    tcur_pos = cur_pos - 1;
/**** add item_code to cursor-bar-string **************/
  sprintf (tbuf, "%d", bill_item[tcur_pos].item_code);
  strcpy (bills[tcur_pos], tbuf);
  left = 4 - strlen (bills[tcur_pos]);
  left += 2;
  format_string (&bills, left, RIGHT_SIDE, NULL);

/**** add item_name to cursor-bar-string **************/
  strcat (bills[tcur_pos], bill_item[tcur_pos].item_name);
  left = 16 - strlen (bill_item[tcur_pos].item_name);
  left += 2;
  format_string (&bills, left, RIGHT_SIDE, NULL);

/**** add item_quntity to cursor-bar-string **************/
  if (override_flag)
    {
      sprintf (tbuf, "%f", bill_item[tcur_pos].qty);
      put_accurate (tbuf, QTY_ACT);
    }
  else
    {
      if (kot_kho)
	{
	  sprintf (tbuf, "%f", xkot_item.qty);
	  put_accurate (tbuf, QTY_ACT);
	}
      else
	strcpy (tbuf, "1.000");
    }
  left = 9 - strlen (tbuf);
  while (left--)
    strcat (bills[tcur_pos], " ");
  strcat (bills[tcur_pos], tbuf);
  if (strlen (bill_item[tcur_pos].unit))
    {
      strcat (bills[tcur_pos], bill_item[tcur_pos].unit);
      left = 3 - strlen (bill_item[tcur_pos].unit);
      while (left--)
	strcat (bills[tcur_pos], " ");
    }
  else
    {
      left = 3;
      while (left--)
	strcat (bills[tcur_pos], " ");
    }
  format_string (&bills, 2, RIGHT_SIDE, NULL);

/**** add item_price to cursor-bar-string **************/
  sprice = bill_item[tcur_pos].price;
  sprintf (tbuf, "%f", sprice);
  put_accurate (tbuf, PRICE_ACT);
  left = 8 - strlen (tbuf);
  while (left--)
    strcat (bills[tcur_pos], " ");
  strcat (bills[tcur_pos], tbuf);
  format_string (&bills, 2, RIGHT_SIDE, NULL);

/**** add item_pieces to cursor-bar-string **************/
  if (bill_item[tcur_pos].pieces_flag)
    {
      sprintf (tbuf, "%f", bill_item[tcur_pos].pieces);
      put_accurate (tbuf, PIECE_ACT);
      left = 4 - strlen (tbuf);
      while (left--)
	strcat (bills[tcur_pos], " ");
      strcat (bills[tcur_pos], tbuf);
      format_string (&bills, 2, RIGHT_SIDE, NULL);
    }
  else
    {
      format_string (&bills, 6, RIGHT_SIDE, NULL);
    }

/**** add item_discount to cursor-bar-string **************/
  if (bill_item[tcur_pos].disc_flag)
    {
      if (bill_item[tcur_pos].disc_flag == 1)
	{
	  tval = bill_item[tcur_pos].per_disc;
	  sprintf (tbuf, "%f", tval);
	  put_accurate (tbuf, PRICE_ACT);
	}
      if (bill_item[tcur_pos].disc_flag == 2)
	{
	  tval = bill_item[tcur_pos].per_disc;
	  sprintf (tbuf, "%f", tval);
	  put_accurate (tbuf, PRICE_ACT);
	}
      left = 5 - strlen (tbuf);
      while (left--)
	strcat (bills[tcur_pos], " ");
      strcat (bills[tcur_pos], tbuf);
      format_string (&bills, 2, RIGHT_SIDE, NULL);
    }
  else
    {
      format_string (&bills, 7, RIGHT_SIDE, NULL);
    }

/**** add item_final_amount to cursor-bar-string **************/
  sprintf (tbuf, "%f", bill_item[tcur_pos].item_amt);
  put_accurate (tbuf, PRICE_ACT);
#			ifdef		MAX_IS_10CR
  /* for item_amt 8.2=12 chars here max is (10crore-1)Rs */
  left = 12 - strlen (tbuf);
#			else
  /* for item_amt 9.2=13 chars here max is (100crore-1)Rs */
  left = 13 - strlen (tbuf);
#			endif
  while (left--)
    strcat (bills[tcur_pos], " ");
  strcat (bills[tcur_pos], tbuf);
#			ifdef		MAX_IS_10CR
  format_string (&bills, 1, RIGHT_SIDE, NULL);
#			endif

/********** display cursor-bar-string is created ********************/
  left = strlen (bills[tcur_pos]);
  while (left < 74)
    bills[tcur_pos][left++] = ' ';
  bills[tcur_pos][74] = 0;
  status_field[0] = 0;
  attron (A_NORMAL | rgb (4));
  enter_status ();
  move (1, 18);
  return 1;
}

void
put_accurate (char *p, char flag)
{

  p = strchr (p, '.');
  if (flag == PRICE_ACT)
    p = p + 3;
  if (flag == QTY_ACT)
    p = p + 4;
  if (flag == PIECE_ACT)
    p = strchr (p, '.');
  *p = 0;
}

/*** 	format_string (); will appends or pre-appends spaces to, 
			either member of 2d-array (first-argument) or array (last-argument) ****/

void
format_string (char (*src)[][80], char no, char side, char *brc)
{
  char tbuf[50];
  int tcur_pos;

  tcur_pos = no_of_items;
  if (override_flag)
    tcur_pos = cur_pos - 1;
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

int
yesexit_do_ok (void *key_menu)
{
  return RET_OK;
}

int
noexit_do_ok (void *key_menu)
{
  return RET_PRIV;
}

int
bill_error (char *err)
{
  if (!yes_move)
    stop_alarm ();
  scr_dump ("billscreen1");
  set_error (err);
  scr_restore ("billscreen1");
  remove ("billscreen1");
  remove ("screen2");
  if (!yes_move)
    start_alarm ();
  status_field[0] = 0;
  refresh ();
  attron (A_NORMAL | rgb (4));
  enter_status ();
  if (!yes_move)
    move (1, 18);
#			if	 0
/****	take care for this in multiple menus and 
			error menus for screen damage. 
			Enable if items disapper in billscreen ****/
  // adjust_item ();
#			endif
  return 0;
}

int
fill_item_hole ()
{
  int i, j;

  for (i = 0; i <= no_of_items; i++)
    if (bill_item[i].valid != 'Y')
      break;
  for (j = i; j < no_of_items; j++)
    {
      bill_item[j] = bill_item[j + 1];
      strcpy (bills[j], bills[j + 1]);
    }
  if (no_of_items)
    --no_of_items;

/* if tax-name is not to display if respective tax is zero */
/* check all items for respective tax_flag, if !found make respective */
/* tax_exist as zero eg. tax_flag !=1|2|3|4, tax1234_exist=0 */
/* cur_pos = no_of_items; ---->> keeps cur_pos at end */

  if (!cur_pos)
    cur_pos = 1;
  if (!no_of_items)
    {
      commit_ok = 0;
      cash_ok = 0;
      chq_ok = 0;
      card_ok = 0;
      credit_ok = 0;
      card_used = 0;
      cash_used = 0;
      credit_used = 0;
      chq_used = 0;
      paid_amt = 0;
      change_amt = 0;
      balance_amt = 0;
      bill_detail.table = 0;
      bill_detail.wtr_no = 0;
      bill_detail.sman_no = 0;
      bill_detail.bill_type = REGULAR;
      bill_detail.dpercent = 0.00;
      bill_detail.bill_amtdisc = 0.00;
      bill_detail.bill_serv = 0.00;
      bill_detail.serv_cent = 0.00;
      bill_detail.bill_pmisc = 0.00;
      bill_detail.bill_nmisc = 0.00;
      bill_detail.bill_tax1 = 0.00;
      bill_detail.bill_tax2 = 0.00;
      bill_detail.bill_tax3 = 0.00;
      bill_detail.bill_tax4 = 0.00;
      bill_detail.bill_taxon1 = 0.00;
      bill_detail.bill_taxon2 = 0.00;
      bill_detail.bill_taxon3 = 0.00;
      bill_detail.bill_taxon4 = 0.00;
      misc1_amt = 0.00;
      misc2_amt = 0.00;
      misc3_amt = 0.00;
      misc4_amt = 0.00;
      misc1_per = 0.00;
      misc2_per = 0.00;
      misc3_per = 0.00;
      misc4_per = 0.00;
      tax1_exist = 0;
      tax2_exist = 0;
      tax3_exist = 0;
      tax4_exist = 0;
      tax1_name[0] = 0;
      taxon1_name[0] = 0;
      tax2_name[0] = 0;
      taxon2_name[0] = 0;
      tax3_name[0] = 0;
      taxon3_name[0] = 0;
      tax4_name[0] = 0;
      taxon4_name[0] = 0;
      bill_detail.cash_amt = 0.00;
      bill_detail.card_amt = 0.00;
      bill_detail.credit_amt = 0.00;
      gcard_no[0] = 0;
      gchq_no[0] = 0;
      gcust_name[0] = 0;
      gcard_name[0] = 0;
      gbank_name[0] = 0;
      no_of_miscs = 0;
      start_misc ();
    }
}

int
enter_status ()
{
  mvaddstr (1, 1, " ENTER ENTITY =>>                              ");
}

int
start_alarm ()
{
  signal (SIGALRM, disp_date_time_bill);
  alarm (60);			/* dont keep less invoke@60sec */
}

int
stop_alarm ()
{
  signal (SIGALRM, SIG_IGN);
}

int
calc_entered_misc (int misc_no)
{
  double dtval;
#			if	1
  calc_bill_total ();
  display_total_items_amt ();
  display_bill_detail ();
  disc_override = 0;
  override_flag = 0;
#			else
  if (misc_no == 1)
    {
      if (strlen (misc.mper1))
	{
	  dtval = bill_detail.bill_total * (double) misc1_per;
	  if (misc.math1[0] == '+')
	    {
	      bill_detail.bill_pmisc += dtval / 100.00;
	    }
	  if (misc.math1[0] == '-')
	    {
	      bill_detail.bill_nmisc -= dtval / 100.00;
	    }
	}
      else
	{
	  if (misc.math1[0] == '+')
	    {
	      bill_detail.bill_pmisc += misc1_amt;
	    }
	  if (misc.math1[0] == '-')
	    {
	      bill_detail.bill_nmisc -= misc1_amt;
	    }
	}
    }
  if (misc_no == 2)
    {
      if (strlen (misc.mper2))
	{
	  dtval = bill_detail.bill_total * (double) misc2_per;
	  if (misc.math2[0] == '+')
	    {
	      bill_detail.bill_pmisc += dtval / 100.00;
	    }
	  if (misc.math2[0] == '-')
	    {
	      bill_detail.bill_nmisc -= dtval / 100.00;
	    }
	}
      else
	{
	  if (misc.math2[0] == '+')
	    {
	      bill_detail.bill_pmisc += misc2_amt;
	    }
	  if (misc.math2[0] == '-')
	    {
	      bill_detail.bill_nmisc -= misc2_amt;
	    }
	}
    }
  if (misc_no == 3)
    {
      if (strlen (misc.mper3))
	{
	  dtval = bill_detail.bill_total * (double) misc3_per;
	  if (misc.math3[0] == '+')
	    {
	      bill_detail.bill_pmisc += dtval / 100.00;
	    }
	  if (misc.math3[0] == '-')
	    {
	      bill_detail.bill_nmisc -= dtval / 100.00;
	    }
	}
      else
	{
	  if (misc.math3[0] == '+')
	    {
	      bill_detail.bill_pmisc += misc3_amt;
	    }
	  if (misc.math3[0] == '-')
	    {
	      bill_detail.bill_nmisc -= misc3_amt;
	    }
	}
    }
  if (misc_no == 4)
    {
      if (strlen (misc.mper4))
	{
	  dtval = bill_detail.bill_total * (double) misc4_per;
	  if (misc.math4[0] == '+')
	    {
	      bill_detail.bill_pmisc += dtval / 100.00;
	    }
	  if (misc.math4[0] == '-')
	    {
	      bill_detail.bill_nmisc -= dtval / 100.00;
	    }
	}
      else
	{
	  if (misc.math4[0] == '+')
	    {
	      bill_detail.bill_pmisc += misc4_amt;
	    }
	  if (misc.math4[0] == '-')
	    {
	      bill_detail.bill_nmisc -= misc4_amt;
	    }
	}
    }

  bill_detail.bill_payble += bill_detail.bill_pmisc;
  bill_detail.bill_payble += bill_detail.bill_nmisc;
#				endif
}

int
start_misc ()
{

  misc_file = fopen ("./pos_files/dbase/misc_ifile", "r");
  fread (&misc, sizeof (MISC), 1, misc_file);
  fclose (misc_file);
  if (strlen (misc.mper1))
    {
      misc1_per = atof (misc.mper1);
    }
  else
    {
      misc1_amt = atof (misc.mamt1);
    }
  if (strlen (misc.mper2))
    {
      misc2_per = atof (misc.mper2);
    }
  else
    {
      misc2_amt = atof (misc.mamt2);
    }
  if (strlen (misc.mper3))
    {
      misc3_per = atof (misc.mper3);
    }
  else
    {
      misc3_amt = atof (misc.mamt3);
    }
  if (strlen (misc.mper4))
    {
      misc4_per = atof (misc.mper4);
    }
  else
    {
      misc4_amt = atof (misc.mamt4);
    }
}
