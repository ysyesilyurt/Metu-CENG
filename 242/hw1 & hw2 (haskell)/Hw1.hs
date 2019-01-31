module Hw1 where

data Cell = H | P | O | X deriving (Read,Show,Eq)
data Result = Fail | Caught (Int,Int) deriving (Read,Show,Eq)
data Direction = N | S | E | W deriving (Read,Show,Eq)

simulate :: [[Cell]] -> [(Direction, Direction)] -> Result
-- DO NOT CHANGE ABOVE THIS LINE, WRITE YOUR CODE BELOW --

--handles simulation
simulate grid dirtpl = hey grid dirtpl 0 (actnum dirtpl)
 
--recursively checks the lists of actions one by one
hey :: [[Cell]] -> [(Direction, Direction)] -> Int -> Int -> Result
hey _ _ seed actnum 
		| seed == actnum = Fail
hey grid dirtpllst seed actnum
		| (reverse (hwhathappens grid dirtpllst [] (hlocation grid)))!!seed == (reverse (pwhathappens grid dirtpllst [] (plocation grid)))!!seed = Caught ((reverse (pwhathappens grid dirtpllst [] (plocation grid)))!!seed)
		| otherwise = hey grid dirtpllst (seed + 1) actnum
 
--maximum action number
actnum :: [(Direction,Direction)] -> Int
actnum tpls = length tpls

--returns a list of hunter's all actions
hwhathappens :: [[Cell]] -> [(Direction,Direction)] -> [(Int,Int)] -> (Int,Int) -> [(Int,Int)]
hwhathappens _ [] newlst _ = newlst
hwhathappens grid (x:tpllstrest) newlst loc 
		|	hactionsus grid (fst x) loc == 0 = hwhathappens grid tpllstrest (loc:newlst) loc
		|	fst x == N = hwhathappens grid tpllstrest ((fst loc, snd loc - 1):newlst) (fst loc, snd loc - 1)
		|	fst x == S = hwhathappens grid tpllstrest ((fst loc, snd loc + 1):newlst) (fst loc, snd loc + 1)
		|	fst x == W = hwhathappens grid tpllstrest ((fst loc - 1, snd loc):newlst) (fst loc - 1, snd loc)
		|	fst x == E = hwhathappens grid tpllstrest ((fst loc + 1, snd loc):newlst) (fst loc + 1, snd loc)

--returns a list of prey's all actions
pwhathappens :: [[Cell]] -> [(Direction,Direction)] -> [(Int,Int)] -> (Int,Int) -> [(Int,Int)]
pwhathappens _ [] newlst _ = newlst
pwhathappens grid (x:tpllstrest) newlst loc 
		|	pactionsus grid (snd x) loc == 0 = pwhathappens grid tpllstrest (loc:newlst) loc
		|	snd x == N = pwhathappens grid tpllstrest ((fst loc, snd loc - 1):newlst) (fst loc, snd loc - 1)
		|	snd x == S = pwhathappens grid tpllstrest ((fst loc, snd loc + 1):newlst) (fst loc, snd loc + 1)
		|	snd x == W = pwhathappens grid tpllstrest ((fst loc - 1, snd loc):newlst) (fst loc - 1, snd loc)
		|	snd x == E = pwhathappens grid tpllstrest ((fst loc + 1, snd loc):newlst) (fst loc + 1, snd loc)

--returns row/column number of grid
rownum grid = (length grid) - 1
columnum grid = (length (grid!!0)) - 1

--actionsus returns 0 or 1 according to restrictions
hactionsus ::[[Cell]] -> Direction -> (Int,Int) -> Int
hactionsus grid direksion location
		|  direksion == N = if snd location == 0 || (grid!!(snd location - 1))!!(fst location) == X
								then 0
								else 1 
		|  direksion == S = if snd location == rownum grid || (grid!!(snd location + 1))!!(fst location) == X
								then 0
								else 1
		|  direksion == W = if fst location == 0 || (grid!!(snd location))!!(fst location - 1) == X
								then 0				
			 					else 1
		|  direksion == E = if fst location == columnum grid || (grid!!(snd location))!!(fst location + 1) == X
								then 0
								else 1

pactionsus ::[[Cell]] -> Direction -> (Int,Int) -> Int
pactionsus grid direksion location
		|  direksion == N = if snd location == 0 || (grid!!(snd location - 1))!!(fst location) == X
								then 0
								else 1 
		|  direksion == S = if snd location == rownum grid || (grid!!(snd location + 1))!!(fst location) == X
								then 0
								else 1
		|  direksion == W = if fst location == 0 || (grid!!(snd location))!!(fst location - 1) == X
								then 0				
			 					else 1
		|  direksion == E = if fst location == columnum grid || (grid!!(snd location))!!(fst location + 1) == X
								then 0
								else 1

--locations of hunter and prey, respectively (column, row)
hlocation grid = (hcolumnum (grid!!(hrownum grid 0)) 0 , hrownum grid 0)
plocation grid = (pcolumnum (grid!!(prownum grid 0)) 0 , prownum grid 0)

--Utility functions for hlocation/plocation
hrownum :: [[Cell]] -> Int -> Int
hrownum grid seed = if elem H (grid!!seed) then seed
										   else hrownum grid (seed + 1)
prownum :: [[Cell]] -> Int -> Int
prownum grid seed = if elem P (grid!!seed) then seed
										   else prownum grid (seed + 1)
hcolumnum :: [Cell] -> Int -> Int
hcolumnum row seed = if H == row!!seed then seed
									   else hcolumnum row (seed + 1)
pcolumnum :: [Cell] -> Int -> Int
pcolumnum row seed = if P == row!!seed then seed
									   else pcolumnum row (seed + 1)		
