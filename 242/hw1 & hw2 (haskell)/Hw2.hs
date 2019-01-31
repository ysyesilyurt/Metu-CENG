module Hw2 where

import Data.List -- YOU MAY USE THIS MODULE FOR SORTING THE AGENTS

data Level = Newbie | Intermediate | Expert deriving (Enum, Eq, Ord, Show, Read)
data Hunter = Hunter {hID::Int, hlevel::Level, hEnergy::Int, hNumberOfCatches::Int, hActions::[Direction]} deriving (Eq, Show, Read)
data Prey = Prey {pID::Int, pEnergy::Int, pActions::[Direction]} deriving (Eq, Show, Read)
data Cell = O | X | H Hunter | P Prey | T deriving (Eq, Show, Read)
data Direction = N | S | E | W deriving (Eq, Show, Read)
type Coordinate = (Int, Int)
-- DO NOT CHANGE THE DEFINITIONS ABOVE. --


-- INSTANCES OF Ord FOR SORTING, UNCOMMENT AND COMPLETE THE IMPLEMENTATIONS --
instance Ord Hunter where
    compare hunter1 hunter2  
    	|	hlevel hunter1 > hlevel hunter2 = GT
    	|	hlevel hunter2 > hlevel hunter1 = LT
    	|	otherwise = if hEnergy hunter1 > hEnergy hunter2 
    						then GT
    						else if hEnergy hunter2 > hEnergy hunter1 
    							then LT
    						    else if hNumberOfCatches hunter1 > hNumberOfCatches hunter2
    						    	then GT
    					    	    else if hNumberOfCatches hunter2 > hNumberOfCatches hunter1 
    					    	    	then LT
    				    	    	    else if hID hunter1 < hID hunter2 
    				    	    	    	then GT
    				    	    	    	else LT
instance Ord Prey where
    compare prey1 prey2 
    		|	pEnergy prey1 > pEnergy prey2 = GT
    		|	pEnergy prey2 > pEnergy prey1 = LT
    		|	otherwise = if pID prey1 < pID prey2 
    							then GT
    						    else LT

-- WRITE THE REST OF YOUR CODE HERE --

simulate :: [[Cell]] -> ([(Hunter, Coordinate)], [(Prey, Coordinate)])
simulate grid = ((harrange (fst (get1 grid)) (snd (get1 grid)) []),(parrange (fst (get2 grid)) (snd (get2 grid)) []))

get1 grid = hng (fst (arrange_final grid (final_three_tuple grid) [] [])) [] []

get2 grid = hngp (snd (arrange_final grid (final_three_tuple grid) [] [])) [] []

harrange [] _ finalhlist = reverse finalhlist
harrange (h:remh) hloclist finalhlist = harrange remh hloclist ((hfind_pair hloclist h):finalhlist)

parrange [] _ finalplist = reverse finalplist
parrange (p:remp) ploclist finalplist = parrange remp ploclist ((pfind_pair ploclist p):finalplist)

hfind_pair (x:hloclist) h
		|	(fst x) == (hID h) = (h,(snd x))
		|	otherwise = hfind_pair hloclist h

pfind_pair (x:ploclist) p
		|	(fst x) == (pID p) = (p,(snd x))
		|	otherwise = pfind_pair ploclist p

hng [] hlist loclist = (reverse (sort hlist),loclist)
hng (h:remhlist) hlist loclist = hng remhlist ((fst h):hlist) ((hID (fst h),(snd h)):loclist)

hngp [] plist loclist = (sort plist,loclist)
hngp (p:remplist) plist loclist = hngp remplist ((fst p):plist) ((pID (fst p),(snd p)):loclist)

-- three_tuple = final_three_tuple
arrange_final grid three_tuple finalhlist finalplist = ((h_handle grid (fst (scnd three_tuple)) (snd (scnd three_tuple)) (fsst three_tuple) finalhlist),(p_handle grid (fst (thrd three_tuple)) (snd (thrd three_tuple)) finalplist))

-- utility functions for small fixes of final output
h_handle _ [] _ _ finalhlist = finalhlist
h_handle grid (hloc:remhloclist) (h:remhlist) index finalhlist
		|	index /= ((actnum grid 0) + 1) = h_handle grid remhloclist remhlist index (((layers h index),hloc):finalhlist)
		|	otherwise = h_handle grid remhloclist remhlist index (((layers h 0),hloc):finalhlist)

