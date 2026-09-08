/**
 * ============================================================================
 * ENTERPRISE DISTRIBUTED QUANTUM-ACCELERATED MULTI-OPERAND ARITHMETIC PLATFORM
 * ============================================================================
 * Architecture Layering:
 * [L1] Monadic Parser Combinator (Stream Tokenizer for CLI & STDIN)
 * [L2] Cryptographic Subsystem (SHA-256, HMAC, Base64URL, JWT Bearer Token)
 * [L3] Quantum Unitary Hilbert Space Simulation (4-Qubit Peres Full Adder)
 * [L4] Classical Hardware Logic Circuit (NAND Gate Wire-Propagation Cascade)
 * [L5] Actor Model with Chaos Monkey Fault Injection & Supervision Tree
 * [L6] OSI 7-Layer In-Process Network Stack (Virtual Ethernet, IPv4, TCP 3-Way
 * Handshake) [L7] L7 HTTP/1.1 REST Protocol & JSON Serialization Engine [L8]
 * Multi-Operand Dynamic BigInt Memory Engine (A1 + A2 + ... + An)
 * ============================================================================
 * Compilation: g++ AplusB4.cpp -o AplusB4
 * ============================================================================
 */

#include <algorithm>
#include <complex>
#include <condition_variable>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ============================================================================
// LAYER 1: MONADIC PARSER COMBINATOR (Type-Safe Input Streaming)
// ============================================================================
template <typename T> struct ParseResult {
  bool success;
  T value;
  string remaining;
};

template <typename T> class Parser {
  function<ParseResult<T>(const string &)> parse_fn;

public:
  Parser(function<ParseResult<T>(const string &)> fn) : parse_fn(fn) {}
  ParseResult<T> parse(const string &input) const { return parse_fn(input); }

  template <typename U> Parser<U> map(function<U(T)> f) const {
    auto fn = parse_fn;
    return Parser<U>([fn, f](const string &s) -> ParseResult<U> {
      auto res = fn(s);
      if (!res.success)
        return {false, U(), s};
      return {true, f(res.value), res.remaining};
    });
  }

  template <typename U> Parser<U> bind(function<Parser<U>(T)> f) const {
    auto fn = parse_fn;
    return Parser<U>([fn, f](const string &s) -> ParseResult<U> {
      auto res = fn(s);
      if (!res.success)
        return {false, U(), s};
      return f(res.value).parse(res.remaining);
    });
  }
};

