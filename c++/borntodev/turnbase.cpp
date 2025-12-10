#include <bits/stdc++.h>
using namespace std;

class Player {
    private:
        double healt;
        double damage;
    public:
        void set(double hp, double dmg) {
            healt = hp;
            damage = dmg;
        }
        double hpleft() {
            return healt;
        }
        double damg() {
            return damage;
        }
        void attacked(double dmg) {
            healt -= dmg;
        }
};

double ddmg(int i) {
    return (++i % 3 == 0)? 1.5 : 1.0;
}

signed main() {
    Player first, second;
    vector<double> temp;
    double t;
    int i;
    for (i = 0; i < 4; i++) {
        cin >> t;
        temp.push_back(t);
    };
    first.set(temp[0], temp[2]);
    second.set(temp[1], temp[3]);

    i = 0;
    while (first.hpleft() > 0 && second.hpleft() > 0) {
        if (i % 2 == 0) {
            second.attacked(first.damg() * ddmg(i));
        } else {
            first.attacked(second.damg());
        }
        i++;
    }

    string cond;

    if (first.hpleft() > 0) {
        cond = "Win";
    } else {
        cond = "Lost";
    }

    cout << "You " << cond << endl;
    return 0;
}
