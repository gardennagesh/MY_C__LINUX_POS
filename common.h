/*********** dbase-fuction prototypes declared here in  common.h ********/

# undef EXTERN
# ifdef COMMON_DECLARES
#	define EXTERN
# else
#	define EXTERN extern
# endif

/* # define MONO */ /* For BLACK AND WHITE */

# define PRICE_ACT 		0
# define QTY_ACT 			1 
# define PIECE_ACT 		2

# define RIGHT_SIDE 	0
# define LEFT_SIDE  	1
# define MIDDLE				2

# define REGULAR 			0
# define REFUND				1
# define SETTLE				2
# define DUPLICATE		3

#		define ONLINE 				223
#		define PAPER_OUT			103
#		define OUT_OF_ORDER		-1	

# define DPRICE				0
# define DQTY					1
# define DPIECE				2
# define DDISC				3

# define RET_LOGOUT 0
# define RET_OK 		1
# define RET_CANCEL 2
# define RET_DELETE 3
# define RET_NEXT 	4
# define RET_STAY 	6
# define RET_LOGIN 	5
# define RET_ESC		7
# define RET_PRIV		8

# define MAX_ITEMS 			6000	
# define MAX_KITCHENS 	5
# define MAX_CASHMAN 		5
# define MAX_CUSTOMERS	5
# define MAX_CASHMANS		5
# define MAX_WAITERS 		5
# define MAX_SMANS			5
# define MAX_TAXES 			3
# define MAX_STORES 		3
# define MAX_HEADS 			3
# define MAX_FOOTS 			3
# define MAX_BILLNOS 		3

typedef struct _cashman {
	char cmanno [3];
	char cname [12];
	char cpasswd [12];
	char commision [6];
	char prefund [3];
	char precall [3];
	char pfresh [3];
	char preset [3];
	char pmanualreset [3];
	char ppricee [3];
	char powner [3];
	char pprog [3];
	char preport [3];
	char	valid;
} CASHMAN;

typedef struct _wtable {
	int tbl;
	int wtr;
	double amt;
	char time [10];
	char valid;
} WTABLE;

typedef struct _kot {
	int tbl;
	int wtr;
	float qty;
	float cancel_qty;
	float sell_price;
	float per_disc;
	char code[5];
	char item_name [17];
	char valid;
} KOT_ITEM;

typedef struct _billitem {
	double	item_amt;
	long 		bill_no;
	int 		item_code; 
	float		price;
	float 	disc_amt;
	float 	qty;
	float 	pieces;
	float 	tax_amt;
	float 	taxon_amt;
	float 	per_disc;
	float 	per_tax;
	float 	per_taxon;
	char 		date [10];
	char 		item_name[18];
	char 		stricode[6];
	char 		dept_link[4];
	char 		tax_link [2];
	char 		unit[3];
	char 		tax_flag;
	char 		disc_flag;
	char 		pieces_flag;
	char 		sect;
	char 		valid;
} BILL_ITEM;

typedef struct _bill_detail {
		int 		no_of_items;
		long 		bill_no;
		float		dpercent;
		float		serv_cent;
		double 	bill_payble;
		double 	bill_total;
		double 	bill_tax;
		double 	bill_tax1;
		double 	bill_tax2;
		double 	bill_tax3;
		double 	bill_tax4;
		double 	bill_taxon;
		double 	bill_taxon1;
		double 	bill_taxon2;
		double 	bill_taxon3;
		double 	bill_taxon4;
		double 	bill_perdamt;
		double 	bill_amtdisc;
		double 	bill_pmisc;
		double 	bill_nmisc;
		double 	bill_serv;
		double 	credit_amt;
		double 	cash_amt;
		double 	card_amt;
		double 	chq_amt;
		short 	cashman_no;
		short 	wtr_no;
		short 	sman_no;
		short 	sect_no;
		short		table;
		char 		date[10];
		char 		time[10];
		char 		bill_type;
		char 		bill_status;
		char 		valid;
} BILL_DETAIL;

