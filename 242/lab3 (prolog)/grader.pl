% Test cases for max_price

write_comment(Comment) :- write(Comment).

test_case_MP1(G) :- not(max_price([], _)) -> G is 8; G is 0, write_comment('Comment :=>> - Test case 1 is failed.\n').
test_case_MP2(G) :- (max_price([c620], PRICE), !, PRICE == 41) -> G is 2; G is 0, write_comment('Comment :=>> - Test case 2 is failed.\n').
test_case_MP3(G) :- not(max_price([c620], 40)) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 3 is failed.\n').
test_case_MP4(G) :- (max_price([c235, c338, c755, c950, c967, c467, c437, c104, c143, c4, c377], PRICE), !, PRICE == 985) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 4 is failed.\n').
test_case_MP5(G) :- (max_price([c612, c830, c745, c249, c338, c967, c834, c249, c372, c235, c467], PRICE), !, PRICE == 897) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 5 is failed.\n').
test_case_MP6(G) :- (max_price([c104, c171, c235, c143, c249, c261, c328, c645, c745, c666], PRICE), !, PRICE == 713) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 6 is failed.\n').
test_case_MP7(G) :- (max_price([c504, c467, c654, c666, c835, c930, c967, c836, c671, c235, c171], PRICE), !, PRICE == 837) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 7 is failed.\n').
test_case_MP8(G) :- (max_price([c104, c104, c235, c104, c235, c298, c4, c4, c620, c522, c755, c755, c522, c620], PRICE), !, PRICE == 662) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 8 is failed.\n').
test_case_MP9(G) :- not(max_price([c104, c104, c235, c104, c235, c298, c4, c4, c620, c522, c755, c755, c522, c620], 77)) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 9 is failed.\n').
test_case_MP10(G) :- not(max_price([c104, c104, c235, c104, c235, c298, c4, c4, c620, c522, c755, c755, c522, c620], 23)) -> G is 5; G is 0, write_comment('Comment :=>> - Test case 10 is failed.\n').

test_case_MP11(G) :- (max_price([c654, c755, c261, c836, c511, c555, c171, c830, c967, c522, c835, c784, c298, c338, c930, c372, c252, c143, c903, c262, c671, c620, c361, c235, c467, c645, c530, c774, c437, c377, c249, c328, c745, c180, c104, c834], PRICE), !, PRICE == 985) -> G is 8; G is 0, write_comment('Comment :=>> - Test case 11 is failed.\n').
test_case_MP12(G) :- not(max_price([c654, c755, c261, c836, c511, c555, c171, c830, c967, c522, c835, c784, c298, c338, c930, c372, c252, c143, c903, c262, c671, c620, c361, c235, c467, c645, c530, c774, c437, c377, c249, c328, c745, c180, c104, c834], 433)) -> G is 2; G is 0, write_comment('Comment :=>> - Test case 12 is failed.\n').
test_case_MP13(G) :- (max_price([c249, c836, c784, c104, c830, c671, c835, c511, c967, c666, c612, c620, c834, c861, c903, c143, c522, c252, c555, c361, c530, c338, c930, c235, c774, c377, c298, c262, c654, c180, c437, c261], PRICE), !, PRICE == 985) -> G is 8; G is 0, write_comment('Comment :=>> - Test case 13 is failed.\n').
test_case_MP14(G) :- not(max_price([c249, c836, c784, c104, c830, c671, c835, c511, c967, c666, c612, c620, c834, c861, c903, c143, c522, c252, c555, c361, c530, c338, c930, c235, c774, c377, c298, c262, c654, c180, c437, c261], 252)) -> G is 2; G is 0, write_comment('Comment :=>> - Test case 14 is failed.\n').
test_case_MP15(G) :- (max_price([c338, c180, c903, c654, c620, c774, c235, c830, c504, c555, c361, c4, c249, c298, c967, c836, c835, c252, c671, c328], PRICE), !, PRICE == 901) -> G is 8; G is 0, write_comment('Comment :=>> - Test case 15 is failed.\n').
test_case_MP16(G) :- not(max_price([c338, c180, c903, c654, c620, c774, c235, c830, c504, c555, c361, c4, c249, c298, c967, c836, c835, c252, c671, c328], 985)) -> G is 2; G is 0, write_comment('Comment :=>> - Test case 16 is failed.\n').
test_case_MP17(G) :- (max_price([c328, c511, c830, c835, c249, c784, c930, c620, c298, c836, c104, c467, c950, c522, c612, c504, c654, c361, c834, c671, c338, c555, c235], PRICE), !, PRICE == 897) -> G is 8; G is 0, write_comment('Comment :=>> - Test case 17 is failed.\n').
test_case_MP18(G) :- not(max_price([c328, c511, c830, c835, c249, c784, c930, c620, c298, c836, c104, c467, c950, c522, c612, c504, c654, c361, c834, c671, c338, c555, c235], 340)) -> G is 2; G is 0, write_comment('Comment :=>> - Test case 18 is failed.\n').
test_case_MP19(G) :- (max_price([c620, c830, c835, c328, c261, c654, c235, c967, c180, c666, c361], PRICE), !, PRICE == 785) -> G is 8; G is 0, write_comment('Comment :=>> - Test case 19 is failed.\n').
test_case_MP20(G) :- not(max_price([c620, c830, c835, c328, c261, c654, c235, c967, c180, c666, c361], 786)) -> G is 2; G is 0, write_comment('Comment :=>> - Test case 20 is failed.\n').