layers h index
		|	index == 0 = h {hActions = []}
		|	otherwise = let 
				  		   z = (hActions h)
				  		in h {hActions = (drop (index-1) z)}

p_handle _ [] _ finalplist = finalplist
p_handle grid (ploc:remploclist) (p:remplist) finalplist = p_handle grid remploclist remplist (((players p),ploc):finalplist)

players p = p {pActions = []}

-- gets 3 tuple from hey -> (index,hunters,preys)
final_three_tuple grid = (fsst (hey grid (fst (hLocationlist grid)) (snd (hLocationlist grid)) (fst (pLocationlist grid)) (snd (pLocationlist grid)) [] [] 0 0),last (scnd (hey grid (fst (hLocationlist grid)) (snd (hLocationlist grid)) (fst (pLocationlist grid)) (snd (pLocationlist grid)) [] [] 0 0)),last (thrd (hey grid (fst (hLocationlist grid)) (snd (hLocationlist grid)) (fst (pLocationlist grid)) (snd (pLocationlist grid)) [] [] 0 0)))

-- handles main part of simulation, returns (how many steps simulated,hlist with locs,plist with locs) for all times
hey grid _ _ _ _ newhlist newplist index _
		|	index == (actnum grid 0) + 1 = (index,reverse newhlist,reverse newplist) 	
hey grid hlist1 hlist2 plist1 plist2 newhlist newplist index flag
		|	flag == 1 = (index,reverse newhlist,reverse newplist) 
		|	plist1 == [] = hey grid (fst (hmoveOnce grid hlist1 hlist2 [] [] index)) (hcatchupdate (fst (simulate_catch (increment_timeforh grid hlist1 hlist2 index) (increment_timeforp grid plist1 plist2 index))) (snd (hmoveOnce grid hlist1 hlist2 [] [] index)) []) (fst (pcatchupdate (snd (simulate_catch (increment_timeforh grid hlist1 hlist2 index) (increment_timeforp grid plist1 plist2 index))) (fst (pmoveOnce grid plist1 plist2 [] [] index)) (snd (pmoveOnce grid plist1 plist2 [] [] index)) [] [])) (snd (pcatchupdate (snd (simulate_catch (increment_timeforh grid hlist1 hlist2 index) (increment_timeforp grid plist1 plist2 index))) (fst (pmoveOnce grid plist1 plist2 [] [] index)) (snd (pmoveOnce grid plist1 plist2 [] [] index)) [] [])) ((hlist1,hlist2):newhlist) ((plist1,plist2):newplist) (index + 1) 1
		|	otherwise = hey grid (fst (hmoveOnce grid hlist1 hlist2 [] [] index)) (hcatchupdate (fst (simulate_catch (increment_timeforh grid hlist1 hlist2 index) (increment_timeforp grid plist1 plist2 index))) (snd (hmoveOnce grid hlist1 hlist2 [] [] index)) []) (fst (pcatchupdate (snd (simulate_catch (increment_timeforh grid hlist1 hlist2 index) (increment_timeforp grid plist1 plist2 index))) (fst (pmoveOnce grid plist1 plist2 [] [] index)) (snd (pmoveOnce grid plist1 plist2 [] [] index)) [] [])) (snd (pcatchupdate (snd (simulate_catch (increment_timeforh grid hlist1 hlist2 index) (increment_timeforp grid plist1 plist2 index))) (fst (pmoveOnce grid plist1 plist2 [] [] index)) (snd (pmoveOnce grid plist1 plist2 [] [] index)) [] [])) ((hlist1,hlist2):newhlist) ((plist1,plist2):newplist) (index + 1) 0

-- utility functions for motion at time t
increment_timeforh grid loclist hlist index = hcriticlist (hmoveOnce grid loclist hlist [] [] index) [] [] 0
increment_timeforp grid loclist plist index = pcriticlist (pmoveOnce grid loclist plist [] [] index) [] [] 0

-- simulates catch at time t
simulate_catch tupleforh tupleforp = catch (sorthcritic tupleforh [] 0 0) (sortpcritic tupleforp [] 0 0) [] []

-- gets [((loc), hID, [])] [((loc), pID)] lists from sorthcritic and sortpcritic respectively
-- returns ([((loc), hID, [catched preys])],[iseaten]) 
catch [] _ newhlist iseaten = (reverse newhlist,reverse iseaten)
catch (h:resthlist) plist newhlist iseaten = catch resthlist plist (fst (checkconflicts h plist iseaten newhlist)) (snd (checkconflicts h plist iseaten newhlist)) 

