:- module(lab3, [max_price/2]).
:- [hardware].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

max_price(COMPONENT_LIST,PRICE) :- hng(COMPONENT_LIST,0,PRICE).

hng([],Max,Res) :- Res = Max.  
hng([Comp|RestComps],Max,Res) :- 
			findCompPrice(Comp,Temp), Max < Temp , !, 
			hng(RestComps,Temp,Res).

hng([Comp|RestComps],Max,Res) :- 
			hng(RestComps,Max,Res). 

findCompPrice(Comp,CompFunc) :- component(Comp,CompFunc,Y). 