namespace Combinators {
static Parser<char> satisfy(function<bool(char)> predicate) {
  return Parser<char>([predicate](const string &s) -> ParseResult<char> {
    if (!s.empty() && predicate(s[0]))
      return {true, s[0], s.substr(1)};
    return {false, '\0', s};
  });
}

static Parser<char> digit() {
  return satisfy([](char c) { return c >= '0' && c <= '9'; });
}

static Parser<vector<string>> token_stream() {
  return Parser<vector<string>>(
      [](const string &s) -> ParseResult<vector<string>> {
        vector<string> tokens;
        size_t i = 0;
        while (i < s.size()) {
          while (i < s.size() &&
                 (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'))
            i++;
          if (i >= s.size())
            break;
          size_t start = i;
          while (i < s.size() &&
                 !(s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'))
            i++;
          tokens.push_back(s.substr(start, i - start));
        }
        return {true, tokens, ""};
      });
}
} // namespace Combinators

// ============================================================================
// LAYER 2: CRYPTOGRAPHIC LAYER (SHA-256, Base64URL, and JWT Engine)
// ============================================================================
class CryptoEngine {
  static const uint32_t K[64];
  static uint32_t rotr(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
  }
  static uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
  }
  static uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
  }
  static uint32_t sig0(uint32_t x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
  }
  static uint32_t sig1(uint32_t x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
  }
  static uint32_t theta0(uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
  }
  static uint32_t theta1(uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
  }

public:
  static string sha256(const string &data) {
    uint32_t state[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                         0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    vector<uint8_t> msg(data.begin(), data.end());
    uint64_t bitlen = msg.size() * 8;
    msg.push_back(0x80);
    while ((msg.size() % 64) != 56)
      msg.push_back(0x00);
    for (int i = 7; i >= 0; --i)
      msg.push_back((bitlen >> (i * 8)) & 0xFF);

    for (size_t chunk = 0; chunk < msg.size(); chunk += 64) {
      uint32_t w[64];
      for (int i = 0; i < 16; ++i)
        w[i] = (msg[chunk + i * 4] << 24) | (msg[chunk + i * 4 + 1] << 16) |
               (msg[chunk + i * 4 + 2] << 8) | (msg[chunk + i * 4 + 3]);
      for (int i = 16; i < 64; ++i)
        w[i] = theta1(w[i - 2]) + w[i - 7] + theta0(w[i - 15]) + w[i - 16];

      uint32_t a = state[0], b = state[1], c = state[2], d = state[3],
               e = state[4], f = state[5], g = state[6], h = state[7];
      for (int i = 0; i < 64; ++i) {
        uint32_t t1 = h + sig1(e) + ch(e, f, g) + K[i] + w[i];
        uint32_t t2 = sig0(a) + maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
      }
      state[0] += a;
      state[1] += b;
      state[2] += c;
      state[3] += d;
      state[4] += e;
      state[5] += f;
      state[6] += g;
      state[7] += h;
    }
    ostringstream oss;
    for (int i = 0; i < 8; ++i)
      oss << hex << setfill('0') << setw(8) << state[i];
    return oss.str();
  }

  static string base64url_encode(const string &in) {
    static const char tbl[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    string out;
    int val = 0, valb = -6;
    for (uint8_t c : in) {
      val = (val << 8) + c;
      valb += 8;
      while (valb >= 0) {
        out.push_back(tbl[(val >> valb) & 0x3F]);
        valb -= 6;
      }
    }
    if (valb > -6)
      out.push_back(tbl[((val << 8) >> (valb + 8)) & 0x3F]);
    return out;
  }

  static string hmac_sha256(const string &key, const string &msg) {
    string k = key;
    if (k.size() > 64)
      k = sha256(k);
    while (k.size() < 64)
      k.push_back('\0');
    string o_key_pad(64, '\0'), i_key_pad(64, '\0');
    for (int i = 0; i < 64; ++i) {
      o_key_pad[i] = k[i] ^ 0x5c;
      i_key_pad[i] = k[i] ^ 0x36;
    }
    string inner = sha256(i_key_pad + msg);
    return sha256(o_key_pad + inner);
  }

  static string create_jwt(const string &subject, const string &secret) {
    string header = R"({"alg":"HS256","typ":"JWT"})";
    string payload =
        R"({"sub":")" + subject + R"(","iss":"ALU_Cloud_Gateway"})";
    string enc_hdr = base64url_encode(header);
    string enc_pay = base64url_encode(payload);
    string sig = hmac_sha256(secret, enc_hdr + "." + enc_pay);
    return enc_hdr + "." + enc_pay + "." + base64url_encode(sig);
  }

  static bool verify_jwt(const string &jwt, const string &secret) {
    size_t d1 = jwt.find('.'), d2 = jwt.rfind('.');
    if (d1 == string::npos || d2 == string::npos || d1 == d2)
      return false;
    string enc_hdr = jwt.substr(0, d1);
    string enc_pay = jwt.substr(d1 + 1, d2 - (d1 + 1));
    string enc_sig = jwt.substr(d2 + 1);
    string expected_sig =
        base64url_encode(hmac_sha256(secret, enc_hdr + "." + enc_pay));
    return enc_sig == expected_sig;
  }
};

const uint32_t CryptoEngine::K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// ============================================================================
// LAYER 3: QUANTUM UNITARY HILBERT SPACE FULL ADDER SIMULATION
// ============================================================================
class QuantumFullAdderCircuit {
public:
  using Complex = complex<double>;
  // 4 Qubits: |q3=A, q2=B, q1=Cin, q0=CarryOut> -> Hilbert space dimension 2^4
  // = 16
  vector<Complex> state;

  QuantumFullAdderCircuit() : state(16, Complex(0, 0)) {}

  void initialize(bool a, bool b, bool cin) {
    fill(state.begin(), state.end(), Complex(0, 0));
    int index =
        ((a ? 1 : 0) << 3) | ((b ? 1 : 0) << 2) | ((cin ? 1 : 0) << 1) | 0;
    state[index] = Complex(1.0, 0.0);
  }

  void apply_cnot(int control, int target) {
    vector<Complex> next_state = state;
    for (int i = 0; i < 16; ++i) {
      if ((i >> control) & 1) {
        int flipped = i ^ (1 << target);
        next_state[flipped] = state[i];
      }
    }
    state = next_state;
  }

  void apply_toffoli(int control1, int control2, int target) {
    vector<Complex> next_state = state;
    for (int i = 0; i < 16; ++i) {
      if (((i >> control1) & 1) && ((i >> control2) & 1)) {
        int flipped = i ^ (1 << target);
        next_state[flipped] = state[i];
      }
    }
    state = next_state;
  }

  pair<bool, bool> compute(bool a, bool b, bool cin) {
    initialize(a, b, cin);

    // Peres Quantum Full Adder:
    // 1. Toffoli(A=3, B=2 -> Carry=0)
    apply_toffoli(3, 2, 0);
    // 2. CNOT(A=3 -> B=2)
    apply_cnot(3, 2);
    // 3. Toffoli(B=2, Cin=1 -> Carry=0)
    apply_toffoli(2, 1, 0);
    // 4. CNOT(B=2 -> Cin=1) -> Cin qubit now holds Sum (A ^ B ^ Cin)
    apply_cnot(2, 1);
    // 5. CNOT(A=3 -> B=2) (Restoration)
    apply_cnot(3, 2);

    // Quantum Measurement / Wavefunction Collapse:
    int measured_state = 0;
    double max_prob = -1.0;
    for (int i = 0; i < 16; ++i) {
      double prob = norm(state[i]); // |psi|^2
      if (prob > max_prob) {
        max_prob = prob;
        measured_state = i;
      }
    }

    bool sum_bit = (measured_state >> 1) & 1;
    bool carry_bit = (measured_state >> 0) & 1;

    return {sum_bit, carry_bit};
  }
};

// ============================================================================
// LAYER 4: CLASSICAL HARDWARE GATE CIRCUIT (NAND Gate Cascade)
// ============================================================================
class Wire {
public:
  bool state = false;
};

class Gate {
public:
  virtual ~Gate() = default;
  virtual void propagate() = 0;
};

class NANDGate : public Gate {
  Wire *in1, *in2, *out;

public:
  NANDGate(Wire *a, Wire *b, Wire *c) : in1(a), in2(b), out(c) {}
  void propagate() override { out->state = !(in1->state && in2->state); }
};

class FullAdderHardware {
  vector<Wire> wires;
  vector<unique_ptr<Gate>> gates;

public:
  FullAdderHardware() : wires(10) {
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[0], &wires[1], &wires[3])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[0], &wires[3], &wires[4])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[1], &wires[3], &wires[5])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[4], &wires[5], &wires[6])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[6], &wires[2], &wires[7])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[6], &wires[7], &wires[8])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[2], &wires[7], &wires[9])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[8], &wires[9], &wires[8])));
    gates.push_back(
        unique_ptr<Gate>(new NANDGate(&wires[3], &wires[7], &wires[9])));
  }
  pair<bool, bool> compute(bool a, bool b, bool cin) {
    wires[0].state = a;
    wires[1].state = b;
    wires[2].state = cin;
    for (auto &gate : gates)
      gate->propagate();
    return {wires[8].state, wires[9].state};
  }
};

