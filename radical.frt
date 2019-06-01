include /home/macav/forthress_fun/is_prime.frt

( num -- rad )
: radical
    1 1 rot		( p c n )   ( )
    >r			( p c )	    ( n )
    repeat		( p c )	    ( n )
	1 +		( p c+=1 )  ( n )
	r@		( p c n )   ( n )
	swap		( p n c )   ( n )
	dup		( p n c c ) ( n )
	>r		( p n c )   ( n c )
	%		( p n%c )   ( n c )
	0 =		( p 0/1 )   ( n c )
	if		( p )	    ( n c )
	    r@		( p c )	    ( n c )
	    is_prime	( p 0/1 )   ( n c )
	    if		( p )	    ( n c ) 
		r@	( p c )	    ( n c )
		*	( p*=c )    ( n c )
	    then
	then		( p )	    ( n c )
	    r>		( p c )	    ( n )
	    dup		( p c c )   ( n )
	    r@		( p c c n)  ( n )
    >  until		( p c )	    ( n )
    drop  r> drop	( p )	    ( )	  
;

