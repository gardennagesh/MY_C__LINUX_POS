/*****************Global Vars for bill process are declared in bill.h**********/

# undef EXTERN
# ifdef BILL_DECLARES
#	define EXTERN
# else
#	define EXTERN extern
# endif
/* NOTE : Following is VIP */
/* keep a > required, & must > no_of_items fit in scroll box */
# define MAX_BILL_ITEMS 500+1 
/* keep a > required, & must > no_of_items fit in scroll box*/
# define MAX_MATCH 			100+1 
/* keep a > required, & must > no_of_items fit in scroll box*/
# define MAX_KOT_ITEMS 			100+1 

typedef struct _tlist {
		int tbl;
		int wtr;
}TLIST;

#		ifdef	BILL_DECLARES
typedef struct _print_bill {
char 	cash_amt [16];
char 	card_amt [16];
char 	chq_amt [16];
char 	credit_amt [16];
char 	bank_name [16];
char 	card_no [20];	
char 	card_name [12];
char 	cust_no [4];
char 	chq_no [8];
char 	cust_name [22];
char 	payble [16];
char 	paid [16];
char 	change [16];
char 	balance [16];
} PRINT_BILL;
#	endif
int cash_init (PMENU *);
int card_init (PMENU *);
int credit_init (PMENU *);
int chq_init (PMENU *);
int bill_print_init (PMENU *);
int cust_no_jump (void *);
int jump_cash (void *);
int jump_card (void *);
int jump_credit (void *);
int jump_chq (void *);
int stock_code_jump (void *);
int stock_in_jump (void *);
int stock_out_jump (void *);
int commit_do_ok (void *);
int stock_do_ok (void *);
int stockexit_do_ok (void *);
int cash_do_ok (void *);
int credit_do_ok (void *);
int card_do_ok (void *);
int chq_do_ok (void *);
int calc_over_flow (float data, char flag); 
void put_accurate (char *, char); 
//void format_string (char (*)[][75], char , char, char *);
void format_string (char (*)[][80], char , char, char *);
void kot_string (char (*)[][60], char , char, char *);
int to_item_list_look ( ITEM *); 
int kot_item_entry (char * ); 

char 	select_buf [10];
char	bl_section [2];
char	bl_billno [6];
char	bl_wtr [3];
char	bl_tbl [5];
char 	*gptr;
char 	stat_cur_pos;
char 	select_flag;
char 	yes_move;
char 	commit_ok;
char 	set_help;
char 	stock_ok;
char 	cash_ok;
char 	card_ok;
char 	credit_ok;
char 	chq_ok;
char 	card_used;
char 	cash_used;
char 	credit_used;
char 	chq_used;
char 	misc_no;
char 	set_ok_flag;
char 	misc1_per_exist;
char 	misc2_per_exist;
char 	misc3_per_exist;
char 	misc4_per_exist;
char 	misc1_amt_exist;
char 	misc2_amt_exist;
char 	misc3_amt_exist;
char 	misc4_amt_exist;
char 	tax1_exist;
char 	tax2_exist;
char 	tax3_exist;
char 	tax4_exist;
char 	tax1_name [20];
char 	taxon1_name [10];
char 	tax2_name [20];
char 	taxon2_name [10];
char 	tax3_name [20];
char 	taxon3_name [10];
char 	tax4_name [20];
char 	taxon4_name [10];
char 	sect_str [4];
char 	from_tbl [6];
char 	to_tbl [6];

char	 gchq_no	[10];
char	 gcard_no	[20];
char	 gcust_name [22];
char	 gcard_name [22];
char	 gbank_name [12];
char	 name_buf [16];
char	 stock_curr [10];
char	 stock_in [10];
char	 stock_out [10];



EXTERN WINDOW *w, *w1, *w2; 
EXTERN WINDOW *w4, *w5, *w6; 
EXTERN WINDOW *w7, *w8, *w9, *wk4;
EXTERN WINDOW *wk5, *wk6, *wk7;
EXTERN int kcase; 
EXTERN int adjust_flag; 
EXTERN int no_of_items; 
EXTERN int no_of_miscs; 
EXTERN int deleted_items; 
EXTERN int first_free_slot; 
EXTERN int cur_pos;
EXTERN int bill_tbl;
EXTERN int lno_of_items; 
EXTERN int	lcur_pos; 
EXTERN char display_set;
EXTERN int isearch;
EXTERN char sbuf[20];
EXTERN char search_box;
EXTERN char	override_flag;
EXTERN char qty_override;
EXTERN char price_override;
EXTERN char disc_override;
EXTERN char piece_override;
EXTERN char status_field [20];
#		ifdef	BILL_DECLARES
double paid_amt;
double balance_amt;
double change_amt;
double misc1_per;
double misc1_amt;
double misc2_per;
double misc2_amt;
double misc3_per;
double misc3_amt;
double misc4_per;
double misc4_amt;
double lmisc1_per;
double lmisc1_amt;
double lmisc2_per;
double lmisc2_amt;
double lmisc3_per;
double lmisc3_amt;
double lmisc4_per;
double lmisc4_amt;
#		endif
EXTERN char lbills[MAX_MATCH][75];
EXTERN KOT_ITEM xkot_item; 
#		ifdef	BILL_DECLARES
EXTERN char bills[MAX_BILL_ITEMS][80];
BILL_ITEM bill_item [MAX_BILL_ITEMS];
BILL_DETAIL bill_detail;
CARD_DETAIL card_detail;
CREDIT_DETAIL credit_detail;
CHQ_DETAIL chq_detail;
PRINT_BILL print_bill;
#		endif
