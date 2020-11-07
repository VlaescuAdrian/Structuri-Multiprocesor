sn = @(x)((x+3)./4);
en = @(x) 0.25 + 0.75./x;
rn = @(x) (1 + log2(x)./x);
qn = @(x) ((x + 3).^2 ./ (16*x + 16*log2(x)));
un = @(x) ((x + 3) .*(x + log2(x)) ./ (4 * x.^2));

fplot(sn,[1,32]);
hold on
fplot(rn,[1,32]);
hold on
fplot(qn,[1,32]);
xlabel('n');
ylabel('Value for S, R and Q');
legend('S(x)','R(x)','Q(x)')
hold off

figure;
fplot(en,[1,32]);
hold on
fplot(un,[1,32]);
xlabel('n');
ylabel('Value for E and U');
legend('E(x)','U(x)')
hold off
