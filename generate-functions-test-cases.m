a = normrnd(1, 1, 50, 50);	A = sin(a);
b = normrnd(1, 1, 50, 50);	B = cos(b);
c = normrnd(1, 1, 50, 50);	C = tan(c);
d = rand(50, 50);		D = asin(d);
e = rand(50, 50);		E = acos(e);
f = rand(50, 50);		F = atan(f);
save sin-cos-tan-functions-test.m a b c d e f A B C D E F

a = normrnd(90, 90, 50, 50);	A = sind(a);
b = normrnd(90, 90, 50, 50);	B = cosd(b);
c = normrnd(90, 90, 50, 50);	C = tand(c);
d = rand(50, 50);		D = asind(d);
e = rand(50, 50);		E = acosd(e);
f = rand(50, 50);		F = atand(f);
save sind-cosd-tand-functions-test.m a b c d e f A B C D E F

a = normrnd(1, 1, 50, 50);	A = sinh(a);
b = normrnd(1, 1, 50, 50);	B = cosh(b);
c = normrnd(1, 1, 50, 50);	C = tanh(c);
d = rand(50, 50);		D = asinh(d);
e = rand(50, 50);		E = acosh(e);
f = rand(50, 50);		F = atanh(f);
save sinh-cosh-tanh-functions-test.m a b c d e f A B C D E F

a = normrnd(1, 1, 50, 50);	A = csc(a);
b = normrnd(1, 1, 50, 50);	B = sec(b);
c = normrnd(1, 1, 50, 50);	C = cot(c);
d = rand(50, 50);		D = acsc(d);
e = rand(50, 50);		E = asec(e);
f = rand(50, 50);		F = acot(f);
save csc-sec-cot-functions-test.m a b c d e f A B C D E F

a = normrnd(90, 90, 50, 50);	A = cscd(a);
b = normrnd(90, 90, 50, 50);	B = secd(b);
c = normrnd(90, 90, 50, 50);	C = cotd(c);
d = rand(50, 50);		D = acscd(d);
e = rand(50, 50);		E = asecd(e);
f = rand(50, 50);		F = acotd(f);
save cscd-secd-cotd-functions-test.m a b c d e f A B C D E F

a = normrnd(1, 1, 50, 50);	A = csch(a);
b = normrnd(1, 1, 50, 50);	B = sech(b);
c = normrnd(1, 1, 50, 50);	C = coth(c);
d = rand(50, 50);		D = acsch(d);
e = rand(50, 50);		E = asech(e);
f = rand(50, 50);		F = acoth(f);
save csch-sech-coth-functions-test.m a b c d e f A B C D E F

a = normrnd(1, 1, 50, 50);
b = normrnd(1, 1, 50, 50);
				C = atan2(a, b);
d = normrnd(90, 90, 50, 50);
e = normrnd(90, 90, 50, 50);
				F = atan2d(a, b);
save atan2-functions-test.m a b C d e F

a = abs(normrnd(100, 50, 50, 50));
b = abs(normrnd(100, 50, 50, 50));
				C = hypot(a, b);
save hypot-functions-test.m a b C

a = normrnd(6.28, 3.14, 50, 50);
				A = rad2deg(a);
b = normrnd(180, 90, 50, 50);   B = deg2rad(b);
save rad-deg-functions-test.m a b A B
