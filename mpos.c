/* main and sub menu initializations for pos application */

char *prog_m[] = {
  " Set Operation ", " Add Kitchen   ", " Include Tax   ",
  " Create Stores ", " Create Items  ", " Add Bill Title",
  " Add Bill Tail ", " Bill Format   ", " Add Cash-Man  ",
  " Add Waiter    ", " Set Kot No    ", " Set Bill No   ",
  " Add Customer  ", " Bill Lines    ", " Add Sales-Man ",
  " Add-Misc-Amt  ", " Owner Password"
};

char *report_m[] = {
  " Item Sales   >", " Financial    >", " Item Stock   >",
  " Profit Report>", " Bill Summary >", " Tax Summary  >",
  " General Rep  >", " Cash-Man Rep >", " Waiter Report>",
  " Sales Man Rep>",
  " Customer Rep >", " Item Details >", " Reset Reports>",
};

char *isale_m[] = { " All items    >", " Store wise   >", " Of a item    >" };

char *finan_m[] = { " Todays       >", " Date wise    >" };

char *stock_m[] = { " All items    >", " Store wise   >", " Of a item    >" };

char *profit_m[] =
  { " All items    >", " Store wise   >", " Of a item    >" };

char *billsum_m[] = { " Todays       >", " Date wise    >" };

char *taxsum_m[] = { " Todays       >", " Date wise    >" };

char *general_m[] = { " Payment type >", " Card detail  >",
  " Cheq detail  >", " Credit detail>"
};

char *cashman_m[] = { " Todays       >", " Date wise    >" };

char *waiter_m[] = { " Todays       >", " Date wise    >" };

char *sman_m[] = { " Todays       >", " Date wise    >" };

char *idetail_m[] =
  { " All items    >", " Store wise   >", " Kitchen wise >" };

char *custmr_m[] = { " All customers>", " Of a customer>" };

char *reset_m[] = { " Transaction   ", " Item stock rep" };

char *remove_m[] = { " Only Reports >", " All Database >" };

PMENU *p_isale[] = {
  &isales_menu, &isales_menu, &isales_menu, NULL
};

PMENU *p_finan[] = {
  &finan_menu, &finan_menu, NULL
};

PMENU *p_istock[] = {
  &istock_menu, &istock_menu, &istock_menu, NULL
};

PMENU *p_profit[] = {
  &profit_menu, &profit_menu, &profit_menu, NULL
};

PMENU *p_billsum[] = {
  &billsum_menu, &billsum_menu, NULL
};

PMENU *p_taxsum[] = {
  &taxsum_menu, &taxsum_menu, NULL
};

PMENU *p_general[] = {
  &general_menu, &general_menu, &general_menu,
  &general_menu, NULL
};

PMENU *p_cashman[] = {
  &cashman_menu, &cashman_menu, NULL
};

PMENU *p_waiter[] = {
  &waiter_menu, &waiter_menu, NULL
};

PMENU *p_isman[] = {
  &isman_menu, &isman_menu, NULL
};

PMENU *p_custmr[] = {
  &custmr_menu, &custmr_menu, NULL
};

PMENU *p_idetail[] = {
  &idetail_menu, &idetail_menu, &idetail_menu, NULL
};

PMENU *p_reset[] = {
  &reset_menu1, &reset_menu2, NULL
};

PMENU *p_rmdbase[] = {
  &remove_menu1, &remove_menu2, NULL
};

SETPOS item_sale =
  { 5, 17, 2, 37, 4, "screen3", &isale_m, NULL, 2, &p_isale };

SETPOS financial =
  { 4, 17, 3, 37, 3, "screen3", &finan_m, NULL, 2, &p_finan };

SETPOS item_stock =
  { 5, 17, 4, 37, 4, "screen3", &stock_m, NULL, 2, &p_istock };

SETPOS item_profit =
  { 5, 17, 5, 37, 4, "screen3", &profit_m, NULL, 2, &p_profit };

SETPOS billsum_r =
  { 4, 17, 6, 37, 3, "screen3", &billsum_m, NULL, 2, &p_billsum };

SETPOS taxsum_r =
  { 4, 17, 7, 37, 3, "screen3", &taxsum_m, NULL, 2, &p_taxsum };

SETPOS general_r =
  { 6, 17, 8, 37, 5, "screen3", &general_m, NULL, 2, &p_general };

SETPOS cashman_r =
  { 4, 17, 9, 37, 3, "screen3", &cashman_m, NULL, 2, &p_cashman };

SETPOS waiter_r =
  { 4, 17, 10, 37, 3, "screen3", &waiter_m, NULL, 2, &p_waiter };

SETPOS sman_r = { 4, 17, 11, 37, 3, "screen3", &sman_m, NULL, 2, &p_isman };

SETPOS custmr_r =
  { 4, 17, 12, 37, 3, "screen3", &custmr_m, NULL, 2, &p_custmr };

SETPOS item_detail =
  { 5, 17, 13, 37, 4, "screen3", &idetail_m, NULL, 2, &p_idetail };

SETPOS reset_reps =
  { 4, 17, 14, 37, 3, "screen3", &reset_m, NULL, 2, &p_reset };

SETPOS *report_nxt[] = {
  &item_sale, &financial, &item_stock,
  &item_profit, &billsum_r, &taxsum_r,
  &general_r, &cashman_r, &waiter_r,
  &sman_r, &custmr_r, &item_detail,
  &reset_reps,
};

SETPOS report_spos =
  { 15, 17, 2, 19, 14, "screen1", &report_m, &report_nxt, 2 };

SETPOS prog_spos = { 19, 17, 1, 19, 18, "screen1", &prog_m, NULL, 1 };

SETPOS remove_spos = { 4, 17, 7, 19, 3, "screen1", &remove_m,
  NULL, 2, &p_rmdbase
};

SETPOS bill_spos = { 0, 0, 0, 0, 0, "screen1", NULL, NULL, 0 };

SETPOS *main_nxt[] = { &prog_spos, &report_spos, &bill_spos, NULL,
  NULL, NULL, &remove_spos
};

char *main_m[] = {
  " Set-Up Mode  >", " View Reports >", " Goto-Billing >",
  " Exit-Billing >", " Save Fl'py   >", " Restore Fl'py>",
  " Remove-Dbase >",
};

SETPOS main_spos = { 9, 17, 1, 1, 8, NULL, &main_m, &main_nxt, 0 };
