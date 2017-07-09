/* cprog.c - initialization for programming menus structures */

BOX_INFO item_box = {
  22, 53, 1, 12, NULL
};

FIELD item_flds[] = {

  {" Item Code [1-15]:", 3, 2, NULL, item_code_unselect, 4 + 2,
   A_NORMAL, DIGIT, item.item_code, 0}
  ,

  {" Item Name       :", 5, 2, NULL, NULL, 16 + 2,
   A_NORMAL, ALPHA, item.item_name, 0}
  ,

  {" Sell Price      :", 7, 2, NULL, NULL, 8 + 2,
   A_NORMAL, AMOUNT, item.sell_price, 0}
  ,

  {" Cost Price      :", 9, 2, NULL, NULL, 8 + 2,
   A_NORMAL, AMOUNT, item.cost_price, 0}
  ,
#			if		0
  {" MRP [rrrrr.pp] :", 11, 2, NULL, NULL, 8 + 2,
   A_NORMAL, AMOUNT, item.mrp, 0}
  ,

  {" Hkey[a-z/A-Z]:", 11, 32, NULL, NULL, 1 + 2,
   A_NORMAL, PASSWD, item.hkey, 0}
  ,
#			endif

  {" Store No [1-50] :", 11, 2, NULL, NULL, 2 + 2,
   A_NORMAL, DIGIT, item.dept_link, 0}
  ,

  {" Tax Link [1-4] :", 11, 28, NULL, NULL, 1 + 2,
   A_NORMAL, DIGIT, item.tax_link, 0}
  ,

  {" Neg Stock [Y/N] :", 13, 2, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, item.fneg_stock, 0}
  ,

  {"Qty Decimal[Y/N]:", 13, 28, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, item.fqty_dec, 0}
  ,

  {"Kitchen No [1-99]:", 15, 2, NULL, NULL, 2 + 2,
   A_NORMAL, DIGIT, item.kit_link, 0}
  ,

  {" Unit [3C]    :", 15, 28, NULL, NULL, 3 + 2,
   A_NORMAL, ALPHA, item.unit, 0}
  ,

  {" Item %Discount  :", 17, 2, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, item.item_disc, 0}
  ,

  {"  NEXT  ", 19, 4, item_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 19, 16, item_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 19, 27, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 19, 38, item_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,

};

PMENU item_menu = {
  14, &item_box, " ITEM CREATION MENU", &item_flds, NULL, item_init, 0
};

BOX_INFO dept_box = {
  12, 53, 1, 12, NULL
};

FIELD dept_flds[] = {

  {" Store No [1-50] :", 3, 6, NULL, dept_no_unselect, 2 + 2,
   A_NORMAL, DIGIT, dept.dept_code, 0}
  ,

  {" Store Name [16C]:", 5, 6, NULL, NULL, 16 + 2,
   A_NORMAL, ALPHA, dept.dept_name, 0}
  ,

  {" Tax Link [1-4]  :", 7, 6, NULL, NULL, 1 + 2,
   A_NORMAL, DIGIT, dept.tax_link, 0}
  ,

  {"  NEXT  ", 9, 4, dept_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 9, 15, dept_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 9, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 9, 35, dept_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,

};

PMENU dept_menu = {
  6, &dept_box, " STORE CREATION MENU ", &dept_flds, NULL, NULL, 0
};

BOX_INFO head_box = {
  17, 53, 1, 12, NULL
};

FIELD head_flds[] = {

  {" Section No [1-4]:", 3, 16, NULL, head_no_unselect, 1 + 2,
   A_NORMAL, DIGIT, head.sect, 0}
  ,

  {" Title1 :", 5, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALNUM, head.line1, 0}
  ,

  {" DW1 [Y/N]:", 5, 36, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, head.dw1, 0}
  ,

  {" Title2 :", 7, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALNUM, head.line2, 0}
  ,

  {" DW2 [Y/N]:", 7, 36, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, head.dw2, 0}
  ,

  {" Title3 :", 9, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALNUM, head.line3, 0}
  ,

  {" DW3 [Y/N]:", 9, 36, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, head.dw3, 0}
  ,

  {" Title4 :", 11, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALNUM, head.line4, 0}
  ,

  {" DW4 [Y/N]:", 11, 36, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, head.dw4, 0}
  ,

  {" Title5 :", 13, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALNUM, head.line5, 0}
  ,

  {" DW5 [Y/N]:", 13, 36, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, head.dw5, 0}
  ,

  {"  NEXT  ", 15, 4, head_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 15, 15, head_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 15, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 15, 35, head_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,
};

PMENU head_menu = {
  14, &head_box, " BILL TITLE MENU", &head_flds, NULL, NULL, 0
};

BOX_INFO foot_box = {
  11, 53, 1, 12, NULL
};

FIELD foot_flds[] = {

  {" Section No [1-4] :", 3, 16, NULL, foot_no_unselect, 1 + 2,
   A_NORMAL, DIGIT, foot.sect, 0}
  ,

  {" Tail1 :", 5, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALPHA, foot.line1, 0}
  ,

  {" DW1 [Y/N]:", 5, 36, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, foot.dw1, 0}
  ,

  {" Tail2 :", 7, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALPHA, foot.line2, 0}
  ,

  {" DW2 [Y/N]:", 7, 36, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, foot.dw2, 0}
  ,

  {"  NEXT  ", 9, 6, foot_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 9, 15, foot_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 9, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 9, 35, foot_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,
};

PMENU foot_menu = {
  8, &foot_box, " BILL TAIL MENU", &foot_flds, NULL, NULL, 0
};


BOX_INFO tax_box = {
  13, 53, 1, 12, NULL
};

FIELD tax_flds[] = {

  {" Tax Link No [1-4]:", 3, 16, NULL, tax_no_unselect, 1 + 2,
   A_NORMAL, DIGIT, tax.tax_no, 0}
  ,

  {" Tax Name [8C]:", 6, 2, NULL, NULL, 8 + 2,
   A_NORMAL, ALPHA, tax.tname, 0}
  ,

  {" Tax Amt  :", 6, 32, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, tax.tamt, 0}
  ,

  {" Cess Name [8C]:", 8, 2, NULL, NULL, 8 + 2,
   A_NORMAL, ALPHA, tax.toname, 0}
  ,

  {" Cess Amt  :", 8, 32, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, tax.toamt, 0}
  ,


  {"  NEXT  ", 10, 4, tax_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 10, 15, tax_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 10, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 10, 35, tax_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,
};

PMENU tax_menu = {
  8, &tax_box, " TAX  SETTINGS  MENU", &tax_flds, NULL, NULL, 0
};

BOX_INFO swprint_box = {
  10, 48, 4, 16, NULL
};

FIELD swprint_flds[] = {

  {" Set To Condensed Mode [Y/N]:", 3, 4, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, oprtion.fsmall, 0}
  ,

  {" Set To Normal Mode    [Y/N]:", 5, 4, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, oprtion.fnormal, 0}
  ,

  {"   OK   ", 7, 8, NULL, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 7, 30, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,
};

PMENU swprint_menu = {
  3, &swprint_box, " S/W SETTINGS FOR PRINTER", &swprint_flds,
  "pscreen1", NULL, 1, 14
};


BOX_INFO opt_box = {
  17, 53, 1, 12, NULL
};

FIELD opt_flds[] = {
  {" Printer Settings by soft-ware   [Y/N]:", 3, 4, NULL, swprint_jump, 1 + 2,
   A_NORMAL, CHECK, oprtion.fswprint, 0}
  ,

  {" Auto-reset reports for next-day [Y/N]:", 5, 4, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, oprtion.fauto, 0}
  ,

  {" Print Report Before next-Day    [Y/N]:", 7, 4, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, oprtion.frepprint, 0}
  ,

  {" Add misc amt by default in bill [Y/N]:", 9, 4, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, oprtion.fmisc_amt, 0}
  ,

  {" Print date/time in reports      [Y/N]:", 11, 4, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, oprtion.frepdate, 0}
  ,

  {" Set soft-ware  RETAIL and KOT [Y/N]  :", 13, 4, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, oprtion.fsoft, 0}
  ,

  {"   OK   ", 15, 8, option_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 15, 30, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,
};

PMENU opt_menu = {
  7, &opt_box, " OPERATION  SETTINGS MENU", &opt_flds, NULL, option_init, 0
};

BOX_INFO kitchen_box = {
  10, 55, 1, 12, NULL
};

FIELD kitchen_flds[] = {

  {" Enter Kitchen No  [1-99] :", 3, 2, NULL, kit_no_unselect, 2 + 2,
   A_NORMAL, DIGIT, kitchen.kitno, 0}
  ,

  {" Enter Kitchen Name [16C] :", 5, 2, NULL, NULL, 16 + 2,
   A_NORMAL, ALPHA, kitchen.kitname, 0}
  ,

  {"  NEXT  ", 7, 4, kit_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 7, 15, kit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 7, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 7, 35, kit_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,
};

PMENU kitchen_menu = {
  5, &kitchen_box, " KITCHEN SETTINGS MENU", &kitchen_flds, NULL, NULL, 0
};


BOX_INFO bill_fmt_box = {
  18, 55, 1, 12, NULL
};

FIELD bill_fmt_flds[] = {

  {" Print Item Code in Bill [Y/N]:", 3, 5, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, billfmt.fitemcode, 0}
  ,

  {" Print Tax In Bill       [Y/N]:", 5, 5, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, billfmt.ftax, 0}
  ,

  {" Print Date In Bill      [Y/N]:", 7, 5, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, billfmt.fdate, 0}
  ,

  {" Print Time In Bill      [Y/N]:", 9, 5, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, billfmt.ftime, 0}
  ,

  {" Print Title Ahead Bill  [Y/N]:", 11, 5, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, billfmt.fahed, 0}
  ,

  {" Bill Width  [1-max, 2, 3-min]:", 13, 5, NULL, NULL, 1 + 2,
   A_NORMAL, DIGIT, billfmt.fahed, 0}
  ,

  {"   OK   ", 15, 9, billfmt_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 15, 30, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

};

PMENU bill_fmt_menu = {
  7, &bill_fmt_box, " BILL FORMAT MENU ", &bill_fmt_flds, NULL, billfmt_init,
    0
};


BOX_INFO cman_box = {
  22, 53, 1, 12, NULL
};

FIELD cman_flds[] = {

  {" Cash-Man No [1-25]:", 3, 2, NULL, cashman_no_unselect, 2 + 2,
   A_NORMAL, DIGIT, cashman.cmanno, 0}
  ,

  {" Cash-Man Name [10C]:", 5, 2, NULL, NULL, 10 + 2,
   A_NORMAL, ALPHA, cashman.cname, 0}
  ,

  {" Password :", 7, 2, NULL, NULL, 10 + 2,
   A_NORMAL, ALPHA, cashman.cpasswd, 0}
  ,

  {" Commision :", 7, 30, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, cashman.commision, 0}
  ,

  {" Refund Bill Privelege     [Y/N]:", 9, 2, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, cashman.prefund, 0}
  ,

  {" Reset  Sales Summary      [Y/N]:", 11, 2, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, cashman.preset, 0}
  ,

  {" Next-Day Key Privelege    [Y/N]:", 13, 2, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, cashman.pmanualreset, 0}
  ,

  {" Start Fresh Key Privelege [Y/N]:", 15, 2, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, cashman.pfresh, 0}
  ,

  {" Privelege to Become Owner [Y/N]:", 17, 2, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, cashman.powner, 0}
  ,

  {"  MORE  ", 17, 42, NULL, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,


  {"  NEXT  ", 19, 4, cashman_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 19, 15, cashman_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 19, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 19, 35, cashman_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,

};

PMENU cmen_menu = {
  13, &cman_box, " CASH-MAN CREATION MENU", &cman_flds, NULL, NULL, 0
};


BOX_INFO wtr_box = {
  13, 53, 1, 12, NULL
};

FIELD wtr_flds[] = {

  {" Waiter No [1-50] :", 3, 6, NULL, waiter_no_unselect, 2 + 2,
   A_NORMAL, DIGIT, waiter.wtrno, 0}
  ,

  {" Waiter Name [20C]:", 5, 6, NULL, NULL, 20 + 2,
   A_NORMAL, ALPHA, waiter.wtrname, 0}
  ,

  {" Waiter Commision :", 7, 6, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, waiter.wtrcomison, 0}
  ,

  {"  NEXT  ", 10, 4, waiter_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 10, 15, waiter_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 10, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 10, 35, waiter_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,
};


PMENU wtr_menu = {
  6, &wtr_box, " WAITER  MENU", &wtr_flds, NULL, NULL, 0
};



BOX_INFO kotno_box = {
  8, 53, 1, 12, NULL
};

FIELD kotno_flds[] = {

  {" Kitchen Order Ticket No :", 3, 6, NULL, NULL, 5 + 2,
   A_NORMAL, DIGIT, kotno.kotno, 0}
  ,

  {"   OK   ", 5, 9, kotno_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 5, 30, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

};

PMENU kotno_menu = {
  2, &kotno_box, " SET KOT NUMBER", &kotno_flds, NULL, kotno_init, 0
};

BOX_INFO billno_box = {
  8, 53, 1, 12, NULL
};

FIELD billno_flds[] = {

  {" Section No [1-4]:", 3, 2, NULL, billno_unselect, 1 + 2,
   A_NORMAL, DIGIT, billno.sectno, 0}
  ,

  {" Enter Bill No :", 3, 27, NULL, NULL, 5 + 2,
   A_NORMAL, DIGIT, billno.billno, 0}
  ,

  {"   OK   ", 5, 10, billno_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 5, 30, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

};

PMENU billno_menu = {
  3, &billno_box, " SET BILL NUMBER ", &billno_flds, NULL, NULL, 0
};

BOX_INFO cust_box = {
  19, 55, 1, 12, NULL
};

FIELD cust_flds[] = {

  {" Customer No [1-100]:", 3, 5, NULL, customer_no_unselect, 3 + 2,
   A_NORMAL, DIGIT, customer.custno, 0}
  ,

  {" Customer Name [20C]:", 5, 5, NULL, NULL, 20 + 2,
   A_NORMAL, ALPHA, customer.custname, 0}
  ,

  {" Customer Phone No  :", 7, 5, NULL, NULL, 10 + 2,
   A_NORMAL, DIGIT, customer.phno, 0}
  ,

  {" Customer Mobile No :", 9, 5, NULL, NULL, 15 + 2,
   A_NORMAL, DIGIT, customer.mobile, 0}
  ,

  {" Customer DL-No     :", 11, 5, NULL, NULL, 15 + 2,
   A_NORMAL, ALNUM, customer.dlno, 0}
  ,

  {" Adds Line1 :", 13, 5, NULL, NULL, 25 + 2,
   A_NORMAL, ALNUM, customer.adds1, 0}
  ,

  {" Adds Line2 :", 15, 5, NULL, NULL, 25 + 2,
   A_NORMAL, ALNUM, customer.adds2, 0}
  ,

  {"  NEXT  ", 17, 4, customer_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 17, 15, customer_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 17, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 17, 35, customer_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,
};

PMENU cust_menu = {
  10, &cust_box, " CUSTOMER MENU ", &cust_flds, NULL, NULL, 0
};

BOX_INFO bill_line_box = {
  8, 53, 1, 12, NULL
};

FIELD bill_line_flds[] = {

  {" Enter No Of Bill Lines  :", 3, 6, NULL, NULL, 2 + 2,
   A_NORMAL, DIGIT, plines.plines, 0}
  ,

  {"   OK   ", 5, 10, plines_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 5, 30, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

};

PMENU bill_line_menu = {
  2, &bill_line_box, " SET BILL LINES", &bill_line_flds, NULL, plines_init, 0
};

BOX_INFO misc_box = {
  16, 62, 5, 8, NULL
};

FIELD misc_flds[] = {

  {"M1Text:", 3, 1, NULL, NULL, 10 + 2,
   A_NORMAL, ALPHA, misc.mtext1, 0}
  ,

  {"Amt1:", 3, 22, NULL, NULL, 5 + 2,
   A_NORMAL, DIGIT, misc.mamt1, 0}
  ,

  {"PCent:", 3, 36, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, misc.mper1, 0}
  ,

  {"[+/-]:", 3, 51, NULL, NULL, 1 + 2,
   A_NORMAL, MATH, misc.math1, 0}
  ,
#		if	1
  {"M2Text:", 5, 1, NULL, NULL, 10 + 2,
   A_NORMAL, DIGIT, misc.mtext2, 0}
  ,

  {"Amt2:", 5, 22, NULL, NULL, 5 + 2,
   A_NORMAL, DIGIT, misc.mamt2, 0}
  ,

  {"PCent:", 5, 36, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, misc.mper2, 0}
  ,

  {"[+/-]:", 5, 51, NULL, NULL, 1 + 2,
   A_NORMAL, MATH, misc.math2, 0}
  ,

  {"M3Text:", 7, 1, NULL, NULL, 10 + 2,
   A_NORMAL, ALPHA, misc.mtext3, 0}
  ,

  {"Amt3:", 7, 22, NULL, NULL, 5 + 2,
   A_NORMAL, DIGIT, misc.mamt3, 0}
  ,

  {"PCent:", 7, 36, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, misc.mper3, 0}
  ,

  {"[+/-]:", 7, 51, NULL, NULL, 1 + 2,
   A_NORMAL, MATH, misc.math3, 0}
  ,

  {"M4Text:", 9, 1, NULL, NULL, 10 + 2,
   A_NORMAL, ALPHA, misc.mtext4, 0}
  ,

  {"Amt4:", 9, 22, NULL, NULL, 5 + 2,
   A_NORMAL, DIGIT, misc.mamt4, 0}
  ,

  {"PCent:", 9, 36, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, misc.mper4, 0}
  ,

  {"[+/-]:", 9, 51, NULL, NULL, 1 + 2,
   A_NORMAL, MATH, misc.math4, 0}
  ,

  {"M1", 11, 20, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {"M2", 11, 28, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {"M3", 11, 36, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {"M4", 11, 42, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {"", 12, 18, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, misc.mvalid1, 0}
  ,

  {"", 12, 26, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, misc.mvalid2, 0}
  ,

  {"", 12, 34, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, misc.mvalid3, 0}
  ,

  {"", 12, 40, NULL, NULL, 1 + 2,
   A_NORMAL, CHECK, misc.mvalid4, 0}
  ,
#	endif
  {"   OK   ", 14, 11, misc_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 14, 45, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

};


PMENU misc_menu = {
  25, &misc_box, " MISC  MENU", &misc_flds, NULL, misc_init, 0,
};

BOX_INFO sman_box = {
  13, 53, 1, 12, NULL
};

FIELD sman_flds[] = {

  {" SalesMan No [1-50] :", 3, 6, NULL, sman_no_unselect, 2 + 2,
   A_NORMAL, DIGIT, sman.smanno, 0}
  ,

  {" SalesMan Name [20C]:", 5, 6, NULL, NULL, 20 + 2,
   A_NORMAL, ALPHA, sman.smaname, 0}
  ,

  {" SalesMan Commision :", 7, 6, NULL, NULL, 5 + 2,
   A_NORMAL, AMOUNT, sman.scomison, 0}
  ,

  {"  NEXT  ", 10, 4, sman_next_do_ok, NULL, 0,
   A_NORMAL, ACTION, &next, 0}
  ,

  {"   OK   ", 10, 15, sman_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 10, 25, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

  {" DELETE ", 10, 35, sman_delete_do_ok, NULL, 0,
   A_NORMAL, ACTION, &del, 0}
  ,
};


PMENU sman_menu = {
  6, &sman_box, " Sales Man Menu", &sman_flds, NULL, NULL, 0
};


BOX_INFO paswd_box = {
  12, 53, 1, 12, NULL
};

FIELD paswd_flds[] = {

  {" Enter Preset Passwd   :", 3, 6, NULL, NULL, 10 + 2,
   A_NORMAL, PASSWD, ppasswd.oldpasswd, 0}
  ,

  {" Enter Future Passwd   :", 5, 6, NULL, NULL, 10 + 2,
   A_NORMAL, PASSWD, ppasswd.newpasswd, 0}
  ,

  {" ReEnter Future Passwd :", 7, 6, NULL, NULL, 10 + 2,
   A_NORMAL, PASSWD, ppasswd.retpasswd, 0}
  ,


  {"   OK   ", 9, 10, paswd_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {" CANCEL ", 9, 30, cancel_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0}
  ,

};

PMENU paswd_menu = {
  4, &paswd_box, " CHANGE PASSWD MENU", &paswd_flds, NULL, NULL, 0
};

PMENU *prog_menu[] = {
  &opt_menu, &kitchen_menu, &tax_menu,
  &dept_menu, &item_menu, &head_menu,
  &foot_menu, &bill_fmt_menu, &cmen_menu,
  &wtr_menu, &kotno_menu, &billno_menu,
  &cust_menu, &bill_line_menu, &sman_menu,
  &misc_menu, &paswd_menu, NULL
};
