/* Login menu initialization structures */

BOX_INFO exit_box = {
  8, 53, 10, 12, NULL
};

FIELD exit_flds[] = {

  {"   You Want Exit Billing   ", 3, 13, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0},

  {" CANCEL ", 5, 11, common_do_cancel, NULL, 0, A_NORMAL, ACTION, &cancel,
   0},

  {"   OK   ", 5, 34, common_do_ok, NULL, 0, A_NORMAL, ACTION, &ok, 0},

};

PMENU exit_menu = {
  2, &exit_box, " LOG-OUT  MENU ", &exit_flds, NULL, NULL, 1, 6
};

BOX_INFO login_box = {
  10, 53, 4, 12, NULL
};

FIELD login_flds[] = {
  {" Login Name :", 3, 14, NULL, NULL, 10 + 2,
   A_NORMAL, ALPHA, loginp, 0},

  {" Password   :", 5, 14, NULL, NULL, 10 + 2,
   A_NORMAL, PASSWD, passp, 0},

  {" LOGIN ", 7, 2, login_do_ok, NULL, 0, A_NORMAL, ACTION, &ok, 0},

  {" EXIT ", 7, 11, login_exit_ok, NULL, 0, A_NORMAL, ACTION, &cancel, 0},

  {"login_passwd both is nagesh", 7, 19, NULL, NULL, 0, A_NORMAL, DISP,
   &cancel, 0},
};

PMENU login_menu = {
  4, &login_box, " Welcome ", &login_flds, NULL, login_init, 1, 6
};

BOX_INFO save_box = {
  8, 53, 10, 12, NULL
};

FIELD save_flds[] = {

  {" Save Present Status ", 1, 15, NULL, NULL, 0, A_NORMAL, DISP, &dummy_buf,
   0},

  {dsave_buf, 3, 9, NULL, NULL, 0, A_NORMAL, DISP, &dummy_buf, 0},

  {tsave_buf, 4, 9, NULL, NULL, 0, A_NORMAL, DISP, &dummy_buf, 0},

  {" CANCEL ", 6, 6, common_do_cancel, NULL, 0, A_NORMAL, ACTION, &cancel, 0},

  {"   OK   ", 6, 39, save_do_ok, NULL, 0, A_NORMAL, ACTION, &ok, 0},

};

PMENU save_menu = {
  4, &save_box, " ", &save_flds, NULL, save_init, 1, 6
};


BOX_INFO restore_box = {
  8, 53, 10, 12, NULL
};

FIELD restore_flds[] = {

  {" Restores USB Data To System ", 1, 11, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0},

  {" All Existing Data Will Overwrite ! ", 3, 9, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0},

  {" Do You Want To Proceed - ? ", 4, 13, NULL, NULL, 0,
   A_NORMAL, DISP, &dummy_buf, 0},

  {" CANCEL ", 6, 6, common_do_cancel, NULL, 0, A_NORMAL, ACTION, &cancel, 0},

  {"   OK   ", 6, 39, restore_do_ok, NULL, 0, A_NORMAL, ACTION, &ok, 0},

};

PMENU restore_menu = {
  4, &restore_box, " ", &restore_flds, NULL, NULL, 1, 18
};
