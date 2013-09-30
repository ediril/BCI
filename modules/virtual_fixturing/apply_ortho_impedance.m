function [outCommand] = apply_ortho_impedance(D, U, Ct)

  m = length(U);
  I = eye(m,m);
  
  spanMatr = PosSpan(D, U);
  %disp('spanMatr');
  %disp(spanMatr);

  kernelMatr = I - spanMatr;
  
  Dtemp = Ct * kernelMatr + spanMatr;
  outCommand = Dtemp * U;
  
 
end

function outMatr = PosSpan(inD, inU)

%  FULL_D_COLS = 2 * length(inU) + size(inD,2);
  
 % useD = zeros(length(inU), FULL_D_COLS);
 % for i=1:length(inU)

 %   if(~dimMask(i))
 %     useD(i, (i-1)*2+1) = 1.0;
 %     useD(i, (i-1)*2+2) = -1.0;
 %   end

 % end

 % useD(:,(2*length(inU)+1):end) = inD;
  nonzerocols = find(sum(abs(inD)>eps));
  D = inD(:,nonzerocols);

  if(isempty(D))
    outMatr = 0;
    return;
  end
   
  
  
%  Dsq = inD .^ 2;
%  Dsum = sum(Dsq);
%  Drep = repmat(Dsum, size(Dsq,1), 1);
%  D = inPD ./ Drep;
%disp('D');
%disp(D);

%disp('Dt');
%disp(D');

%D = inD;
%  W = D' * inU;
%newW = pinv(D) * inU;

normD0 = sqrt(sum(D.^2));
normD = repmat(normD0, size(D,1), 1);
if(sum(normD) == 0)
  keyboard;
  unitD = zeros(size(D));
  
else
  unitD = D ./ normD;
end
%unitDot = unitD' * inU;
  

posD = GetPosSpanVectors(unitD, inU);

D2 = posD;
%%%%
% [maxdot closestVector] = max(unitDot);  

% Do = D(:, closestVector);
% modU = (inU - Do);


%   W = D' * modU;
  
  
%   negW = find(W<=0);
  
%   negW = setdiff(negW, closestVector);
%   D2 = D;
%   D2(:, negW) = 0;
%%%%%55


%unitD(:, closestVector) = nan;
%[mindot secondClosestVector] = min(unitDot);


  X = D2' * D2;

  %[U, S, V] = svd(X);
%  Smatr = diag(S);
 % temp2 = S * U';
 % temp = V * temp2;
[u s v] = svd(X);
sinv = pinv(s);
dS=diag(s);
dS(dS<1e-8) = 0;
d1 = 1./dS;

d2 = d1;
d2(isinf(d2)) = 0.0;
 nFact = max(d2);
 rat = d2 ./ nFact;
 d3 = d2;
 d3(rat < 0.000005) = 0;
 sinv2 = diag(d3);


t0 = v * sinv2* u';
%temp = pinv(X);
%temp

  outMatr = D2 * t0 * D2';

%  if(size(inD, 2) == 1)


    
%  end

  
end