-- utility function for catch
-- gets h plist iseaten []
-- returns (newhlist,iseaten) to catch
checkconflicts h [] iseaten newhlist = ((h:newhlist),iseaten)
checkconflicts h (p:restplist) iseaten newhlist
		|	length (thrd h) == 2 = ((h:newhlist),iseaten)
		|	(fsst h) == (fst p) = if (notElem (snd p) iseaten)
									then checkconflicts (fsst h,scnd h,((snd p):(thrd h))) restplist ((snd p):iseaten) newhlist
									else checkconflicts h restplist iseaten newhlist
		|	otherwise = checkconflicts h restplist iseaten newhlist

-- update for hunter to catch preys
-- gets (fst (catch x y [] 0)) and hmoveOnce's oldhlist [] 
-- returns same indexed list with hmoveOnce
hcatchupdate _ [] newlist = reverse newlist
hcatchupdate newhlist (h:oldresthlist) newlist = hcatchupdate newhlist oldresthlist (hcatchupt_helper newhlist h newlist)

-- utility functions for hcatchupdate
hcatchupt_helper (newh:restnewhlist) h newlist
		|	(hID h) == (scnd newh) = if length (thrd newh) == 0
									 	then (h:newlist)
									 	else if length (thrd newh) == 1
									 		then ((updatehfor_1 h):newlist)
									 		else ((updatehfor_2 h):newlist)
		|	otherwise = hcatchupt_helper restnewhlist h newlist

updatehfor_1 h = let 
					x = (hEnergy h)
		  			y = (hNumberOfCatches h)
	  			 in if (x + 20) < 100 then h {hEnergy = x + 20, hNumberOfCatches = y + 1}
									  else h {hEnergy = 100, hNumberOfCatches = y + 1}
updatehfor_2 h = let 
					x = (hEnergy h)
		  			y = (hNumberOfCatches h)
	  			 in if (x + 40) < 100 then h {hEnergy = x + 40, hNumberOfCatches = y + 2}
									  else h {hEnergy = 100, hNumberOfCatches = y + 2}

-- update for killing preys after motion
-- gets (snd (catch x y [] 0)) pmoveOnce's oldploclist and pmoveOnce's oldplist 
-- returns ([updateloclist],[updated preys]) 
pcatchupdate _ _ [] newplist newploclist = (reverse newploclist,reverse newplist)
pcatchupdate iseatenlist (ploc:oldrestploclist) (p:oldrestplist) newplist newploclist
		|	notElem (pID p) iseatenlist = pcatchupdate iseatenlist oldrestploclist oldrestplist (p:newplist) (ploc:newploclist)
		|	otherwise = pcatchupdate iseatenlist oldrestploclist oldrestplist newplist newploclist

-- gets tuple from hmoveOnce
-- returns ([((location),Hunter ID,[])],[sorted hunter list]) list to sorthcritic
hcriticlist tuple newlist hlist seed 
		|	seed == length (fst tuple) = (newlist,(reverse (sort hlist)))
hcriticlist tuple newlist hlist seed = hcriticlist tuple ((((fst tuple)!!seed), (hID ((snd tuple)!!seed)), []):newlist) (((snd tuple)!!seed):hlist) (seed + 1)

-- gets ([((location),Hunter ID,[])],[sorted hunter list]) from hcriticlist
-- returns prey list from highest to lowest, i.e -> [((location),Hunter ID,[])] list 
sorthcritic tuple newlist _ index 
		|	index == (length (snd tuple)) = reverse newlist
sorthcritic tuple newlist seed index
		|	(scnd ((fst tuple)!!seed)) == hID ((snd tuple)!!index) = sorthcritic tuple (((fst tuple)!!seed):newlist) 0 (index + 1)
		|	otherwise = sorthcritic tuple newlist (seed + 1) index 

-- gets tuple from pmoveOnce
-- returns ([((location),Prey ID)],[sorted prey list]) list to sortpcritic
pcriticlist tuple newlist plist seed 
		|	seed == length (fst tuple) = (newlist, (sort plist))
pcriticlist tuple newlist plist seed = pcriticlist tuple ((((fst tuple)!!seed), (pID ((snd tuple)!!seed))):newlist) (((snd tuple)!!seed):plist) (seed + 1)

