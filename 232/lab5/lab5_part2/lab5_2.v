`timescale 1ns / 1ps

module Elevator(input CLK,
					input [1:0] mode,
					input [3:0] request,
					output reg[3:0] currentFloor1,
					output reg[3:0] currentFloor2,
					output reg doorOpen1, 
					output reg doorOpen2, 
					output reg [3:0] listingLeds,
					output reg listBusy,
					output reg state);

//Write your code below
integer taskCount;//used for keeping the # of tasks
integer listIndex;//used for loops such as list mode loop etc
integer i,j;//used for simple for loops
reg [3:0]tasks[7:0];//used for keeping the tasks
integer task1,task2;//used for keeping the tasks of individual elevators in work mode
//integer workMode;//used for ensuring work mode works
integer isInList,deleted;

initial begin
	currentFloor1[3:0] = 1;
	currentFloor2[3:0] = 1;
	doorOpen1=1;
	doorOpen2=1;
	listingLeds=4'b0000;
	listBusy = 0;
	state = 0;
	
	//MINE
	i=0;
	j=0;
	isInList=0;
	for(i=0;i < 8;i=i+1) tasks[i]=4'b0000; 
	taskCount=0;
	task1=0;
	task2=0;
	deleted=0;
	//workMode=0;

end


always@(posedge CLK)
begin

//listingLeds=4'b0000;//set 0 for all op.'s other than list mode


	if(mode==2'b00 && !listBusy)//ADD MODE            //DONE
	begin
		isInList=0;
		if(taskCount!=8)
		begin
			for(j=0;j<8;j=j+1)
			begin
				if(tasks[j]==request)
				begin
					isInList=1;
				end
			end
			if(!isInList)
			begin
				tasks[taskCount]=request;
				taskCount=taskCount+1;
			end
		end
	end
	
	
	if(mode==2'b01 || listBusy)//LIST MODE           //DONE
	begin
		//change listing leds
		listBusy=1;//set this to 0 (@ the end of this mode --marked CHECKPOINT#1) if you finished listing
		if(listIndex==taskCount)
		begin
			listingLeds=4'b0000;
			listIndex=0;
			listBusy=0;// CHECKPOINT#1
		end
		
		else
		begin
		
		
		
			listingLeds=tasks[listIndex];
			listIndex=listIndex+1;
		end
		
		
		
	end


	if(mode==2'b10 && !listBusy)//DELETE MODE
	begin
		j=0;
		deleted=0;
		//entry confirmed
		for(i=0;i<8;i=i+1) //set listIndex to 0(@ the end of this mode --marked CHECKPOINT#2)
		begin
			
			if(tasks[i]==request)
			begin 
				j=i;//delete operation confirmed
				deleted=1;
				taskCount=taskCount-1;
			end
		end
		for(i=0;i<7;i=i+1)
		begin
			//doorOpen1=0;
				
				if(i>=j) tasks[i]=tasks[i+1];
		end
		if(j!=0) tasks[7]=4'b0000;
		
		i=0;// CHECKPOINT#2
	end


	if(mode==2'b11 && !listBusy)//WORK MODE
	begin
	
		state=1;//if task1=task2=0 and taskpool=0 make state=0;
		
		//IMPLEMENT end case-> if(doorOpen1 && doorOpen2 && tasks[0]==0000) etc.
		if(doorOpen1 && doorOpen2 && tasks[0]==0000)
		begin
			state=0;
			//return;
		end
		
		else
		begin
			if(doorOpen1)//if door1 is open take a task if there exists a task
			begin
				if(tasks[0]!=4'b0000)//if a task exists take it and sort the tasks again     //also close the door?
				begin
					task1=tasks[0];
					for(i=0;i<7;i=i+1) tasks[i]=tasks[i+1];
					tasks[7]=4'b0000;
					doorOpen1=0;
					taskCount=taskCount-1;
				end
				
			end
			
			if(!doorOpen1)//if door1 is closed  //you must do this in another if because you should move the elevator if you find a task
			begin
				if(currentFloor1==task1 || currentFloor1==task1+1 || currentFloor1==task1-1)//if you are already at the destination or you are going to reach in this pulse open the door
				begin
					doorOpen1=1;
				end
				if(currentFloor1!=task1)//if you have not reached the destionation move      //also close the door
				begin
					//doorOpen1=0;
					currentFloor1=(task1>currentFloor1)? currentFloor1+1 : currentFloor1-1;
				end
			end
			
			
			if(doorOpen2)//if door2 is open take a task if there exists a task
			begin
				if(tasks[0]!=4'b0000)//if a task exists take it and sort the tasks again     //also close the door?
				begin
					task2=tasks[0];
					for(i=0;i<7;i=i+1) tasks[i]=tasks[i+1];
					tasks[7]=4'b0000;
					doorOpen2=0;
					taskCount=taskCount-1;
				end
				
			end
			
			if(!doorOpen2)//if door2 is closed  //you must do this in another if because you should move the elevator if you find a task
			begin
				if(currentFloor2==task2 || currentFloor2==task2+1 || currentFloor2==task2-1)//if you are already at the destination or you are going to reach in this pulse open the door
				begin
					doorOpen2=1;
				end
				if(currentFloor2!=task2)//if you have not reached the destination move      //also close the door
				begin
					//doorOpen2=0;
					currentFloor2=(task2>currentFloor2)? currentFloor2+1 : currentFloor2-1;
				end
			end
	
		
		end
		
	end

end

endmodule