gradeMaxPrice(Grade, Report) :-
	TimeLimit is 10,
	ExtendedTimeLimit is 120,
        catch(call_with_time_limit(TimeLimit, test_case_MP1(G1)), _, (G1 is 0, write_comment('Comment :=>> - Test case 1 timed out.\n'))),
        catch(call_with_time_limit(TimeLimit, test_case_MP2(G2)), _, (G2 is 0, write_comment('Comment :=>> - Test case 2 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP3(G3)), _, (G3 is 0, write_comment('Comment :=>> - Test case 3 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP4(G4)), _, (G4 is 0, write_comment('Comment :=>> - Test case 4 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP5(G5)), _, (G5 is 0, write_comment('Comment :=>> - Test case 5 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP6(G6)), _, (G6 is 0, write_comment('Comment :=>> - Test case 6 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP7(G7)), _, (G7 is 0, write_comment('Comment :=>> - Test case 7 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP8(G8)), _, (G8 is 0, write_comment('Comment :=>> - Test case 8 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP9(G9)), _, (G9 is 0, write_comment('Comment :=>> - Test case 9 timed out.\n'))),
	catch(call_with_time_limit(TimeLimit, test_case_MP10(G10)), _, (G10 is 0, write_comment('Comment :=>> - Test case 10 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP11(G11)), _, (G11 is 0, write_comment('Comment :=>> - Test case 11 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP12(G12)), _, (G12 is 0, write_comment('Comment :=>> - Test case 12 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP13(G13)), _, (G13 is 0, write_comment('Comment :=>> - Test case 13 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP14(G14)), _, (G14 is 0, write_comment('Comment :=>> - Test case 14 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP15(G15)), _, (G15 is 0, write_comment('Comment :=>> - Test case 15 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP16(G16)), _, (G16 is 0, write_comment('Comment :=>> - Test case 16 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP17(G17)), _, (G17 is 0, write_comment('Comment :=>> - Test case 17 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP18(G18)), _, (G18 is 0, write_comment('Comment :=>> - Test case 18 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP19(G19)), _, (G19 is 0, write_comment('Comment :=>> - Test case 19 timed out.\n'))),
	catch(call_with_time_limit(ExtendedTimeLimit, test_case_MP20(G20)), _, (G20 is 0, write_comment('Comment :=>> - Test case 20 timed out.\n'))),
        Grade is G1 + G2 + G3 + G4 + G5 + G6 + G7 + G8 + G9 + G10 + G11 + G12 + G13 + G14 + G15 + G16 + G17 + G18 + G19 + G20,
        ( Grade =:= 100 ->
            Report = 'Comment :=>> ** Test cases for max_price are successful.\n'
        ;
            Report = 'Comment :=>> ** Problem with max_price predicate.\n'
        ).
gradeMaxPrice(1, 'Comment :=>> ** Problem with max_price predicate.\n'). 

testMaxPrice(1, 'Comment :=>> ** Predicate max_price/2 is not found.\n') :-
    not(current_predicate(max_price/2)), 
    !.

testMaxPrice(Grade, Report) :-
    gradeMaxPrice(Grade, Report).

    
testLab :-
	write_comment('\nComment :=>> Results: \n'),
	testMaxPrice(MPG, MPR),
	write_comment(MPR),    
	Grade is MPG,
	write(Grade),
	write('\n').    

runGrader(File) :- 
	use_module(File),
	catch(call_with_time_limit(1220, testLab), _, _).

