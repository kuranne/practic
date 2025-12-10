// gen_numbers.cpp
// compile: g++ -O3 -march=native -pipe gen_numbers.cpp -o gen_numbers
// run: ./gen_numbers file.txt

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

static inline char* append_uint64(char* dst, uint64_t v) {
    // เขียนตัวเลขกลับด้านลงบัฟเฟอร์ แล้วกลับกลับ
    char tmp[32];
    int len = 0;
    if (v == 0) {
        tmp[len++] = '0';
    } else {
        while (v) {
            tmp[len++] = char('0' + (v % 10));
            v /= 10;
        }
    }
    // copy กลับจาก tmp
    for (int i = len - 1; i >= 0; --i) *dst++ = tmp[i];
    return dst;
}

int main(int argc, char** argv) {
    const char* outname = (argc >= 2) ? argv[1] : "file.txt";
    FILE* f = fopen(outname, "wb");
    if (!f) {
        perror("fopen");
        return 1;
    }

    const size_t BUF_SIZE = 32u * 1024u * 1024u; // 32 MB buffer
    char* buffer = (char*)malloc(BUF_SIZE);
    if (!buffer) {
        perror("malloc");
        fclose(f);
        return 1;
    }

    char* ptr = buffer;
    size_t remaining = BUF_SIZE;

    // เป้าหมาย: 0 .. 1_000_000_000 (รวมทั้งสิ้น 1e9 + 1 ค่า)
    const uint64_t LIMIT = 1000000000ULL;

    for (uint64_t i = 0; i <= LIMIT; ++i) {
        // ประมาณความต้องการสูงสุด: 11 bytes ต่อเลข (10 digits + '\n')
        // ถ้าพื้นที่เหลือไม่พอ ให้ flush
        if (remaining < 24) { // เผื่อไว้สบาย ๆ
            size_t used = ptr - buffer;
            if (fwrite(buffer, 1, used, f) != used) {
                perror("fwrite");
                free(buffer);
                fclose(f);
                return 1;
            }
            ptr = buffer;
            remaining = BUF_SIZE;
        }

        ptr = append_uint64(ptr, i);
        *ptr++ = '\n';
        remaining = BUF_SIZE - (ptr - buffer);
    }

    // flush ที่เหลือ
    size_t used = ptr - buffer;
    if (used > 0) {
        if (fwrite(buffer, 1, used, f) != used) {
            perror("fwrite");
            free(buffer);
            fclose(f);
            return 1;
        }
    }

    free(buffer);
    fclose(f);
    return 0;
}