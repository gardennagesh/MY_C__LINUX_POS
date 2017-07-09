/********************* menu.h - menu drawing structures ********************/

# define NMONO
# undef EXTERN
# ifdef MENU_DEFINED
#	define EXTERN
# else
#	define EXTERN extern
# endif

#define rgb(x) COLOR_PAIR(x)
/******* DONT CHANGE ORDER OF STRUCT MEMBERS******************************/
 typedef struct {
	int r, c, x, y;
	WINDOW * w;
 } BOX_INFO;

/******* DONT CHANGE ORDER OF STRUCT MEMBERS******************************/
 typedef struct {
	char *fname;
	int x; int y;
	int (*pfn) (void *); 
	int (*pfnt) (void *);
	int datalen; 
	int attr;
	char type; 
	char * datad;
	char action;
	void *myself;  
 } FIELD;

/******* DONT CHANGE ORDER OF STRUCT MEMBERS********************************/
 typedef struct _prog {
	int flds; /* imp->keep a less than no. of the flds */
	BOX_INFO *bp;
	char *title;
	FIELD (*pf)[];
	char *menu;
	int (*pok) (struct _prog *);   
	char clear_scr;
	char clr;
 } PMENU;

/******* DONT CHANGE ORDER OF STRUCT MEMBERS******************************/
typedef struct setpos {
		int r;
		int c;	
		int x;
		int y;
		int pos;  /* no. of fields, keep a more than actual */
		char *ascreen;
		char *(*pp)[];
		struct setpos* (*nxt) [];
		char tmenu;
		PMENU* (*gmenu)[];
} SETPOS;

extern PMENU *prog_menu [];
/* char *(*pp)[]; */

EXTERN char dsave_buf[80];
EXTERN char tsave_buf[40];
EXTERN char dummy_buf;
EXTERN char ok;
EXTERN char del;
EXTERN char next;
EXTERN char cancel;
EXTERN char loginp[30];
EXTERN char passp [30];
EXTERN char key [16]; 
