:- module(hardware, [sections/1, adjacent/2]).

% W P E _ _
% J A C X _
% _ _ F _ _
% _ _ Q S T
% _ _ _ Y _

sections([sA, sC, sE, sF, sJ, sP, sQ, sS, sT, sW, sX, sY]).

adjacent(sA, sC).
adjacent(sA, sJ).
adjacent(sA, sP).
adjacent(sC, sX).
adjacent(sC, sF).
adjacent(sC, sE).
adjacent(sE, sP).
adjacent(sF, sQ).
adjacent(sJ, sW).
adjacent(sQ, sS).
adjacent(sP, sW).
adjacent(sS, sT).
adjacent(sS, sY).