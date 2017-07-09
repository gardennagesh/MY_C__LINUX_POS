/*prog.c-DATA-BASE-CRETING-FUNCTIONS-ARE-DEFINED-HERE*/
/* Developer: Nagesh Nanjundachari */

#define PROG_DECLARES

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include "prog.h"
#include "menu.h"
#include "common.h"
#include "key.h"
#include "cprog.c"

int
open_close_all_files (int flag)
{


  if ((item_file = fopen ("./pos_files/dbase/item_ifile", "r")) == NULL)
    {
      if ((item_file = fopen ("./pos_files/dbase/item_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/item_ifile");
          endwin ();
	  exit (0);
	}
    }
  else
    {
      rewind (item_file);
      while (fread (&item, sizeof (ITEM), 1, item_file))
	++item_count;
    }
  fclose (item_file);

/*************************************************************************/
  if ((billno_file = fopen ("./pos_files/dbase/billno_ifile", "r")) == NULL)
    {
      if ((billno_file = fopen ("./pos_files/dbase/billno_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/billno_ifile ");
          endwin ();
	  exit (0);
	}
    }
/*** init billno for 4-sections *****/
  if (fread (&billno, sizeof (BILLNO), 1, billno_file) != 1)
    {
      strcpy (billno.sectno, "1");
      strcpy (billno.billno, "1");
      billno.valid = 'Y';
      fwrite (&billno, sizeof (BILLNO), 1, billno_file);
    }
  if (fread (&billno, sizeof (BILLNO), 1, billno_file) != 1)
    {
      strcpy (billno.sectno, "2");
      strcpy (billno.billno, "1");
      billno.valid = 'Y';
      fwrite (&billno, sizeof (BILLNO), 1, billno_file);
    }
  if (fread (&billno, sizeof (BILLNO), 1, billno_file) != 1)
    {
      strcpy (billno.sectno, "3");
      strcpy (billno.billno, "1");
      billno.valid = 'Y';
      fwrite (&billno, sizeof (BILLNO), 1, billno_file);
    }
  if (fread (&billno, sizeof (BILLNO), 1, billno_file) != 1)
    {
      strcpy (billno.sectno, "4");
      strcpy (billno.billno, "1");
      billno.valid = 'Y';
      fwrite (&billno, sizeof (BILLNO), 1, billno_file);
    }
  fclose (billno_file);

/*************************************************************************/
  if ((table_file = fopen ("./pos_files/dbase/table_ifile", "r")) == NULL)
    {
      if ((table_file = fopen ("./pos_files/dbase/table_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/table_ifile  ");
	  endwin ();
	  exit (0);
	}
    }
  fclose (table_file);

  if ((kot_file = fopen ("./pos_files/dbase/kot_ifile", "r")) == NULL)
    {
      if ((kot_file = fopen ("./pos_files/dbase/kot_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/kot_ifile  ");
	  endwin ();
	  exit (0);
	}
    }
  fclose (kot_file);

  if ((bills_file = fopen ("./pos_files/dbase/bills_ifile", "r")) == NULL)
    {
      if ((bills_file = fopen ("./pos_files/dbase/bills_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/bills_ifile");
          endwin ();
	  exit (0);
	}
    }
  fclose (bills_file);

  if ((billitem_file = fopen ("./pos_files/dbase/billitem_ifile", "r")) == NULL)
    {
      if ((billitem_file = fopen ("./pos_files/dbase/billitem_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/billitem_ifile");
          endwin ();
	  exit (0);
	}
    }
  fclose (billitem_file);

  if ((chq_file = fopen ("./pos_files/dbase/chq_ifile", "r")) == NULL)
    {
      if ((chq_file = fopen ("./pos_files/dbase/chq_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/chq_ifile");
	  endwin ();
	  exit (0);
	}
    }
  fclose (chq_file);

  if ((card_file = fopen ("./pos_files/dbase/card_ifile", "r")) == NULL)
    {
      if ((card_file = fopen ("./pos_files/dbase/card_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/card_ifile");
	  endwin ();
	  exit (0);
	}
    }
  fclose (card_file);

  if ((credit_file = fopen ("./pos_files/dbase/credit_ifile", "r")) == NULL)
    {
      if ((credit_file = fopen ("./pos_files/dbase/credit_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/credit_ifile");
	  endwin ();
	  exit (0);
	}
    }
  fclose (credit_file);

/*************************************************************************/

  if ((plines_file = fopen ("./pos_files/dbase/plines_ifile", "r")) == NULL)
    {
      if ((plines_file = fopen ("./pos_files/dbase/plines_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/plines_ifile");
          endwin ();
	  exit (0);
	}
    }
  if (fread (&plines, sizeof (REFUNDNO), 1, plines_file) != 1)
    {
      strcpy (plines.plines, "1");
      fwrite (&plines, sizeof (REFUNDNO), 1, plines_file);
    }
  fclose (plines_file);

/*************************************************************************/
  if ((sman_file = fopen ("./pos_files/dbase/sman_ifile", "r")) == NULL)
    {
      if ((sman_file = fopen ("./pos_files/dbase/sman_ifile", "w")) == NULL)
	{
	  set_error (" Failed: ./pos_files/dbase/sman_ifile");
          endwin ();
	  exit (0);
	}
    }
  else
    {
      rewind (sman_file);
      while (fread (&sman, sizeof (WAITER), 1, sman_file))
	++sman_count;
    }
  fclose (sman_file);

/*************************************************************************/
  if ((kotno_file = fopen ("./pos_files/dbase/kotno_ifile", "r")) == NULL)
    {
      if ((kotno_file = fopen ("./pos_files/dbase/kotno_ifile", "w")) == NULL)
	{
	  set_error (" NO KOTNO_FILE ");
	  exit (0);
	}
    }
  if (fread (&kotno, sizeof (KOTNO), 1, kotno_file) != 1)
    {
      strcpy (kotno.kotno, "1");
      fwrite (&kotno, sizeof (KOTNO), 1, kotno_file);
    }
  fclose (kotno_file);

/*************************************************************************/

  if ((paswd_file = fopen ("./pos_files/dbase/paswd_ifile", "r")) == NULL)
    {
      if ((paswd_file = fopen ("./pos_files/dbase/paswd_ifile", "w")) == NULL)
	{
	  set_error (" NO PASWD_FILE ");
	  exit (0);
	}
    }
  if (fread (&ppasswd, sizeof (PPASSWD), 1, paswd_file) != 1)
    {
      strcpy (ppasswd.newpasswd, "owner");
      fwrite (&ppasswd, sizeof (PPASSWD), 1, paswd_file);
    }
  fclose (paswd_file);

/*****************************************************************/

  if ((option_file = fopen ("./pos_files/dbase/option_ifile", "r")) == NULL)
    {
      if ((option_file = fopen ("./pos_files/dbase/option_ifile", "w")) == NULL)
	{
	  set_error (" NO OPTION_FILE ");
	  exit (0);
	}
    }
  if (fread (&oprtion, sizeof (OPRTION), 1, option_file) != 1)
    {
      strcpy (oprtion.fswprint, "N");
      strcpy (oprtion.fsmall, "N");
      strcpy (oprtion.fnormal, "N");
      strcpy (oprtion.fmisc_amt, "Y");
      strcpy (oprtion.frepprint, "Y");
      strcpy (oprtion.frepdate, "Y");
      strcpy (oprtion.fauto, "Y");
      strcpy (oprtion.fsoft, "Y");
      fwrite (&oprtion, sizeof (OPRTION), 1, option_file);
    }
  fclose (option_file);

/*****************************************************************/

  if ((misc_file = fopen ("./pos_files/dbase/misc_ifile", "r")) == NULL)
    {
      if ((misc_file = fopen ("./pos_files/dbase/misc_ifile", "w")) == NULL)
	{
	  set_error (" NO MISC_FILE ");
	  exit (0);
	}
    }
  if (fread (&misc, sizeof (MISC), 1, misc_file) != 1)
    {
      strcpy (misc.mvalid1, "N");
      strcpy (misc.math1, "+");
      strcpy (misc.mvalid2, "N");
      strcpy (misc.math2, "+");
      strcpy (misc.mvalid3, "N");
      strcpy (misc.math3, "+");
      strcpy (misc.mvalid4, "N");
      strcpy (misc.math4, "+");
      fwrite (&misc, sizeof (MISC), 1, misc_file);
    }
  fclose (misc_file);

/*****************************************************************/

  if ((billfmt_file = fopen ("./pos_files/dbase/billfmt_ifile", "r")) == NULL)
    {
      if ((billfmt_file = fopen ("./pos_files/dbase/billfmt_ifile", "w")) == NULL)
	{
	  set_error (" NO BILLFMT_FILE ");
	  exit (0);
	}
    }
  if (fread (&billfmt, sizeof (BILLFMT), 1, billfmt_file) != 1)
    {
      strcpy (billfmt.fitemcode, "Y");
      strcpy (billfmt.fdate, "Y");
      strcpy (billfmt.ftime, "Y");
      strcpy (billfmt.fahed, "Y");
      strcpy (billfmt.fwidth, "1");
      fwrite (&oprtion, sizeof (BILLFMT), 1, billfmt_file);
    }
  fclose (billfmt_file);

/*****************************************************************/


  if ((kit_file = fopen ("./pos_files/dbase/kit_ifile", "r")) == NULL)
    {
      if ((kit_file = fopen ("./pos_files/dbase/kit_ifile", "w")) == NULL)
	{
	  set_error (" NO KITCHEN_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (kit_file);
      while (fread (&kitchen, sizeof (KITCHEN), 1, kit_file))
	++kit_count;
    }
  fclose (kit_file);

/*********************************************************************/

  if ((tax_file = fopen ("./pos_files/dbase/tax_ifile", "r")) == NULL)
    {
      if ((tax_file = fopen ("./pos_files/dbase/tax_ifile", "w")) == NULL)
	{
	  set_error (" NO TAX_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (tax_file);
      while (fread (&tax, sizeof (TAX), 1, tax_file))
	++tax_count;
    }
  fclose (tax_file);

/************************************************************************/

  if ((dept_file = fopen ("./pos_files/dbase/dept_ifile", "r")) == NULL)
    {
      if ((dept_file = fopen ("./pos_files/dbase/dept_ifile", "w")) == NULL)
	{
	  set_error (" NO DEPT_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (dept_file);
      while (fread (&dept, sizeof (DEPT), 1, dept_file))
	++dept_count;
    }
  fclose (dept_file);

/************************************************************************/

  if ((head_file = fopen ("./pos_files/dbase/head_ifile", "r")) == NULL)
    {
      if ((head_file = fopen ("./pos_files/dbase/head_ifile", "w")) == NULL)
	{
	  set_error (" NO HEAD_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (head_file);
      while (fread (&head, sizeof (HEAD), 1, head_file))
	++head_count;
    }
  fclose (head_file);

/************************************************************************/

  if ((foot_file = fopen ("./pos_files/dbase/foot_ifile", "r")) == NULL)
    {
      if ((foot_file = fopen ("./pos_files/dbase/foot_ifile", "w")) == NULL)
	{
	  set_error (" NO FOOT_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (foot_file);
      while (fread (&foot, sizeof (FOOT), 1, foot_file))
	++foot_count;
    }
  fclose (foot_file);

/************************************************************************/

  if ((waiter_file = fopen ("./pos_files/dbase/waiter_ifile", "r")) == NULL)
    {
      if ((waiter_file = fopen ("./pos_files/dbase/waiter_ifile", "w")) == NULL)
	{
	  set_error (" NO WAITER_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (waiter_file);
      while (fread (&waiter, sizeof (WAITER), 1, waiter_file))
	++waiter_count;
    }
  fclose (waiter_file);

/************************************************************************/

  if ((customer_file = fopen ("./pos_files/dbase/customer_ifile", "r")) == NULL)
    {
      if ((customer_file = fopen ("./pos_files/dbase/customer_ifile", "w")) == NULL)
	{
	  set_error (" NO CUSTOMER_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (customer_file);
      while (fread (&customer, sizeof (CUSTOMER), 1, customer_file))
	++customer_count;
    }
  fclose (customer_file);

/************************************************************************/

  if ((cashman_file = fopen ("./pos_files/dbase/cashman_ifile", "r")) == NULL)
    {
      if ((cashman_file = fopen ("./pos_files/dbase/cashman_ifile", "w")) == NULL)
	{
	  set_error (" NO CASHMAN_FILE ");
	  exit (0);
	}
    }
  else
    {
      rewind (cashman_file);
      while (fread (&cashman, sizeof (CASHMAN), 1, cashman_file))
	++cashman_count;
    }
  fclose (cashman_file);


}

/******************************************************************************/

int
check_billno_fields ()
{
  int j;
  long i;

  i = atol (billno.billno);
  if (i <= 0)
    {
      set_error (" BILL No. MUST [1-99999] ");
      return 0;
    }
  return 0;
}

int
billno_do_ok (void *menu_key)
{
  BILLNO tbillno;
  char item_found = 0;
  int i;

  if (!strlen (billno.billno))
    {
      set_error (" BILLNO NO NOT ENTERED ");
      return RET_STAY;
    }
  if (!strlen (billno.sectno))
    {
      set_error (" BILLNO NAME NOT ENTERED ");
      return RET_STAY;
    }
  if (((i = atoi (billno.sectno)) >= 5) || i == 0)
    {
      set_error ("  SECT No. IS [ 1-4 ] ");
      return RET_STAY;
    }
  billno_file = fopen ("./pos_files/dbase/billno_ifile", "r+");
  while (fread (&tbillno, sizeof (BILLNO), 1, billno_file))
    {
      if (!strcmp (tbillno.sectno, billno.sectno))
	{
	  if (tbillno.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (billno.valid == 'N')
	{
	  billno.valid = 'Y';
	  ++billno_count;
	}
      fseek (billno_file, -sizeof (BILLNO), SEEK_CUR);
      store_entity (billno_file, &billno, sizeof (BILLNO));
      return RET_OK;
    }
  if (billno_count <= MAX_BILLNOS)
    {
      rewind (billno_file);
      while (fread (&tbillno, sizeof (BILLNO), 1, billno_file))
	{
	  if (tbillno.valid == 'N')
	    {
	      billno.valid = 'Y';
	      fseek (billno_file, -sizeof (BILLNO), SEEK_CUR);
	      store_entity (billno_file, &billno, sizeof (BILLNO));
	      ++billno_count;
	      return RET_OK;
	    }
	}
      billno.valid = 'Y';
      fseek (billno_file, 0, SEEK_END);
      store_entity (billno_file, &billno, sizeof (BILLNO));
      ++billno_count;
      return RET_OK;
    }
  else
    {
      set_error (" SECTION NO LIMIT EXCEEDED ");
      return RET_STAY;
    }
  fclose (billno_file);
}

int
billno_unselect (void *menu)
{
  BILLNO tbillno;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  billno_file = fopen ("./pos_files/dbase/billno_ifile", "r");
  while (fread (&tbillno, sizeof (BILLNO), 1, billno_file))
    {
      if (!strcmp (tbillno.sectno, billno.sectno))
	{
	  if (tbillno.valid == 'Y')
	    {
	      billno = tbillno;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (billno_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

/******************************************************************************/

int
check_plines_fields ()
{
  return 0;
}

int
plines_do_ok (void *menu_key)
{

  if ((plines_file = fopen ("./pos_files/dbase/plines_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (check_plines_fields ())
    {
      return RET_STAY;
    }
  if (!store_entity (plines_file, &plines, sizeof (REFUNDNO)))
    {
      set_error (" FILE WRITE ERROR ");
      return RET_STAY;
    }
  return RET_OK;
}

int
plines_init (PMENU * menu)
{
  REFUNDNO tplines;

  if ((plines_file = fopen ("./pos_files/dbase/plines_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (!read_entity (plines_file, &plines, sizeof (REFUNDNO)))
    {
      set_error ("FILE READ ERROR");
      return RET_STAY;
    }
}

/******************************************************************************/

int
check_refno_fields ()
{
  long i;
  i = atol (refno.refno);
  if (i <= 0)
    {
      set_error (" REFUND No. MUST [1-99999] ");
      return 0;
    }
  return 0;
}

int
refno_do_ok (void *menu_key)
{

  if ((refno_file = fopen ("./pos_files/dbase/refno_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (check_refno_fields ())
    {
      return RET_STAY;
    }
  if (!store_entity (refno_file, &refno, sizeof (REFUNDNO)))
    {
      set_error (" FILE WRITE ERROR ");
      return RET_STAY;
    }
  return RET_OK;
}

int
refno_init (PMENU * menu)
{
  REFUNDNO trefno;

  if ((refno_file = fopen ("./pos_files/dbase/refno_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (!read_entity (refno_file, &refno, sizeof (REFUNDNO)))
    {
      set_error ("FILE READ ERROR");
      return RET_STAY;
    }
}

/***********************************************************************/

int
check_kotno_fields ()
{
  long i;
  i = atol (kotno.kotno);
  if (i <= 0)
    {
      set_error (" KOT No. MUST [1-99999] ");
      return 0;
    }
  return 0;
}

int
kotno_do_ok (void *menu_key)
{

  if ((kotno_file = fopen ("./pos_files/dbase/kotno_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (check_kotno_fields ())
    {
      return RET_STAY;
    }
  if (!store_entity (kotno_file, &kotno, sizeof (KOTNO)))
    {
      set_error (" FILE WRITE ERROR ");
      return RET_STAY;
    }
  return RET_OK;
}

int
kotno_init (PMENU * menu)
{
  KOTNO tkotno;

  if ((kotno_file = fopen ("./pos_files/dbase/kotno_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (!read_entity (kotno_file, &kotno, sizeof (KOTNO)))
    {
      set_error ("FILE READ ERROR");
      return RET_STAY;
    }
}

/***********************************************************************/
int
swprint_jump (void *menu)
{
  BILLNO tbillno;
  PMENU *pmenu;

  if (oprtion.fswprint[0] == 'Y')
    {
      draw_menu (&swprint_menu);
      refresh ();
    }
  else
    {
      refresh_menu ((PMENU *) menu, 7, 0, 0);
    }
}

int
check_opt_fields ()
{
  if (!strlen (oprtion.fmisc_amt) || !strlen (oprtion.frepprint) ||
      !strlen (oprtion.frepdate) || !strlen (oprtion.fauto) ||
      !strlen (oprtion.fsoft))
    {
      set_error (" ENTER [Y/N] IN ALL FIELDS ");
      return 1;
    }
  return 0;
}

int
option_do_ok (void *menu_key)
{

  if ((option_file = fopen ("./pos_files/dbase/option_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (check_opt_fields ())
    {
      return RET_STAY;
    }
  if (!store_entity (option_file, &oprtion, sizeof (OPRTION)))
    {
      set_error (" FILE WRITE ERROR ");
      return RET_STAY;
    }
  return RET_OK;
}

int
option_init (PMENU * menu)
{
  OPRTION toption;

  if ((option_file = fopen ("./pos_files/dbase/option_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (!read_entity (option_file, &oprtion, sizeof (OPRTION)))
    {
      set_error ("FILE READ ERROR");
      return RET_STAY;
    }
}

/*****************************************************************************/

int
item_init (PMENU * menu)
{
  ITEM titem;
  long fspace = 1;
#		if	DONT_USE
/* analysys is reqd */
  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
  while (fread (&titem, sizeof (ITEM), 1, item_file))
    {
      if (titem.valid == 'N')
	{
	  break;
	}
      fspace++;
    }
  fclose (item_file);
  sprintf (item.item_code, "%d", fspace);
#			endif
  strcpy (item.fneg_stock, "Y");
  strcpy (item.fqty_dec, "Y");
  strcpy (item.sell_price, "0");
  strcpy (item.cost_price, "0");
  strcpy (item.mrp, "0");
}

int
item_do_ok (void *menu_key)
{
  ITEM titem;
  char item_found = 0;

  if (!strlen (item.item_code))
    {
      set_error (" ITEM CODE NOT ENTERED ");
      return RET_STAY;
    }
  if (item.item_code[0] == '0')
    {
      set_error (" REENTER ITEM CODE ");
      return RET_STAY;
    }
  item_file = fopen ("./pos_files/dbase/item_ifile", "r+");
  while (fread (&titem, sizeof (ITEM), 1, item_file))
    {
      if (!strcmp (titem.item_code, item.item_code))
	{
	  if (titem.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (item_fields_check ())
	{
	  return RET_STAY;
	}
      if (item.valid == 'N')
	{
	  item.valid = 'Y';
	  ++item_count;
	}
      fseek (item_file, -sizeof (ITEM), SEEK_CUR);
      store_entity (item_file, &item, sizeof (ITEM));
      return RET_OK;
    }
  if (item_count <= MAX_ITEMS)
    {
      rewind (item_file);
      while (fread (&titem, sizeof (ITEM), 1, item_file))
	{
	  if (titem.valid == 'N')
	    {
	      if (item_fields_check ())
		{
		  return RET_STAY;
		}
	      item.valid = 'Y';
	      fseek (item_file, -sizeof (ITEM), SEEK_CUR);
	      store_entity (item_file, &item, sizeof (ITEM));
	      ++item_count;
	      return RET_OK;
	    }
	}
      if (item_fields_check ())
	{
	  return RET_STAY;
	}
      item.valid = 'Y';
      fseek (item_file, 0, SEEK_END);
      store_entity (item_file, &item, sizeof (ITEM));
      ++item_count;
      return RET_OK;
    }
  else
    {
      set_error (" ITEM LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
item_code_unselect (void *menu)
{
  ITEM titem;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  item_file = fopen ("./pos_files/dbase/item_ifile", "r");
  while (fread (&titem, sizeof (ITEM), 1, item_file))
    {
      if (!strcmp (titem.item_code, item.item_code))
	{
	  if (titem.valid == 'Y')
	    {
	      item = titem;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (item_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
item_next_do_ok (void *key_menu)
{
  int i;

  if (item_do_ok (key_menu) == RET_OK)
    {
      i = atoi (item.item_code);
      i++;
      sprintf (item.item_code, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      item_code_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
item_delete_do_ok (void *key_menu)
{
  ITEM titem;
  char item_found = 0;
  if (!strlen (item.item_code))
    {
      set_error (" ITEM CODE NOT FOUND ");
      return RET_STAY;
    }
  item_file = fopen ("./pos_files/dbase/item_ifile", "r+");
  while (fread (&titem, sizeof (ITEM), 1, item_file))
    {
      if (!strcmp (titem.item_code, item.item_code))
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
      item.valid = 'N';
      fseek (item_file, -sizeof (ITEM), SEEK_CUR);
      store_entity (item_file, &item, sizeof (ITEM));
      --item_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" ITEM  NOT EXIST ");
      return RET_STAY;
    }
}

int
item_fields_check ()
{
  int i;
  char j;
  long k;

  k = atoi (item.item_code);
  if (k == 0 || k >= 16)
    {
      set_error (" ITEM CODE MUST [ 1-15 ] ");
      return 1;
    }
  if (!strlen (item.item_name))
    {
      set_error (" ITEM NAME NOT ENTERED ");
      return 1;
    }
  if (strchr (item.sell_price, '.') != NULL)
    {
      if (strchr (item.sell_price, '.') != strrchr (item.sell_price, '.'))
	{
	  set_error (" SELL PRICE WRONG ENTERED ");
	  return 1;
	}
    }
  if (strchr (item.cost_price, '.') != NULL)
    {
      if (strchr (item.cost_price, '.') != strrchr (item.cost_price, '.'))
	{
	  set_error (" COST PRICE WRONG ENTERED ");
	  return 1;
	}
    }
  if (strchr (item.mrp, '.') != NULL)
    {
      if (strchr (item.mrp, '.') != strrchr (item.mrp, '.'))
	{
	  set_error (" MRP WRONG ENTERED ");
	  return 1;
	}
    }
  return 0;
}

/**************************************************************************/

int
kit_next_do_ok (void *key_menu)
{
  int i;

  if (kit_do_ok (key_menu) == RET_OK)
    {
      i = atoi (kitchen.kitno);
      i++;
      sprintf (kitchen.kitno, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      kit_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
kit_delete_do_ok (void *key_menu)
{
  KITCHEN tkit;
  char item_found = 0;
  if (!strlen (kitchen.kitno))
    {
      set_error (" ITEM CODE NOT FOUND ");
      return RET_STAY;
    }
  kit_file = fopen ("./pos_files/dbase/kit_ifile", "r+");
  while (fread (&tkit, sizeof (KITCHEN), 1, kit_file))
    {
      if (!strcmp (tkit.kitno, kitchen.kitno))
	{
	  if (kitchen.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      kitchen.valid = 'N';
      fseek (kit_file, -sizeof (KITCHEN), SEEK_CUR);
      store_entity (kit_file, &kitchen, sizeof (KITCHEN));
      --kit_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" KITCHEN  NOT EXIST ");
      return RET_STAY;
    }
}

int
kit_no_unselect (void *menu)
{
  KITCHEN tkit;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  kit_file = fopen ("./pos_files/dbase/kit_ifile", "r");
  while (fread (&tkit, sizeof (KITCHEN), 1, kit_file))
    {
      if (!strcmp (tkit.kitno, kitchen.kitno))
	{
	  if (tkit.valid == 'Y')
	    {
	      kitchen = tkit;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (kit_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
kit_do_ok (void *menu_key)
{
  KITCHEN tkit;
  char item_found = 0;

  if (!strlen (kitchen.kitno))
    {
      set_error (" KITCHEN No. NOT ENTERED ");
      return RET_STAY;
    }
  if (!strlen (kitchen.kitname))
    {
      set_error (" KITCHEN NAME NOT ENTERED ");
      return RET_STAY;
    }
  kit_file = fopen ("./pos_files/dbase/kit_ifile", "r+");
  while (fread (&tkit, sizeof (KITCHEN), 1, kit_file))
    {
      if (!strcmp (tkit.kitno, kitchen.kitno))
	{
	  if (tkit.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (kitchen.valid == 'N')
	{
	  kitchen.valid = 'Y';
	  ++kit_count;
	}
      fseek (kit_file, -sizeof (KITCHEN), SEEK_CUR);
      store_entity (kit_file, &kitchen, sizeof (KITCHEN));
      return RET_OK;
    }
  if (kit_count <= MAX_KITCHENS)
    {
      rewind (kit_file);
      while (fread (&tkit, sizeof (KITCHEN), 1, kit_file))
	{
	  if (tkit.valid == 'N')
	    {
	      kitchen.valid = 'Y';
	      fseek (kit_file, -sizeof (KITCHEN), SEEK_CUR);
	      store_entity (kit_file, &kitchen, sizeof (KITCHEN));
	      ++kit_count;
	      return RET_OK;
	    }
	}
      kitchen.valid = 'Y';
      fseek (kit_file, 0, SEEK_END);
      store_entity (kit_file, &kitchen, sizeof (KITCHEN));
      ++kit_count;
      return RET_OK;
    }
  else
    {
      set_error (" KITCHEN LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

/***************************************************************************/


int
store_entity (FILE * fp, void *entity, int size)
{

  if (fwrite (entity, size, 1, fp) != 1)
    return 0;
  fseek (fp, 0, SEEK_END);
  fflush (fp);
  fclose (fp);
  return 1;
}

int
read_entity (FILE * fp, void *entity, int size)
{

  if (fread (entity, size, 1, fp) != 1)
    return 0;
  fseek (fp, 0, SEEK_END);
  fflush (fp);
  fclose (fp);
  return 1;
}

/******************************************************************************/

int
tax_do_ok (void *menu_key)
{
  TAX ttax;
  char item_found = 0;

  if (!strlen (tax.tax_no))
    {
      set_error (" TAX No. NOT ENTERED ");
      return RET_STAY;
    }
  tax_file = fopen ("./pos_files/dbase/tax_ifile", "r+");
  while (fread (&ttax, sizeof (TAX), 1, tax_file))
    {
      if (!strcmp (ttax.tax_no, tax.tax_no))
	{
	  if (ttax.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (tax_fields_check ())
	{
	  return RET_STAY;
	}
      if (tax.valid == 'N')
	{
	  tax.valid = 'Y';
	  ++tax_count;
	}
      fseek (tax_file, -sizeof (TAX), SEEK_CUR);
      store_entity (tax_file, &tax, sizeof (TAX));
      return RET_OK;
    }
  if (tax_count <= MAX_TAXES)
    {
      rewind (tax_file);
      while (fread (&ttax, sizeof (TAX), 1, tax_file))
	{
	  if (ttax.valid == 'N')
	    {
	      if (tax_fields_check ())
		{
		  return RET_STAY;
		}
	      tax.valid = 'Y';
	      fseek (tax_file, -sizeof (TAX), SEEK_CUR);
	      store_entity (tax_file, &tax, sizeof (TAX));
	      ++tax_count;
	      return RET_OK;
	    }
	}
      if (tax_fields_check ())
	{
	  return RET_STAY;
	}
      tax.valid = 'Y';
      fseek (tax_file, 0, SEEK_END);
      store_entity (tax_file, &tax, sizeof (TAX));
      ++tax_count;
      return RET_OK;
    }
  else
    {
      set_error (" TAX LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
tax_fields_check ()
{
  int k;

  k = atoi (tax.tax_no);
  if (k >= 5 || k == 0 || k < 0)
    {
      set_error (" TAX NO MUST [1-4] ");
      return 1;
    }
  if (strlen (tax.tamt))
    {
      if (!strlen (tax.tname))
	{
	  set_error (" Tax Name Not Entered ");
	  return 1;
	}
    }
  if (strlen (tax.toamt))
    {
      if (!strlen (tax.toname))
	{
	  set_error (" Cess Name Not Entered ");
	  return 1;
	}
    }
  if (strchr (tax.tamt, '.') != NULL)
    {
      if (strchr (tax.tamt, '.') != strrchr (tax.tamt, '.'))
	{
	  set_error (" TAX PRICE WRONG ENTERED ");
	  return 1;
	}
    }
  if (strchr (tax.toamt, '.') != NULL)
    {
      if (strchr (tax.toamt, '.') != strrchr (tax.toamt, '.'))
	{
	  set_error (" TAX PRICE WRONG ENTERED ");
	  return 1;
	}
    }
  if (strlen (tax.toamt) && !strlen (tax.tamt))
    {
      set_error (" TAX NOT ENTERED ");
      return 1;
    }
  return 0;
}

int
tax_no_unselect (void *menu)
{
  TAX ttax;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  tax_file = fopen ("./pos_files/dbase/tax_ifile", "r");
  while (fread (&ttax, sizeof (TAX), 1, tax_file))
    {
      if (!strcmp (ttax.tax_no, tax.tax_no))
	{
	  if (ttax.valid == 'Y')
	    {
	      tax = ttax;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (tax_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
tax_delete_do_ok (void *key_menu)
{
  TAX ttax;
  char item_found = 0;
  if (!strlen (tax.tax_no))
    {
      set_error (" TAX NO  NOT FOUND ");
      return RET_STAY;
    }
  tax_file = fopen ("./pos_files/dbase/tax_ifile", "r+");
  while (fread (&ttax, sizeof (TAX), 1, tax_file))
    {
      if (!strcmp (ttax.tax_no, tax.tax_no))
	{
	  if (tax.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      tax.valid = 'N';
      fseek (tax_file, -sizeof (TAX), SEEK_CUR);
      store_entity (tax_file, &tax, sizeof (TAX));
      --tax_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" TAX  NOT EXIST ");
      return RET_STAY;
    }
}

int
tax_next_do_ok (void *key_menu)
{
  int i;

  if (tax_do_ok (key_menu) == RET_OK)
    {
      i = atoi (tax.tax_no);
      i++;
      sprintf (tax.tax_no, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      tax_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

/************************************************************************/

int
dept_no_unselect (void *menu)
{
  DEPT tdept;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  dept_file = fopen ("./pos_files/dbase/dept_ifile", "r");
  while (fread (&tdept, sizeof (DEPT), 1, dept_file))
    {
      if (!strcmp (tdept.dept_code, dept.dept_code))
	{
	  if (tdept.valid == 'Y')
	    {
	      dept = tdept;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (dept_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
dept_delete_do_ok (void *key_menu)
{
  DEPT tdept;
  char item_found = 0;

  if (!strlen (dept.dept_code))
    {
      set_error (" STORE No. NOT FOUND ");
      return RET_STAY;
    }
  dept_file = fopen ("./pos_files/dbase/dept_ifile", "r+");
  while (fread (&tdept, sizeof (DEPT), 1, dept_file))
    {
      if (!strcmp (tdept.dept_code, dept.dept_code))
	{
	  if (dept.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      dept.valid = 'N';
      fseek (dept_file, -sizeof (DEPT), SEEK_CUR);
      store_entity (dept_file, &dept, sizeof (DEPT));
      --dept_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" DEPT  NOT EXIST ");
      return RET_STAY;
    }
}

int
dept_next_do_ok (void *key_menu)
{
  int i;

  if (dept_do_ok (key_menu) == RET_OK)
    {
      i = atoi (dept.dept_code);
      i++;
      sprintf (dept.dept_code, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      dept_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
dept_do_ok (void *menu_key)
{
  DEPT tdept;
  char item_found = 0;

  if (!strlen (dept.dept_code))
    {
      set_error (" DEPT No. NOT ENTERED ");
      return RET_STAY;
    }
  dept_file = fopen ("./pos_files/dbase/dept_ifile", "r+");
  while (fread (&tdept, sizeof (DEPT), 1, dept_file))
    {
      if (!strcmp (tdept.dept_code, dept.dept_code))
	{
	  if (tdept.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (dept_fields_check ())
	{
	  return RET_STAY;
	}
      if (dept.valid == 'N')
	{
	  dept.valid = 'Y';
	  ++dept_count;
	}
      fseek (dept_file, -sizeof (DEPT), SEEK_CUR);
      store_entity (dept_file, &dept, sizeof (DEPT));
      return RET_OK;
    }
  if (dept_count <= MAX_STORES)
    {
      rewind (dept_file);
      while (fread (&tdept, sizeof (DEPT), 1, dept_file))
	{
	  if (tdept.valid == 'N')
	    {
	      if (dept_fields_check ())
		{
		  return RET_STAY;
		}
	      dept.valid = 'Y';
	      fseek (dept_file, -sizeof (DEPT), SEEK_CUR);
	      store_entity (dept_file, &dept, sizeof (DEPT));
	      ++dept_count;
	      return RET_OK;
	    }
	}
      if (dept_fields_check ())
	{
	  return RET_STAY;
	}
      dept.valid = 'Y';
      fseek (dept_file, 0, SEEK_END);
      store_entity (dept_file, &dept, sizeof (DEPT));
      ++dept_count;
      return RET_OK;
    }
  else
    {
      set_error (" DEPT LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
dept_fields_check ()
{
  return 0;
}

/****************************************************************************/

int
head_no_unselect (void *menu)
{
  HEAD thead;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  head_file = fopen ("./pos_files/dbase/head_ifile", "r");
  while (fread (&thead, sizeof (HEAD), 1, head_file))
    {
      if (!strcmp (thead.sect, head.sect))
	{
	  if (thead.valid == 'Y')
	    {
	      head = thead;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (head_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
head_delete_do_ok (void *key_menu)
{
  HEAD thead;
  char item_found = 0;

  if (!strlen (head.sect))
    {
      set_error (" SECTION  NOT  ENTERED ");
      return RET_STAY;
    }
  head_file = fopen ("./pos_files/dbase/head_ifile", "r+");
  while (fread (&thead, sizeof (HEAD), 1, head_file))
    {
      if (!strcmp (thead.sect, head.sect))
	{
	  if (head.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      head.valid = 'N';
      fseek (head_file, -sizeof (HEAD), SEEK_CUR);
      store_entity (head_file, &head, sizeof (HEAD));
      --head_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" HEAD  NOT EXIST ");
      return RET_STAY;
    }
}

int
head_next_do_ok (void *key_menu)
{
  int i;

  if (head_do_ok (key_menu) == RET_OK)
    {
      i = atoi (head.sect);
      i++;
      sprintf (head.sect, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      head_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
head_do_ok (void *menu_key)
{
  HEAD thead;
  char item_found = 0;

  if (!strlen (head.sect))
    {
      set_error (" HEAD No. NOT ENTERED ");
      return RET_STAY;
    }
  head_file = fopen ("./pos_files/dbase/head_ifile", "r+");
  while (fread (&thead, sizeof (HEAD), 1, head_file))
    {
      if (!strcmp (thead.sect, head.sect))
	{
	  if (thead.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (head_fields_check ())
	{
	  return RET_STAY;
	}
      if (head.valid == 'N')
	{
	  head.valid = 'Y';
	  ++head_count;
	}
      fseek (head_file, -sizeof (HEAD), SEEK_CUR);
      store_entity (head_file, &head, sizeof (HEAD));
      return RET_OK;
    }
  if (head_count <= MAX_HEADS)
    {
      rewind (head_file);
      while (fread (&thead, sizeof (HEAD), 1, head_file))
	{
	  if (thead.valid == 'N')
	    {
	      if (head_fields_check ())
		{
		  return RET_STAY;
		}
	      head.valid = 'Y';
	      fseek (head_file, -sizeof (HEAD), SEEK_CUR);
	      store_entity (head_file, &head, sizeof (HEAD));
	      ++head_count;
	      return RET_OK;
	    }
	}
      if (head_fields_check ())
	{
	  return RET_STAY;
	}
      head.valid = 'Y';
      fseek (head_file, 0, SEEK_END);
      store_entity (head_file, &head, sizeof (HEAD));
      ++head_count;
      return RET_OK;
    }
  else
    {
      set_error (" HEAD LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
head_fields_check ()
{
  return 0;
}

/************************************************************************/

int
foot_no_unselect (void *menu)
{
  FOOT tfoot;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  foot_file = fopen ("./pos_files/dbase/foot_ifile", "r");
  while (fread (&tfoot, sizeof (FOOT), 1, foot_file))
    {
      if (!strcmp (tfoot.sect, foot.sect))
	{
	  if (tfoot.valid == 'Y')
	    {
	      foot = tfoot;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (foot_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
foot_delete_do_ok (void *key_menu)
{
  FOOT tfoot;
  char item_found = 0;

  if (!strlen (foot.sect))
    {
      set_error (" SECTION  NOT  ENTERED ");
      return RET_STAY;
    }
  foot_file = fopen ("./pos_files/dbase/foot_ifile", "r+");
  while (fread (&tfoot, sizeof (FOOT), 1, foot_file))
    {
      if (!strcmp (tfoot.sect, foot.sect))
	{
	  if (foot.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      foot.valid = 'N';
      fseek (foot_file, -sizeof (FOOT), SEEK_CUR);
      store_entity (foot_file, &foot, sizeof (FOOT));
      --foot_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" FOOT  NOT EXIST ");
      return RET_STAY;
    }
}

int
foot_next_do_ok (void *key_menu)
{
  int i;

  if (foot_do_ok (key_menu) == RET_OK)
    {
      i = atoi (foot.sect);
      i++;
      sprintf (foot.sect, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      foot_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
foot_do_ok (void *menu_key)
{
  FOOT tfoot;
  char item_found = 0;

  if (!strlen (foot.sect))
    {
      set_error (" FOOT No. NOT ENTERED ");
      return RET_STAY;
    }
  foot_file = fopen ("./pos_files/dbase/foot_ifile", "r+");
  while (fread (&tfoot, sizeof (FOOT), 1, foot_file))
    {
      if (!strcmp (tfoot.sect, foot.sect))
	{
	  if (tfoot.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (foot_fields_check ())
	{
	  return RET_STAY;
	}
      if (foot.valid == 'N')
	{
	  foot.valid = 'Y';
	  ++foot_count;
	}
      fseek (foot_file, -sizeof (FOOT), SEEK_CUR);
      store_entity (foot_file, &foot, sizeof (FOOT));
      return RET_OK;
    }
  if (foot_count <= MAX_HEADS)
    {
      rewind (foot_file);
      while (fread (&tfoot, sizeof (FOOT), 1, foot_file))
	{
	  if (tfoot.valid == 'N')
	    {
	      if (foot_fields_check ())
		{
		  return RET_STAY;
		}
	      foot.valid = 'Y';
	      fseek (foot_file, -sizeof (FOOT), SEEK_CUR);
	      store_entity (foot_file, &foot, sizeof (FOOT));
	      ++foot_count;
	      return RET_OK;
	    }
	}
      if (foot_fields_check ())
	{
	  return RET_STAY;
	}
      foot.valid = 'Y';
      fseek (foot_file, 0, SEEK_END);
      store_entity (foot_file, &foot, sizeof (FOOT));
      ++foot_count;
      return RET_OK;
    }
  else
    {
      set_error (" FOOT LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
foot_fields_check ()
{
  return 0;
}

/****************************************************************************/

int
customer_no_unselect (void *menu)
{
  CUSTOMER tcustomer;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  customer_file = fopen ("./pos_files/dbase/customer_ifile", "r");
  while (fread (&tcustomer, sizeof (CUSTOMER), 1, customer_file))
    {
      if (!strcmp (tcustomer.custno, customer.custno))
	{
	  if (tcustomer.valid == 'Y')
	    {
	      customer = tcustomer;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (customer_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
customer_delete_do_ok (void *key_menu)
{
  CUSTOMER tcustomer;
  char item_found = 0;

  if (!strlen (customer.custno))
    {
      set_error (" CUSTOMER No.  NOT FOUND ");
      return RET_STAY;
    }
  customer_file = fopen ("./pos_files/dbase/customer_ifile", "r+");
  while (fread (&tcustomer, sizeof (CUSTOMER), 1, customer_file))
    {
      if (!strcmp (tcustomer.custno, customer.custno))
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
      customer.valid = 'N';
      fseek (customer_file, -sizeof (CUSTOMER), SEEK_CUR);
      store_entity (customer_file, &customer, sizeof (CUSTOMER));
      --customer_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" CUSTOMER  NOT EXIST ");
      return RET_STAY;
    }
}

int
customer_next_do_ok (void *key_menu)
{
  int i;

  if (customer_do_ok (key_menu) == RET_OK)
    {
      i = atoi (customer.custno);
      i++;
      sprintf (customer.custno, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      customer_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
customer_do_ok (void *menu_key)
{
  CUSTOMER tcustomer;
  char item_found = 0;

  if (!strlen (customer.custno))
    {
      set_error (" CUSTOMER No. NOT ENTERED ");
      return RET_STAY;
    }
  customer_file = fopen ("./pos_files/dbase/customer_ifile", "r+");
  while (fread (&tcustomer, sizeof (CUSTOMER), 1, customer_file))
    {
      if (!strcmp (tcustomer.custno, customer.custno))
	{
	  if (tcustomer.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (customer_fields_check ())
	{
	  return RET_STAY;
	}
      if (customer.valid == 'N')
	{
	  customer.valid = 'Y';
	  ++customer_count;
	}
      fseek (customer_file, -sizeof (CUSTOMER), SEEK_CUR);
      store_entity (customer_file, &customer, sizeof (CUSTOMER));
      return RET_OK;
    }
  if (customer_count <= MAX_CUSTOMERS)
    {
      rewind (customer_file);
      while (fread (&tcustomer, sizeof (CUSTOMER), 1, customer_file))
	{
	  if (tcustomer.valid == 'N')
	    {
	      if (customer_fields_check ())
		{
		  return RET_STAY;
		}
	      customer.valid = 'Y';
	      fseek (customer_file, -sizeof (CUSTOMER), SEEK_CUR);
	      store_entity (customer_file, &customer, sizeof (CUSTOMER));
	      ++customer_count;
	      return RET_OK;
	    }
	}
      if (customer_fields_check ())
	{
	  return RET_STAY;
	}
      customer.valid = 'Y';
      fseek (customer_file, 0, SEEK_END);
      store_entity (customer_file, &customer, sizeof (CUSTOMER));
      ++customer_count;
      return RET_OK;
    }
  else
    {
      set_error (" CUSTOMER LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
customer_fields_check ()
{
  return 0;
}

/*****************************************************************************/

int
sman_no_unselect (void *menu)
{
  SMAN tsman;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  sman_file = fopen ("./pos_files/dbase/sman_ifile", "r");
  while (fread (&tsman, sizeof (SMAN), 1, sman_file))
    {
      if (!strcmp (tsman.smanno, sman.smanno))
	{
	  if (tsman.valid == 'Y')
	    {
	      sman = tsman;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (sman_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
sman_delete_do_ok (void *key_menu)
{
  SMAN tsman;
  char item_found = 0;

  if (!strlen (sman.smanno))
    {
      set_error (" Sales man No.  Not Found ");
      return RET_STAY;
    }
  sman_file = fopen ("./pos_files/dbase/sman_ifile", "r+");
  while (fread (&tsman, sizeof (SMAN), 1, sman_file))
    {
      if (!strcmp (tsman.smanno, sman.smanno))
	{
	  if (sman.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      sman.valid = 'N';
      fseek (sman_file, -sizeof (SMAN), SEEK_CUR);
      store_entity (sman_file, &sman, sizeof (SMAN));
      --sman_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" Slaes Man Not Exist ");
      return RET_STAY;
    }
}

int
sman_next_do_ok (void *key_menu)
{
  int i;

  if (sman_do_ok (key_menu) == RET_OK)
    {
      i = atoi (sman.smanno);
      i++;
      sprintf (sman.smanno, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      sman_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
sman_do_ok (void *menu_key)
{
  SMAN tsman;
  char item_found = 0;

  if (!strlen (sman.smanno))
    {
      set_error (" SMAN No. NOT ENTERED ");
      return RET_STAY;
    }
  sman_file = fopen ("./pos_files/dbase/sman_ifile", "r+");
  while (fread (&tsman, sizeof (SMAN), 1, sman_file))
    {
      if (!strcmp (tsman.smanno, sman.smanno))
	{
	  if (tsman.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (sman_fields_check ())
	{
	  return RET_STAY;
	}
      if (sman.valid == 'N')
	{
	  sman.valid = 'Y';
	  ++sman_count;
	}
      fseek (sman_file, -sizeof (SMAN), SEEK_CUR);
      store_entity (sman_file, &sman, sizeof (SMAN));
      return RET_OK;
    }
  if (sman_count <= MAX_SMANS)
    {
      rewind (sman_file);
      while (fread (&tsman, sizeof (SMAN), 1, sman_file))
	{
	  if (tsman.valid == 'N')
	    {
	      if (sman_fields_check ())
		{
		  return RET_STAY;
		}
	      sman.valid = 'Y';
	      fseek (sman_file, -sizeof (SMAN), SEEK_CUR);
	      store_entity (sman_file, &sman, sizeof (SMAN));
	      ++sman_count;
	      return RET_OK;
	    }
	}
      if (sman_fields_check ())
	{
	  return RET_STAY;
	}
      sman.valid = 'Y';
      fseek (sman_file, 0, SEEK_END);
      store_entity (sman_file, &sman, sizeof (SMAN));
      ++sman_count;
      return RET_OK;
    }
  else
    {
      set_error (" SMAN LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
sman_fields_check ()
{
  return 0;
}

/****************************************************************************/

int
waiter_no_unselect (void *menu)
{
  WAITER twaiter;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  waiter_file = fopen ("./pos_files/dbase/waiter_ifile", "r");
  while (fread (&twaiter, sizeof (WAITER), 1, waiter_file))
    {
      if (!strcmp (twaiter.wtrno, waiter.wtrno))
	{
	  if (twaiter.valid == 'Y')
	    {
	      waiter = twaiter;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (waiter_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
waiter_delete_do_ok (void *key_menu)
{
  WAITER twaiter;
  char item_found = 0;

  if (!strlen (waiter.wtrno))
    {
      set_error (" WAITER No.  NOT FOUND ");
      return RET_STAY;
    }
  waiter_file = fopen ("./pos_files/dbase/waiter_ifile", "r+");
  while (fread (&twaiter, sizeof (WAITER), 1, waiter_file))
    {
      if (!strcmp (twaiter.wtrno, waiter.wtrno))
	{
	  if (waiter.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      waiter.valid = 'N';
      fseek (waiter_file, -sizeof (WAITER), SEEK_CUR);
      store_entity (waiter_file, &waiter, sizeof (WAITER));
      --waiter_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" WAITER  NOT EXIST ");
      return RET_STAY;
    }
}

int
waiter_next_do_ok (void *key_menu)
{
  int i;

  if (waiter_do_ok (key_menu) == RET_OK)
    {
      i = atoi (waiter.wtrno);
      i++;
      sprintf (waiter.wtrno, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      waiter_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
waiter_do_ok (void *menu_key)
{
  WAITER twaiter;
  char item_found = 0;

  if (!strlen (waiter.wtrno))
    {
      set_error (" WAITER No. NOT ENTERED ");
      return RET_STAY;
    }
  waiter_file = fopen ("./pos_files/dbase/waiter_ifile", "r+");
  while (fread (&twaiter, sizeof (WAITER), 1, waiter_file))
    {
      if (!strcmp (twaiter.wtrno, waiter.wtrno))
	{
	  if (twaiter.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (waiter_fields_check ())
	{
	  return RET_STAY;
	}
      if (waiter.valid == 'N')
	{
	  waiter.valid = 'Y';
	  ++waiter_count;
	}
      fseek (waiter_file, -sizeof (WAITER), SEEK_CUR);
      store_entity (waiter_file, &waiter, sizeof (WAITER));
      return RET_OK;
    }
  if (waiter_count <= MAX_WAITERS)
    {
      rewind (waiter_file);
      while (fread (&twaiter, sizeof (WAITER), 1, waiter_file))
	{
	  if (twaiter.valid == 'N')
	    {
	      if (waiter_fields_check ())
		{
		  return RET_STAY;
		}
	      waiter.valid = 'Y';
	      fseek (waiter_file, -sizeof (WAITER), SEEK_CUR);
	      store_entity (waiter_file, &waiter, sizeof (WAITER));
	      ++waiter_count;
	      return RET_OK;
	    }
	}
      if (waiter_fields_check ())
	{
	  return RET_STAY;
	}
      waiter.valid = 'Y';
      fseek (waiter_file, 0, SEEK_END);
      store_entity (waiter_file, &waiter, sizeof (WAITER));
      ++waiter_count;
      return RET_OK;
    }
  else
    {
      set_error (" WAITER LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
waiter_fields_check ()
{
  return 0;
}

/****************************************************************************/

int
cashman_no_unselect (void *menu)
{
  CASHMAN tcashman;
  PMENU *pmenu;
  char item_found;

  pmenu = (PMENU *) menu;
  item_found = 0;
  cashman_file = fopen ("./pos_files/dbase/cashman_ifile", "r");
  while (fread (&tcashman, sizeof (CASHMAN), 1, cashman_file))
    {
      if (!strcmp (tcashman.cmanno, cashman.cmanno))
	{
	  if (tcashman.valid == 'Y')
	    {
	      cashman = tcashman;
	      item_found = 1;
	      break;
	    }
	}
    }
  fclose (cashman_file);
  refresh_menu (pmenu, 1, item_found, 1);
}

int
cashman_delete_do_ok (void *key_menu)
{
  CASHMAN tcashman;
  char item_found = 0;

  if (!strlen (cashman.cmanno))
    {
      set_error (" CASH-MAN No. NOT FOUND ");
      return RET_STAY;
    }
  cashman_file = fopen ("./pos_files/dbase/cashman_ifile", "r+");
  while (fread (&tcashman, sizeof (CASHMAN), 1, cashman_file))
    {
      if (!strcmp (tcashman.cmanno, cashman.cmanno))
	{
	  if (cashman.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	}
    }
  if (item_found)
    {
      cashman.valid = 'N';
      fseek (cashman_file, -sizeof (CASHMAN), SEEK_CUR);
      store_entity (cashman_file, &cashman, sizeof (CASHMAN));
      --cashman_count;
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_CANCEL;
    }
  else
    {
      set_error (" CASHMAN  NOT EXIST ");
      return RET_STAY;
    }
}

int
cashman_next_do_ok (void *key_menu)
{
  int i;

  if (cashman_do_ok (key_menu) == RET_OK)
    {
      i = atoi (cashman.cmanno);
      i++;
      sprintf (cashman.cmanno, "%d", i);
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      cashman_no_unselect (key_menu);
      return RET_CANCEL;
    }
  else
    {
      refresh_menu ((PMENU *) key_menu, 1, 0, 1);
      return RET_STAY;
    }
}

int
cashman_do_ok (void *menu_key)
{
  CASHMAN tcashman;
  char item_found = 0;

  if (!strlen (cashman.cmanno))
    {
      set_error (" CASHMAN No. NOT ENTERED ");
      return RET_STAY;
    }
  cashman_file = fopen ("./pos_files/dbase/cashman_ifile", "r+");
  while (fread (&tcashman, sizeof (CASHMAN), 1, cashman_file))
    {
      if (!strcmp (tcashman.cmanno, cashman.cmanno))
	{
	  if (tcashman.valid == 'Y')
	    {
	      item_found = 1;
	      break;
	    }
	  else
	    {
	      item_found = 2;
	      break;
	    }
	}
    }
  if (item_found)
    {
      if (cashman_fields_check ())
	{
	  return RET_STAY;
	}
      if (cashman.valid == 'N')
	{
	  cashman.valid = 'Y';
	  ++cashman_count;
	}
      fseek (cashman_file, -sizeof (CASHMAN), SEEK_CUR);
      store_entity (cashman_file, &cashman, sizeof (CASHMAN));
      return RET_OK;
    }
  if (cashman_count <= MAX_CASHMANS)
    {
      rewind (cashman_file);
      while (fread (&tcashman, sizeof (CASHMAN), 1, cashman_file))
	{
	  if (tcashman.valid == 'N')
	    {
	      if (cashman_fields_check ())
		{
		  return RET_STAY;
		}
	      cashman.valid = 'Y';
	      fseek (cashman_file, -sizeof (CASHMAN), SEEK_CUR);
	      store_entity (cashman_file, &cashman, sizeof (CASHMAN));
	      ++cashman_count;
	      return RET_OK;
	    }
	}
      if (cashman_fields_check ())
	{
	  return RET_STAY;
	}
      cashman.valid = 'Y';
      fseek (cashman_file, 0, SEEK_END);
      store_entity (cashman_file, &cashman, sizeof (CASHMAN));
      ++cashman_count;
      return RET_OK;
    }
  else
    {
      set_error (" CASHMAN LIMIT EXCEEDED ");
      return RET_STAY;
    }
}

int
cashman_fields_check ()
{
  return 0;
}

/*************************************************************************/

check_misc_fields ()
{
  float tval, dval;
  char vmisc = 0;

  if (!strlen (misc.mvalid1) || !strlen (misc.mvalid2) ||
      !strlen (misc.mvalid3) || !strlen (misc.mvalid4) ||
      !strlen (misc.math1) || !strlen (misc.math2) ||
      !strlen (misc.math3) || !strlen (misc.math4))
    {
      set_error ("[M1-M4] OR [+/-] field blank");
      return 1;
    }
  tval = atoi (misc.mamt1);
  dval = atoi (misc.mper1);
  if (dval > 99)
    {
      set_error (" Max Misc Percentage [99.99] ");
      return 1;
    }
  if ((tval > 0) && (dval > 0))
    {
      set_error (" Entar Either Amont Or Percentage ");
      return 1;
    }
  if (!strlen (misc.mtext1) && ((tval > 0) || (dval > 0)))
    {
      set_error (" Misc Text1 Missing ");
      return 1;
    }
  tval = atoi (misc.mamt2);
  dval = atoi (misc.mper2);
  if (dval > 99)
    {
      set_error (" Max Misc Percentage [99.99] ");
      return 1;
    }
  if ((tval > 0) && (dval > 0))
    {
      set_error (" Entar Either Amont Or Percentage ");
      return 1;
    }
  if (!strlen (misc.mtext2) && ((tval > 0) || (dval > 0)))
    {
      set_error (" Misc Text2 Missing ");
      return 1;
    }
  tval = atoi (misc.mamt3);
  dval = atoi (misc.mper3);
  if (dval > 99)
    {
      set_error (" Max Misc Percentage [99.99] ");
      return 1;
    }
  if ((tval > 0) && (dval > 0))
    {
      set_error (" Entar Either Amont Or Percentage ");
      return 1;
    }
  if (!strlen (misc.mtext3) && ((tval > 0) || (dval > 0)))
    {
      set_error (" Misc Text3 Missing ");
      return 1;
    }
  tval = atoi (misc.mamt4);
  dval = atoi (misc.mper4);
  if (dval > 99.99)
    {
      set_error (" Max Misc Percentage [99.99] ");
      return 1;
    }
  if ((tval > 0) && (dval > 0))
    {
      set_error (" Entar Either Amont Or Percentage ");
      return 1;
    }
  if (!strlen (misc.mtext4) && ((tval > 0) || (dval > 0)))
    {
      set_error (" Misc Text4 Missing ");
      return 1;
    }
  if (misc.mvalid1[0] == 'Y')
    ++vmisc;
  if (misc.mvalid2[0] == 'Y')
    ++vmisc;
  if (misc.mvalid3[0] == 'Y')
    ++vmisc;
  if (misc.mvalid4[0] == 'Y')
    ++vmisc;
  if (vmisc >= 3)
    {
      set_error (" ANY TWO MISCS CAN SET [Y] ");
      return 1;
    }
  return 0;
}

int
misc_do_ok (void *menu_key)
{

  if ((misc_file = fopen ("./pos_files/dbase/misc_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (check_misc_fields ())
    {
      return RET_STAY;
    }
  if (!store_entity (misc_file, &misc, sizeof (MISC)))
    {
      set_error (" FILE WRITE ERROR ");
      return RET_STAY;
    }
  return RET_OK;
}

int
misc_init (PMENU * menu)
{
  MISC tmisc;

  if ((misc_file = fopen ("./pos_files/dbase/misc_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (!read_entity (misc_file, &misc, sizeof (MISC)))
    {
      set_error ("FILE READ ERROR");
      return RET_STAY;
    }
}

/*****************************************************************************/

check_billfmt_fields ()
{
  return 0;
}

int
billfmt_do_ok (void *menu_key)
{

  if ((billfmt_file = fopen ("./pos_files/dbase/billfmt_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (check_billfmt_fields ())
    {
      return RET_STAY;
    }
  if (!store_entity (billfmt_file, &billfmt, sizeof (BILLFMT)))
    {
      set_error (" FILE WRITE ERROR ");
      return RET_STAY;
    }
  return RET_OK;
}

int
billfmt_init (PMENU * menu)
{
  BILLFMT tbillfmt;

  if ((billfmt_file = fopen ("./pos_files/dbase/billfmt_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (!read_entity (billfmt_file, &billfmt, sizeof (BILLFMT)))
    {
      set_error ("FILE READ ERROR");
      return RET_STAY;
    }
}

/***************************************************************************/

check_paswd_fields ()
{
  return 0;
}

int
paswd_do_ok (void *menu_key)
{

  if ((paswd_file = fopen ("./pos_files/dbase/paswd_ifile", "r+")) == NULL)
    {
      set_error (" CANNOT OPEN FILE ");
      return RET_STAY;
    }
  if (check_paswd_fields ())
    {
      return RET_STAY;
    }
  if (!store_entity (paswd_file, &ppasswd, sizeof (PPASSWD)))
    {
      set_error (" FILE WRITE ERROR ");
      return RET_STAY;
    }
  return RET_OK;
}

/***************************************************************************/
int
owner_check ()
{
  if (strcmp (loginp, "owner"))
    return 0;
  paswd_file = fopen ("./pos_files/dbase/paswd_ifile", "r");
  fread (&ppasswd, sizeof (PPASSWD), 1, paswd_file);
  fclose (paswd_file);
  if (!strcmp (passp, ppasswd.newpasswd))
    return 1;
  else
    return 0;
}
