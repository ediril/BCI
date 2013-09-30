function [ e, theta ] = rotmat2rotvec( rotmat )
%UNTITLED2 Summary of this function goes here
%   e is a unit vector representing axis of rotation
%   theta is magnitude of rotation in radians

A = rotmat;
theta = real(acos((A(1,1) + A(2,2) + A(3,3) - 1)/2));
if theta < eps || abs(pi - theta) < eps || abs(pi + theta) < eps
    e = [0 0 0];
else
    e1 = (A(3,2) - A(2,3)) / (2 * sin(theta));
    e2 = (A(1,3) - A(3,1)) / (2 * sin(theta));
    e3 = (A(2,1) - A(1,2)) / (2 * sin(theta));
    e = [e1 e2 e3];
end