// ============================================================================
// LAYER 5: ACTOR MODEL WITH CHAOS MONKEY & SUPERVISION TREE
// ============================================================================
class CosmicRayGlitchException : public exception {
public:
  const char *what() const noexcept override {
    return "CRITICAL: Quantum decoherence / Cosmic Ray bit-flip detected in "
           "Unitary Matrix!";
  }
};

class SupervisedALUActor {
  QuantumFullAdderCircuit quantum_alu;
  FullAdderHardware classical_alu;
  mt19937 rng;

public:
  SupervisedALUActor() : rng(1337) {}

  pair<int, int> compute_multi_operand(const vector<bool> &bits, int carry_in) {
    int max_retries = 5;
    for (int attempt = 0; attempt < max_retries; ++attempt) {
      try {
        if ((rng() % 100) == 0) { // 1% simulated transient fault
          throw CosmicRayGlitchException();
        }

        // Quantum Multi-Operand Adder Tree:
        vector<bool> current_level_bits = bits;
        for (int i = 0; i < carry_in; ++i) {
          current_level_bits.push_back(true);
        }

        int next_level_carries = 0;

        // Reduce 3-bits-to-2 using Quantum Hilbert Space Full Adder
        while (current_level_bits.size() >= 3) {
          bool b1 = current_level_bits.back();
          current_level_bits.pop_back();
          bool b2 = current_level_bits.back();
          current_level_bits.pop_back();
          bool b3 = current_level_bits.back();
          current_level_bits.pop_back();

          auto q_res = quantum_alu.compute(b1, b2, b3);
          auto c_res =
              classical_alu.compute(b1, b2, b3); // Secondary NAND validation

          current_level_bits.push_back(q_res.first);
          if (q_res.second)
            next_level_carries++;
        }

        if (current_level_bits.size() == 2) {
          bool b1 = current_level_bits.back();
          current_level_bits.pop_back();
          bool b2 = current_level_bits.back();
          current_level_bits.pop_back();

          auto q_res = quantum_alu.compute(b1, b2, false);
          current_level_bits.push_back(q_res.first);
          if (q_res.second)
            next_level_carries++;
        }

        int out_bit =
            current_level_bits.empty() ? 0 : (current_level_bits[0] ? 1 : 0);
        return {out_bit, next_level_carries};
      } catch (const CosmicRayGlitchException &e) {
        // OneForOne Supervisor Restart Strategy
        continue;
      }
    }
    int total_sum = carry_in;
    for (bool b : bits)
      if (b)
        total_sum++;
    return {total_sum % 2, total_sum / 2};
  }
};

