( num -- 0/1 )
: is_prime			    ( n )	    ( )
    dup 2 <			    ( n 1/0 )	    ( )
    if drop 0			    ( 0 )	    ( )
    else			    ( n )	    ( )
	dup 4 <			    ( n 0/1 )	    ( )
	if drop 1		    ( 1 )	    ( )		
	else			    ( n )	    ( )
	   dup 2 % not		    ( n 1/0 )	    ( )
	    if drop 0		    ( 0 )	    ( )
	    else		    ( n )	    ( )
		dup 3 >r	    ( n n )	    ( i )
		repeat
		    drop dup r@	    ( n n i )	    ( i )
		    % 0 =	    ( n 0/1 )	    ( i )
		    if 0	    ( n 0 )	    ( i )
		    else	    ( n )	    ( i )
			dup r@	    ( n n i )	    ( i )
			dup *	    ( n n i^2 )	    ( i )
			< if 1	    ( n 1 )	    ( i )
			else -1	    ( n -1 )	    ( i )
			then		
			r> 2 +	    ( n 1/-1 i+2 )  (  )
			>r	    ( n 1/-1 )	    ( i )
		    then	    ( n 0/1/-1 )    ( i )
		    dup -1 = not    ( n 0/1/-1 1/0 )( i )
		until		    ( n 0/1 )	    ( i )
		r> drop		    ( n 0/1 )	    ( )
		swap drop	    ( 0/1 )	    ( )
	    then
	then
    then
;
	
