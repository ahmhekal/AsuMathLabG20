% dummy matrix; for some reason, a test involving the last matrix in a file
% always fails. This means that all one arg functions' tests fail, too.
% So introducing a dummy matrix and making it the last matrix in a file should
% solve this problem. It's only in our test code, which we have total control
% on. So this workaround should not pose a problem.
x = [ 1 ];

% first: all one argument trig functions
a = normrnd(1, 1, 50, 50);              A =  sin(a);
b = normrnd(1, 1, 50, 50);              B =  cos(b);
c = normrnd(1, 1, 50, 50);              C =  tan(c);
d = rand(50, 50);                       D = asin(d);
e = rand(50, 50);                       E = acos(e);
f = rand(50, 50);                       F = atan(f);
save sin-cos-tan-test.mat a b c d e f A B C D E F x

a = normrnd(90, 90, 50, 50);            A =  sind(a);
b = normrnd(90, 90, 50, 50);            B =  cosd(b);
c = normrnd(90, 90, 50, 50);            C =  tand(c);
d = rand(50, 50);                       D = asind(d);
e = rand(50, 50);                       E = acosd(e);
f = rand(50, 50);                       F = atand(f);
save sind-cosd-tand-test.mat a b c d e f A B C D E F x

a = normrnd(1, 1, 50, 50);              A =  sinh(a);
b = normrnd(1, 1, 50, 50);              B =  cosh(b);
c = normrnd(1, 1, 50, 50);              C =  tanh(c);
d = rand(50, 50);                       D = asinh(d);
e = rand(50, 50);                       E = acosh(e);
f = rand(50, 50);                       F = atanh(f);
save sinh-cosh-tanh-test.mat a b c d e f A B C D E F x

a = normrnd(1, 1, 50, 50);              A =  csc(a);
b = normrnd(1, 1, 50, 50);              B =  sec(b);
c = normrnd(1, 1, 50, 50);              C =  cot(c);
d = rand(50, 50);                       D = acsc(d);
e = rand(50, 50);                       E = asec(e);
f = rand(50, 50);                       F = acot(f);
save csc-sec-cot-test.mat a b c d e f A B C D E F x

a = normrnd(90, 90, 50, 50);            A =  cscd(a);
b = normrnd(90, 90, 50, 50);            B =  secd(b);
c = normrnd(90, 90, 50, 50);            C =  cotd(c);
d = rand(50, 50);                       D = acscd(d);
e = rand(50, 50);                       E = asecd(e);
f = rand(50, 50);                       F = acotd(f);
save cscd-secd-cotd-test.mat a b c d e f A B C D E F x

a = normrnd(1, 1, 50, 50);              A =  csch(a);
b = normrnd(1, 1, 50, 50);              B =  sech(b);
c = normrnd(1, 1, 50, 50);              C =  coth(c);
d = rand(50, 50);                       D = acsch(d);
e = rand(50, 50);                       E = asech(e);
f = rand(50, 50);                       F = acoth(f);
save csch-sech-coth-test.mat a b c d e f A B C D E F x

% second: two argument functions
a =  normrnd(1, 1, 50, 50);
b =  normrnd(1, 1, 50, 50);
C =  atan2(a, b);
save atan2-test.mat a b C x

a =  normrnd(90, 90, 50, 50);
b =  normrnd(90, 90, 50, 50);
C =  atan2d(a, b);
save atan2d-test.mat a b C x

a =  abs(normrnd(100, 50, 50, 50));
b =  abs(normrnd(100, 50, 50, 50));
C =  hypot(a, b);
save hypot-test.mat a b C x

a =  rand(50, 50);
b =  rand(50, 50);
C =  power(a, b);
save power-test.mat a b C x

% third: one argument non-trig functions
a =  normrnd(6.28, 3.14, 50, 50);
A =  rad2deg(a);
save rad2deg-test.mat a A x

a =  normrnd(180, 90, 50, 50);
A =  deg2rad(a);
save deg2rad-test.mat a A x

a =  rand(50, 50);
A =  exp(a);
save exp-test.mat a A x

a =  rand(50, 50);
A =  log(a);
save log-test.mat a A x

a =  rand(50, 50);
A =  log10(a);
save log10-test.mat a A x

a =  rand(50, 50);
A =  log2(a);
save log2-test.mat a A x

a =  rand(50, 50);
A =  log1p(a);
save log1p-test.mat a A x

a =  rand(50, 50);
A =  sqrt(a);
save sqrt-test.mat a A x

