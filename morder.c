/* KITCHER ORDER TOKEN menus initialization */

BOX_INFO kot_print_box = {
  5, 43, 6, 2, NULL
};

FIELD kot_print_flds[] = {

  {"   OK   ", 3, 6, yeskot_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 3, 30, nokot_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU kot_print_menu = {
  1, &kot_print_box, " You Want Print Kot ",
  &kot_print_flds, "kotscreen", NULL, 1, 14
};

BOX_INFO kot_exit_box = {
  5, 43, 6, 2, NULL
};

FIELD kot_exit_flds[] = {

  {" CANCEL ", 3, 6, kotexitno_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

  {"   OK   ", 3, 30, kotexit_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

};

PMENU kot_exit_menu = {
  1, &kot_exit_box, " You Want Exit Kot Menu ",
  &kot_exit_flds, "kotscreen", NULL, 1, 14
};

BOX_INFO bill_tbl_box = {
  5, 33, 6, 46, NULL
};

FIELD bill_tbl_flds[] = {

  {"   OK   ", 3, 2, yeskot_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 3, 23, nokot_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU bill_tbl_menu = {
  1, &bill_tbl_box, " You Want Bill Table ",
  &bill_tbl_flds, "kotscreen", NULL, 1, 14
};

BOX_INFO xfer_box = {
  7, 43, 6, 2, NULL
};

FIELD xfer_flds[] = {

  {" From Tbl:", 3, 2, NULL, NULL, 4 + 2,
   A_NORMAL, DISP, from_tbl, 0},

  {" To Tbl:", 3, 25, xfer_do_ok, NULL, 4 + 2,
   A_NORMAL, DIGIT, to_tbl, 0},

  {"   OK   ", 5, 4, xfer_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 5, 30, xfer_cancel_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU xfer_menu = {
  3, &xfer_box, " Table Transfer Menu ", &xfer_flds, "kotscreen", xfer_init,
    1, 14
};


BOX_INFO del_kot_box = {
  5, 43, 6, 2, NULL
};

FIELD del_kot_flds[] = {

  {"   OK   ", 3, 6, yeskot_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 3, 30, nokot_do_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU del_kot_menu = {
  1, &kot_print_box, " Print Kot Canceled Items ",
  &kot_print_flds, "kotscreen", NULL, 1, 14
};

BOX_INFO instrn_box = {
  9, 43, 6, 2, NULL
};

FIELD instrn_flds[] = {

  {" Instruction1 :", 3, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALNUM, dsave_buf, 0},

  {" Instruction2 :", 5, 2, NULL, NULL, 20 + 2,
   A_NORMAL, ALNUM, tsave_buf, 0},

  {"   OK   ", 7, 4, instrn_do_ok, NULL, 0,
   A_NORMAL, ACTION, &ok, 0},

  {" CANCEL ", 7, 30, instrn_cancel_ok, NULL, 0,
   A_NORMAL, ACTION, &cancel, 0},

};

PMENU instrn_menu = {
  3, &instrn_box, " Customer Instruction ", &instrn_flds, "kotscreen", NULL,
    1, 14
};
