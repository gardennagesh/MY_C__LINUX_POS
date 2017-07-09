		/* prog.h - global & templates for prog.c */
# undef EXTERN
# ifdef PROG_DECLARES
#	define EXTERN
# else
#	define EXTERN extern
# endif

typedef struct _item {
		float open_stock;
		float stock_in;
		float stock_out;
		float today_sale_qty;
		float curr_stock;
		char item_code [6];
		char item_name [17];
		char sell_price [9];
		char cost_price [9];
		char mrp [9];
		char hkey [3];
		char dept_link [4];
		char tax_link [3];
		char fneg_stock [3];
		char fqty_dec [3];
		char kit_link [3];
		char item_disc [3];
		char unit [5];
		char valid;
	}	ITEM;

typedef struct _dept {
	char dept_code [4];
	char dept_name [17];
	char tax_link [2];
	char	valid;
	} DEPT;

typedef struct _head {
	char 	sect[3];
	char line1[21];
	char line2[21];
	char line3[21];
	char line4[21];
	char line5[21];
	char	dw1[3];
	char	dw2[3];
	char	dw3[3];
	char	dw4[3];
	char	dw5[3];
	char	valid;
	} HEAD;

typedef struct _foot {
	char 	sect[3];
	char line1[21];
	char line2[21];
	char	dw1[3];
	char	dw2[3];
	char	valid;
	} FOOT;

typedef struct _tax {
	char	tax_no [3];
	char tname[17];
	char tamt [7];
	char toname [17];
	char toamt [7];
	char	valid;
	} TAX;

typedef struct _oprtion {
	char fswprint [3];
	char fsmall [3];
	char fnormal[3];
	char fmisc_amt [3];
	char frepprint [3];
	char frepdate [3];
	char fauto [3];
	char fsoft [3];
	} OPRTION;

typedef struct _kitchen {
	char kitno [5];
	char kitname [17];
	char	valid;
	} KITCHEN;

typedef struct _waiter {
	char wtrno [4];
	char wtrname [11];
	char wtrcomison [5];
	char	valid;
	} WAITER;

typedef struct _sman {
	char smanno [4];
	char smaname [11];
	char scomison [5];
	char	valid;
	} SMAN;

typedef struct _billfmt {
	char fitemcode [3];
	char ftax [3];
	char fdate [3];
	char ftime [3];
	char fahed [3];
	char fwidth [3];
} BILLFMT;

typedef struct _passwd {
		char oldpasswd [11];
		char newpasswd [11];
		char retpasswd [11];
} PPASSWD;

typedef struct _cust_bills {
		int bilno;
		long amt;
		char date [10];
} CUST_BILLS;

typedef struct _customer {
	char custno[4];
	char custname [21];
	char phno [10];
	char mobile [15];
	char dlno [15];
	char adds1 [26];
	char adds2 [26];
	CUST_BILLS cust_bills [50];
	char	valid;
} CUSTOMER;

typedef struct _kot_no{
	char kotno [6];
} KOTNO;

typedef struct _bill_no{
	char sectno [3];
	char billno [7];
	char valid;
} BILLNO;

typedef struct _cr_lines{
	char plines [4];
} PLINES;

typedef struct _daytime {
	char refno [5];
} REFUNDNO;

typedef struct _miscamt {
	char mtext1 [12];	
	char mtext2 [12];	
	char mtext3 [12];	
	char mtext4 [12];	
	char mamt1	[8]; 
	char mamt2 	[8];
	char mamt3 	[8]; 
	char mamt4 	[8];
	char mper1 	[7];
	char mper2 	[7];
	char mper3 	[7];
	char mper4 	[7];
	char mvalid1 [3];
	char mvalid2 [3];
	char mvalid3 [3];
	char mvalid4 [3];
	char math1 [3];
	char math2 [3];
	char math3 [3];
	char math4 [3];
} MISC;

EXTERN TAX 				tax;
EXTERN ITEM 			item;
EXTERN DEPT 			dept;
EXTERN HEAD 			head;
EXTERN FOOT 			foot;
EXTERN MISC 			misc;
EXTERN SMAN				sman;
EXTERN KOTNO 			kotno;
EXTERN WAITER 		waiter;
EXTERN PLINES 		plines;
EXTERN BILLNO 		billno;
EXTERN OPRTION 		oprtion;
EXTERN BILLFMT 		billfmt;
EXTERN PPASSWD 		ppasswd;
EXTERN REFUNDNO 	refno;
EXTERN KITCHEN 		kitchen;
EXTERN CUSTOMER 	customer;


