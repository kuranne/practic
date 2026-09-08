#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <memory>

using namespace std;

class Wire
{
public:
    bool state = false;
};

class Gate
{
public:
    virtual ~Gate() = default;
    virtual void propagate() = 0;
};

class NANDGate : public Gate
{
    Wire *in1, *in2, *out;

public:
    NANDGate(Wire *a, Wire *b, Wire *c) : in1(a), in2(b), out(c) {}
    void propagate() override
    {

        out->state = !(in1->state && in2->state);
    }
};

class FullAdderHardware
{
    vector<Wire> wires;
    vector<unique_ptr<Gate>> gates;

public:
    FullAdderHardware() : wires(10)
    {
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[0], &wires[1], &wires[3])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[0], &wires[3], &wires[4])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[1], &wires[3], &wires[5])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[4], &wires[5], &wires[6])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[6], &wires[2], &wires[7])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[6], &wires[7], &wires[8])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[2], &wires[7], &wires[9])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[8], &wires[9], &wires[8])));
        gates.push_back(unique_ptr<Gate>(new NANDGate(&wires[3], &wires[7], &wires[9])));
    }
    pair<bool, bool> compute(bool a, bool b, bool cin)
    {
        wires[0].state = a;
        wires[1].state = b;
        wires[2].state = cin;
        for (auto &gate : gates)
            gate->propagate();
        return {wires[8].state, wires[9].state};
    }
};

struct Packet
{
    bool bit_a, bit_b, eof;
};

class VirtualSocket
{
    queue<Packet> q;
    mutex mtx;
    condition_variable cv;

public:
    void send(Packet p)
    {
        unique_lock<mutex> lock(mtx);
        q.push(p);
        cv.notify_one();
    }
    Packet receive()
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]
                { return !q.empty(); });
        Packet p = q.front();
        q.pop();
        return p;
    }
};

VirtualSocket client_to_server;
VirtualSocket server_to_client;

void hardware_server()
{
    FullAdderHardware alu;
    bool carry = false;
    while (true)
    {
        Packet p = client_to_server.receive();
        if (p.eof)
        {

            server_to_client.send({carry, false, true});
            break;
        }

        pair<bool, bool> res;
        thread hw_worker([&]()
                         { res = alu.compute(p.bit_a, p.bit_b, carry); });
        hw_worker.join();

        carry = res.second;
        server_to_client.send({res.first, false, false});
    }
}

int divide_str_by_2(char *s)
{
    int carry = 0, len = 0;
    while (*(s + len) != '\0')
        len++;
    for (int i = 0; i < len; ++i)
    {
        int val = (*(s + i) - '0') + carry * 10;
        *(s + i) = (val / 2) + '0';
        carry = val % 2;
    }
    return carry;
}

bool str_is_zero(const char *s)
{
    int i = 0;
    while (*(s + i) != '\0')
    {
        if (*(s + i) != '0')
            return false;
        i++;
    }
    return true;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char *str_a = (char *)calloc(10000, sizeof(char));
    char *str_b = (char *)calloc(10000, sizeof(char));

    if (argc == 3)
    {
        int i = 0;
        while (*(argv[1] + i))
        {
            *(str_a + i) = *(argv[1] + i);
            i++;
        }
        int j = 0;
        while (*(argv[2] + j))
        {
            *(str_b + j) = *(argv[2] + j);
            j++;
        }
    }
    else
    {
        cin >> str_a >> str_b;
    }

    thread server_thread(hardware_server);

    int bit_count = 0;
    while (!str_is_zero(str_a) || !str_is_zero(str_b))
    {
        bool bit_a = divide_str_by_2(str_a);
        bool bit_b = divide_str_by_2(str_b);
        client_to_server.send({bit_a, bit_b, false});
        bit_count++;
    }
    client_to_server.send({false, false, true});

    int cap = 64, sz = 0;
    double *result_bits = new double[cap]();

    while (true)
    {
        Packet p = server_to_client.receive();
        if (p.eof)
        {
            if (p.bit_a)
            {
                if (sz >= cap)
                {
                    cap += 64;
                    double *temp = (double *)calloc(cap, sizeof(double));
                    for (int i = 0; i < sz; ++i)
                        *(temp + i) = *(result_bits + i);
                    delete[] result_bits;
                    result_bits = temp;
                }
                *(result_bits + sz++) = 1.0;
            }
            break;
        }
        if (sz >= cap)
        {
            cap += 64;
            double *temp = new double[cap]();
            for (int i = 0; i < sz; ++i)
                *(temp + i) = *(result_bits + i);

            delete[] result_bits;
            result_bits = temp;
        }
        *(result_bits + sz++) = p.bit_a ? 1.0 : 0.0;
    }

    server_thread.join();

    int hex_cap = (sz / 4) + 2;
    char *hex_arr = (char *)calloc(hex_cap, sizeof(char));
    int hex_len = 0;

    for (int i = 0; i < sz; i += 4)
    {
        int hex_val = (int)*(result_bits + i) * 1 +
                      ((i + 1 < sz) ? (int)*(result_bits + i + 1) * 2 : 0) +
                      ((i + 2 < sz) ? (int)*(result_bits + i + 2) * 4 : 0) +
                      ((i + 3 < sz) ? (int)*(result_bits + i + 3) * 8 : 0);
        *(hex_arr + hex_len++) = (char)hex_val;
    }

    char *dec_str = (char *)calloc(10000, sizeof(char));
    *(dec_str + 0) = '0';
    int dec_len = 1;

    for (int i = hex_len - 1; i >= 0; --i)
    {
        int add_val = *(hex_arr + i);
        int current_carry = add_val;

        for (int j = 0; j < dec_len; ++j)
        {
            int val = (*(dec_str + j) - '0') * 16 + current_carry;
            *(dec_str + j) = (val % 10) + '0';
            current_carry = val / 10;
        }
        while (current_carry > 0)
        {
            *(dec_str + dec_len++) = (current_carry % 10) + '0';
            current_carry /= 10;
        }
    }

    for (int i = dec_len - 1; i >= 0; --i)
        cout << *(dec_str + i);
    cout << "\n";

    free(str_a);
    free(str_b);
    free(hex_arr);
    free(dec_str);

    delete[] result_bits;

    return 0;
}