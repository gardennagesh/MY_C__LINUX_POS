/* menu initializations for reporting functionality module */
BOX_INFO isales_box = {
  18, 38, 2, 20, NULL
};

FIELD isales_flds[] = {

  {" Section No.     [1-4]:", 3, 2, isales_do_ok, sect_jump, 1 + 2,
   A_NORMAL, DIGIT, sect_buf, 0}
  ,

  {" Todays Sales    [Y/N]:", 5, 2, isales_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Store No.[1-50]:", 7, 2, isales_do_ok, NULL, 2 + 2,
   A_NORMAL, DIGIT, store_buf, 0}
  ,

  {" Enter Item Code      :", 9, 2, isales_do_ok, NULL, 4 + 2,
   A_NORMAL, DIGIT, code_buf, 0}
  ,

  {" Start Date [dd/mm/yy]:", 11, 2, NULL, start_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {" End Date   [dd/mm/yy]:", 13, 2, NULL, end_jump, 8 + 2,
   A_NORMAL, DATE, end_date, 0}
  ,

  {"   SCREEN  ", 15, 2, isales_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 15, 25, isales_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU isales_menu = {
  7, &isales_box, " ITEMS SALES REPORT ", &isales_flds, NULL, isale_init, 0
};

BOX_INFO istock_box = {
  12, 38, 2, 20, NULL
};

FIELD istock_flds[] = {

  {"Stock Of All Items    :", 3, 2, istock_do_ok, stock_jump, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Store No.[1-50]:", 5, 2, istock_do_ok, NULL, 2 + 2,
   A_NORMAL, DIGIT, store_buf, 0}
  ,

  {" Enter Item Code      :", 7, 2, istock_do_ok, NULL, 4 + 2,
   A_NORMAL, DIGIT, code_buf, 0}
  ,

  {"  SCREEN   ", 9, 2, istock_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 9, 25, istock_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU istock_menu = {
  4, &istock_box, " ITEMS STOCK REPORT ", &istock_flds, NULL, istock_init, 0
};

BOX_INFO profit_box = {
  18, 38, 2, 20, NULL
};

FIELD profit_flds[] = {

  {" Section No.     [1-4]:", 3, 2, profit_do_ok, sect_jump, 1 + 2,
   A_NORMAL, DIGIT, sect_buf, 0}
  ,

  {" Todays Sales    [Y/N]:", 5, 2, profit_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Store No.[1-50]:", 7, 2, profit_do_ok, NULL, 2 + 2,
   A_NORMAL, DIGIT, store_buf, 0}
  ,

  {" Enter Item Code      :", 9, 2, profit_do_ok, NULL, 4 + 2,
   A_NORMAL, DIGIT, code_buf, 0}
  ,

  {" Start Date [dd/mm/yy]:", 11, 2, NULL, start_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {" End Date   [dd/mm/yy]:", 13, 2, profit_do_ok, end_jump, 8 + 2,
   A_NORMAL, DATE, end_date, 0}
  ,

  {"  SCREEN   ", 15, 2, profit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 15, 25, profit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU profit_menu = {
  7, &profit_box, " ITEMS PROFIT REPORT ", &profit_flds, NULL, isale_init, 0
};

BOX_INFO idetail_box = {
  12, 36, 2, 20, NULL
};

FIELD idetail_flds[] = {

  {" Of All Items         :", 3, 2, idetail_do_ok, detail_jump, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Store No.[1-50]:", 5, 2, idetail_do_ok, NULL, 2 + 2,
   A_NORMAL, DIGIT, store_buf, 0}
  ,

  {" Enter Kit No.  [1-50]:", 7, 2, idetail_do_ok, NULL, 2 + 2,
   A_NORMAL, DIGIT, code_buf, 0}
  ,

  {"  SCREEN   ", 9, 2, idetail_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 9, 22, idetail_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU idetail_menu = {
  4, &idetail_box, " ITEMS DEATL REPORT ", &idetail_flds, NULL, detail_init, 0
};

BOX_INFO finan_box = {
  14, 38, 2, 20, NULL
};

FIELD finan_flds[] = {

  {" Section No.     [1-4]:", 3, 2, finan_do_ok, finan_sect_jump, 1 + 2,
   A_NORMAL, DIGIT, sect_buf, 0}
  ,

  {" Todays Sales    [Y/N]:", 5, 2, finan_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Start Date [dd/mm/yy]:", 7, 2, NULL, finan_date_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {" End Date   [dd/mm/yy]:", 9, 2, NULL, end_jump, 8 + 2,
   A_NORMAL, DATE, end_date, 0}
  ,

  {"   SCREEN  ", 11, 2, finan_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 11, 25, finan_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU finan_menu = {
  5, &finan_box, " FINANCIAL REPORT ", &finan_flds, NULL, finan_init, 0
};

BOX_INFO billsum_box = {
  12, 38, 2, 20, NULL
};

FIELD billsum_flds[] = {

  {" Section No.     [1-4]:", 3, 2, billsum_do_ok, billsum_sect_jump, 1 + 2,
   A_NORMAL, DIGIT, sect_buf, 0}
  ,

  {" Todays  Summary [Y/N]:", 5, 2, billsum_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Date [dd/mm/yy]:", 7, 2, NULL, billsum_date_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {"   SCREEN  ", 9, 2, billsum_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 9, 25, billsum_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU billsum_menu = {
  4, &billsum_box, " BILL-SUMMARY REPORT ", &billsum_flds,
  NULL, billsum_init, 0
};

BOX_INFO taxsum_box = {
  12, 38, 2, 20, NULL
};

FIELD taxsum_flds[] = {

  {" Section No.     [1-4]:", 3, 2, taxsum_do_ok, taxsum_sect_jump, 1 + 2,
   A_NORMAL, DIGIT, sect_buf, 0}
  ,

  {" Todays  Summary [Y/N]:", 5, 2, taxsum_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Date [dd/mm/yy]:", 7, 2, NULL, taxsum_date_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {"   SCREEN  ", 9, 2, taxsum_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 9, 25, taxsum_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU taxsum_menu = {
  4, &taxsum_box, " TAX-SUMMARY REPORT ", &taxsum_flds,
  NULL, taxsum_init, 0
};

BOX_INFO cashman_box = {
  10, 38, 2, 20, NULL
};

FIELD cashman_flds[] = {

  {" Todays Sales    [Y/N]:", 3, 2, icashman_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Date [dd/mm/yy]:", 5, 2, NULL, cashman_date_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {"   SCREEN  ", 7, 2, icashman_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 7, 25, icashman_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU cashman_menu = {
  3, &cashman_box, " CASH-MAN REPORT ", &cashman_flds,
  NULL, cashman_init, 0
};

BOX_INFO waiter_box = {
  10, 38, 2, 20, NULL
};

FIELD waiter_flds[] = {

  {" Todays Sales    [Y/N]:", 3, 2, iwaiter_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Date [dd/mm/yy]:", 5, 2, NULL, waiter_date_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {"   SCREEN  ", 7, 2, iwaiter_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 7, 25, iwaiter_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU waiter_menu = {
  3, &waiter_box, " WAITER REPORT ", &waiter_flds,
  NULL, waiter_init, 0
};

BOX_INFO isman_box = {
  10, 38, 2, 20, NULL
};

FIELD isman_flds[] = {

  {" Todays Sales    [Y/N]:", 3, 2, isman_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Date [dd/mm/yy]:", 5, 2, NULL, isman_date_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {"   SCREEN  ", 7, 2, isman_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 7, 25, isman_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU isman_menu = {
  3, &isman_box, " SALES MAN REPORT ", &isman_flds,
  NULL, isman_init, 0
};




BOX_INFO general_box = {
  12, 38, 2, 20, NULL
};

FIELD general_flds[] = {

  {" Section No.     [1-4]:", 3, 2, general_do_ok, general_sect_jump, 1 + 2,
   A_NORMAL, DIGIT, sect_buf, 0}
  ,

  {" Todays Report   [Y/N]:", 5, 2, general_do_ok, NULL, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Date [dd/mm/yy]:", 7, 2, NULL, general_date_jump, 8 + 2,
   A_NORMAL, DATE, start_date, 0}
  ,

  {"   SCREEN  ", 9, 2, general_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 9, 25, general_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU general_menu = {
  4, &general_box, " PAYMENT-DETAIL REPORT ", &general_flds,
  NULL, general_init, 0
};

BOX_INFO custmr_box = {
  10, 36, 2, 20, NULL
};

FIELD custmr_flds[] = {

  {" Of All Customer      :", 3, 2, custmr_do_ok, custmr_jump, 1 + 2,
   A_NORMAL, CHECK, rep_buf, 0}
  ,

  {" Enter Customer No.   :", 5, 2, custmr_do_ok, NULL, 2 + 2,
   A_NORMAL, DIGIT, store_buf, 0}
  ,

  {"  SCREEN   ", 7, 2, idetail_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"  PRINTER  ", 7, 22, idetail_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU custmr_menu = {
  3, &custmr_box, " CUSTOMER  REPORT ", &custmr_flds, NULL, custmr_init, 0
};

BOX_INFO reset_box1 = {
  8, 50, 6, 14, NULL
};

FIELD reset_flds1[] = {
  {" Resets All Transaction Reports !! ", 3, 7, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {"  CANCEL  ", 5, 6, reset_cancel_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"    OK    ", 5, 33, reset_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU reset_menu1 = {
  2, &reset_box1, " Transaction Reset Menu ", &reset_flds1, NULL, NULL, 0, 18
};

BOX_INFO reset_box2 = {
  8, 50, 6, 14, NULL
};

FIELD reset_flds2[] = {
  {" Resets All Items Stock ", 3, 12, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {"  CANCEL  ", 5, 6, reset_cancel_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

  {"    OK    ", 5, 33, reset_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU reset_menu2 = {
  2, &reset_box2, " Stock Reset Menu ", &reset_flds2, NULL, NULL, 0, 6
};

BOX_INFO remove_box1 = {
  8, 53, 12, 12, NULL
};

FIELD remove_flds1[] = {

  {" Removes All Reports Database ", 3, 11, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {" CANCEL ", 5, 9, common_do_cancel, NULL, 0, A_NORMAL, ACTION, &cancel, 0}
  ,

  {"   OK   ", 5, 34, NULL, NULL, 0, A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU remove_menu1 = {
  2, &remove_box1, " Report Remove Menu ", &remove_flds1, NULL, NULL, 1, 6
};

BOX_INFO remove_box2 = {
  8, 53, 12, 12, NULL
};

FIELD remove_flds2[] = {

  {" Removes Setup and Report Database ", 3, 8, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0}
  ,

  {" CANCEL ", 5, 9, common_do_cancel, NULL, 0, A_NORMAL, ACTION, &cancel, 0}
  ,

  {"   OK   ", 5, 34, NULL, NULL, 0, A_NORMAL, ACTION, &ok, 0}
  ,

};

PMENU remove_menu2 = {
  2, &remove_box2, " Database Remove Menu ", &remove_flds2, NULL, NULL, 1, 18
};