typedef struct _chq {
			long bill_no;
			double chq_amt;
			char chq_no [8];
			char bank_name [12];
			char date [10];
			char time [10];
			char cust_name [30];
			char sect_no;
			char	valid;
} CHQ_DETAIL;

typedef struct _card {
			long bill_no;
			double card_amt;
			char card_no [20];
			char card_name [12];
			char date [10];
			char time [10];
			char cust_name [30];
			char sect_no;
			char 		valid;
} CARD_DETAIL;

typedef struct _credit {
			long bill_no;
			int cust_no;
			double credit_amt;
			char date [10];
			char time [10];
			char sect_no;
			char 		valid;
} CREDIT_DETAIL;

WINDOW *wtime;
WINDOW *gwind;
EXTERN int owner;
EXTERN int gcashman_no;

EXTERN FILE *fp1;
EXTERN FILE *disp_file;
EXTERN FILE *help_file;
EXTERN FILE *print_file;
EXTERN FILE *table_file;
EXTERN FILE *kot_file;
EXTERN FILE *billitem_file;
EXTERN FILE *bills_file;
EXTERN FILE *chq_file;
EXTERN FILE *card_file;
EXTERN FILE *credit_file;
EXTERN FILE *plines_file;
EXTERN FILE *refno_file;
EXTERN FILE *billno_file;
EXTERN FILE *kotno_file;
EXTERN FILE *paswd_file;
EXTERN FILE *option_file;
EXTERN FILE *billfmt_file;
EXTERN FILE *misc_file;
EXTERN FILE *item_file;
EXTERN FILE *kit_file;
EXTERN FILE *dept_file;
EXTERN FILE *tax_file;
EXTERN FILE *head_file;
EXTERN FILE *foot_file;
EXTERN FILE *customer_file;
EXTERN FILE *cashman_file;
EXTERN FILE *waiter_file;
EXTERN FILE *sman_file;

EXTERN long billno_count;
EXTERN long item_count;
EXTERN int repays;
EXTERN int 	sman_count;
EXTERN int 	rep_line;
EXTERN int 	kstate;
EXTERN int 	kit_count;
EXTERN int 	tax_count;
EXTERN int 	dept_count;
EXTERN int 	head_count;
EXTERN int 	foot_count;
EXTERN int 	waiter_count;
EXTERN int 	customer_count;
EXTERN int 	cashman_count;
EXTERN int 	gxx;
EXTERN int 	printer_on;
EXTERN int 	gyy;
EXTERN char	kot_kho;
EXTERN char kcash1 [20];
EXTERN char apaid1 [20];
EXTERN char	bl_cashman [12];
EXTERN char	bl_date [10];
EXTERN char	bl_time [10];
EXTERN char	bla_date [10];
EXTERN char	bla_time [10];
EXTERN char	start_date [10];
EXTERN char	end_date [10];
EXTERN char	rep_buf [3];
EXTERN char	sect_buf [3];
EXTERN char	store_buf [4];
EXTERN char	code_buf [6];
EXTERN FIELD (*pfield) [];
EXTERN BOX_INFO tbox;
EXTERN PMENU tmenu;
EXTERN CASHMAN 		cashman;

void disp_date_time_bill (int ); 
void disp_date_time_comn (int );

int instrn_do_ok (void *);
int instrn_cancel_ok (void *);
int xfer_do_ok (void *);
int xfer_cancel_ok (void *);
int profit_do_ok (void *);
int reset_do_ok (void *);
int reset_cancel_ok (void *);
int custmr_do_ok (void *);
int billsum_do_ok (void *);
int general_do_ok (void *);
int taxsum_do_ok (void *);
int finan_do_ok (void *);
int istock_do_ok (void *);
int icashman_do_ok (void *);
int iwaiter_do_ok (void *);
int isales_do_ok (void *);
int idetail_do_ok (void *);
int detail_jump (void *);
int reset_jump (void *);
int custmr_jump (void *);
int finan_sect_jump (void *);
int finan_date_jump (void *);
int general_sect_jump (void *);
int general_date_jump (void *);
int billsum_sect_jump (void *);
int billsum_date_jump (void *);
int taxsum_sect_jump (void *);
int taxsum_date_jump (void *);
int cashman_date_jump (void *);
int waiter_date_jump (void *);
int isman_date_jump (void *);
int stock_jump (void *);
int sect_jump (void *);
int start_jump(void *);
int end_jump(void *);

