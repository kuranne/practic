/**
 * ============================================================================
 * ENTERPRISE DISTRIBUTED QUANTUM-ACCELERATED MULTI-OPERAND ARITHMETIC PLATFORM
 * ============================================================================
 * [ARCHITECTURAL FORMALISM & CATEGORICAL HIERARCHY]
 *
 * Layer 1: Monadic Category-Theoretic Parser Combinator
 *          - Type-safe functorial mapping & monadic bind (>>=) stream tokenization
 *
 * Layer 2: Cryptographic Authentication Subsystem
 *          - RFC 6234 SHA-256 Digest Engine & RFC 2104 HMAC-SHA256
 *          - RFC 7515/7519 JSON Web Signature (JWS) / JWT Bearer Token validation
 *
 * Layer 3: Quantum Unitary Hilbert Space Simulation (H = C^16)
 *          - 4-Qubit Reversible Peres Full Adder Circuit:
 *            |psi_0> = |A, B, Cin, 0> in H_16
 *            U_Peres = CNOT(3->2) . CNOT(2->1) . Toffoli(2,1->0) . CNOT(3->2) . Toffoli(3,2->0)
 *          - Wavefunction collapse via Born's Rule: P(k) = |<k|psi>|^2
 *
 * Layer 4: Classical Hardware Logic Circuit
 *          - Transistor-level 9-NAND Gate Wire-Propagation Cascade validation
 *
 * Layer 5: Distributed Actor Model with Multi-Threaded Large Array Reduction
 *          - Thread-safe Enterprise Worker Thread Pool (EnterpriseThreadPool)
 *          - Parallel Wallace Tree / Carry-Save Adder (CSA) multi-operand reduction
 *          - 1% simulated cosmic ray quantum decoherence fault injection
 *          - Erlang/OTP OneForOne supervisor restart strategy
 *
 * Layer 6: OSI 7-Layer In-Process Network Stack & HTTP/1.1 REST Protocol
 *          - Virtual Ethernet Switch, IPv4 packetization, TCP 3-Way Handshake
 *          - RESTful HTTP/1.1 endpoint with JWT bearer authentication
 *
 * Layer 7: Fast Fourier Transform (FFT) & Schönhage–Strassen Polynomial Engine
 *          - Evaluation of A(x) = \sum a_i x^i on N-th roots of unity \omega_N^k = e^{2\pi i k / N}
 *          - Cooley-Tukey Radix-2 Decimation-in-Time (DIT) Butterfly Network
 *          - Inverse Fast Fourier Transform (IFFT) coefficient interpolation & convolution
 *
 * Layer 8: Lattice-Based Homomorphic Encryption Engine (Ring-LWE)
 *          - Cyclotomic Polynomial Ring R_q = Z_q[x] / (x^d + 1)
 *          - Zero-Trust Confidential Cloud ALU: Homomorphic Addition (c_sum = c_a (+) c_b)
 *          - Secret-key decryption and noise-budget management
 *
 * Layer 9: Unbounded Dynamic Radix Conversion & BigInteger Engine
 *          - O(M * L) limb-based conversion between Base-10^9 and Base-2^32
 *          - Completely uncapped dynamic scaling: 100k+, 1M+, 10M+ digits
 *
 * Layer 10: Multi-Operand Zero-Trust Confidential Computing Quantum Runtime & Entrypoint
 *          - Multi-threaded operand ingestion, lattice-encrypted streaming, and CLI I/O
 * ============================================================================
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <condition_variable>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#if defined(__ARM_NEON)
#include <arm_neon.h>
#elif defined(__AVX2__)
#include <immintrin.h>
#endif

using namespace std;

// ============================================================================
// LAYER 1: MONADIC PARSER COMBINATOR (Type-Safe Input Streaming)
// ============================================================================
template <typename T>
struct ParseResult
{
  bool success;
  T value;
  string remaining;
};

template <typename T>
class Parser
{
  function<ParseResult<T>(const string &)> parse_fn;

public:
  Parser(function<ParseResult<T>(const string &)> fn) : parse_fn(fn) {}
  ParseResult<T> parse(const string &input) const { return parse_fn(input); }

  template <typename U>
  Parser<U> map(function<U(T)> f) const
  {
    auto fn = parse_fn;
    return Parser<U>([fn, f](const string &s) -> ParseResult<U>
                     {
      auto res = fn(s);
      if (!res.success)
        return {false, U(), s};
      return {true, f(res.value), res.remaining}; });
  }

  template <typename U>
  Parser<U> bind(function<Parser<U>(T)> f) const
  {
    auto fn = parse_fn;
    return Parser<U>([fn, f](const string &s) -> ParseResult<U>
                     {
      auto res = fn(s);
      if (!res.success)
        return {false, U(), s};
      return f(res.value).parse(res.remaining); });
  }
};

namespace Combinators
{
  static Parser<char> satisfy(function<bool(char)> predicate)
  {
    return Parser<char>([predicate](const string &s) -> ParseResult<char>
                        {
    if (!s.empty() && predicate(s[0]))
      return {true, s[0], s.substr(1)};
    return {false, '\0', s}; });
  }

  [[maybe_unused]] static Parser<char> digit()
  {
    return satisfy([](char c)
                   { return c >= '0' && c <= '9'; });
  }

  static Parser<vector<string>> token_stream()
  {
    return Parser<vector<string>>(
        [](const string &s) -> ParseResult<vector<string>>
        {
          vector<string> tokens;
          size_t i = 0;
          while (i < s.size())
          {
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

  class FastIOReader
  {
    static const size_t BUF_SIZE = 1 << 20; // 1MB chunk buffer
    char buffer[BUF_SIZE];

  public:
    FastIOReader() = default;

    string read_all()
    {
      string out;
      while (true)
      {
        size_t bytes = fread(buffer, 1, BUF_SIZE, stdin);
        if (bytes == 0)
          break;
        out.append(buffer, bytes);
      }
      return out;
    }
  };

  struct ParsedDecimal
  {
    bool is_negative = false;
    string int_part;
    string frac_part;
  };

  static ParsedDecimal parse_decimal(const string &s)
  {
    ParsedDecimal res;
    if (s.empty())
      return res;
    size_t idx = 0;
    if (s[0] == '-')
    {
      res.is_negative = true;
      idx = 1;
    }
    else if (s[0] == '+')
    {
      idx = 1;
    }
    size_t dot_pos = s.find('.', idx);
    if (dot_pos == string::npos)
    {
      res.int_part = s.substr(idx);
      res.frac_part = "";
    }
    else
    {
      res.int_part = s.substr(idx, dot_pos - idx);
      res.frac_part = s.substr(dot_pos + 1);
    }
    if (res.int_part.empty())
      res.int_part = "0";
    return res;
  }

  static string format_decimal(bool is_neg, string raw_dec, size_t scale)
  {
    if (raw_dec == "0" || raw_dec.empty())
      return "0";

    if (scale == 0)
      return is_neg ? ("-" + raw_dec) : raw_dec;

    if (raw_dec.size() <= scale)
    {
      raw_dec = string(scale + 1 - raw_dec.size(), '0') + raw_dec;
    }

    string int_part = raw_dec.substr(0, raw_dec.size() - scale);
    string frac_part = raw_dec.substr(raw_dec.size() - scale);

    // Strip trailing zeros from fractional part
    while (!frac_part.empty() && frac_part.back() == '0')
    {
      frac_part.pop_back();
    }

    if (frac_part.empty())
    {
      if (int_part == "0")
        return "0";
      return is_neg ? ("-" + int_part) : int_part;
    }

    return (is_neg ? "-" : "") + int_part + "." + frac_part;
  }
} // namespace Combinators

// ============================================================================
// LAYER 2: CRYPTOGRAPHIC SUBSYSTEM (SHA-256, HMAC, and JWT Engine)
// ============================================================================
class CryptoEngine
{
  static const uint32_t K[64];
  static inline uint32_t rotr(uint32_t x, uint32_t n)
  {
    return (x >> n) | (x << (32 - n));
  }
  static inline uint32_t ch(uint32_t x, uint32_t y, uint32_t z)
  {
    return (x & y) ^ (~x & z);
  }
  static inline uint32_t maj(uint32_t x, uint32_t y, uint32_t z)
  {
    return (x & y) ^ (x & z) ^ (y & z);
  }
  static inline uint32_t sig0(uint32_t x)
  {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
  }
  static inline uint32_t sig1(uint32_t x)
  {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
  }
  static inline uint32_t theta0(uint32_t x)
  {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
  }
  static inline uint32_t theta1(uint32_t x)
  {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
  }

public:
  static string sha256(const string &data)
  {
    uint32_t state[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                         0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    vector<uint8_t> msg(data.begin(), data.end());
    uint64_t bitlen = (uint64_t)msg.size() * 8;
    msg.push_back(0x80);
    while ((msg.size() % 64) != 56)
      msg.push_back(0x00);
    for (int i = 7; i >= 0; --i)
      msg.push_back((bitlen >> (i * 8)) & 0xFF);

    for (size_t chunk = 0; chunk < msg.size(); chunk += 64)
    {
      uint32_t w[64];
      for (int i = 0; i < 16; ++i)
        w[i] = ((uint32_t)msg[chunk + i * 4] << 24) |
               ((uint32_t)msg[chunk + i * 4 + 1] << 16) |
               ((uint32_t)msg[chunk + i * 4 + 2] << 8) |
               ((uint32_t)msg[chunk + i * 4 + 3]);
      for (int i = 16; i < 64; ++i)
        w[i] = theta1(w[i - 2]) + w[i - 7] + theta0(w[i - 15]) + w[i - 16];

      uint32_t a = state[0], b = state[1], c = state[2], d = state[3],
               e = state[4], f = state[5], g = state[6], h = state[7];
      for (int i = 0; i < 64; ++i)
      {
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

  static string base64url_encode(const string &in)
  {
    static const char tbl[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    string out;
    int val = 0, valb = -6;
    for (uint8_t c : in)
    {
      val = (val << 8) + c;
      valb += 8;
      while (valb >= 0)
      {
        out.push_back(tbl[(val >> valb) & 0x3F]);
        valb -= 6;
      }
    }
    if (valb > -6)
      out.push_back(tbl[((val << 8) >> (valb + 8)) & 0x3F]);
    return out;
  }

  static string hmac_sha256(const string &key, const string &msg)
  {
    string k = key;
    if (k.size() > 64)
      k = sha256(k);
    while (k.size() < 64)
      k.push_back('\0');
    string o_key_pad(64, '\0'), i_key_pad(64, '\0');
    for (int i = 0; i < 64; ++i)
    {
      o_key_pad[i] = k[i] ^ 0x5c;
      i_key_pad[i] = k[i] ^ 0x36;
    }
    string inner = sha256(i_key_pad + msg);
    return sha256(o_key_pad + inner);
  }

  static string create_jwt(const string &subject, const string &secret)
  {
    string header = R"({"alg":"HS256","typ":"JWT"})";
    string payload =
        R"({"sub":")" + subject + R"(","iss":"ALU_Cloud_Gateway"})";
    string enc_hdr = base64url_encode(header);
    string enc_pay = base64url_encode(payload);
    string sig = hmac_sha256(secret, enc_hdr + "." + enc_pay);
    return enc_hdr + "." + enc_pay + "." + base64url_encode(sig);
  }

  static bool verify_jwt(const string &jwt, const string &secret)
  {
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
class QuantumFullAdderCircuit
{
public:
  using Complex = complex<double>;
  // 4 Qubits: |q3=A, q2=B, q1=Cin, q0=CarryOut> in Hilbert Space H = C^16
  array<Complex, 16> state;

  QuantumFullAdderCircuit()
  {
    state.fill(Complex(0, 0));
  }

  inline void initialize(bool a, bool b, bool cin)
  {
    state.fill(Complex(0, 0));
    int index =
        ((a ? 1 : 0) << 3) | ((b ? 1 : 0) << 2) | ((cin ? 1 : 0) << 1) | 0;
    state[index] = Complex(1.0, 0.0);
  }

  inline void apply_cnot(int control, int target)
  {
    int c_mask = 1 << control;
    int t_mask = 1 << target;
    for (int i = 0; i < 16; ++i)
    {
      if ((i & c_mask) && !(i & t_mask))
      {
        std::swap(state[i], state[i | t_mask]);
      }
    }
  }

  inline void apply_toffoli(int control1, int control2, int target)
  {
    int c_mask = (1 << control1) | (1 << control2);
    int t_mask = 1 << target;
    for (int i = 0; i < 16; ++i)
    {
      if (((i & c_mask) == c_mask) && !(i & t_mask))
      {
        std::swap(state[i], state[i | t_mask]);
      }
    }
  }

  pair<bool, bool> compute(bool a, bool b, bool cin)
  {
    initialize(a, b, cin);

    // Peres Reversible Quantum Full Adder:
    // 1. Toffoli(A=3, B=2 -> Carry=0)
    apply_toffoli(3, 2, 0);
    // 2. CNOT(A=3 -> B=2)
    apply_cnot(3, 2);
    // 3. Toffoli(B=2, Cin=1 -> Carry=0)
    apply_toffoli(2, 1, 0);
    // 4. CNOT(B=2 -> Cin=1) -> Cin qubit now holds Sum (A ^ B ^ Cin)
    apply_cnot(2, 1);
    // 5. CNOT(A=3 -> B=2) (Restoration of register B)
    apply_cnot(3, 2);

    // Quantum Measurement / Wavefunction Collapse via Born's Rule
    int measured_state = 0;
    for (int i = 0; i < 16; ++i)
    {
      if (norm(state[i]) > 0.5)
      {
        measured_state = i;
        break;
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
  void propagate() override { out->state = !(in1->state && in2->state); }
};

class FullAdderHardware
{
  vector<Wire> wires;
  vector<unique_ptr<Gate>> gates;

public:
  FullAdderHardware() : wires(10)
  {
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

// ============================================================================
// LAYER 5: ACTOR MODEL WITH MULTI-THREADED LARGE ARRAY REDUCTION
// ============================================================================
class CosmicRayGlitchException : public exception
{
public:
  const char *what() const noexcept override
  {
    return "CRITICAL: Quantum decoherence / Cosmic Ray bit-flip detected in "
           "Unitary Matrix!";
  }
};

class EnterpriseThreadPool
{
  vector<thread> workers;
  queue<function<void()>> tasks;
  mutex queue_mtx;
  condition_variable cv;
  bool stop = false;

public:
  EnterpriseThreadPool(size_t threads = max(1u, thread::hardware_concurrency()))
  {
    for (size_t i = 0; i < threads; ++i)
    {
      workers.emplace_back([this]
                           {
        while (true) {
          function<void()> task;
          {
            unique_lock<mutex> lock(this->queue_mtx);
            this->cv.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
            if (this->stop && this->tasks.empty()) return;
            task = std::move(this->tasks.front());
            this->tasks.pop();
          }
          task();
        } });
    }
  }

  template <class F, class... Args>
  auto enqueue(F &&f, Args &&...args)
      -> future<decltype(std::declval<F>()(std::declval<Args>()...))>
  {
    using return_type = decltype(std::declval<F>()(std::declval<Args>()...));
    auto task = make_shared<packaged_task<return_type()>>(
        bind(std::forward<F>(f), std::forward<Args>(args)...));
    future<return_type> res = task->get_future();
    {
      unique_lock<mutex> lock(queue_mtx);
      if (stop)
        throw runtime_error("enqueue on stopped ThreadPool");
      tasks.emplace([task]()
                    { (*task)(); });
    }
    cv.notify_one();
    return res;
  }

  size_t size() const { return workers.size(); }

  ~EnterpriseThreadPool()
  {
    {
      unique_lock<mutex> lock(queue_mtx);
      stop = true;
    }
    cv.notify_all();
    for (thread &worker : workers)
    {
      if (worker.joinable())
        worker.join();
    }
  }
};

class SupervisedALUActor
{
  QuantumFullAdderCircuit quantum_alu;
  FullAdderHardware classical_alu;
  mt19937 rng;

public:
  SupervisedALUActor() : rng(1337) {}

  pair<int, int> compute_multi_operand(const vector<bool> &bits, int carry_in)
  {
    int max_retries = 5;
    for (int attempt = 0; attempt < max_retries; ++attempt)
    {
      try
      {
        if ((rng() % 100) == 0)
        { // 1% simulated transient fault
          throw CosmicRayGlitchException();
        }

        // Quantum Multi-Operand Carry-Save Adder Tree:
        vector<bool> current_level_bits;
        current_level_bits.reserve(bits.size() + carry_in + 16);
        current_level_bits.insert(current_level_bits.end(), bits.begin(), bits.end());
        current_level_bits.insert(current_level_bits.end(), carry_in, true);

        int next_level_carries = 0;

        // Reduce 3-bits-to-2 using Quantum Hilbert Space Full Adder
        while (current_level_bits.size() >= 3)
        {
          size_t sz = current_level_bits.size();
          bool b1 = current_level_bits[sz - 1];
          bool b2 = current_level_bits[sz - 2];
          bool b3 = current_level_bits[sz - 3];
          current_level_bits.pop_back();
          current_level_bits.pop_back();

          auto q_res = quantum_alu.compute(b1, b2, b3);
          auto c_res = classical_alu.compute(b1, b2, b3); // Secondary NAND validation
          if (q_res.first != c_res.first || q_res.second != c_res.second)
          {
            throw CosmicRayGlitchException();
          }

          current_level_bits.back() = q_res.first;
          if (q_res.second)
            next_level_carries++;
        }

        if (current_level_bits.size() == 2)
        {
          bool b1 = current_level_bits[1];
          bool b2 = current_level_bits[0];
          current_level_bits.pop_back();

          auto q_res = quantum_alu.compute(b1, b2, false);
          auto c_res = classical_alu.compute(b1, b2, false);
          if (q_res.first != c_res.first || q_res.second != c_res.second)
          {
            throw CosmicRayGlitchException();
          }

          current_level_bits[0] = q_res.first;
          if (q_res.second)
            next_level_carries++;
        }

        int out_bit =
            current_level_bits.empty() ? 0 : (current_level_bits[0] ? 1 : 0);
        return {out_bit, next_level_carries};
      }
      catch (const CosmicRayGlitchException &e)
      {
        // Erlang/OTP OneForOne Supervisor Restart Strategy
        continue;
      }
    }
    int total_sum = carry_in;
    for (bool b : bits)
      if (b)
        total_sum++;
    return {total_sum % 2, total_sum / 2};
  }

  // Parallel Large Array Reduction for massive multi-operand bit vectors
  pair<int, int> compute_multi_operand_parallel(const vector<bool> &bits, int carry_in, EnterpriseThreadPool &pool)
  {
    if (bits.size() < 128 || pool.size() <= 1)
    {
      return compute_multi_operand(bits, carry_in);
    }

    size_t num_threads = pool.size();
    size_t chunk_size = (bits.size() + num_threads - 1) / num_threads;
    vector<future<pair<vector<bool>, int>>> futures;

    for (size_t t = 0; t < num_threads; ++t)
    {
      size_t start = t * chunk_size;
      size_t end = min(bits.size(), start + chunk_size);
      if (start >= end)
        continue;

      futures.push_back(pool.enqueue([&bits, start, end]
                                     {
        SupervisedALUActor local_actor;
        vector<bool> current_level(bits.begin() + start, bits.begin() + end);
        int local_carries = 0;

        while (current_level.size() >= 3) {
          bool b1 = current_level.back(); current_level.pop_back();
          bool b2 = current_level.back(); current_level.pop_back();
          bool b3 = current_level.back(); current_level.pop_back();

          auto q_res = local_actor.quantum_alu.compute(b1, b2, b3);
          current_level.push_back(q_res.first);
          if (q_res.second) local_carries++;
        }

        if (current_level.size() == 2) {
          bool b1 = current_level.back(); current_level.pop_back();
          bool b2 = current_level.back(); current_level.pop_back();
          auto q_res = local_actor.quantum_alu.compute(b1, b2, false);
          current_level.push_back(q_res.first);
          if (q_res.second) local_carries++;
        }

        return make_pair(current_level, local_carries); }));
    }

    vector<bool> merged_bits;
    int tree_carries = 0;
    for (auto &f : futures)
    {
      auto res = f.get();
      merged_bits.insert(merged_bits.end(), res.first.begin(), res.first.end());
      tree_carries += res.second;
    }

    auto merge_res = compute_multi_operand(merged_bits, carry_in);
    return {merge_res.first, merge_res.second + tree_carries};
  }
};

// ============================================================================
// LAYER 7: FAST FOURIER TRANSFORM (FFT) & SCHÖNHAGE–STRASSEN POLYNOMIAL ENGINE
// ============================================================================
class FastFourierTransform
{
public:
  using Complex = complex<double>;
  static constexpr double PI = 3.141592653589793238462643383279502884;

private:
  inline static vector<Complex> roots;
  inline static vector<Complex> inv_roots;
  inline static mutex twiddle_mtx;

  static void ensure_twiddles(int n)
  {
    unique_lock<mutex> lock(twiddle_mtx);
    if ((int)roots.size() >= n)
      return;
    int old_size = (int)roots.size();
    if (old_size == 0)
    {
      roots.resize(2);
      inv_roots.resize(2);
      roots[1] = Complex(1, 0);
      inv_roots[1] = Complex(1, 0);
      old_size = 2;
    }
    while ((int)roots.size() < n)
    {
      int k = (int)roots.size();
      roots.resize(k * 2);
      inv_roots.resize(k * 2);
      double ang = 2.0 * PI / (k * 2);
      for (int i = k / 2; i < k; ++i)
      {
        roots[2 * i] = roots[i];
        inv_roots[2 * i] = inv_roots[i];
        double a = ang * (2 * i + 1 - k);
        roots[2 * i + 1] = Complex(cos(a), sin(a));
        inv_roots[2 * i + 1] = Complex(cos(-a), sin(-a));
      }
    }
  }

public:
  static void clear_twiddles()
  {
    unique_lock<mutex> lock(twiddle_mtx);
    roots.clear();
    roots.shrink_to_fit();
    inv_roots.clear();
    inv_roots.shrink_to_fit();
  }

  // In-place Bit-Reversal Permutation: O(N)
  static void bit_reverse_permutation(vector<Complex> &a)
  {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; ++i)
    {
      int bit = n >> 1;
      for (; j & bit; bit >>= 1)
        j ^= bit;
      j ^= bit;
      if (i < j)
        swap(a[i], a[j]);
    }
  }

  // Cooley-Tukey Radix-2 Decimation-In-Time (DIT) Fast Fourier Transform: O(N log N) with Zero-Allocation Twiddle Lookup
  static void fft(vector<Complex> &a, bool invert)
  {
    int n = (int)a.size();
    ensure_twiddles(n);
    bit_reverse_permutation(a);

    const Complex *tw = invert ? inv_roots.data() : roots.data();

    for (int len = 2; len <= n; len <<= 1)
    {
      int half = len / 2;
      const Complex *w = tw + half;
      for (int i = 0; i < n; i += len)
      {
        for (int j = 0; j < half; ++j)
        {
          Complex u = a[i + j];
          Complex v = a[i + j + half] * w[j];
          a[i + j] = u + v;
          a[i + j + half] = u - v;
        }
      }
    }

    if (invert)
    {
      double inv_n = 1.0 / (double)n;
      for (Complex &x : a)
        x *= inv_n;
    }
  }

  // Polynomial Evaluation on N-th Roots of Unity
  static vector<Complex> evaluate_on_roots_of_unity(const vector<double> &coeffs)
  {
    int n = 1;
    while (n < (int)coeffs.size())
      n <<= 1;
    vector<Complex> a(n, Complex(0.0, 0.0));
    for (size_t i = 0; i < coeffs.size(); ++i)
      a[i] = Complex(coeffs[i], 0.0);
    fft(a, false);
    return a;
  }

  // Inverse FFT: Reconstruct Polynomial Coefficients from Roots of Unity
  static vector<double> interpolate_from_roots_of_unity(vector<Complex> point_values)
  {
    fft(point_values, true);
    vector<double> coeffs(point_values.size());
    for (size_t i = 0; i < point_values.size(); ++i)
    {
      coeffs[i] = point_values[i].real();
    }
    return coeffs;
  }

  // SIMD Vectorized Complex Pointwise Multiplication
  static void vector_complex_mul(Complex *a, const Complex *b, size_t n)
  {
#if defined(__ARM_NEON)
    size_t i = 0;
    for (; i + 1 < n; i += 2)
    {
      float64x2_t a0 = vld1q_f64(reinterpret_cast<const double*>(&a[i]));
      float64x2_t a1 = vld1q_f64(reinterpret_cast<const double*>(&a[i + 1]));
      float64x2_t b0 = vld1q_f64(reinterpret_cast<const double*>(&b[i]));
      float64x2_t b1 = vld1q_f64(reinterpret_cast<const double*>(&b[i + 1]));

      double ar0 = vgetq_lane_f64(a0, 0);
      double ai0 = vgetq_lane_f64(a0, 1);
      double br0 = vgetq_lane_f64(b0, 0);
      double bi0 = vgetq_lane_f64(b0, 1);

      float64x2_t r0 = {ar0 * br0 - ai0 * bi0, ar0 * bi0 + ai0 * br0};
      vst1q_f64(reinterpret_cast<double*>(&a[i]), r0);

      double ar1 = vgetq_lane_f64(a1, 0);
      double ai1 = vgetq_lane_f64(a1, 1);
      double br1 = vgetq_lane_f64(b1, 0);
      double bi1 = vgetq_lane_f64(b1, 1);
      float64x2_t r1 = {ar1 * br1 - ai1 * bi1, ar1 * bi1 + ai1 * br1};
      vst1q_f64(reinterpret_cast<double*>(&a[i + 1]), r1);
    }
    for (; i < n; ++i)
    {
      a[i] *= b[i];
    }
#elif defined(__AVX2__)
    size_t i = 0;
    for (; i + 1 < n; i += 2)
    {
      __m256d va = _mm256_loadu_pd(reinterpret_cast<const double*>(&a[i]));
      __m256d vb = _mm256_loadu_pd(reinterpret_cast<const double*>(&b[i]));

      __m256d a_real = _mm256_unpacklo_pd(va, va);
      __m256d a_imag = _mm256_unpackhi_pd(va, va);
      a_real = _mm256_permute4x64_pd(a_real, _MM_SHUFFLE(3, 1, 2, 0));
      a_imag = _mm256_permute4x64_pd(a_imag, _MM_SHUFFLE(3, 1, 2, 0));

      __m256d b_swap = _mm256_shuffle_pd(vb, vb, 0b0101);

      __m256d prod1 = _mm256_mul_pd(a_real, vb);
      __m256d prod2 = _mm256_mul_pd(a_imag, b_swap);

      __m256d res = _mm256_addsub_pd(prod1, prod2);
      _mm256_storeu_pd(reinterpret_cast<double*>(&a[i]), res);
    }
    for (; i < n; ++i)
    {
      a[i] *= b[i];
    }
#else
    for (size_t i = 0; i < n; ++i)
    {
      a[i] *= b[i];
    }
#endif
  }

  // SIMD Vectorized Complex Pointwise Squaring
  static void vector_complex_sqr(Complex *a, size_t n)
  {
#if defined(__ARM_NEON)
    size_t i = 0;
    for (; i + 1 < n; i += 2)
    {
      float64x2_t a0 = vld1q_f64(reinterpret_cast<const double*>(&a[i]));
      float64x2_t a1 = vld1q_f64(reinterpret_cast<const double*>(&a[i + 1]));

      double ar0 = vgetq_lane_f64(a0, 0);
      double ai0 = vgetq_lane_f64(a0, 1);
      float64x2_t r0 = {ar0 * ar0 - ai0 * ai0, 2.0 * ar0 * ai0};
      vst1q_f64(reinterpret_cast<double*>(&a[i]), r0);

      double ar1 = vgetq_lane_f64(a1, 0);
      double ai1 = vgetq_lane_f64(a1, 1);
      float64x2_t r1 = {ar1 * ar1 - ai1 * ai1, 2.0 * ar1 * ai1};
      vst1q_f64(reinterpret_cast<double*>(&a[i + 1]), r1);
    }
    for (; i < n; ++i)
    {
      a[i] = a[i] * a[i];
    }
#elif defined(__AVX2__)
    size_t i = 0;
    for (; i + 1 < n; i += 2)
    {
      __m256d va = _mm256_loadu_pd(reinterpret_cast<const double*>(&a[i]));
      __m256d a_real = _mm256_unpacklo_pd(va, va);
      __m256d a_imag = _mm256_unpackhi_pd(va, va);
      a_real = _mm256_permute4x64_pd(a_real, _MM_SHUFFLE(3, 1, 2, 0));
      a_imag = _mm256_permute4x64_pd(a_imag, _MM_SHUFFLE(3, 1, 2, 0));

      __m256d b_swap = _mm256_shuffle_pd(va, va, 0b0101);
      __m256d prod1 = _mm256_mul_pd(a_real, va);
      __m256d prod2 = _mm256_mul_pd(a_imag, b_swap);
      __m256d res = _mm256_addsub_pd(prod1, prod2);
      _mm256_storeu_pd(reinterpret_cast<double*>(&a[i]), res);
    }
    for (; i < n; ++i)
    {
      a[i] = a[i] * a[i];
    }
#else
    for (size_t i = 0; i < n; ++i)
    {
      a[i] = a[i] * a[i];
    }
#endif
  }

  // Schönhage–Strassen Sub-Quadratic Polynomial Convolution: C(x) = A(x) * B(x)
  static vector<uint64_t> multiply_polynomials(const vector<uint32_t> &a,
                                               const vector<uint32_t> &b)
  {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)(a.size() + b.size()))
      n <<= 1;
    fa.resize(n, Complex(0.0, 0.0));
    fb.resize(n, Complex(0.0, 0.0));

    fft(fa, false);
    fft(fb, false);
    vector_complex_mul(fa.data(), fb.data(), n);
    fft(fa, true);

    vector<uint64_t> result(n);
    for (int i = 0; i < n; ++i)
      result[i] = (uint64_t)llround(fa[i].real());
    return result;
  }

  // 16-Bit Half-Limb Sub-Quadratic Integer Convolution for BigInteger Limbs
  static vector<uint32_t> multiply_bigint_binary(const vector<uint32_t> &a,
                                                 const vector<uint32_t> &b)
  {
    if (a.empty() || b.empty())
      return {};
    if (a.size() == 1 && a[0] == 0)
      return {0};
    if (b.size() == 1 && b[0] == 0)
      return {0};

    // Small operand threshold: use schoolbook multiplication
    if (a.size() <= 16 || b.size() <= 16)
    {
      vector<uint64_t> prod(a.size() + b.size(), 0);
      for (size_t i = 0; i < a.size(); ++i)
      {
        uint64_t carry = 0;
        for (size_t j = 0; j < b.size(); ++j)
        {
          __uint128_t cur = (__uint128_t)a[i] * b[j] + prod[i + j] + carry;
          prod[i + j] = (uint64_t)(uint32_t)cur;
          carry = (uint64_t)(cur >> 32);
        }
        prod[i + b.size()] += carry;
      }
      vector<uint32_t> res;
      uint64_t carry = 0;
      for (size_t i = 0; i < prod.size(); ++i)
      {
        uint64_t cur = prod[i] + carry;
        res.push_back((uint32_t)cur);
        carry = cur >> 32;
      }
      while (carry > 0)
      {
        res.push_back((uint32_t)carry);
        carry >>= 32;
      }
      while (res.size() > 1 && res.back() == 0)
        res.pop_back();
      return res;
    }

    bool is_square = (&a == &b);

    // Split 32-bit limbs into 16-bit half-limbs (base 2^16 = 65536)
    vector<double> ha(a.size() * 2);
    for (size_t i = 0; i < a.size(); ++i)
    {
      ha[2 * i] = (double)(a[i] & 0xFFFF);
      ha[2 * i + 1] = (double)(a[i] >> 16);
    }
    while (ha.size() > 1 && ha.back() == 0.0)
      ha.pop_back();

    int n = 1;
    if (is_square)
    {
      while (n < (int)(ha.size() * 2))
        n <<= 1;
      vector<Complex> fa(n, Complex(0.0, 0.0));
      for (size_t i = 0; i < ha.size(); ++i)
        fa[i] = Complex(ha[i], 0.0);
      fft(fa, false);
      vector_complex_sqr(fa.data(), n);
      fft(fa, true);

      // Carry propagation in base 2^16
      vector<uint32_t> half_res;
      uint64_t carry = 0;
      for (int i = 0; i < n; ++i)
      {
        int64_t val = (int64_t)llround(fa[i].real()) + carry;
        half_res.push_back((uint32_t)(val & 0xFFFF));
        carry = (uint64_t)(val >> 16);
      }
      while (carry > 0)
      {
        half_res.push_back((uint32_t)(carry & 0xFFFF));
        carry >>= 16;
      }

      // Recombine 16-bit half-limbs into 32-bit binary limbs
      vector<uint32_t> res((half_res.size() + 1) / 2, 0);
      for (size_t i = 0; i < half_res.size(); ++i)
      {
        if (i % 2 == 0)
          res[i / 2] |= half_res[i];
        else
          res[i / 2] |= (half_res[i] << 16);
      }

      while (res.size() > 1 && res.back() == 0)
        res.pop_back();
      return res;
    }
    else
    {
      vector<double> hb(b.size() * 2);
      for (size_t i = 0; i < b.size(); ++i)
      {
        hb[2 * i] = (double)(b[i] & 0xFFFF);
        hb[2 * i + 1] = (double)(b[i] >> 16);
      }
      while (hb.size() > 1 && hb.back() == 0.0)
        hb.pop_back();

      while (n < (int)(ha.size() + hb.size()))
        n <<= 1;

      vector<Complex> fa(n, Complex(0.0, 0.0));
      vector<Complex> fb(n, Complex(0.0, 0.0));
      for (size_t i = 0; i < ha.size(); ++i)
        fa[i] = Complex(ha[i], 0.0);
      for (size_t i = 0; i < hb.size(); ++i)
        fb[i] = Complex(hb[i], 0.0);

      fft(fa, false);
      fft(fb, false);
      vector_complex_mul(fa.data(), fb.data(), n);
      fft(fa, true);

      // Carry propagation in base 2^16
      vector<uint32_t> half_res;
      uint64_t carry = 0;
      for (int i = 0; i < n; ++i)
      {
        int64_t val = (int64_t)llround(fa[i].real()) + carry;
        half_res.push_back((uint32_t)(val & 0xFFFF));
        carry = (uint64_t)(val >> 16);
      }
      while (carry > 0)
      {
        half_res.push_back((uint32_t)(carry & 0xFFFF));
        carry >>= 16;
      }

      // Recombine 16-bit half-limbs into 32-bit binary limbs
      vector<uint32_t> res((half_res.size() + 1) / 2, 0);
      for (size_t i = 0; i < half_res.size(); ++i)
      {
        if (i % 2 == 0)
          res[i / 2] |= half_res[i];
        else
          res[i / 2] |= (half_res[i] << 16);
      }

      while (res.size() > 1 && res.back() == 0)
        res.pop_back();
      return res;
    }
  }
};

// ============================================================================
// LAYER 8: LATTICE-BASED HOMOMORPHIC ENCRYPTION ENGINE (Ring-LWE)
// ============================================================================
namespace LatticeLWE
{
  static const int D = 4;              // Cyclotomic Polynomial Degree (x^D + 1)
  static const int64_t Q = 2147483647; // Mersenne Prime 2^31 - 1
  static const int64_t T = 65536;      // Plaintext modulus (allows multi-operand sums up to 65535)
  static const int64_t DELTA = Q / T;  // Scaling factor = 32767

  struct alignas(32) RingPoly
  {
    int64_t coeffs[D];

    RingPoly()
    {
      for (int i = 0; i < D; ++i)
        coeffs[i] = 0;
    }

    static inline int64_t mod_q(int64_t x)
    {
      int64_t r = x % Q;
      if (r < 0)
        r += Q;
      return r;
    }

    RingPoly operator+(const RingPoly &o) const
    {
      RingPoly res;
#if defined(__ARM_NEON)
      int64x2_t vq = vdupq_n_s64(Q);
      int64x2_t a01 = vld1q_s64(&coeffs[0]);
      int64x2_t b01 = vld1q_s64(&o.coeffs[0]);
      int64x2_t s01 = vaddq_s64(a01, b01);
      uint64x2_t mask01 = vcgeq_s64(s01, vq);
      int64x2_t sub01 = vsubq_s64(s01, vq);
      int64x2_t r01 = vbslq_s64(mask01, sub01, s01);
      vst1q_s64(&res.coeffs[0], r01);

      int64x2_t a23 = vld1q_s64(&coeffs[2]);
      int64x2_t b23 = vld1q_s64(&o.coeffs[2]);
      int64x2_t s23 = vaddq_s64(a23, b23);
      uint64x2_t mask23 = vcgeq_s64(s23, vq);
      int64x2_t sub23 = vsubq_s64(s23, vq);
      int64x2_t r23 = vbslq_s64(mask23, sub23, s23);
      vst1q_s64(&res.coeffs[2], r23);
#elif defined(__AVX2__)
      __m256i va = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(coeffs));
      __m256i vb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(o.coeffs));
      __m256i vq = _mm256_set1_epi64x(Q);
      __m256i vs = _mm256_add_epi64(va, vb);
      __m256i mask = _mm256_cmpgt_epi64(vs, _mm256_sub_epi64(vq, _mm256_set1_epi64x(1)));
      __m256i vsub = _mm256_sub_epi64(vs, vq);
      __m256i vres = _mm256_blendv_epi8(vs, vsub, mask);
      _mm256_storeu_si256(reinterpret_cast<__m256i*>(res.coeffs), vres);
#else
      for (int i = 0; i < D; ++i)
      {
        int64_t sum = coeffs[i] + o.coeffs[i];
        if (sum >= Q)
          sum -= Q;
        res.coeffs[i] = sum;
      }
#endif
      return res;
    }

    RingPoly operator-(const RingPoly &o) const
    {
      RingPoly res;
#if defined(__ARM_NEON)
      int64x2_t vq = vdupq_n_s64(Q);
      int64x2_t vzero = vdupq_n_s64(0);
      int64x2_t a01 = vld1q_s64(&coeffs[0]);
      int64x2_t b01 = vld1q_s64(&o.coeffs[0]);
      int64x2_t d01 = vsubq_s64(a01, b01);
      uint64x2_t mask01 = vcltq_s64(d01, vzero);
      int64x2_t add01 = vaddq_s64(d01, vq);
      int64x2_t r01 = vbslq_s64(mask01, add01, d01);
      vst1q_s64(&res.coeffs[0], r01);

      int64x2_t a23 = vld1q_s64(&coeffs[2]);
      int64x2_t b23 = vld1q_s64(&o.coeffs[2]);
      int64x2_t d23 = vsubq_s64(a23, b23);
      uint64x2_t mask23 = vcltq_s64(d23, vzero);
      int64x2_t add23 = vaddq_s64(d23, vq);
      int64x2_t r23 = vbslq_s64(mask23, add23, d23);
      vst1q_s64(&res.coeffs[2], r23);
#elif defined(__AVX2__)
      __m256i va = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(coeffs));
      __m256i vb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(o.coeffs));
      __m256i vq = _mm256_set1_epi64x(Q);
      __m256i vd = _mm256_sub_epi64(va, vb);
      __m256i mask = _mm256_cmpgt_epi64(_mm256_setzero_si256(), vd);
      __m256i vadd = _mm256_add_epi64(vd, vq);
      __m256i vres = _mm256_blendv_epi8(vd, vadd, mask);
      _mm256_storeu_si256(reinterpret_cast<__m256i*>(res.coeffs), vres);
#else
      for (int i = 0; i < D; ++i)
        res.coeffs[i] = mod_q(coeffs[i] - o.coeffs[i]);
#endif
      return res;
    }

    // Polynomial multiplication in Z_q[x] / (x^D + 1)
    RingPoly operator*(const RingPoly &o) const
    {
      RingPoly res;
      for (int i = 0; i < D; ++i)
      {
        for (int j = 0; j < D; ++j)
        {
          int64_t term = (coeffs[i] * o.coeffs[j]) % Q;
          if (i + j < D)
          {
            int64_t s = res.coeffs[i + j] + term;
            if (s >= Q)
              s -= Q;
            res.coeffs[i + j] = s;
          }
          else
          {
            int64_t s = res.coeffs[i + j - D] - term;
            if (s < 0)
              s += Q;
            res.coeffs[i + j - D] = s;
          }
        }
      }
      return res;
    }
  };

  struct SecretKey
  {
    RingPoly s;
  };

  struct PublicKey
  {
    RingPoly b;
    RingPoly a;
  };

  struct Ciphertext
  {
    RingPoly c0;
    RingPoly c1;

    Ciphertext operator+(const Ciphertext &o) const
    {
      return {c0 + o.c0, c1 + o.c1};
    }

    string serialize() const
    {
      string out;
      out.reserve(D * 2 * 12);
      for (int i = 0; i < D; ++i)
      {
        if (i > 0)
          out.push_back(',');
        out += std::to_string(c0.coeffs[i]);
      }
      out.push_back(':');
      for (int i = 0; i < D; ++i)
      {
        if (i > 0)
          out.push_back(',');
        out += std::to_string(c1.coeffs[i]);
      }
      return out;
    }

    static Ciphertext deserialize(const string &str)
    {
      Ciphertext ct;
      size_t colon = str.find(':');
      if (colon == string::npos)
        return ct;

      // Parse c0
      size_t start = 0;
      for (int i = 0; i < D; ++i)
      {
        size_t comma = str.find(',', start);
        if (comma != string::npos && comma < colon)
        {
          ct.c0.coeffs[i] = stoll(str.substr(start, comma - start));
          start = comma + 1;
        }
        else
        {
          ct.c0.coeffs[i] = stoll(str.substr(start, colon - start));
          break;
        }
      }

      // Parse c1
      start = colon + 1;
      for (int i = 0; i < D; ++i)
      {
        size_t comma = str.find(',', start);
        if (comma != string::npos)
        {
          ct.c1.coeffs[i] = stoll(str.substr(start, comma - start));
          start = comma + 1;
        }
        else
        {
          ct.c1.coeffs[i] = stoll(str.substr(start));
          break;
        }
      }
      return ct;
    }
  };

  class RingLWEContext
  {
    mt19937_64 rng;
    uniform_int_distribution<int> dist_small{-1, 1};
    uniform_int_distribution<int64_t> dist_uniform{0, Q - 1};

  public:
    RingLWEContext(uint64_t seed = 1337) : rng(seed) {}

    RingPoly sample_small()
    {
      RingPoly p;
      for (int i = 0; i < D; ++i)
      {
        int v = dist_small(rng);
        p.coeffs[i] = (v < 0) ? (v + Q) : v;
      }
      return p;
    }

    RingPoly sample_uniform()
    {
      RingPoly p;
      for (int i = 0; i < D; ++i)
      {
        p.coeffs[i] = dist_uniform(rng);
      }
      return p;
    }

    pair<SecretKey, PublicKey> keygen()
    {
      SecretKey sk;
      sk.s = sample_small();
      RingPoly e = sample_small();
      RingPoly a = sample_uniform();
      RingPoly b = (RingPoly() - (a * sk.s)) - e;
      PublicKey pk = {b, a};
      return {sk, pk};
    }

    Ciphertext encrypt(const PublicKey &pk, int64_t m)
    {
      RingPoly u = sample_small();
      RingPoly e1 = sample_small();
      RingPoly e2 = sample_small();

      RingPoly m_poly;
      m_poly.coeffs[0] = (m % T) * DELTA;

      Ciphertext ct;
      ct.c0 = pk.b * u + e1 + m_poly;
      ct.c1 = pk.a * u + e2;
      return ct;
    }

    int64_t decrypt(const SecretKey &sk, const Ciphertext &ct)
    {
      RingPoly v = ct.c0 + ct.c1 * sk.s;
      int64_t val = v.coeffs[0];
      if (val > Q / 2)
        val -= Q;
      double approx = (double)val / (double)DELTA;
      int64_t m = (int64_t)round(approx);
      m = (m % T + T) % T;
      return m;
    }
  };
} // namespace LatticeLWE

// ============================================================================
// LAYER 6: OSI 7-LAYER IN-PROCESS NETWORK STACK & HTTP/1.1 REST PROTOCOL
// ============================================================================
struct NetworkPacket
{
  uint32_t seq = 0;
  uint32_t ack = 0;
  uint8_t flags = 0; // 0x01 = SYN, 0x02 = ACK, 0x04 = DATA, 0x08 = FIN
  uint16_t checksum = 0;
  string http_body;
  string jwt_token;
  vector<vector<LatticeLWE::Ciphertext>> framed_slices;
  vector<LatticeLWE::Ciphertext> result_ciphertexts;
};

class VirtualNetworkSwitch
{
  queue<NetworkPacket> q;
  mutex mtx;
  condition_variable cv;

public:
  void transmit(NetworkPacket p)
  {
    unique_lock<mutex> lock(mtx);
    q.push(std::move(p));
    cv.notify_one();
  }
  NetworkPacket receive()
  {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [this]
            { return !q.empty(); });
    NetworkPacket p = std::move(q.front());
    q.pop();
    return p;
  }
};

static VirtualNetworkSwitch uplink_switch;
static VirtualNetworkSwitch downlink_switch;

// Zero-Trust Cloud ALU Microservice Server
void cloud_microservice_server(EnterpriseThreadPool &pool)
{
  const string secret_key = "DeepMind-ALU-Secret-Key-2026";

  // TCP 3-Way Handshake
  NetworkPacket syn = uplink_switch.receive();
  if (syn.flags & 0x01)
  {
    NetworkPacket syn_ack;
    syn_ack.seq = 100;
    syn_ack.ack = syn.seq + 1;
    syn_ack.flags = 0x03;
    syn_ack.checksum = 0xFFFF;
    syn_ack.http_body = "HTTP/1.1 200 Connection Established\r\n\r\n";
    downlink_switch.transmit(std::move(syn_ack));
  }
  NetworkPacket ack = uplink_switch.receive();
  (void)ack;

  // Stream Encrypted Ciphertext Processing
  while (true)
  {
    NetworkPacket pkt = uplink_switch.receive();
    if (pkt.flags & 0x08)
    { // FIN
      NetworkPacket fin_ack;
      fin_ack.seq = pkt.ack;
      fin_ack.ack = pkt.seq + 1;
      fin_ack.flags = 0x08;
      fin_ack.checksum = 0xFFFF;
      fin_ack.http_body = "SESSION_CLOSED";
      downlink_switch.transmit(std::move(fin_ack));
      break;
    }

    if (!CryptoEngine::verify_jwt(pkt.jwt_token, secret_key))
    {
      cerr << "FATAL: Unauthorized ALU API call (Invalid JWT signature)!\n";
      exit(1);
    }

    size_t num_slices = pkt.framed_slices.size();
    vector<LatticeLWE::Ciphertext> out_ciphertexts(num_slices);

    size_t num_threads = pool.size();
    if (num_slices >= 64 && num_threads > 1)
    {
      size_t chunk_size = (num_slices + num_threads - 1) / num_threads;
      vector<future<void>> futures;

      for (size_t t = 0; t < num_threads; ++t)
      {
        size_t start = t * chunk_size;
        size_t end = min(num_slices, start + chunk_size);
        if (start >= end)
          continue;

        futures.push_back(pool.enqueue([&pkt, &out_ciphertexts, start, end]
        {
          for (size_t s = start; s < end; ++s)
          {
            const auto &slice = pkt.framed_slices[s];
            if (slice.empty())
              continue;
            LatticeLWE::Ciphertext homomorphic_sum = slice[0];
            for (size_t op = 1; op < slice.size(); ++op)
            {
              // Zero-Trust Homomorphic Addition in R_q without knowing Secret Key
              homomorphic_sum = homomorphic_sum + slice[op];
            }
            out_ciphertexts[s] = homomorphic_sum;
          }
        }));
      }

      for (auto &f : futures)
      {
        f.get();
      }
    }
    else
    {
      for (size_t s = 0; s < num_slices; ++s)
      {
        const auto &slice = pkt.framed_slices[s];
        if (slice.empty())
          continue;
        LatticeLWE::Ciphertext homomorphic_sum = slice[0];
        for (size_t op = 1; op < slice.size(); ++op)
        {
          homomorphic_sum = homomorphic_sum + slice[op];
        }
        out_ciphertexts[s] = homomorphic_sum;
      }
    }

    NetworkPacket resp;
    resp.seq = pkt.ack;
    resp.ack = pkt.seq + 1;
    resp.flags = 0x04;
    resp.checksum = 0xFFFF;
    resp.result_ciphertexts = std::move(out_ciphertexts);
    downlink_switch.transmit(std::move(resp));
  }
}

// ============================================================================
// LAYER 9: UNBOUNDED DYNAMIC RADIX CONVERSION & BIGINTEGER ENGINE
// ============================================================================
struct DynamicBigInt
{
  static const uint32_t RADIX_DEC = 1000000000; // Base 10^9
  bool is_negative = false;
  vector<uint32_t> dec_limbs;                   // Base 10^9 representation

  DynamicBigInt() : is_negative(false) {}
  DynamicBigInt(const string &s) : is_negative(false)
  {
    if (s.empty())
      return;
    size_t start_idx = 0;
    if (s[0] == '-')
    {
      is_negative = true;
      start_idx = 1;
    }
    else if (s[0] == '+')
    {
      start_idx = 1;
    }
    while (start_idx < s.size() && s[start_idx] == '0')
      start_idx++;

    if (start_idx == s.size())
    {
      is_negative = false;
      return;
    }

    int n = (int)s.size();
    for (int i = n; i > (int)start_idx; i -= 9)
    {
      int cur_start = max((int)start_idx, i - 9);
      uint32_t val = 0;
      for (int j = cur_start; j < i; ++j)
      {
        val = val * 10 + (s[j] - '0');
      }
      dec_limbs.push_back(val);
    }
    trim();
  }

  void trim()
  {
    while (dec_limbs.size() > 1 && dec_limbs.back() == 0)
      dec_limbs.pop_back();
    if (dec_limbs.size() == 1 && dec_limbs[0] == 0)
      dec_limbs.clear();
    if (dec_limbs.empty())
      is_negative = false;
  }

  bool is_zero() const { return dec_limbs.empty(); }

  uint32_t divide_by_uint32(uint64_t divisor)
  {
    uint64_t rem = 0;
    if (divisor == 0x100000000ULL)
    {
      for (int i = (int)dec_limbs.size() - 1; i >= 0; --i)
      {
        uint64_t cur = dec_limbs[i] + rem * RADIX_DEC;
        dec_limbs[i] = (uint32_t)(cur >> 32);
        rem = (uint32_t)cur;
      }
    }
    else
    {
      for (int i = (int)dec_limbs.size() - 1; i >= 0; --i)
      {
        uint64_t cur = dec_limbs[i] + rem * RADIX_DEC;
        dec_limbs[i] = (uint32_t)(cur / divisor);
        rem = cur % divisor;
      }
    }
    trim();
    return (uint32_t)rem;
  }

  void mul_add_uint32(uint64_t mul, uint64_t add)
  {
    uint64_t carry = add;
    if (mul == 0x100000000ULL)
    {
      for (size_t i = 0; i < dec_limbs.size(); ++i)
      {
        uint64_t cur = ((uint64_t)dec_limbs[i] << 32) + carry;
        dec_limbs[i] = (uint32_t)(cur % RADIX_DEC);
        carry = cur / RADIX_DEC;
      }
    }
    else
    {
      for (size_t i = 0; i < dec_limbs.size(); ++i)
      {
        uint64_t cur = (uint64_t)dec_limbs[i] * mul + carry;
        dec_limbs[i] = (uint32_t)(cur % RADIX_DEC);
        carry = cur / RADIX_DEC;
      }
    }
    while (carry > 0)
    {
      dec_limbs.push_back((uint32_t)(carry % RADIX_DEC));
      carry /= RADIX_DEC;
    }
    trim();
  }

  // Binary Arithmetic Primitives for Base-2^32 limbs
  static vector<uint32_t> add_binary(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    vector<uint32_t> res;
    size_t n = max(a.size(), b.size());
    uint64_t carry = 0;
    for (size_t i = 0; i < n || carry; ++i)
    {
      uint64_t sum = carry;
      if (i < a.size())
        sum += a[i];
      if (i < b.size())
        sum += b[i];
      res.push_back((uint32_t)sum);
      carry = sum >> 32;
    }
    while (res.size() > 1 && res.back() == 0)
      res.pop_back();
    return res;
  }

  static int compare_binary(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    size_t a_sz = a.size();
    while (a_sz > 0 && a[a_sz - 1] == 0)
      a_sz--;
    size_t b_sz = b.size();
    while (b_sz > 0 && b[b_sz - 1] == 0)
      b_sz--;

    if (a_sz != b_sz)
      return a_sz < b_sz ? -1 : 1;
    for (int i = (int)a_sz - 1; i >= 0; --i)
    {
      if (a[i] != b[i])
        return a[i] < b[i] ? -1 : 1;
    }
    return 0;
  }

  static vector<uint32_t> sub_binary(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    vector<uint32_t> res;
    int64_t borrow = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
      int64_t b_val = (i < b.size()) ? (int64_t)b[i] : 0;
      int64_t diff = (int64_t)a[i] - borrow - b_val;
      if (diff < 0)
      {
        diff += 0x100000000LL;
        borrow = 1;
      }
      else
      {
        borrow = 0;
      }
      res.push_back((uint32_t)diff);
    }
    while (res.size() > 1 && res.back() == 0)
      res.pop_back();
    return res;
  }

  static vector<uint32_t> mul_binary(const vector<uint32_t> &a, const vector<uint32_t> &b)
  {
    return FastFourierTransform::multiply_bigint_binary(a, b);
  }

  static void divrem_uint32(const vector<uint32_t> &u, uint32_t v, vector<uint32_t> &q, uint32_t &r)
  {
    q.resize(u.size());
    uint64_t rem = 0;
    for (int i = (int)u.size() - 1; i >= 0; --i)
    {
      uint64_t cur = (rem << 32) | u[i];
      q[i] = (uint32_t)(cur / v);
      rem = cur % v;
    }
    r = (uint32_t)rem;
    while (q.size() > 1 && q.back() == 0)
      q.pop_back();
  }

  static void divrem_binary(const vector<uint32_t> &u_in, const vector<uint32_t> &v_in,
                            vector<uint32_t> &q, vector<uint32_t> &r)
  {
    if (v_in.empty() || (v_in.size() == 1 && v_in[0] == 0))
      throw runtime_error("Division by zero in divrem_binary");
    int cmp = compare_binary(u_in, v_in);
    if (cmp < 0)
    {
      q = {0};
      r = u_in;
      return;
    }
    if (cmp == 0)
    {
      q = {1};
      r = {0};
      return;
    }
    if (v_in.size() == 1)
    {
      uint32_t rem_val = 0;
      divrem_uint32(u_in, v_in[0], q, rem_val);
      r = {rem_val};
      return;
    }

    // Knuth Algorithm D with base 2^32
    size_t m = u_in.size() - v_in.size();
    size_t n = v_in.size();

    int shift = __builtin_clz(v_in.back());
    vector<uint32_t> u(u_in.size() + 1, 0);
    vector<uint32_t> v(v_in.size(), 0);

    if (shift == 0)
    {
      for (size_t i = 0; i < u_in.size(); ++i)
        u[i] = u_in[i];
      for (size_t i = 0; i < v_in.size(); ++i)
        v[i] = v_in[i];
    }
    else
    {
      uint64_t carry = 0;
      for (size_t i = 0; i < u_in.size(); ++i)
      {
        uint64_t cur = ((uint64_t)u_in[i] << shift) | carry;
        u[i] = (uint32_t)cur;
        carry = cur >> 32;
      }
      u[u_in.size()] = (uint32_t)carry;

      carry = 0;
      for (size_t i = 0; i < v_in.size(); ++i)
      {
        uint64_t cur = ((uint64_t)v_in[i] << shift) | carry;
        v[i] = (uint32_t)cur;
        carry = cur >> 32;
      }
    }

    q.assign(m + 1, 0);
    uint64_t vn1 = v[n - 1];
    uint64_t vn2 = v[n - 2];

    for (int j = (int)m; j >= 0; --j)
    {
      __uint128_t u_top = ((__uint128_t)u[j + n] << 32) | u[j + n - 1];
      uint64_t qhat = (uint64_t)(u_top / vn1);
      uint64_t rhat = (uint64_t)(u_top % vn1);

      if (qhat >= 0x100000000ULL || (qhat * vn2 > ((rhat << 32) | u[j + n - 2])))
      {
        qhat--;
        rhat += vn1;
        if (rhat < 0x100000000ULL)
        {
          if (qhat >= 0x100000000ULL || (qhat * vn2 > ((rhat << 32) | u[j + n - 2])))
          {
            qhat--;
          }
        }
      }

      int64_t borrow = 0;
      for (size_t i = 0; i < n; ++i)
      {
        __uint128_t prod = (__uint128_t)qhat * v[i] + borrow;
        borrow = (int64_t)(prod >> 32);
        uint32_t p_low = (uint32_t)prod;
        if (u[j + i] < p_low)
          borrow++;
        u[j + i] -= p_low;
      }
      if (u[j + n] < (uint32_t)borrow)
      {
        u[j + n] -= (uint32_t)borrow;
        qhat--;
        uint64_t carry = 0;
        for (size_t i = 0; i < n; ++i)
        {
          uint64_t sum = (uint64_t)u[j + i] + v[i] + carry;
          u[j + i] = (uint32_t)sum;
          carry = sum >> 32;
        }
        u[j + n] += (uint32_t)carry;
      }
      else
      {
        u[j + n] -= (uint32_t)borrow;
      }

      q[j] = (uint32_t)qhat;
    }

    r.resize(n);
    if (shift == 0)
    {
      for (size_t i = 0; i < n; ++i)
        r[i] = u[i];
    }
    else
    {
      uint64_t carry = 0;
      for (int i = (int)n - 1; i >= 0; --i)
      {
        uint64_t cur = ((uint64_t)u[i]) | (carry << 32);
        r[i] = (uint32_t)(cur >> shift);
        carry = u[i] & ((1ULL << shift) - 1);
      }
    }

    while (q.size() > 1 && q.back() == 0)
      q.pop_back();
    while (r.size() > 1 && r.back() == 0)
      r.pop_back();
  }

  static vector<vector<uint32_t>> &get_radix_power_cache()
  {
    static vector<vector<uint32_t>> powers;
    return powers;
  }

  static mutex &get_radix_power_mutex()
  {
    static mutex p_mtx;
    return p_mtx;
  }

  static vector<uint32_t> get_radix_power(int k)
  {
    auto &p_mtx = get_radix_power_mutex();
    auto &powers = get_radix_power_cache();
    unique_lock<mutex> lock(p_mtx);
    if (powers.empty())
    {
      powers.push_back({1000000000}); // P_0 = 10^9
    }
    while ((int)powers.size() <= k)
    {
      powers.push_back(mul_binary(powers.back(), powers.back()));
    }
    return powers[k];
  }

  static void clear_radix_powers()
  {
    auto &p_mtx = get_radix_power_mutex();
    auto &powers = get_radix_power_cache();
    unique_lock<mutex> lock(p_mtx);
    powers.clear();
    powers.shrink_to_fit();
  }

  vector<uint32_t> to_binary_limbs_iterative()
  {
    vector<uint32_t> bin_limbs;
    while (!is_zero())
    {
      bin_limbs.push_back(divide_by_uint32(0x100000000ULL)); // 2^32
    }
    return bin_limbs;
  }

  static vector<uint32_t> dec_to_bin_dc(const uint32_t *limbs, size_t count)
  {
    if (count == 0)
      return {};
    if (count <= 64)
    {
      DynamicBigInt small_bi;
      small_bi.dec_limbs.assign(limbs, limbs + count);
      small_bi.trim();
      return small_bi.to_binary_limbs_iterative();
    }

    int k = 0;
    while ((1ULL << (k + 1)) < count)
      k++;

    size_t split = 1ULL << k;
    vector<uint32_t> P_k = get_radix_power(k);

    vector<uint32_t> bin_lo = dec_to_bin_dc(limbs, split);
    vector<uint32_t> bin_hi = dec_to_bin_dc(limbs + split, count - split);

    if (bin_hi.empty() || (bin_hi.size() == 1 && bin_hi[0] == 0))
      return bin_lo;

    vector<uint32_t> hi_scaled = mul_binary(bin_hi, P_k);
    return add_binary(hi_scaled, bin_lo);
  }

  // Convert Base 10^9 to Base-2^32 binary limbs dynamically with zero caps
  vector<uint32_t> to_binary_limbs()
  {
    if (dec_limbs.empty())
      return {};
    if (dec_limbs.size() <= 64)
    {
      return to_binary_limbs_iterative();
    }
    return dec_to_bin_dc(dec_limbs.data(), dec_limbs.size());
  }

  static string binary_limbs_to_decimal_string_iterative(const vector<uint32_t> &bin_limbs)
  {
    if (bin_limbs.empty())
      return "0";
    DynamicBigInt res;
    for (int i = (int)bin_limbs.size() - 1; i >= 0; --i)
    {
      res.mul_add_uint32(0x100000000ULL, bin_limbs[i]);
    }
    if (res.dec_limbs.empty())
      return "0";
    string out = std::to_string(res.dec_limbs.back());
    for (int i = (int)res.dec_limbs.size() - 2; i >= 0; --i)
    {
      string part = std::to_string(res.dec_limbs[i]);
      out.append(9 - part.size(), '0');
      out.append(part);
    }
    return out;
  }

  static string bin_to_dec_dc(const vector<uint32_t> &bin_limbs)
  {
    if (bin_limbs.empty() || (bin_limbs.size() == 1 && bin_limbs[0] == 0))
      return "0";
    if (bin_limbs.size() <= 64)
    {
      return binary_limbs_to_decimal_string_iterative(bin_limbs);
    }

    size_t est_dec_limbs = bin_limbs.size() * 32 / 30;
    int k = 0;
    while ((1ULL << (k + 1)) <= (est_dec_limbs / 2))
      k++;

    vector<uint32_t> P_k = get_radix_power(k);
    if (compare_binary(bin_limbs, P_k) < 0)
    {
      return binary_limbs_to_decimal_string_iterative(bin_limbs);
    }

    vector<uint32_t> q, r;
    divrem_binary(bin_limbs, P_k, q, r);

    string str_hi = bin_to_dec_dc(q);
    string str_lo = bin_to_dec_dc(r);

    size_t expected_lo_len = (size_t)9 * (1ULL << k);
    if (str_lo.size() < expected_lo_len)
    {
      str_lo = string(expected_lo_len - str_lo.size(), '0') + str_lo;
    }

    return str_hi + str_lo;
  }

  // Convert Base-2^32 binary limbs to Base-10 string with zero caps
  static string binary_limbs_to_decimal_string(const vector<uint32_t> &bin_limbs)
  {
    if (bin_limbs.empty())
      return "0";
    if (bin_limbs.size() <= 64)
    {
      return binary_limbs_to_decimal_string_iterative(bin_limbs);
    }
    return bin_to_dec_dc(bin_limbs);
  }

  static vector<uint32_t> get_power_of_10(size_t k)
  {
    if (k == 0)
      return {1};
    DynamicBigInt p("1" + string(k, '0'));
    return p.to_binary_limbs();
  }
};

// Arbitrary-Precision Decimal Arithmetic Structure
struct ArbitraryDecimal
{
  bool is_negative = false;
  vector<uint32_t> limbs;
  size_t scale = 0;

  ArbitraryDecimal() : is_negative(false), limbs({0}), scale(0) {}
  ArbitraryDecimal(bool neg, vector<uint32_t> l, size_t s) : is_negative(neg), limbs(std::move(l)), scale(s)
  {
    trim();
  }

  static ArbitraryDecimal from_string(const string &s)
  {
    auto dec = Combinators::parse_decimal(s);
    DynamicBigInt bigint(dec.int_part + dec.frac_part);
    return ArbitraryDecimal(dec.is_negative, bigint.to_binary_limbs(), dec.frac_part.size());
  }

  void trim()
  {
    while (limbs.size() > 1 && limbs.back() == 0)
      limbs.pop_back();
    if (limbs.empty())
    {
      limbs = {0};
      is_negative = false;
    }
    if (limbs.size() == 1 && limbs[0] == 0)
    {
      is_negative = false;
    }
  }

  bool is_zero() const
  {
    return limbs.empty() || (limbs.size() == 1 && limbs[0] == 0);
  }

  string to_string_formatted() const
  {
    if (is_zero())
      return "0";
    string dec_str = DynamicBigInt::binary_limbs_to_decimal_string(limbs);
    return Combinators::format_decimal(is_negative, dec_str, scale);
  }

  static ArbitraryDecimal add(const ArbitraryDecimal &a, const ArbitraryDecimal &b)
  {
    if (a.is_zero())
      return b;
    if (b.is_zero())
      return a;

    size_t target_scale = max(a.scale, b.scale);
    vector<uint32_t> a_limbs = a.limbs;
    vector<uint32_t> b_limbs = b.limbs;

    if (target_scale > a.scale)
    {
      a_limbs = DynamicBigInt::mul_binary(a_limbs, DynamicBigInt::get_power_of_10(target_scale - a.scale));
    }
    if (target_scale > b.scale)
    {
      b_limbs = DynamicBigInt::mul_binary(b_limbs, DynamicBigInt::get_power_of_10(target_scale - b.scale));
    }

    if (a.is_negative == b.is_negative)
    {
      vector<uint32_t> sum_limbs = DynamicBigInt::add_binary(a_limbs, b_limbs);
      return ArbitraryDecimal(a.is_negative, sum_limbs, target_scale);
    }
    else
    {
      int cmp = DynamicBigInt::compare_binary(a_limbs, b_limbs);
      if (cmp == 0)
      {
        return ArbitraryDecimal(false, {0}, 0);
      }
      else if (cmp > 0)
      {
        vector<uint32_t> diff_limbs = DynamicBigInt::sub_binary(a_limbs, b_limbs);
        return ArbitraryDecimal(a.is_negative, diff_limbs, target_scale);
      }
      else
      {
        vector<uint32_t> diff_limbs = DynamicBigInt::sub_binary(b_limbs, a_limbs);
        return ArbitraryDecimal(b.is_negative, diff_limbs, target_scale);
      }
    }
  }

  static ArbitraryDecimal sub(const ArbitraryDecimal &a, const ArbitraryDecimal &b)
  {
    ArbitraryDecimal neg_b = b;
    neg_b.is_negative = !b.is_negative;
    if (neg_b.is_zero())
      neg_b.is_negative = false;
    return add(a, neg_b);
  }

  static ArbitraryDecimal mul(const ArbitraryDecimal &a, const ArbitraryDecimal &b)
  {
    if (a.is_zero() || b.is_zero())
      return ArbitraryDecimal(false, {0}, 0);

    bool res_neg = (a.is_negative != b.is_negative);
    size_t res_scale = a.scale + b.scale;
    vector<uint32_t> res_limbs = DynamicBigInt::mul_binary(a.limbs, b.limbs);
    return ArbitraryDecimal(res_neg, res_limbs, res_scale);
  }

  static ArbitraryDecimal div(const ArbitraryDecimal &a, const ArbitraryDecimal &b, size_t max_frac_precision = 50)
  {
    if (b.is_zero())
    {
      throw runtime_error("Division by zero");
    }
    if (a.is_zero())
    {
      return ArbitraryDecimal(false, {0}, 0);
    }

    bool res_neg = (a.is_negative != b.is_negative);

    vector<uint32_t> num = a.limbs;
    vector<uint32_t> den = b.limbs;
    size_t shift = b.scale + max_frac_precision;
    if (shift >= a.scale)
    {
      size_t diff = shift - a.scale;
      if (diff > 0)
        num = DynamicBigInt::mul_binary(num, DynamicBigInt::get_power_of_10(diff));
    }
    else
    {
      size_t diff = a.scale - shift;
      den = DynamicBigInt::mul_binary(den, DynamicBigInt::get_power_of_10(diff));
    }

    vector<uint32_t> q, r;
    DynamicBigInt::divrem_binary(num, den, q, r);

    return ArbitraryDecimal(res_neg, q, max_frac_precision);
  }
};

enum class TokenType
{
  NUMBER,
  PLUS,
  MINUS,
  STAR,
  SLASH,
  LPAREN,
  RPAREN,
  END_OF_FILE
};

struct Token
{
  TokenType type;
  string text;
};

class ExpressionLexer
{
  string src;
  size_t pos = 0;

public:
  ExpressionLexer(const string &s) : src(s), pos(0) {}

  vector<Token> tokenize()
  {
    vector<Token> tokens;
    while (pos < src.size())
    {
      char c = src[pos];
      if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
      {
        pos++;
        continue;
      }
      if (c == '+')
      {
        tokens.push_back({TokenType::PLUS, "+"});
        pos++;
      }
      else if (c == '-')
      {
        tokens.push_back({TokenType::MINUS, "-"});
        pos++;
      }
      else if (c == '*')
      {
        tokens.push_back({TokenType::STAR, "*"});
        pos++;
      }
      else if (c == '/')
      {
        tokens.push_back({TokenType::SLASH, "/"});
        pos++;
      }
      else if (c == '(')
      {
        tokens.push_back({TokenType::LPAREN, "("});
        pos++;
      }
      else if (c == ')')
      {
        tokens.push_back({TokenType::RPAREN, ")"});
        pos++;
      }
      else if ((c >= '0' && c <= '9') || c == '.')
      {
        size_t start = pos;
        bool has_dot = (c == '.');
        pos++;
        while (pos < src.size())
        {
          char ch = src[pos];
          if (ch >= '0' && ch <= '9')
          {
            pos++;
          }
          else if (ch == '.' && !has_dot)
          {
            has_dot = true;
            pos++;
          }
          else
          {
            break;
          }
        }
        tokens.push_back({TokenType::NUMBER, src.substr(start, pos - start)});
      }
      else
      {
        pos++;
      }
    }
    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
  }
};

// ============================================================================
// LAYER 10: CUSTOM BYTECODE VM, COMPILER & VERIFIER SUBSYSTEM
// ============================================================================
enum class BytecodeOpcode : uint8_t
{
  OP_PUSH_CONST = 0x01,
  OP_ADD        = 0x02,
  OP_SUB        = 0x03,
  OP_MUL        = 0x04,
  OP_DIV        = 0x05,
  OP_NEG        = 0x06,
  OP_STREAM_ADD = 0x07,
  OP_HALT       = 0xFF
};

struct BytecodeProgram
{
  vector<uint8_t> code;
  vector<ArbitraryDecimal> constants;

  uint32_t add_constant(ArbitraryDecimal d)
  {
    constants.push_back(std::move(d));
    return (uint32_t)(constants.size() - 1);
  }

  void emit(BytecodeOpcode op)
  {
    code.push_back(static_cast<uint8_t>(op));
  }

  void emit_u32(uint32_t val)
  {
    code.push_back(static_cast<uint8_t>(val & 0xFF));
    code.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
    code.push_back(static_cast<uint8_t>((val >> 16) & 0xFF));
    code.push_back(static_cast<uint8_t>((val >> 24) & 0xFF));
  }
};

struct ASTNode
{
  virtual ~ASTNode() = default;
  virtual void compile(BytecodeProgram &prog) const = 0;
};

struct NumberNode : public ASTNode
{
  ArbitraryDecimal val;
  NumberNode(ArbitraryDecimal v) : val(std::move(v)) {}
  void compile(BytecodeProgram &prog) const override
  {
    uint32_t cid = prog.add_constant(val);
    prog.emit(BytecodeOpcode::OP_PUSH_CONST);
    prog.emit_u32(cid);
  }
};

struct UnaryOpNode : public ASTNode
{
  TokenType op;
  unique_ptr<ASTNode> expr;
  UnaryOpNode(TokenType o, unique_ptr<ASTNode> e) : op(o), expr(std::move(e)) {}
  void compile(BytecodeProgram &prog) const override
  {
    expr->compile(prog);
    if (op == TokenType::MINUS)
    {
      prog.emit(BytecodeOpcode::OP_NEG);
    }
  }
};

struct BinaryOpNode : public ASTNode
{
  TokenType op;
  unique_ptr<ASTNode> left;
  unique_ptr<ASTNode> right;
  BinaryOpNode(TokenType o, unique_ptr<ASTNode> l, unique_ptr<ASTNode> r)
      : op(o), left(std::move(l)), right(std::move(r)) {}

  void compile(BytecodeProgram &prog) const override
  {
    left->compile(prog);
    right->compile(prog);
    switch (op)
    {
      case TokenType::PLUS:
        prog.emit(BytecodeOpcode::OP_ADD);
        break;
      case TokenType::MINUS:
        prog.emit(BytecodeOpcode::OP_SUB);
        break;
      case TokenType::STAR:
        prog.emit(BytecodeOpcode::OP_MUL);
        break;
      case TokenType::SLASH:
        prog.emit(BytecodeOpcode::OP_DIV);
        break;
      default:
        break;
    }
  }
};

struct StreamAddNode : public ASTNode
{
  vector<ArbitraryDecimal> operands;
  StreamAddNode(vector<ArbitraryDecimal> ops) : operands(std::move(ops)) {}

  void compile(BytecodeProgram &prog) const override
  {
    for (const auto &op : operands)
    {
      uint32_t cid = prog.add_constant(op);
      prog.emit(BytecodeOpcode::OP_PUSH_CONST);
      prog.emit_u32(cid);
    }
    prog.emit(BytecodeOpcode::OP_STREAM_ADD);
    prog.emit_u32((uint32_t)operands.size());
  }
};

class ExpressionParser
{
  vector<Token> tokens;
  size_t idx = 0;

  const Token &peek() const
  {
    if (idx < tokens.size())
      return tokens[idx];
    static Token eof_token{TokenType::END_OF_FILE, ""};
    return eof_token;
  }

  Token consume()
  {
    if (idx < tokens.size())
      return tokens[idx++];
    return {TokenType::END_OF_FILE, ""};
  }

  bool match(TokenType t)
  {
    if (peek().type == t)
    {
      idx++;
      return true;
    }
    return false;
  }

public:
  ExpressionParser(vector<Token> tok) : tokens(std::move(tok)), idx(0) {}

  unique_ptr<ASTNode> parse_expression()
  {
    return parse_add_sub();
  }

private:
  unique_ptr<ASTNode> parse_add_sub()
  {
    auto left = parse_mul_div();
    while (true)
    {
      if (match(TokenType::PLUS))
      {
        auto right = parse_mul_div();
        left = make_unique<BinaryOpNode>(TokenType::PLUS, std::move(left), std::move(right));
      }
      else if (match(TokenType::MINUS))
      {
        auto right = parse_mul_div();
        left = make_unique<BinaryOpNode>(TokenType::MINUS, std::move(left), std::move(right));
      }
      else
      {
        break;
      }
    }
    return left;
  }

  unique_ptr<ASTNode> parse_mul_div()
  {
    auto left = parse_factor();
    while (true)
    {
      if (match(TokenType::STAR))
      {
        auto right = parse_factor();
        left = make_unique<BinaryOpNode>(TokenType::STAR, std::move(left), std::move(right));
      }
      else if (match(TokenType::SLASH))
      {
        auto right = parse_factor();
        left = make_unique<BinaryOpNode>(TokenType::SLASH, std::move(left), std::move(right));
      }
      else
      {
        break;
      }
    }
    return left;
  }

  unique_ptr<ASTNode> parse_factor()
  {
    if (match(TokenType::PLUS))
    {
      return parse_factor();
    }
    if (match(TokenType::MINUS))
    {
      auto val = parse_factor();
      return make_unique<UnaryOpNode>(TokenType::MINUS, std::move(val));
    }
    if (match(TokenType::LPAREN))
    {
      auto val = parse_expression();
      match(TokenType::RPAREN);
      return val;
    }
    if (peek().type == TokenType::NUMBER)
    {
      Token t = consume();
      return make_unique<NumberNode>(ArbitraryDecimal::from_string(t.text));
    }
    return make_unique<NumberNode>(ArbitraryDecimal(false, {0}, 0));
  }
};

class BytecodeVerifier
{
public:
  static bool verify(const BytecodeProgram &prog)
  {
    size_t pc = 0;
    int stack_depth = 0;
    const auto &code = prog.code;

    while (pc < code.size())
    {
      BytecodeOpcode op = static_cast<BytecodeOpcode>(code[pc++]);
      if (op == BytecodeOpcode::OP_HALT)
      {
        return (stack_depth == 1 && pc == code.size());
      }
      else if (op == BytecodeOpcode::OP_PUSH_CONST)
      {
        if (pc + 4 > code.size())
          return false;
        uint32_t cid = code[pc] | (code[pc + 1] << 8) | (code[pc + 2] << 16) | (code[pc + 3] << 24);
        pc += 4;
        if (cid >= prog.constants.size())
          return false;
        stack_depth++;
      }
      else if (op == BytecodeOpcode::OP_ADD || op == BytecodeOpcode::OP_SUB ||
               op == BytecodeOpcode::OP_MUL || op == BytecodeOpcode::OP_DIV)
      {
        if (stack_depth < 2)
          return false;
        stack_depth--;
      }
      else if (op == BytecodeOpcode::OP_NEG)
      {
        if (stack_depth < 1)
          return false;
      }
      else if (op == BytecodeOpcode::OP_STREAM_ADD)
      {
        if (pc + 4 > code.size())
          return false;
        uint32_t count = code[pc] | (code[pc + 1] << 8) | (code[pc + 2] << 16) | (code[pc + 3] << 24);
        pc += 4;
        if (stack_depth < (int)count)
          return false;
        stack_depth -= (int)count;
        stack_depth++;
      }
      else
      {
        return false;
      }
    }
    return (stack_depth == 1);
  }
};

class BytecodeVM
{
  function<ArbitraryDecimal(const vector<ArbitraryDecimal> &)> stream_add_handler;

public:
  BytecodeVM(function<ArbitraryDecimal(const vector<ArbitraryDecimal> &)> stream_fn)
      : stream_add_handler(stream_fn) {}

  ArbitraryDecimal execute(const BytecodeProgram &prog)
  {
    if (!BytecodeVerifier::verify(prog))
    {
      throw runtime_error("Bytecode verification failed: invalid stack or opcode bounds");
    }

    vector<ArbitraryDecimal> stack;
    size_t pc = 0;
    const auto &code = prog.code;

    while (pc < code.size())
    {
      BytecodeOpcode op = static_cast<BytecodeOpcode>(code[pc++]);
      if (op == BytecodeOpcode::OP_HALT)
      {
        break;
      }
      else if (op == BytecodeOpcode::OP_PUSH_CONST)
      {
        uint32_t cid = code[pc] | (code[pc + 1] << 8) | (code[pc + 2] << 16) | (code[pc + 3] << 24);
        pc += 4;
        stack.push_back(prog.constants[cid]);
      }
      else if (op == BytecodeOpcode::OP_ADD)
      {
        ArbitraryDecimal b = std::move(stack.back());
        stack.pop_back();
        ArbitraryDecimal a = std::move(stack.back());
        stack.pop_back();
        stack.push_back(ArbitraryDecimal::add(a, b));
      }
      else if (op == BytecodeOpcode::OP_SUB)
      {
        ArbitraryDecimal b = std::move(stack.back());
        stack.pop_back();
        ArbitraryDecimal a = std::move(stack.back());
        stack.pop_back();
        stack.push_back(ArbitraryDecimal::sub(a, b));
      }
      else if (op == BytecodeOpcode::OP_MUL)
      {
        ArbitraryDecimal b = std::move(stack.back());
        stack.pop_back();
        ArbitraryDecimal a = std::move(stack.back());
        stack.pop_back();
        stack.push_back(ArbitraryDecimal::mul(a, b));
      }
      else if (op == BytecodeOpcode::OP_DIV)
      {
        ArbitraryDecimal b = std::move(stack.back());
        stack.pop_back();
        ArbitraryDecimal a = std::move(stack.back());
        stack.pop_back();
        stack.push_back(ArbitraryDecimal::div(a, b));
      }
      else if (op == BytecodeOpcode::OP_NEG)
      {
        stack.back().is_negative = !stack.back().is_negative;
        if (stack.back().is_zero())
          stack.back().is_negative = false;
      }
      else if (op == BytecodeOpcode::OP_STREAM_ADD)
      {
        uint32_t count = code[pc] | (code[pc + 1] << 8) | (code[pc + 2] << 16) | (code[pc + 3] << 24);
        pc += 4;
        vector<ArbitraryDecimal> ops(count);
        for (int i = (int)count - 1; i >= 0; --i)
        {
          ops[i] = std::move(stack.back());
          stack.pop_back();
        }
        stack.push_back(stream_add_handler(ops));
      }
    }

    if (stack.empty())
      return ArbitraryDecimal(false, {0}, 0);
    return stack.back();
  }
};

// ============================================================================
// LAYER 10: APPLICATION ENTRYPOINT & ZERO-TRUST QUANTUM RUNTIME
// ============================================================================
static ArbitraryDecimal run_quantum_homomorphic_stream_pipeline(const vector<ArbitraryDecimal> &ops, EnterpriseThreadPool &thread_pool)
{
  if (ops.empty())
    return ArbitraryDecimal(false, {0}, 0);
  if (ops.size() == 1)
    return ops[0];

  size_t max_scale = 0;
  for (const auto &op : ops)
    max_scale = max(max_scale, op.scale);

  vector<string> aligned_operands;
  aligned_operands.reserve(ops.size());
  for (const auto &op : ops)
  {
    string s = op.to_string_formatted();
    auto dec = Combinators::parse_decimal(s);
    string aligned = (dec.is_negative ? "-" : "");
    aligned += dec.int_part;
    aligned += dec.frac_part;
    if (dec.frac_part.size() < max_scale)
    {
      aligned.append(max_scale - dec.frac_part.size(), '0');
    }
    aligned_operands.push_back(std::move(aligned));
  }

  const string secret_key = "DeepMind-ALU-Secret-Key-2026";
  string jwt_token = CryptoEngine::create_jwt("root_user", secret_key);

  // Initialize Lattice-Based Homomorphic Encryption Cryptosystem (Ring-LWE)
  LatticeLWE::RingLWEContext lwe_ctx(2026);
  auto keypair = lwe_ctx.keygen();
  const auto &sk = keypair.first;
  const auto &pk = keypair.second;

  struct SignedLimb
  {
    bool is_negative;
    vector<uint32_t> limbs;
  };
  vector<SignedLimb> signed_ops(aligned_operands.size());
  size_t num_threads = thread_pool.size();
  if (aligned_operands.size() >= 8 && num_threads > 1)
  {
    size_t chunk_size = (aligned_operands.size() + num_threads - 1) / num_threads;
    vector<future<void>> futures;

    for (size_t t = 0; t < num_threads; ++t)
    {
      size_t start = t * chunk_size;
      size_t end = min(aligned_operands.size(), start + chunk_size);
      if (start >= end)
        continue;

      futures.push_back(thread_pool.enqueue([&aligned_operands, &signed_ops, start, end]
      {
        for (size_t i = start; i < end; ++i) {
          DynamicBigInt bigint(aligned_operands[i]);
          signed_ops[i] = {bigint.is_negative, bigint.to_binary_limbs()};
        }
      }));
    }

    for (auto &f : futures)
    {
      f.get();
    }
  }
  else
  {
    for (size_t i = 0; i < aligned_operands.size(); ++i)
    {
      DynamicBigInt bigint(aligned_operands[i]);
      signed_ops[i] = {bigint.is_negative, bigint.to_binary_limbs()};
    }
  }

  vector<vector<uint32_t>> pos_binary_limbs;
  vector<vector<uint32_t>> neg_binary_limbs;
  for (auto &op : signed_ops)
  {
    if (!op.limbs.empty() && !(op.limbs.size() == 1 && op.limbs[0] == 0))
    {
      if (op.is_negative)
        neg_binary_limbs.push_back(std::move(op.limbs));
      else
        pos_binary_limbs.push_back(std::move(op.limbs));
    }
  }

  // Boot Zero-Trust Cloud ALU Microservice Thread
  thread server_thread(cloud_microservice_server, ref(thread_pool));

  // Perform TCP 3-Way Handshake
  NetworkPacket syn_pkt;
  syn_pkt.seq = 1000;
  syn_pkt.flags = 0x01;
  syn_pkt.checksum = 0xFFFF;
  uplink_switch.transmit(std::move(syn_pkt));                        // SYN
  NetworkPacket syn_ack = downlink_switch.receive();                 // SYN-ACK
  NetworkPacket ack_pkt;
  ack_pkt.seq = 1001;
  ack_pkt.ack = syn_ack.seq + 1;
  ack_pkt.flags = 0x02;
  ack_pkt.checksum = 0xFFFF;
  uplink_switch.transmit(std::move(ack_pkt));                        // ACK

  uint32_t seq_num = 2000;

  auto stream_and_add = [&](const vector<vector<uint32_t>> &op_limbs) -> vector<uint32_t>
  {
    if (op_limbs.empty())
      return {};

    size_t max_bin_limbs = 0;
    for (const auto &bin : op_limbs)
    {
      max_bin_limbs = max(max_bin_limbs, bin.size());
    }
    if (max_bin_limbs == 0)
      return {};

    size_t total_bits = max_bin_limbs * 32;
    const size_t FRAME_SIZE = 16384; // Batch slices into TCP frame packets

    vector<uint32_t> result_bin_limbs;
    size_t current_bit_idx = 0;
    uint32_t cur_word = 0;
    int session_carry = 0;
    SupervisedALUActor client_quantum_alu;

    for (size_t bit_start = 0; bit_start < total_bits; bit_start += FRAME_SIZE)
    {
      size_t bit_end = min(total_bits, bit_start + FRAME_SIZE);
      size_t slice_count = bit_end - bit_start;
      size_t op_count = op_limbs.size();

      vector<vector<LatticeLWE::Ciphertext>> framed_slices(slice_count, vector<LatticeLWE::Ciphertext>(op_count));

      if (num_threads > 1 && slice_count * op_count >= 128)
      {
        size_t chunk_slices = (slice_count + num_threads - 1) / num_threads;
        vector<future<void>> futures;

        for (size_t t = 0; t < num_threads; ++t)
        {
          size_t s_start = t * chunk_slices;
          size_t s_end = min(slice_count, s_start + chunk_slices);
          if (s_start >= s_end)
            continue;

          futures.push_back(thread_pool.enqueue([&pk, &op_limbs, &framed_slices, bit_start, s_start, s_end, op_count, t]
          {
            LatticeLWE::RingLWEContext local_lwe_ctx(2026 + t * 99991 + bit_start + s_start);
            for (size_t s = s_start; s < s_end; ++s)
            {
              size_t bit_pos = bit_start + s;
              size_t limb_idx = bit_pos / 32;
              size_t bit_in_limb = bit_pos % 32;

              for (size_t op_idx = 0; op_idx < op_count; ++op_idx)
              {
                int bit_val = 0;
                if (limb_idx < op_limbs[op_idx].size())
                {
                  bit_val = (op_limbs[op_idx][limb_idx] >> bit_in_limb) & 1;
                }
                framed_slices[s][op_idx] = local_lwe_ctx.encrypt(pk, bit_val);
              }
            }
          }));
        }

        for (auto &f : futures)
        {
          f.get();
        }
      }
      else
      {
        for (size_t s = 0; s < slice_count; ++s)
        {
          size_t bit_pos = bit_start + s;
          size_t limb_idx = bit_pos / 32;
          size_t bit_in_limb = bit_pos % 32;

          for (size_t op_idx = 0; op_idx < op_count; ++op_idx)
          {
            int bit_val = 0;
            if (limb_idx < op_limbs[op_idx].size())
            {
              bit_val = (op_limbs[op_idx][limb_idx] >> bit_in_limb) & 1;
            }
            framed_slices[s][op_idx] = lwe_ctx.encrypt(pk, bit_val);
          }
        }
      }

      NetworkPacket pkt;
      pkt.seq = seq_num++;
      pkt.flags = 0x04;
      pkt.checksum = 0xFFFF;
      pkt.jwt_token = jwt_token;
      pkt.framed_slices = std::move(framed_slices);
      uplink_switch.transmit(std::move(pkt));

      NetworkPacket resp = downlink_switch.receive();
      const auto &res_cts = resp.result_ciphertexts;
      size_t res_count = res_cts.size();
      vector<int64_t> plain_sums(res_count);

      if (num_threads > 1 && res_count >= 64)
      {
        size_t chunk_size = (res_count + num_threads - 1) / num_threads;
        vector<future<void>> futures;

        for (size_t t = 0; t < num_threads; ++t)
        {
          size_t start = t * chunk_size;
          size_t end = min(res_count, start + chunk_size);
          if (start >= end)
            continue;

          futures.push_back(thread_pool.enqueue([&sk, &res_cts, &plain_sums, start, end]
          {
            LatticeLWE::RingLWEContext local_lwe_ctx;
            for (size_t i = start; i < end; ++i)
            {
              plain_sums[i] = local_lwe_ctx.decrypt(sk, res_cts[i]);
            }
          }));
        }

        for (auto &f : futures)
        {
          f.get();
        }
      }
      else
      {
        for (size_t i = 0; i < res_count; ++i)
        {
          plain_sums[i] = lwe_ctx.decrypt(sk, res_cts[i]);
        }
      }

      for (size_t i = 0; i < res_count; ++i)
      {
        int64_t plain_sum = plain_sums[i];

        vector<bool> bits(plain_sum, true);
        auto q_res = client_quantum_alu.compute_multi_operand(bits, session_carry);
        int sum_bit = q_res.first;
        session_carry = q_res.second;

        cur_word |= ((uint32_t)sum_bit << (current_bit_idx % 32));
        current_bit_idx++;
        if (current_bit_idx % 32 == 0)
        {
          result_bin_limbs.push_back(cur_word);
          cur_word = 0;
        }
      }
    }

    while (session_carry > 0)
    {
      int b = session_carry % 2;
      session_carry /= 2;
      cur_word |= ((uint32_t)b << (current_bit_idx % 32));
      current_bit_idx++;
      if (current_bit_idx % 32 == 0)
      {
        result_bin_limbs.push_back(cur_word);
        cur_word = 0;
      }
    }
    if (current_bit_idx % 32 != 0)
    {
      result_bin_limbs.push_back(cur_word);
    }

    while (result_bin_limbs.size() > 1 && result_bin_limbs.back() == 0)
      result_bin_limbs.pop_back();

    return result_bin_limbs;
  };

  vector<uint32_t> pos_sum = stream_and_add(pos_binary_limbs);
  vector<uint32_t> neg_sum = stream_and_add(neg_binary_limbs);

  NetworkPacket fin_pkt;
  fin_pkt.seq = seq_num++;
  fin_pkt.flags = 0x08;
  fin_pkt.checksum = 0xFFFF;
  fin_pkt.http_body = "EOF";
  uplink_switch.transmit(std::move(fin_pkt));

  NetworkPacket fin_resp = downlink_switch.receive();
  (void)fin_resp;

  server_thread.join();

  int cmp = DynamicBigInt::compare_binary(pos_sum, neg_sum);
  if (cmp == 0)
  {
    return ArbitraryDecimal(false, {0}, 0);
  }
  else if (cmp > 0)
  {
    vector<uint32_t> diff = DynamicBigInt::sub_binary(pos_sum, neg_sum);
    return ArbitraryDecimal(false, diff, max_scale);
  }
  else
  {
    vector<uint32_t> diff = DynamicBigInt::sub_binary(neg_sum, pos_sum);
    return ArbitraryDecimal(true, diff, max_scale);
  }
}

int main(int argc, char *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string combined_input;
  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      combined_input += argv[i];
      combined_input.push_back(' ');
    }
  }
  else
  {
    Combinators::FastIOReader reader;
    combined_input = reader.read_all();
  }

  if (combined_input.empty())
  {
    cout << 0 << "\n";
    return 0;
  }

  // Monadic stream parsing verification
  auto parse_res = Combinators::token_stream().parse(combined_input);
  vector<string> operands = parse_res.value;

  if (operands.empty())
  {
    cout << 0 << "\n";
    return 0;
  }

  ExpressionLexer lexer(combined_input);
  vector<Token> expr_tokens = lexer.tokenize();

  bool is_complex_expr = false;
  for (const auto &t : expr_tokens)
  {
    if (t.type == TokenType::STAR || t.type == TokenType::SLASH ||
        t.type == TokenType::LPAREN || t.type == TokenType::RPAREN)
    {
      is_complex_expr = true;
      break;
    }
  }
  for (const auto &op : operands)
  {
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "(" || op == ")")
    {
      is_complex_expr = true;
      break;
    }
  }

  EnterpriseThreadPool thread_pool;
  BytecodeVM vm([&thread_pool](const vector<ArbitraryDecimal> &ops) {
    return run_quantum_homomorphic_stream_pipeline(ops, thread_pool);
  });

  BytecodeProgram prog;
  if (is_complex_expr)
  {
    ExpressionParser parser(std::move(expr_tokens));
    auto ast = parser.parse_expression();
    ast->compile(prog);
  }
  else
  {
    vector<ArbitraryDecimal> dec_ops;
    for (const auto &op : operands)
    {
      dec_ops.push_back(ArbitraryDecimal::from_string(op));
    }
    StreamAddNode stream_node(std::move(dec_ops));
    stream_node.compile(prog);
  }
  prog.emit(BytecodeOpcode::OP_HALT);

  ArbitraryDecimal result = vm.execute(prog);
  cout << result.to_string_formatted() << "\n";

  // Clean up cached radix powers and FFT twiddle tables before program termination
  DynamicBigInt::clear_radix_powers();
  FastFourierTransform::clear_twiddles();

  return 0;
}
