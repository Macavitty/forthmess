( adr0, adr1 -- adr2 )
: concat
  dup	( a0 a1 a1 )
  count ( a0 a1 l1 )
  rot 	( a1 l1 a0 )
  dup 	( a1 l1 a0 a0 )
  count	( a1 l1 a0 l0 )
  rot	( a1 a0 l0 l1 )
  dup	( a1 a0 l0 l1 l1 )
  rot	( a1 a0 l1 l1 l0 )
  +	       ( a1 a0 l1 l1+l0=l2)
  heap-alloc   ( a1 a0 l1 a2 )
  >r 	       ( a1 a0 l1 )
  rot	       ( a0 l1 a1 )
  dup	       ( a0 l1 a1 a1 )
  r>	       ( a0 l1 a1 a1 a2 )
  dup	       ( a0 l1 a1 a1 a2 a2 )
  rot 	       ( a0 l1 a1 a2 a2 a1 )
  string-copy  ( a0 l1 a1 a2 )
  swap	       ( a0 l1 a2 a1 )
  heap-free    ( a0 l1 a2 )
  dup	       ( a0 l1 a2 a2 )
  rot	       ( a0 a2 a2 l1 )
  + 	       ( a0 a2 a2+l1 )
  rot 	       ( a2 a2+l1 a0 )
  dup	       ( a2 a2+l1 a0 a0 )
  rot	       ( a2 a0 a0 a2+l1 )
  swap	       ( a2 a0 a2+l1 a0 )
  string-copy  ( a2 a0 )
  heap-free    ( a2 )
;