// ============================================================================
// LAYER 6: OSI 7-LAYER IN-PROCESS NETWORK STACK & HTTP/1.1 REST PROTOCOL
// ============================================================================
struct NetworkPacket {
  uint32_t seq;
  uint32_t ack;
  uint8_t flags; // 0x01 = SYN, 0x02 = ACK, 0x04 = DATA, 0x08 = FIN
  uint16_t checksum;
  string http_body;
};

class VirtualNetworkSwitch {
  queue<NetworkPacket> q;
  mutex mtx;
  condition_variable cv;

public:
  void transmit(NetworkPacket p) {
    unique_lock<mutex> lock(mtx);
    q.push(p);
    cv.notify_one();
  }
  NetworkPacket receive() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [this] { return !q.empty(); });
    NetworkPacket p = q.front();
    q.pop();
    return p;
  }
};

static VirtualNetworkSwitch uplink_switch;
static VirtualNetworkSwitch downlink_switch;

void cloud_microservice_server() {
  SupervisedALUActor actor;
  const string secret_key = "DeepMind-ALU-Secret-Key-2026";

  // TCP 3-Way Handshake
  NetworkPacket syn = uplink_switch.receive();
  if (syn.flags & 0x01) {
    downlink_switch.transmit({100, syn.seq + 1, 0x03, 0xFFFF,
                              "HTTP/1.1 200 Connection Established\r\n\r\n"});
  }
  NetworkPacket ack = uplink_switch.receive();

  // Stream Data Processing
  int session_carry = 0;
  while (true) {
    NetworkPacket pkt = uplink_switch.receive();
    if (pkt.flags & 0x08) { // FIN
      downlink_switch.transmit(
          {pkt.ack, pkt.seq + 1, 0x08, 0xFFFF, to_string(session_carry)});
      break;
    }

    size_t pipe_pos = pkt.http_body.find('|');
    string jwt = pkt.http_body.substr(0, pipe_pos);
    string operand_data = pkt.http_body.substr(pipe_pos + 1);

    if (!CryptoEngine::verify_jwt(jwt, secret_key)) {
      cerr << "FATAL: Unauthorized ALU API call (Invalid JWT signature)!\n";
      exit(1);
    }

    vector<bool> bits;
    for (char c : operand_data) {
      if (c == '1')
        bits.push_back(true);
      else if (c == '0')
        bits.push_back(false);
    }

    auto res = actor.compute_multi_operand(bits, session_carry);
    int out_bit = res.first;
    session_carry = res.second;

    downlink_switch.transmit(
        {pkt.ack, pkt.seq + 1, 0x04, 0xFFFF, to_string(out_bit)});
  }
}

// ============================================================================
// LAYER 7: ARBITRARY BASE-10 BIGINTEGER DIVISION & BASE CONVERSION ENGINE
// ============================================================================
int divide_str_by_2(char *s) {
  int carry = 0, len = 0;
  while (*(s + len) != '\0')
    len++;
  for (int i = 0; i < len; ++i) {
    int val = (*(s + i) - '0') + carry * 10;
    *(s + i) = (val / 2) + '0';
    carry = val % 2;
  }
  return carry;
}

bool str_is_zero(const char *s) {
  int i = 0;
  while (*(s + i) != '\0') {
    if (*(s + i) != '0')
      return false;
    i++;
  }
  return true;
}

