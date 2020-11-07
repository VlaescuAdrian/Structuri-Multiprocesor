O1 = @(x) x.^2;
T1 = @(x) x.^2;
On = @(x) x * log2(x);
Tn = @(x) x;
sn = @(x)(T1(x)./Tn(x));
en = @(x) sn(x) ./ x; #consideram ca p = n
rn = @(x) (On(x)./O1(x));
qn = @(x) (sn(x).* en(x) ./ rn(x));
un = @(x) rn(x) * 2;

fplot(sn,[1,32]);
hold on

fplot(qn,[1,32]);
xlabel('n');
ylabel('Value for S and Q');
legend('S(x)','Q(x)')
hold off

figure;
fplot(rn,[1,32]);
xlabel('n');
ylabel('Value for R');
legend('R(x)')
figure;

fplot(en,[1,32]);
hold on

fplot(un,[1,32]);
xlabel('n');
ylabel('Value for E and U');
legend('E(x)','U(x)')
hold off