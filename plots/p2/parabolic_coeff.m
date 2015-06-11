#!/usr/bin/octave --quiet
format long E

function f = get_bino_coef(r, k)
  f = 1; 
  for i = 1:k
	f = f * (r - i + 1) / (k - i + 1);
  end
end
    
function s = get_gamma(r)
  s = 0;
  for i = 0:1000
    s = s + get_bino_coef(r, i) * (-1^i /(i+1));
  end
end
    

d = 3;

printf("#alpha;r;gamma;n;K\n");

for a = 0:0.005:2
  r = (-a + 1) * d;

  gamma 	= get_gamma(r);
  avra_n	= r + 1;
  avra_K	= -1/(-a+1)^d * gamma;

  printf("%.16E;%.16E;%.16E;%.16E;%.16E\n", a, r, gamma, avra_n, avra_K);
end;
