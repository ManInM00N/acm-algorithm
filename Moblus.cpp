const int MAXN = 1000000;
bool check[MAXN + 10];
int prime[MAXN + 10];
int mu[MAXN + 10];
int phi[MAXN + 10];
int tot = 0;
void Moblus() {
    memset(check, false, sizeof(check));
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= MAXN; i++) {
        if (!check[i]) {
            prime[tot++] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int j = 0; j < tot; j++) {
            if (i * prime[j] > MAXN)
                break;
            check[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}
