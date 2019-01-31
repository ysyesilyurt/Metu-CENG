:- module(hw5, [configuration/3]).
:- [hardware].

configuration(COMPONENT_LIST,CONSTRAINT_LIST,PLACEMENT_LIST) :- 
			hardware:sections(RestSections), hardware:sections(AllSections), 
			nickTheChopper(COMPONENT_LIST,CONSTRAINT_LIST,RestSections,AllSections,[],PlacedList),
			nickTheOrder(COMPONENT_LIST,PlacedList,Temp,X), PLACEMENT_LIST = X.

nickTheOrder([],_,Temp,NewPlacementList) :- reverse(Temp,Nick), NewPlacementList = Nick, !.
nickTheOrder([Comp|RestOfIt],PLACEMENT_LIST,Temp,NewPlacementList) :- 
			member(put(Comp,Sec),PLACEMENT_LIST), insert(put(Comp,Sec),Temp,Tempo), !, 
			nickTheOrder(RestOfIt,PLACEMENT_LIST,Tempo,NewPlacementList).

nickTheChopper([],_,_,_,Res,PLACEMENT_LIST) :- PLACEMENT_LIST = Res. 

% outer_edge constraint
nickTheChopper([Comp|RestOfIt],CONSTRAINT_LIST,RestSections,AllSections,Res,PLACEMENT_LIST) :-
		    isOuterMember(Comp,CONSTRAINT_LIST),!, findOuterEdge(RestSections,AllSections,Sec), 
		    delete(RestSections,Sec,RetRestSections), delete(CONSTRAINT_LIST,outer_edge(Comp),NewConstList),
		    insert(put(Comp,Sec),Res,NewPlacedList), 
		    nickTheChopper(RestOfIt,NewConstList,RetRestSections,RetRestSections,NewPlacedList,PLACEMENT_LIST).  

% close_to constraint
nickTheChopper([Comp|RestOfIt],CONSTRAINT_LIST,RestSections,AllSections,Res,PLACEMENT_LIST) :-
			isCloseMember(Comp,CONSTRAINT_LIST,RestOfIt,OtherComp,N), N == 0 , !,
			findCloseEdges(RestSections,AllSections,Sec1,Sec2), delete(RestOfIt,OtherComp,RetRestOfIt),
			delete(RestSections,Sec1,RetRestSections), delete(RetRestSections,Sec2,Ret2RestSections), 
			delete(CONSTRAINT_LIST,close_to(Comp,OtherComp),NewConstList), insert(put(Comp,Sec1),Res,NewPlacedList),
			insert(put(OtherComp,Sec2),NewPlacedList,New2PlacedList),
				nickTheChopper(RetRestOfIt,NewConstList,Ret2RestSections,Ret2RestSections,New2PlacedList,PLACEMENT_LIST);
			isCloseMember(Comp,CONSTRAINT_LIST,RestOfIt,OtherComp,N), N == 1 , !,
			findCloseEdges(RestSections,AllSections,Sec1,Sec2), delete(RestOfIt,OtherComp,RetRestOfIt), 
			delete(RestSections,Sec1,RetRestSections), delete(RetRestSections,Sec2,Ret2RestSections), 
			delete(CONSTRAINT_LIST,close_to(OtherComp,Comp),NewConstList), insert(put(Comp,Sec1),Res,NewPlacedList),
			insert(put(OtherComp,Sec2),NewPlacedList,New2PlacedList),
				nickTheChopper(RetRestOfIt,NewConstList,Ret2RestSections,Ret2RestSections,New2PlacedList,PLACEMENT_LIST).

% no constraints
nickTheChopper([Comp|RestOfIt],CONSTRAINT_LIST,RestSections,AllSections,Res,PLACEMENT_LIST) :-
			getSection(RestSections,Sec),insert(put(Comp,Sec),Res,NewPlacedList),
			delete(RestSections,Sec,RetRestSections),
			nickTheChopper(RestOfIt,CONSTRAINT_LIST,RetRestSections,AllSections,NewPlacedList,PLACEMENT_LIST).

getSection([],Res) :- false.
getSection([A|Rest],Res) :- Res = A.
getSection([A|Rest],Res) :- getSection(Rest,Res).

insert(X,R,[X|R]).

findOuterEdge([],_,_) :- false, !.
findOuterEdge([SecToBeChecked|Resto],AllSections,Sec) :- delete(AllSections,SecToBeChecked,SendTheList),helperOfOuter(SecToBeChecked,SendTheList,Res), Res \= 0,Sec = Res.
findOuterEdge([SecToBeChecked|Resto],AllSections,Sec) :- findOuterEdge(Resto,AllSections,Sec).

helperOfOuter(_,[],Res) :- Res = 0, !.
helperOfOuter(CheckSec,[Sec|Resting],Res) :- hardware:adjacent(Sec,CheckSec), helperOfOuter(CheckSec,Resting,Res),! ; hardware:adjacent(CheckSec,Sec), helperOfOuter(CheckSec,Resting,Res),!.
helperOfOuter(CheckSec,[Sec|Resting],Res) :- Res = CheckSec, !.

findCloseEdges([],_,_,_) :- false, !.
findCloseEdges([SecToBeChecked|Resto],AllSections,Sec1,Sec2) :- delete(AllSections,SecToBeChecked,SendTheList),helperOfClose(SecToBeChecked,SendTheList,Res1,Res2), Res1 \= 0, Sec1 = Res1, Sec2 = Res2.
findCloseEdges([SecToBeChecked|Resto],AllSections,Sec1,Sec2) :- findCloseEdges(Resto,AllSections,Sec1,Sec2).

helperOfClose(_,[],Res1,_) :- Res1 = 0, !.
helperOfClose(CheckSec,[Sec|Resting],Res1,Res2) :- hardware:adjacent(CheckSec,Sec), Res1 = CheckSec, Res2 = Sec ; hardware:adjacent(Sec,CheckSec), Res1 = CheckSec, Res2 = Sec.
helperOfClose(CheckSec,[Sec|Resting],Res1,Res2) :- helperOfClose(CheckSec,Resting,Res1,Res2).

isOuterMember(_,[]) :- false, !.
isOuterMember(Comp,[FunConst|Rest]) :- FunConst == outer_edge(Comp), !.
isOuterMember(Comp,[FunConst|Rest]) :- isOuterMember(Comp,Rest).

isCloseMember(_,[],_,_,_) :- false, !.
isCloseMember(Comp,[FunConst|Rest],COMPONENT_LIST,OtherComp,N) :- isCloseHelper(Comp,COMPONENT_LIST,FunConst,Res,X), OtherComp = Res, N = X, !.
isCloseMember(Comp,[FunConst|Rest],COMPONENT_LIST,OtherComp,N) :- isCloseMember(Comp,Rest,COMPONENT_LIST,OtherComp,N).

isCloseHelper(_,[],_,_._) :- false, !.
isCloseHelper(Comp,[OtherComp|Resto],FunConst,Res,N) :- FunConst == close_to(Comp,OtherComp), Res = OtherComp, N = 0, !; FunConst == close_to(OtherComp,Comp), Res = OtherComp, N = 1, !.
isCloseHelper(Comp,[OtherComp|Resto],FunConst,Res,N) :- isCloseHelper(Comp,Resto,FunConst,Res,N), !.