-- gets ([((location),Prey ID)],[sorted prey list]) from pcriticlist
-- returns prey list from lowest to highest, i.e -> [((location),Prey ID)] list 
sortpcritic tuple newlist _ index 
		|	index == (length (snd tuple)) = reverse newlist
sortpcritic tuple newlist seed index
		|	(snd ((fst tuple)!!seed)) == pID ((snd tuple)!!index) = sortpcritic tuple (((fst tuple)!!seed):newlist) 0 (index + 1)
		|	otherwise = sortpcritic tuple newlist (seed + 1) index 

-- utility function for returning elements of 3-tuples
fsst (a,_,_) = a
scnd (_,a,_) = a
thrd (_,_,a) = a

-- utility function for move hunter at time t
hmoveOnce _ [] _ newloclist newhlist _ = (reverse newloclist,reverse newhlist)
hmoveOnce grid (loc:restloc) (hunter:resthunter) newloclist newhlist index = hmoveOnce grid restloc resthunter ((hMove grid loc hunter index):newloclist) ((hUpdate grid loc hunter  index):newhlist)  index

-- utility function for move prey at time t
pmoveOnce _ [] _ newloclist newplist _ = (reverse newloclist, reverse newplist)
pmoveOnce grid (loc:restloc) (prey:restprey) newloclist newplist index = pmoveOnce grid restloc restprey ((pMove grid loc prey index):newloclist) ((pUpdate grid loc prey index):newplist) index

-- utility function for motion of hunter
hMove grid location hunter index
		|	fst (hactionsus grid ((hActions hunter)!!index) location hunter 0) == 0 = location
		|	((hActions hunter)!!index) == N = (fst location, snd location - 1)
		|	((hActions hunter)!!index) == S = (fst location, snd location + 1)
		|	((hActions hunter)!!index) == W = (fst location - 1, snd location)
		|	((hActions hunter)!!index) == E = (fst location + 1, snd location)

-- utility function for motion of prey
pMove grid location prey index
		|	fst (pactionsus grid ((pActions prey)!!index) location prey 0) == 0 = location
		|	((pActions prey)!!index) == N = (fst location, snd location - 1)
		|	((pActions prey)!!index) == S = (fst location, snd location + 1)
		|	((pActions prey)!!index) == W = (fst location - 1, snd location)
		|	((pActions prey)!!index) == E = (fst location + 1, snd location)

-- energy update function for hunters
hUpdate grid location hunter  index
	    |	snd (hactionsus grid ((hActions hunter)!!index) location hunter  0) == 0 = let x = (hEnergy hunter) in if (x - 1) >= 0 then hunter {hEnergy = x - 1} --energy will decrease by 1
																																  			else hunter {hEnergy = 0}
		|	snd (hactionsus grid ((hActions hunter)!!index) location hunter  0) == 1 = let x = (hEnergy hunter) in if (x + 1) < 100 then hunter {hEnergy = x + 1}--energy will increase by 1
																															 	   			 else hunter {hEnergy = 100} 		
-- energy update function for preys
pUpdate grid location prey index
		|	snd (pactionsus grid ((pActions prey)!!index) location prey 0) == 0 = let x = (pEnergy prey) in if (x - 1) >= 0 then prey {pEnergy = x - 1} --energy will decrease by 1
																															else prey {pEnergy = 0}
		|	snd (pactionsus grid ((pActions prey)!!index) location prey 0) == 1 = let x = (pEnergy prey) in if (x + 1) < 100 then prey {pEnergy = x + 1}--energy will increase by 1
																															 else prey {pEnergy = 100} 		
		|	snd (pactionsus grid ((pActions prey)!!index) location prey 0) == 2 = let x = (pEnergy prey) in if (x - 11) >= 0 then prey {pEnergy = x - 11}--energy will decrease by 10
																															 else prey {pEnergy = 0}
		|	snd (pactionsus grid ((pActions prey)!!index) location prey 0) == 3 = let x = (pEnergy prey) in if (x - 9) >= 0 then prey {pEnergy = x - 9}--energy will decrease by 9
																															else prey {pEnergy = 0}
