`timescale 1ns / 1ps

module lab4_2(
	input[3:0] userID, 
	input CLK, 
	input team,
	input [1:0] mode,
	output reg  [7:0] numPlyLP,
	output reg  [7:0] numPlyCF,
	output reg  teamWng,
	output reg capWngLP,
	output reg capWngCF,
	output reg findRes,
	output reg [3:0] listOut,
	output reg  listMode
    );
//Write your code below


reg [3:0] logicPlayers [4:0];//Team Logic POwer
reg [3:0] cengPlayers [4:0];//Team Ceng Force
integer i;//used for for loops
integer j;	//used for printing the j'th index in list mode





integer flag;
integer index;
integer countLP;
integer countCF;

//make ID's of each team's players 0000
initial
begin
	for(i=0;i<=4;i=i+1)
	begin
		logicPlayers[i]=4'b0000;
		cengPlayers[i]=4'b0000;
	end
	numPlyLP = 0;
	numPlyCF = 0;
	capWngLP = 1;
	capWngCF = 1;
	j = 0;
	listOut=0;
	countLP=0;
	countCF=0;
end


always@(posedge CLK)
begin
index = -1;
flag = 0;
findRes = 0;	
teamWng = 0;
listMode=0;
numPlyLP=countLP;
numPlyCF=countCF;
	if(mode==2'b00) //LOGOUT mode
	begin
		j=0;//this is the j for list print
		if(team == 0) //logicPlayers choice
		begin
			for(i = 0; i <= 4; i = i + 1)//searches the userID in the team (userID is logged in to team already)
			begin
				if(logicPlayers[i] == userID)//finds the location
				begin
					logicPlayers[i] = 4'b0000;
					countLP = countLP- 1; 
					if(countLP == 0)//if empty make cap 1
					begin
						capWngLP = 1;
					end
				end
			end
		end
		else //cengPlayers choice
		begin
			for(i = 0; i <= 4; i = i + 1)//searches the userID in the team (userID is logged in to team already)
			begin
				if(cengPlayers[i] == userID)//finds the location
				begin
					cengPlayers[i] = 4'b0000;
					countCF = countCF - 1; 
					if(countCF == 0)//if empty make cap 1
					begin
						capWngCF = 1;
					end
				end
			end
		end
	end
	else if(mode==2'b01) //LOGIN mode
	begin
		j=0;//this is the j for list print
		if(team != userID[3]) //violation of rule 5
		begin
			teamWng = 1;
		end
		else
		begin
			if(team == 0) //logicPlayers choice
			begin
				for(i = 0; i < 5; i = i + 1)//checks for empty spaces in team and if sameID exists in team
				begin
					if(logicPlayers[i] == 4'b0000)//finds the index of empty space
					begin
						index = (index >= 0) ? index : i;
					end
				end
				for(i = 0; i < 5; i = i + 1)//checks for empty spaces in team and if sameID exists in team
				begin
					if(logicPlayers[i] == userID)
					begin
						flag = 1; //sameID exists in team
					end
				end
				
				if((flag == 0) && (index >= 0)) //login successful
				begin
					logicPlayers[index] = userID;
					countLP = countLP + 1;
					if((countLP == 5) || (countLP == 0))
					begin
						capWngLP = 1;
					end
					else if((countLP < 5) && (countLP > 0))
					begin
						capWngLP = 0;
					end
				end
				
			end
			else //cengPlayers choice
			begin
				for(i = 0; i <= 4; i = i + 1)
				begin
					if(cengPlayers[i] == 4'b0000)
					begin
						index = (index >= 0) ? index : i;
					end
				end
				for(i = 0; i <= 4; i = i + 1)
				begin
					if(cengPlayers[i] == userID)
					begin
						flag = 1; //sameID exists in team
					end
				end
				
				if((flag == 0) && (index >= 0)) //login successful
				begin
					cengPlayers[index] = userID;
					countCF = countCF + 1;
					if((countCF == 5) || (countCF == 0))
					begin
						capWngCF = 1;
					end
					else if((countCF < 5) && (countCF > 0))
					begin
						capWngCF = 0;
					end
				end
				
			end
		end
	end
	else if(mode==2'b10) //FIND mode
	begin
		j=0;//this is the j for list print
		//search in logicPlayers team
		if(team==0)
		begin
			//for loop for searching inside the logicPlayers team
			for(i=0;i<=4;i=i+1)
			begin
				if(logicPlayers[i]==userID) //we have found the user, give warning
				begin
					findRes=1;
				end
			end
		end
		//search in cengPlayers team
		else
		begin
			for(i=0;i<=4;i=i+1)
			begin
				if(cengPlayers[i]==userID) //we have found the user, give warning
				begin
					findRes=1;
				end
			end
		end
	end
	else if(mode == 2'b11) //LIST MODE
	begin
		//show list mode
		listMode=1;
		if(team==0)//print logicPlayers
		begin
			listOut = logicPlayers[j];
			j = (j == 4) ? 0: j + 1;
		end
		
		else//print cengPlayers
		begin
			listOut = cengPlayers[j];
			j = (j == 4) ? 0: j + 1;
		end
	end
end


endmodule