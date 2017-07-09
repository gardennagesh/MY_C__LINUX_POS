/* Bill Menu Initialization structures */


BOX_INFO bill_exit_box = {
  7, 53, 5, 12, NULL
};

FIELD bill_exit_flds[] = {

  {" You Want Exit Billing Menu ", 3, 12, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0},

  {" CANCEL ", 5, 9, noexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

  {"   OK   ", 5, 36, yesexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

};

PMENU bill_exit_menu = {
  2, &bill_exit_box, " Bill Exit Menu ", &bill_exit_flds, "billscreen", NULL,
    1, 14
};

BOX_INFO bill_print_box = {
  17, 31, 5, 23, NULL
};

FIELD bill_print_flds[] = {

  {"Amt By Cash:", 3, 1, commit_do_ok, jump_cash, 14 + 2,
   A_NORMAL, BAMOUNT, print_bill.cash_amt, 0},

  {"Amt By Card:", 5, 1, NULL, jump_card, 14 + 2,
   A_NORMAL, DISP, print_bill.card_amt, 0},

  {"Amt By Cheq:", 7, 1, NULL, jump_chq, 14 + 2,
   A_NORMAL, DISP, print_bill.chq_amt, 0},

  {"Credit Amt :", 9, 1, NULL, jump_credit, 14 + 2,
   A_NORMAL, DISP, print_bill.credit_amt, 0},

  {"Paid Amt   :", 11, 1, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.paid, 0},

  {"Balance Amt:", 13, 1, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.balance, 0},

  {"Change  Amt:", 15, 1, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.change, 0},


};

PMENU bill_print_menu = {
  6, &bill_print_box, " Press Enter Key ", &bill_print_flds,
  "billscreen", bill_print_init, 1, 14
};

BOX_INFO cash_box = {
  11, 36, 5, 21, NULL
};

FIELD cash_flds[] = {

  {" Paid Amt    :", 3, 3, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.paid, 0},

  {" Balance Amt :", 5, 3, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.balance, 0},

  {" Enter Amt   :", 7, 3, NULL, NULL, 14 + 2,
   A_NORMAL, BAMOUNT, print_bill.cash_amt, 0},

  {"   OK   ", 9, 2, cash_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 9, 26, noexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU cash_menu = {
  4, &cash_box, " Cash Menu ", &cash_flds, "billscreen", cash_init, 1, 14
};

BOX_INFO card_box = {
  15, 38, 5, 21, NULL
};

FIELD card_flds[] = {

  {" Paid Amt     :", 3, 2, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.paid, 0},

  {" Balance Amt  :", 5, 2, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.balance, 0},

  {" Enter Amt    :", 7, 2, NULL, NULL, 14 + 2,
   A_NORMAL, BAMOUNT, print_bill.card_amt, 0},

  {" Card No.     :", 9, 2, NULL, NULL, 16 + 2,
   A_NORMAL, DIGIT, print_bill.card_no, 0},

  {" Card Name    :", 11, 2, NULL, NULL, 10 + 2,
   A_NORMAL, ALPHA, print_bill.card_name, 0},

  {"   OK   ", 13, 3, card_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 13, 27, noexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU card_menu = {
  6, &card_box, " Card Menu ", &card_flds, "billscreen", card_init, 1, 14
};

BOX_INFO credit_box = {
  15, 40, 5, 18, NULL
};

FIELD credit_flds[] = {

  {" Paid Amt   :", 3, 2, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.paid, 0},

  {" Balance Amt:", 5, 2, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.balance, 0},

  {" Cust No.   :", 7, 2, NULL, cust_no_jump, 2 + 2,
   A_NORMAL, DIGIT, print_bill.cust_no, 0},

  {" Cust Name  :", 9, 2, NULL, NULL, 20 + 2,
   A_NORMAL, DISP, print_bill.cust_name, 0},

  {" Enter Amt  :", 11, 2, NULL, NULL, 14 + 2,
   A_NORMAL, AMOUNT, print_bill.credit_amt, 0},

  {"   OK   ", 13, 3, credit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 13, 28, noexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU credit_menu = {
  6, &credit_box, " Credit Menu ", &credit_flds, "billscreen", credit_init, 1,
    14
};

BOX_INFO chq_box = {
  15, 40, 5, 18, NULL
};

FIELD chq_flds[] = {

  {" Paid Amt     :", 3, 1, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.paid, 0},

  {" Balance Amt  :", 5, 1, NULL, NULL, 14 + 2,
   A_NORMAL, DISP, print_bill.balance, 0},

  {" Enter Amt    :", 7, 1, NULL, NULL, 14 + 2,
   A_NORMAL, BAMOUNT, print_bill.chq_amt, 0},

  {" Cheque No.   :", 9, 1, NULL, NULL, 6 + 2,
   A_NORMAL, DIGIT, print_bill.chq_no, 0},

  {" Customer Name:", 11, 1, NULL, NULL, 20 + 2,
   A_NORMAL, ALPHA, print_bill.cust_name, 0},

  {"   OK   ", 13, 3, chq_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 13, 28, noexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU chq_menu = {
  6, &chq_box, " Cheqe Menu ", &chq_flds, "billscreen", chq_init, 1, 14
};

#		if	1
BOX_INFO stock_box = {
  13, 43, 5, 18, NULL
};

FIELD stock_flds[] = {

  {" Code :", 3, 1, NULL, stock_code_jump, 4 + 2,
   A_NORMAL, DIGIT, code_buf, 0},

  {" Name :", 3, 16, NULL, NULL, 16 + 2,
   A_NORMAL, DISP, name_buf, 0},

  {" Current Stock :", 5, 1, NULL, NULL, 10 + 2,
   A_NORMAL, DISP, stock_curr, 0},

  {" Stock In      :", 7, 1, stock_do_ok, NULL, 10 + 2,
   A_NORMAL, DIGIT, stock_in, 0},

  {" Stock Out     :", 9, 1, stock_do_ok, NULL, 10 + 2,
   A_NORMAL, DIGIT, stock_out, 0},

  {"  NEXT  ", 11, 3, NULL, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {"   OK   ", 11, 17, stock_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 11, 30, stockexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU stock_menu = {
  7, &stock_box, " Item Stock In/Out Menu ", &stock_flds, "billscreen", NULL,
    1, 14
};
#	endif