-- returns tuple (moved or not,flag of update) and flag default=0
hactionsus grid direksion location hunter  flag
		|  direksion == N = if snd location == 0 || (grid!!(snd location - 1))!!(fst location) == X -- hunter cannot move
								then if (hEnergy hunter) < 10 -- low energy, so rests, flag = 1 en+1
								 		then (0,1)
								 		else (0,0) -- hunter cannot move, has energy, flag = 0 en-1
							else if (hEnergy hunter) < 10 -- hunter cannot move due to low energy , (0,1)
								then (0,1) -- en+1
								else (1,0) -- hunter moved normally, flag = 1 en-1
		|  direksion == S = if snd location == rownum grid || (grid!!(snd location + 1))!!(fst location) == X || (hEnergy hunter) < 10 
								then if (hEnergy hunter) < 10 -- low energy, so rests, flag = 1 en+1
								 		then (0,1)
								 		else (0,0) -- hunter cannot move, has energy, flag = 0 en-1
							else if (hEnergy hunter) < 10 -- hunter cannot move due to low energy , (0,1)
								then (0,1) -- en+1
								else (1,0) -- hunter moved normally, flag = 1 en-1
		|  direksion == W = if fst location == 0 || (grid!!(snd location))!!(fst location - 1) == X || (hEnergy hunter) < 10 
								then if (hEnergy hunter) < 10 -- low energy, so rests, flag = 1 en+1
								 		then (0,1)
								 		else (0,0) -- hunter cannot move, has energy, flag = 0 en-1
							else if (hEnergy hunter) < 10 -- hunter cannot move due to low energy , (0,1)
								then (0,1) -- en+1
								else (1,0) -- hunter moved normally, flag = 1 en-1
		|  direksion == E = if fst location == columnum grid || (grid!!(snd location))!!(fst location + 1) == X || (hEnergy hunter) < 10 
								then if (hEnergy hunter) < 10 -- low energy, so rests, flag = 1 en+1
								 		then (0,1)
								 		else (0,0) -- hunter cannot move, has energy, flag = 0 en-1
							else if (hEnergy hunter) < 10 -- hunter cannot move due to low energy , (0,1)
								then (0,1) -- en+1
								else (1,0) -- hunter moved normally, flag = 1 en-1

-- returns tuple (moved or not,flag of update) and flag default=0 
pactionsus grid direksion location prey flag
		|  direksion == N = if snd location == 0 || (grid!!(snd location - 1))!!(fst location) == X -- prey cannot move
							then if (pEnergy prey) >= 10 && ((grid!!(snd location))!!(fst location) == T) -- has energy and still on trap, flag = 2 en-11
								 	then (0,2)
								 	else if (pEnergy prey) < 10 && ((grid!!(snd location))!!(fst location) == T) -- low energy and on trap! (prey stuck), flag = 3 en-9
								 		then (0,3)
								 		else if (pEnergy prey) < 10 -- low energy, so rests, flag = 1 en+1
								 			then (0,1)
								 			else (0,0) -- prey cannot move, has energy, flag = 0 en-1
							else if (pEnergy prey) < 10 -- prey cannot move due to low energy , (0,1)
								then (0,1)
								else if (grid!!(snd location - 1))!!(fst location) == T -- prey goes into trap, flag = 2 en-11
									then (1,2)
									else (1,0) -- prey moved normally, flag = 1
		|  direksion == S = if snd location == rownum grid || (grid!!(snd location + 1))!!(fst location) == X || (pEnergy prey) < 10 
							then if (pEnergy prey) >= 10 && ((grid!!(snd location))!!(fst location) == T) -- has energy and still on trap, flag = 2 en-11
								 	then (0,2)
								 	else if (pEnergy prey) < 10 && ((grid!!(snd location))!!(fst location) == T) -- low energy and on trap! (prey stuck), flag = 3 en-9
								 		then (0,3)
								 		else if (pEnergy prey) < 10 -- low energy, so rests, flag = 1 en+1
								 			then (0,1)
								 			else (0,0) -- prey cannot move, has energy, flag = 0 en-1
							else if (pEnergy prey) < 10 -- prey cannot move due to low energy , (0,1)
								then (0,1)
								else if (grid!!(snd location + 1))!!(fst location) == T -- prey goes into trap, flag = 2 en-11
									then (1,2)
									else (1,0) -- prey moved normally, flag = 1
		|  direksion == W = if fst location == 0 || (grid!!(snd location))!!(fst location - 1) == X || (pEnergy prey) < 10 
							then if (pEnergy prey) >= 10 && ((grid!!(snd location))!!(fst location) == T) -- has energy and still on trap, flag = 2 en-11
								 	then (0,2)
								 	else if (pEnergy prey) < 10 && ((grid!!(snd location))!!(fst location) == T) -- low energy and on trap! (prey stuck), flag = 3 en-9
								 		then (0,3)
								 		else if (pEnergy prey) < 10 -- low energy, so rests, flag = 1 en+1
								 			then (0,1)
								 			else (0,0) -- prey cannot move, has energy, flag = 0 en-1
							else if (pEnergy prey) < 10 -- prey cannot move due to low energy , (0,1)
								then (0,1)
								else if (grid!!(snd location))!!(fst location - 1) == T -- prey goes into trap, flag = 2 en-11
									then (1,2)
									else (1,0) -- prey moved normally, flag = 1
		|  direksion == E = if fst location == columnum grid || (grid!!(snd location))!!(fst location + 1) == X || (pEnergy prey) < 10 
							then if (pEnergy prey) >= 10 && ((grid!!(snd location))!!(fst location) == T) -- has energy and still on trap, flag = 2 en-11
								 	then (0,2)
								 	else if (pEnergy prey) < 10 && ((grid!!(snd location))!!(fst location) == T) -- low energy and on trap! (prey stuck), flag = 3 en-9
								 		then (0,3)
								 		else if (pEnergy prey) < 10 -- low energy, so rests, flag = 1 en+1
								 			then (0,1)
								 			else (0,0) -- prey cannot move, has energy, flag = 0 en-1
							else if (pEnergy prey) < 10 -- prey cannot move due to low energy , (0,1)
								then (0,1)
								else if (grid!!(snd location))!!(fst location + 1) == T -- prey goes into trap, flag = 2 en-11
									then (1,2)
									else (1,0) -- prey moved normally, flag = 1
