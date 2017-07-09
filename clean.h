	start_color ();
#	ifdef MONO
	init_pair (1, 7, 0);
	init_pair (2, 0, 7);
	init_pair (3, 0, 7);
	init_pair (4, 0, 7);
	init_pair (5, 7, 0);
	init_pair (6, 7, 0);
	init_pair (7, 0, 7);
	init_pair (11, 0, 7);
#	else
	init_pair (2, 4, 6);
	init_pair (1, 6, 4);
	init_pair (3, 7, 1);
	init_pair (4, 7, 5);
	init_pair (5, 4, 0);
	init_pair (6, 7, 4);
	init_pair (7, 0, 6);
	init_pair (8, 6, 0);
	init_pair (9, 0, 7);
	init_pair (10, 3, 0);
	init_pair (11, 0, 2);
	init_pair (12, 5, 0);
	init_pair (13, 7, 0);
	init_pair (14, 6, 0);
	init_pair (15, 7, 4);
	init_pair (16, 1, 0);
	init_pair (17, 3, 4);
	init_pair (18, 1, 4);
	init_pair (19, 4, 4);
	init_pair (20, 3, 4);
	init_pair (21, 1, 6);
	init_pair (22, 4, 6);
	init_pair (23, 5, 6);
	init_pair (24, 0, 6);
#	endif
	ESCDELAY = 1;
