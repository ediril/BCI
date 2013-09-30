function outD = GetPosSpanVectors(unitD, inU)

dots = unitD' * inU;
[maxdot, closestVector] = max(dots);
%disp('inU');
%disp(inU');
%disp('dots');
%disp(dots');
%disp('maxdot');
%disp(maxdot);
if(maxdot <= 0.0)
    %disp('md < 0');
  outD = zeros(length(inU), 1);
  return;
end
%disp('unitD');
%disp(unitD);
Do = unitD(:,closestVector);
%disp('Do');
%disp(Do');
%fprintf('Do - '); disp(Do');
projU_D = Do * (1/(Do' * Do)) * Do' *  inU;

unitD2 = unitD;
unitD2(:,closestVector) = 0;

modU = (inU - projU_D);

W = unitD2' * modU;

negW = find(W<=0);
unitD22 = unitD2;
unitD22(:,negW) = 0;
outD = [Do GetPosSpanVectors(unitD22, modU)];
%outD



end