actnum [] seed = seed
actnum (row:gridrest) seed
		|	seed == 0 = actnum gridrest (getrow row 0) 
		|	otherwise = seed

--maximum action number
getrow [] seed = seed
getrow (cell:rowrest) seed
		|	cell == O || cell == T || cell == X = getrow rowrest seed 
		|	checkph cell == 0 = length(hActions (hextract cell))
		|	checkph cell == 1 = length(pActions (pextract cell))

-- returns row/column number of grid
rownum grid = (length grid) - 1
columnum grid = (length (grid!!0)) - 1

-- functions for returning the locations of hunters and preys respectively
hLocationlist grid = hrowsend grid 0 ([],[])
pLocationlist grid = prowsend grid 0 ([],[])

-- utility functions for location functions
hrowsend [] _ (hloclist,hlist) = (hloclist,hlist)
hrowsend (row:gridrest) hrownum (hloclist,hlist) = hrowsend gridrest (hrownum + 1) (hlocationfinder row hrownum 0 (hloclist,hlist))

hlocationfinder [] _ _ (hloclist,hlist) = (hloclist,hlist)
hlocationfinder (cell:rowrest) hrownum hcolumnnum (hloclist,hlist) 
		|	cell == O || cell == T || cell == X = hlocationfinder rowrest hrownum (hcolumnnum + 1) (hloclist,hlist)
		|	checkph cell == 0 = hlocationfinder rowrest hrownum (hcolumnnum + 1) (((hcolumnnum,hrownum):hloclist), ((hextract cell):hlist))
		|	otherwise = hlocationfinder rowrest hrownum (hcolumnnum + 1) (hloclist,hlist)

prowsend [] _ (ploclist,plist) = (ploclist,plist)
prowsend (row:gridrest) prownum (ploclist,plist) = prowsend gridrest (prownum + 1) (plocationfinder row prownum 0 (ploclist,plist))

plocationfinder [] _ _ (ploclist,plist) = (ploclist,plist)
plocationfinder (cell:rowrest) prownum pcolumnnum (ploclist,plist)
		|	cell == O || cell == T || cell == X = plocationfinder rowrest prownum (pcolumnnum + 1) (ploclist,plist)
		|	checkph cell == 1 = plocationfinder rowrest prownum (pcolumnnum + 1) (((pcolumnnum,prownum):ploclist), ((pextract cell):plist))
		|	otherwise = plocationfinder rowrest prownum (pcolumnnum + 1) (ploclist,plist)

checkph (H x) = 0
checkph (P x) = 1

hextract (H x) = x
pextract (P x) = x