int kotexit_do_ok (void *);
int kotexitno_do_ok (void *);
int yeskot_do_ok (void *);
int nokot_do_ok (void *);
int yesexit_do_ok (void *);
int noexit_do_ok (void *);
int plines_do_ok (void *);
int refno_do_ok (void *);
int billno_do_ok (void *);
int kotno_do_ok (void *);
int paswd_do_ok (void *);
int option_do_ok (void *);
int misc_do_ok (void *);
int billfmt_do_ok (void *);
int item_do_ok (void *);
int login_do_ok (void *);
int login_exit_ok (void *);
int login_shut_ok (void *);
int common_do_cancel (void *);
int common_do_ok (void *);
int save_do_ok (void *);
int restore_do_ok (void *);
int cancel_do_ok (void *);
int kit_do_ok (void *);
int dept_do_ok (void *);
int tax_do_ok (void *);
int head_do_ok (void *);
int foot_do_ok (void *);
int waiter_do_ok (void *);
int sman_do_ok (void *);
int isman_do_ok (void *);
int customer_do_ok (void *);
int cashman_do_ok (void *);
int bank_do_ok (void *);

int xfer_init (PMENU *);
int reset_init (PMENU *);
int custmr_init (PMENU *);
int cashman_init (PMENU *);
int waiter_init (PMENU *);
int sman_init (PMENU *);
int isman_init (PMENU *);
int billsum_init (PMENU *);
int general_init (PMENU *);
int taxsum_init (PMENU *);
int finan_init (PMENU *);
int isale_init (PMENU *);
int detail_init (PMENU *);
int istock_init (PMENU *);
int plines_init (PMENU *);
int refno_init (PMENU *);
int kotno_init (PMENU *);
int option_init (PMENU *);
int billfmt_init (PMENU *);
int misc_init (PMENU *);
int item_init (PMENU *);
int login_init (PMENU *);
int save_init( PMENU *);
int bank_init (PMENU *);

int dept_next_do_ok (void *); 
int item_next_do_ok (void *); 
int tax_next_do_ok (void *); 
int kit_next_do_ok (void *); 
int head_next_do_ok (void *); 
int foot_next_do_ok (void *); 
int waiter_next_do_ok (void *); 
int sman_next_do_ok (void *); 
int customer_next_do_ok (void *); 
int cashman_next_do_ok (void *); 

int dept_delete_do_ok (void *); 
int kit_delete_do_ok (void *); 
int tax_delete_do_ok (void *); 
int item_delete_do_ok (void *); 
int head_delete_do_ok (void *); 
int foot_delete_do_ok (void *); 
int waiter_delete_do_ok (void *); 
int sman_delete_do_ok (void *); 
int customer_delete_do_ok (void *); 
int cashman_delete_do_ok (void *); 

int swprint_jump (void *);
int billno_unselect (void *);
int item_code_unselect (void *);
int kit_no_unselect (void *); 
int tax_no_unselect (void *); 
int dept_no_unselect (void *); 
int head_no_unselect (void *); 
int foot_no_unselect (void *); 
int waiter_no_unselect (void *); 
int sman_no_unselect (void *); 
int customer_no_unselect (void *); 
int cashman_no_unselect (void *); 

int set_pos (SETPOS *);
int set_error (char *err); 
int check_ch (int, int, int); 
int draw_menu (PMENU *); 
int refresh_menu (PMENU *, int, char, char); 
int open_all_files (int);
void billing (void); 

