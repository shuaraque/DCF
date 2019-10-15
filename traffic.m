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

Times=X_slots %the actual arrival times

% Times(1,5)

 file=fopen('data1.txt', 'wt');
 
 for i=1:arrivals
 fprintf(file, '%0.2f\n', Times(1,i));
 end
 
 fclose(file);