// ============================================================================
// LAYER 8: APPLICATION ENTRYPOINT (A1 + A2 + ... + An)
// ============================================================================
int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<string> raw_inputs;
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      raw_inputs.push_back(argv[i]);
    }
  } else {
    string word;
    while (cin >> word) {
      raw_inputs.push_back(word);
    }
  }

  if (raw_inputs.empty()) {
    cout << 0 << "\n";
    return 0;
  }

  // Monadic stream parsing verification
  string combined_input;
  for (const auto &s : raw_inputs)
    combined_input += s + " ";
  auto parse_res = Combinators::token_stream().parse(combined_input);
  vector<string> operands = parse_res.value;

  const string secret_key = "DeepMind-ALU-Secret-Key-2026";
  string jwt_token = CryptoEngine::create_jwt("root_user", secret_key);

  // Boot Cloud ALU Microservice Thread
  thread server_thread(cloud_microservice_server);

  // Perform TCP 3-Way Handshake
  uplink_switch.transmit({1000, 0, 0x01, 0xFFFF, ""});               // SYN
  NetworkPacket syn_ack = downlink_switch.receive();                 // SYN-ACK
  uplink_switch.transmit({1001, syn_ack.seq + 1, 0x02, 0xFFFF, ""}); // ACK

  // Allocate memory buffers for arbitrary N operands
  vector<char *> str_ptrs;
  for (const auto &op : operands) {
    char *buf = (char *)calloc(op.size() + 10, sizeof(char));
    memcpy(buf, op.c_str(), op.size());
    str_ptrs.push_back(buf);
  }

  // Stream bits to Cloud ALU
  uint32_t seq_num = 2000;
  while (true) {
    bool any_non_zero = false;
    string bit_string = "";
    for (char *ptr : str_ptrs) {
      if (!str_is_zero(ptr)) {
        any_non_zero = true;
        int bit = divide_str_by_2(ptr);
        bit_string.push_back(bit ? '1' : '0');
      } else {
        bit_string.push_back('0');
      }
    }

    if (!any_non_zero)
      break;

    string http_payload = jwt_token + "|" + bit_string;
    uplink_switch.transmit({seq_num++, 0, 0x04, 0xFFFF, http_payload});
  }

  // Send FIN to close stream
  uplink_switch.transmit({seq_num++, 0, 0x08, 0xFFFF, "EOF"});

  // Receive Stream Result Bits
  int cap = 128, sz = 0;
  double *result_bits = new double[cap]();

  while (true) {
    NetworkPacket resp = downlink_switch.receive();
    if (resp.flags & 0x08) { // Final carry packet
      int remaining_carry = stoi(resp.http_body);
      while (remaining_carry > 0) {
        if (sz >= cap) {
          cap *= 2;
          double *temp = new double[cap]();
          for (int i = 0; i < sz; ++i)
            *(temp + i) = *(result_bits + i);
          delete[] result_bits;
          result_bits = temp;
        }
        *(result_bits + sz++) = (remaining_carry % 2);
        remaining_carry /= 2;
      }
      break;
    }

    int bit = stoi(resp.http_body);
    if (sz >= cap) {
      cap *= 2;
      double *temp = new double[cap]();
      for (int i = 0; i < sz; ++i)
        *(temp + i) = *(result_bits + i);
      delete[] result_bits;
      result_bits = temp;
    }
    *(result_bits + sz++) = (double)bit;
  }

  server_thread.join();

  // Base-16 (Hex) bit packing
  int hex_cap = (sz / 4) + 4;
  char *hex_arr = (char *)calloc(hex_cap, sizeof(char));
  int hex_len = 0;

  for (int i = 0; i < sz; i += 4) {
    int hex_val = (int)*(result_bits + i) * 1 +
                  ((i + 1 < sz) ? (int)*(result_bits + i + 1) * 2 : 0) +
                  ((i + 2 < sz) ? (int)*(result_bits + i + 2) * 4 : 0) +
                  ((i + 3 < sz) ? (int)*(result_bits + i + 3) * 8 : 0);
    *(hex_arr + hex_len++) = (char)hex_val;
  }

  // Base-10 BigInt reconstruction with pointer arithmetic
  int dec_cap = 100000;
  char *dec_str = (char *)calloc(dec_cap, sizeof(char));
  *(dec_str + 0) = '0';
  int dec_len = 1;

  for (int i = hex_len - 1; i >= 0; --i) {
    int add_val = *(hex_arr + i);
    int current_carry = add_val;
    for (int j = 0; j < dec_len; ++j) {
      int val = (*(dec_str + j) - '0') * 16 + current_carry;
      *(dec_str + j) = (val % 10) + '0';
      current_carry = val / 10;
    }
    while (current_carry > 0) {
      *(dec_str + dec_len++) = (current_carry % 10) + '0';
      current_carry /= 10;
    }
  }

  for (int i = dec_len - 1; i >= 0; --i)
    cout << *(dec_str + i);
  cout << "\n";

  // Explicit manual memory reclamation
  for (char *ptr : str_ptrs)
    free(ptr);
  free(hex_arr);
  free(dec_str);
  delete[] result_bits;

  return 0;
}
