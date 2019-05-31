( num -- 0/1 )
: is_prime
	( n )
	dup 2 <
	( n, 1/0 )
	if drop 0 ( 0 ) 
	else
		( n )
		dup 4 <
		( n, 0/1 )
		if drop 1 ( 1 )
		else
			dup 2 % not
			if drop 0
			else
				( n )
				dup 5 >r repeat
				    drop
				    ( n ) 
				    dup r@ % 0 = 
				    if 0 
				    else
					dup r@
					( n, n, i )
					dup *
					( n, n, i*i)
					< if 1 else -1 then		
					( n, 0/1 )
					r> 2 + >r	
				    then
					dup -1 = not until
					( n, 0/1 )
					r> drop ( clearing adress stack)
					swap drop ( clearing data stack )
			then
		then
	then ;
	
