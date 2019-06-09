N=4144;      % size of the Monte Carlo simulation with alpha = 0.01 and error = 0.02

% Parameter Definitions %
lambdaMotor1 = 40;   
lambdaCar1 = 30;  
lambdaTruck1 = 20;   
lambdaMotor2 = 0.15; alphaMotor = 16; 
lambdaCar2 = 0.05;  alphaCar = 60;
lambdaTruck2 = 0.01; alphaTruck = 84;

% a vector that keeps the total weight of vehicles that use the bridge for each Monte Carlo run %
TotalWeight=zeros(N,1);

for k=1:N;

	% first generate sample "NMotors" using sampling from Poisson
	U = rand; i = 0; 
	F = exp(-lambdaMotor1);
	while (U>=F);
		i=i+1;
		F = F+exp(-lambdaMotor1)*lambdaMotor1^i/gamma(i+1);
	end;
	NMotors = i;   % NMotors is the number of motocycles that use the bridge 

	% then generate sample "NCars" using sampling from Poisson
	U = rand; i = 0; 
	F = exp(-lambdaCar1);
	while (U>=F);
		i=i+1;
		F = F+exp(-lambdaCar1)*lambdaCar1^i/gamma(i+1);
	end;
	NCars = i;   % NCars is the number of automobiles that use the bridge 

	% afterwards generate sample "NTrucks" using sampling from Poisson
	U = rand; i = 0; 
	F = exp(-lambdaTruck1);
	while (U>=F);
		i=i+1;
		F = F+exp(-lambdaTruck1)*lambdaTruck1^i/gamma(i+1);
	end;
	NTrucks = i;   % NTrucks is the number of trucks that use the bridge 

	% Generate sample weight for all vehicles with their generated numbers %
	WMotors = 0;
	for j=1:NMotors;
		WMotors = WMotors + sum(-1/lambdaMotor2 * log(rand(alphaMotor, 1)));
	end;

	WCars = 0;
	for j=1:NCars;
		WCars = WCars + sum(-1/lambdaCar2 * log(rand(alphaCar, 1)));
	end;

	WTrucks = 0;
	for j=1:NTrucks;
		WTrucks = WTrucks + sum(-1/lambdaTruck2 * log(rand(alphaTruck, 1)));
	end;

	TotalWeight(k) = WMotors + WCars + WTrucks;
end;
p_est = mean(TotalWeight>220000);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);
fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);