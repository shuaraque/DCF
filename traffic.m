%Generating poisson distributed traffic:

%Step1:
format short g

lada=50;

arrivals=5;

U=rand(1,arrivals)

%Step2:
X=-log(1-U)./lada %interarrival times in seconds

X_slots= X*(10^5) %interarrival times in slots


   for i = 2:arrivals
      X_slots(1,i) = X_slots(1,i)+X_slots(1,i-1);
    end

X_slots %the actual arrival times
