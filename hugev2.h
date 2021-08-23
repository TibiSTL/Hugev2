#pragma warning (disable : 26451)
#pragma warning (disable : 4996)
#include <vector>
#include <string>
using namespace std;
void add(vector<int>& a, int c) {
    if (a.size() == 0) {
        a.push_back(0);
    }
    a[0]++;
    a.push_back(c);
}
void rem(vector<int>& a) {
    a[0]--;
    a.pop_back();
}
void atribuie(vector<int>& a, long long x) {
    while (x > 9) {
        add(a, x % 10);
        x /= 10;
    }
    add(a, x % 10);
}
int cmp(vector<int> a, vector<int> b) {
    reverse(a.begin() + 1, a.end());
    reverse(b.begin() + 1, b.end());
    return (a == b ? -1 : a < b ? 1 : 0);
}
vector<int> inmultire_10(vector<int> a, int exp) {
    vector<int> c;
    for (int i = 1; i <= exp; ++i) {
        add(c, 0);
    }
    for (int i = 1; i <= a[0]; ++i) {
        add(c, a[i]);
    }
    return c;
}
vector<int> impartire_10(vector<int> a, int exp) {
    vector<int> c;
    for (int i = exp + 1; i <= a[0]; ++i) {
        add(c, a[i]);
    }
    return c;
}
vector<int> suma(vector<int> a, vector<int> b) {
    if (cmp(a, b) == 1) {
        swap(a, b);
    }
    int t = 0;
    vector<int> c;
    for (int i = 1; i <= b[0]; ++i) {
        int cifra = a[i] + b[i] + t;
        t = cifra / 10;
        cifra %= 10;
        add(c, cifra);
    }
    for (int i = b[0] + 1; i <= a[0]; ++i) {
        int cifra = a[i] + t;
        t = cifra / 10;
        cifra %= 10;
        add(c, cifra);
    }
    while (t) {
        add(c, t % 10);
        t /= 10;
    }
    return c;
}
vector<int> diferenta(vector<int> a, vector<int> b) {
    if (cmp(a, b) == 1) {
        swap(a, b);
    }
    bool imprumut = false;
    vector<int> c;
    for (int i = 1; i <= b[0]; ++i) {
        int cifra = a[i] - b[i] - imprumut;
        if (cifra < 0) {
            cifra += 10;
            imprumut = true;
        }
        else {
            imprumut = false;
        }
        add(c, cifra);
    }
    for (int i = b[0] + 1; i <= a[0]; ++i) {
        int cifra = a[i] - imprumut;
        if (cifra < 0) {
            cifra += 10;
            imprumut = true;
        }
        else {
            imprumut = false;
        }
        add(c, cifra);
    }
    while (c[c[0]] == 0 && c[0] > 1) {
        rem(c);
    }
    return c;
}
vector<int> inmultire_scalar(vector<int> a, int x) {
    int t = 0;
    vector<int> c;
    for (int i = 1; i <= a[0]; ++i) {
        int cifra = a[i] * x + t;
        t = cifra / 10;
        cifra %= 10;
        add(c, cifra);
    }
    while (t) {
        add(c, t % 10);
        t /= 10;
    }
    return c;
}
vector<int> inmultire(vector<int> a, vector<int> b) {
    vector<int> c(a[0] + b[0]);
    c[0] = a[0] + b[0] - 1;
    for (int i = 1; i <= a[0]; ++i) {
        for (int j = 1; j <= b[0]; ++j) {
            c[i + j - 1] += a[i] * b[j];
        }
    }
    int t = 0;
    for (int i = 1; i <= c[0]; ++i) {
        int cifra = c[i] + t;
        t = cifra / 10;
        cifra %= 10;
        c[i] = cifra;
    }
    while (t) {
        add(c, t % 10);
        t /= 10;
    }
    return c;
}
pair<vector<int>, int> impartire_scalar(vector<int> a, int x) {
    int r = 0;
    vector<int> c(a[0] + 1);
    c[0] = a[0];
    for (int i = a[0]; i >= 1; --i) {
        r = r * 10 + a[i];
        c[i] = r / x;
        r = r % x;
    }
    while (c[c[0]] == 0 && c[0] > 1) {
        rem(c);
    }
    return { c , r };
}
pair<vector<int>, vector<int>> impartire(vector<int> a, vector<int> b) {
    vector<int> c(a[0] + 1);
    vector<int> r;
    r.push_back(0);
    c[0] = a[0];
    for (int i = a[0]; i >= 1; --i) {
        r = inmultire_10(r, 1);
        r[1] = a[i];
        while (r[r[0]] == 0 && r[0] > 1) {
            rem(r);
        }
        while (cmp(r, b) != 1) {
            c[i]++;
            r = diferenta(r, b);
        }
    }
    while (c[c[0]] == 0 && c[0] > 1) {
        rem(c);
    }
    return { c , r };
}
class huge {
private:
    vector<int> val;
public:
    huge(long long x) {
        atribuie(val, x);
    }
    huge(vector<int> x) {
        val = x;
    }
    huge() {}
    friend istream& operator >>(istream& is, huge& a) {
        string s;
        is >> s;
        for (int i = (int)s.size() - 1; i >= 0; --i) {
            add(a.val, s[i] - '0');
        }
        return is;
    }
    friend ostream& operator << (ostream& os, huge a) {
        for (int i = a.val[0]; i >= 1; --i) {
            os << a.val[i];
        }
        return os;
    }
    huge operator /(huge b) {
        return impartire(val, b.val).first;
    }
    huge operator +(huge b) {
        return suma(val, b.val);
    }
    huge operator -(huge b) {
        return diferenta(val, b.val);
    }
    huge operator *(huge b) {
        return inmultire(val, b.val);
    }
    huge operator %(huge b) {
        return impartire(val, b.val).second;
    }
    huge operator ++() {
        val = suma(val, vector<int>{ 1 , 1 });
        return val;
    }
    huge operator ++(int) {
        val = suma(val, vector<int>{ 1, 1 });
        return diferenta(val, vector<int>{1, 1});
    }
    huge operator --() {
        val = diferenta(val, vector<int>{ 1, 1 });
        return val;
    }
    huge operator --(int) {
        val = diferenta(val, vector<int>{ 1, 1 });
        return suma(val, vector<int>{1, 1});
    }
    huge operator +=(huge b) {
        val = suma(val, b.val);
        return val;
    }
    huge operator -=(huge b) {
        val = diferenta(val, b.val);
        return val;
    }
    huge operator *=(huge b) {
        val = inmultire(val, b.val);
        return val;
    }
    huge operator /=(huge b) {
        val = impartire(val, b.val).first;
        return val;
    }
    huge operator %=(huge b) {
        val = impartire(val, b.val).second;
        return val;
    }
    bool operator <(huge b) {
        return (cmp(val, b.val) == 1);
    }
    bool operator ==(huge b) {
        return (cmp(val, b.val) == -1);
    }
    bool operator !=(huge b) {
        int ans = cmp(val, b.val);
        return (ans != -1);
    }
    bool operator >(huge b) {
        return (cmp(val, b.val) == 0);
    }
    bool operator >=(huge b) {
        int ans = cmp(val, b.val);
        return (ans == 0 || ans == -1);
    }
    bool operator <=(huge b) {
        int ans = cmp(val, b.val);
        return (ans == 1 || ans == -1);
    }
    bool is_pal() {
        huge b = val;
        reverse(b.val.begin() + 1, b.val.end());
        return (val == b.val);
    }
    huge rev() {
        huge b = val;
        reverse(b.val.begin() + 1, b.val.end());
        return b;
    }
};
huge max(huge a, huge b) {
    return (a > b ? a : b);
}
huge min(huge a, huge b) {
    return (a < b ? a : b);
}
huge sqrt(huge a) {
    huge st = 1, dr = a;
    huge ans = 0;
    while (st <= dr) {
        huge mid = (st + dr) / 2;
        if (mid * mid <= a) {
            ans = mid;
            st = mid + 1;
        }
        else {
            dr = mid - 1;
        }
    }
    return ans;
}
huge cbrt(huge a) {
    huge st = 1, dr = a;
    huge ans = 0;
    while (st <= dr) {
        huge mid = (st + dr) / 2;
        if (mid * mid * mid <= a) {
            ans = mid;
            st = mid + 1;
        }
        else {
            dr = mid - 1;
        }
    }
    return ans;
}
huge power(huge a, huge b) {
    if (b == 0) {
        return 1;
    }
    if (b % 2 == 1) {
        return a * power(a, b - 1);
    }
    huge P = power(a, b / 2);
    return P * P;
}
huge rad(huge a, huge k) {
    huge st = 1, dr = a;
    huge ans = 0;
    while (st <= dr) {
        huge mid = (st + dr) / 2;
        if (power(mid, k) <= a) {
            ans = mid;
            st = mid + 1;
        }
        else {
            dr = mid - 1;
        }
    }
    return ans;
}
huge log(huge a, huge k) {
    if (a < k) {
        return 0;
    }
    return log(a / k, k) + 1;
}
huge gcd(huge a, huge b) {
    while (b != 0) {
        huge c = a % b;
        a = b;
        b = c;
    }
    return a;
}
huge lcm(huge a, huge b) {
    return a * b / gcd(a, b);
}
huge fact(int n) {
    huge ans = 1;
    for (int i = 2; i <= n; ++i) {
        ans *= i;
    }
    return ans;
}
//Semnat tibinyte