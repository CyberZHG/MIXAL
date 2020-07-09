#include <iostream>
#include <memory>
#include "test.h"
#include "machine.h"
#include "parser.h"

namespace test {

class TestMachineLoadCodes : public UnitTest {
 public:
    mixal::Machine machine;

    TestMachineLoadCodes() : machine() {}

    void setUpEach() final {
        machine.reset();
    }
};

__TEST_U(TestMachineLoadCodes, test_load_sample) {
    std::vector<std::string> codes = {
        "X       EQU  1000",
        "        ORIG 3000",
        "MAXIMUM STJ  EXIT",
        "INIT    ENT3 0,1",
        "        JMP  CHANGEM",
        "LOOP    CMPA X,3",
        "        JGE  *+3",
        "CHANGEM ENT2 0,3",
        "        LDA  X,3",
        "        DEC3 1",
        "        J3P  LOOP",
        "EXIT    JMP  *",
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 2, 32), machine.memory[3000]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 1, 2, 51), machine.memory[3001]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3005, 0, 0, 39), machine.memory[3002]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5, 56), machine.memory[3003]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3007, 0, 7, 39), machine.memory[3004]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 3, 2, 50), machine.memory[3005]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5,  8), machine.memory[3006]);
    __ASSERT_EQ(mixal::ComputerWord(false,    1, 0, 1, 51), machine.memory[3007]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3003, 0, 2, 43), machine.memory[3008]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 0, 39), machine.memory[3009]);
}

__TEST_U(TestMachineLoadCodes, test_run_sample) {
    std::vector<std::string> codes = {
        "X       EQU  1000",
        "        ORIG 3000",
        "MAXIMUM STJ  EXIT",
        "INIT    ENT3 0,1",
        "        JMP  CHANGEM",
        "LOOP    CMPA X,3",
        "        JGE  *+3",
        "CHANGEM ENT2 0,3",
        "        LDA  X,3",
        "        DEC3 1",
        "        J3P  LOOP",
        "EXIT    JMP  *",
    };
    machine.loadCodes(codes);
    machine.rI1.set(5);
    machine.rJ.set(3009);
    machine.memory[1000].set(123);
    machine.memory[1001].set(456);
    machine.memory[1002].set(789);
    machine.memory[1003].set(654);
    machine.executeUntilSelfLoop();
    __ASSERT_EQ(789, machine.rA.value());
}

__TEST_U(TestMachineLoadCodes, test_load_constant) {
    std::vector<std::string> codes = {
        " CON  100000",
        " ORIG 3000",
        " CON  1000000",
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(100000, machine.memory[0].value());
    __ASSERT_EQ(1000000, machine.memory[3000].value());
}

__TEST_U(TestMachineLoadCodes, test_load_set_all_zeros) {
    std::vector<std::string> codes = {
        "        ORIG    3000",
        "        STZ     0",
        "        LD1     =1=",
        "        MOVE    0(49)",
        "        MOVE    0(50)"
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 49, 7), machine.memory[3002]);
    __ASSERT_EQ(mixal::ComputerWord(false, 0, 0, 50, 7), machine.memory[3003]);
}

__TEST_U(TestMachineLoadCodes, test_load_literal_constant) {
    std::vector<std::string> codes = {
        " ORIG 3000",
        " LDA  =10-23=,0+0(2+3)",
    };
    machine.loadCodes(codes, false);
    __ASSERT_EQ(mixal::ComputerWord(false, 3001, 0, 5, 8), machine.memory[3000]);
    __ASSERT_EQ(-13, machine.memory[3001].value());
}

__TEST_U(TestMachineLoadCodes, test_load_sample_with_local_symbols) {
    std::vector<std::string> codes = {
        "X       EQU  1000",
        "        ORIG 3000",
        "MAXIMUM STJ  2F",
        "INIT    ENT3 0,1",
        "        JMP  6F",
        "4H      CMPA X,3",
        "        JGE  *+3",
        "6H      ENT2 0,3",
        "        LDA  X,3",
        "        DEC3 1",
        "        J3P  4B",
        "2H      JMP  *",
    };
    machine.loadCodes(codes);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 2, 32), machine.memory[3000]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 1, 2, 51), machine.memory[3001]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3005, 0, 0, 39), machine.memory[3002]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5, 56), machine.memory[3003]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3007, 0, 7, 39), machine.memory[3004]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 3, 2, 50), machine.memory[3005]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1000, 3, 5,  8), machine.memory[3006]);
    __ASSERT_EQ(mixal::ComputerWord(false,    1, 0, 1, 51), machine.memory[3007]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3003, 0, 2, 43), machine.memory[3008]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3009, 0, 0, 39), machine.memory[3009]);
}

__TEST_U(TestMachineLoadCodes, test_load_codes_prime) {
    std::vector<std::string> codes = {
        "* EXAMPLE PROGRAM ... TABLE OF PRIMES",
        "*",
        "L       EQU  500               The number of primes to find",
        "PRINTER EQU  18                Unit number of the line printer",
        "PRIME   EQU  -1                Memory area for table of primes",
        "BUF0    EQU  2000              Memory area for BUFFER[0]",
        "BUF1    EQU  BUF0+25           Memory area for BUFFER[1]",
        "        ORIG 3000",
        "START   IOC  0(PRINTER)        Skip to new page.",
        "        LD1  =1-L=             P1. Start table. J ← 1.",
        "        LD2  =3=                   N ← 3.",
        "2H      INC1 1                 P2. N is prime. J ← J + 1.",
        "        ST2  PRIME+L,1             PRIME[J] ← N.",
        "        J1Z  2F                P3. 500 found?",
        "4H      INC2 2                 P4. Advance N.",
        "        ENT3 2                 P5. K ← 2.",
        "6H      ENTA 0                 P6. PRIME[K]\\N?",
        "        ENTX 0,2                   rAX ← N.",
        "        DIV  PRIME,3               rA ← Q, rX ← R.",
        "        JXZ  4B                    To P4 if R = 0.",
        "        CMPA PRIME,3           P7. PRIME[K] large?",
        "        INC3 1                 P8. Advance K.",
        "        JG   6B                    To P6 if Q > PRIME[K].",
        "        JMP  2B                    Otherwise N is prime.",
        "2H      OUT  TITLE(PRINTER)    P9. Print title.",
        "        ENT4 BUF1+10               Set B ← 1.",
        "        ENT5 -50                   Set M ← 0.",
        "2H      INC5 L+1                   Advance M.",
        "4H      LDA  PRIME,5           P10. Set up line. (Right to left)",
        "        CHAR                       Convert PRIME[M] to decimal.",
        "        STX  0,4(1:4)",
        "        DEC4 1",
        "        DEC5 50                    (rI5 goes down by 50 until",
        "        J5P  4B                        it becomes nonpositive)",
        "        OUT  0,4(PRINTER)      P11. Print line.",
        "        LD4  24,4                  Switch buffers.",
        "        J5N  2B                    If rI5 = 0, we are done.",
        "        HLT",
        "* INITIAL CONTENTS OF TABLES AND BUFFERS",
        "        ORIG PRIME+1",
        "        CON  2                 The first prime is 2.",
        "        ORIG BUF0-5",
        "TITLE   ALF  FIRST             Alphabetic information for",
        "        ALF   FIVE                 title line",
        "        ALF   HUND",
        "        ALF  RED P",
        "        ALF  RIMES",
        "        ORIG BUF0+24",
        "        CON  BUF1+10           Each buffer refers to the other.",
        "        ORIG BUF1+24",
        "        CON  BUF0+10",
        "        END  START             End of routine.",
    };
    machine.loadCodes(codes, false);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 0, 18, 35), machine.memory[3000]);
    __ASSERT_EQ(mixal::ComputerWord(false, 2050, 0,  5,  9), machine.memory[3001]);
    __ASSERT_EQ(mixal::ComputerWord(false, 2051, 0,  5, 10), machine.memory[3002]);
    __ASSERT_EQ(mixal::ComputerWord(false,    1, 0,  0, 49), machine.memory[3003]);
    __ASSERT_EQ(mixal::ComputerWord(false,  499, 1,  5, 26), machine.memory[3004]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3016, 0,  1, 41), machine.memory[3005]);
    __ASSERT_EQ(mixal::ComputerWord(false,    2, 0,  0, 50), machine.memory[3006]);
    __ASSERT_EQ(mixal::ComputerWord(false,    2, 0,  2, 51), machine.memory[3007]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 0,  2, 48), machine.memory[3008]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 2,  2, 55), machine.memory[3009]);

    __ASSERT_EQ(mixal::ComputerWord(true,     1, 3,  5,  4), machine.memory[3010]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3006, 0,  1, 47), machine.memory[3011]);
    __ASSERT_EQ(mixal::ComputerWord(true,     1, 3,  5, 56), machine.memory[3012]);
    __ASSERT_EQ(mixal::ComputerWord(false,    1, 0,  0, 51), machine.memory[3013]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3008, 0,  6, 39), machine.memory[3014]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3003, 0,  0, 39), machine.memory[3015]);
    __ASSERT_EQ(mixal::ComputerWord(false, 1995, 0, 18, 37), machine.memory[3016]);
    __ASSERT_EQ(mixal::ComputerWord(false, 2035, 0,  2, 52), machine.memory[3017]);
    __ASSERT_EQ(mixal::ComputerWord(true,    50, 0,  2, 53), machine.memory[3018]);
    __ASSERT_EQ(mixal::ComputerWord(false,  501, 0,  0, 53), machine.memory[3019]);

    __ASSERT_EQ(mixal::ComputerWord(true,     1, 5,  5,  8), machine.memory[3020]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 0,  1,  5), machine.memory[3021]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 4, 12, 31), machine.memory[3022]);
    __ASSERT_EQ(mixal::ComputerWord(false,    1, 0,  1, 52), machine.memory[3023]);
    __ASSERT_EQ(mixal::ComputerWord(false,   50, 0,  1, 53), machine.memory[3024]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3020, 0,  2, 45), machine.memory[3025]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 4, 18, 37), machine.memory[3026]);
    __ASSERT_EQ(mixal::ComputerWord(false,   24, 4,  5, 12), machine.memory[3027]);
    __ASSERT_EQ(mixal::ComputerWord(false, 3019, 0,  0, 45), machine.memory[3028]);
    __ASSERT_EQ(mixal::ComputerWord(false,    0, 0,  2,  5), machine.memory[3029]);

    __ASSERT_EQ(2, machine.memory[0].value());
    __ASSERT_EQ(2035, machine.memory[2024].value());
    __ASSERT_EQ(2010, machine.memory[2049].value());
    __ASSERT_EQ(-499, machine.memory[2050].value());
    __ASSERT_EQ(3, machine.memory[2051].value());

    __ASSERT_EQ(mixal::ComputerWord(false,  6,  9, 19, 22, 23), machine.memory[1995]);
    __ASSERT_EQ(mixal::ComputerWord(false,  0,  6,  9, 25,  5), machine.memory[1996]);
    __ASSERT_EQ(mixal::ComputerWord(false,  0,  8, 24, 15,  4), machine.memory[1997]);
    __ASSERT_EQ(mixal::ComputerWord(false, 19,  5,  4,  0, 17), machine.memory[1998]);
    __ASSERT_EQ(mixal::ComputerWord(false, 19,  9, 14,  5, 22), machine.memory[1999]);

    machine.executeUntilHalt();
    auto linePrinter = std::dynamic_pointer_cast<mixal::IODeviceLinePrinter>(machine.getDevice(18));
    std::vector<std::string> outputs;
    for (int i = 0; i < 51; ++i) {
        outputs.push_back(linePrinter->line(1, i).substr(0, 55));
    }
    std::vector<std::string> expects {
        "FIRST FIVE HUNDRED PRIMES                              ",
        "     0002 0233 0547 0877 1229 1597 1993 2371 2749 3187 ",
        "     0003 0239 0557 0881 1231 1601 1997 2377 2753 3191 ",
        "     0005 0241 0563 0883 1237 1607 1999 2381 2767 3203 ",
        "     0007 0251 0569 0887 1249 1609 2003 2383 2777 3209 ",
        "     0011 0257 0571 0907 1259 1613 2011 2389 2789 3217 ",
        "     0013 0263 0577 0911 1277 1619 2017 2393 2791 3221 ",
        "     0017 0269 0587 0919 1279 1621 2027 2399 2797 3229 ",
        "     0019 0271 0593 0929 1283 1627 2029 2411 2801 3251 ",
        "     0023 0277 0599 0937 1289 1637 2039 2417 2803 3253 ",
        "     0029 0281 0601 0941 1291 1657 2053 2423 2819 3257 ",
        "     0031 0283 0607 0947 1297 1663 2063 2437 2833 3259 ",
        "     0037 0293 0613 0953 1301 1667 2069 2441 2837 3271 ",
        "     0041 0307 0617 0967 1303 1669 2081 2447 2843 3299 ",
        "     0043 0311 0619 0971 1307 1693 2083 2459 2851 3301 ",
        "     0047 0313 0631 0977 1319 1697 2087 2467 2857 3307 ",
        "     0053 0317 0641 0983 1321 1699 2089 2473 2861 3313 ",
        "     0059 0331 0643 0991 1327 1709 2099 2477 2879 3319 ",
        "     0061 0337 0647 0997 1361 1721 2111 2503 2887 3323 ",
        "     0067 0347 0653 1009 1367 1723 2113 2521 2897 3329 ",
        "     0071 0349 0659 1013 1373 1733 2129 2531 2903 3331 ",
        "     0073 0353 0661 1019 1381 1741 2131 2539 2909 3343 ",
        "     0079 0359 0673 1021 1399 1747 2137 2543 2917 3347 ",
        "     0083 0367 0677 1031 1409 1753 2141 2549 2927 3359 ",
        "     0089 0373 0683 1033 1423 1759 2143 2551 2939 3361 ",
        "     0097 0379 0691 1039 1427 1777 2153 2557 2953 3371 ",
        "     0101 0383 0701 1049 1429 1783 2161 2579 2957 3373 ",
        "     0103 0389 0709 1051 1433 1787 2179 2591 2963 3389 ",
        "     0107 0397 0719 1061 1439 1789 2203 2593 2969 3391 ",
        "     0109 0401 0727 1063 1447 1801 2207 2609 2971 3407 ",
        "     0113 0409 0733 1069 1451 1811 2213 2617 2999 3413 ",
        "     0127 0419 0739 1087 1453 1823 2221 2621 3001 3433 ",
        "     0131 0421 0743 1091 1459 1831 2237 2633 3011 3449 ",
        "     0137 0431 0751 1093 1471 1847 2239 2647 3019 3457 ",
        "     0139 0433 0757 1097 1481 1861 2243 2657 3023 3461 ",
        "     0149 0439 0761 1103 1483 1867 2251 2659 3037 3463 ",
        "     0151 0443 0769 1109 1487 1871 2267 2663 3041 3467 ",
        "     0157 0449 0773 1117 1489 1873 2269 2671 3049 3469 ",
        "     0163 0457 0787 1123 1493 1877 2273 2677 3061 3491 ",
        "     0167 0461 0797 1129 1499 1879 2281 2683 3067 3499 ",
        "     0173 0463 0809 1151 1511 1889 2287 2687 3079 3511 ",
        "     0179 0467 0811 1153 1523 1901 2293 2689 3083 3517 ",
        "     0181 0479 0821 1163 1531 1907 2297 2693 3089 3527 ",
        "     0191 0487 0823 1171 1543 1913 2309 2699 3109 3529 ",
        "     0193 0491 0827 1181 1549 1931 2311 2707 3119 3533 ",
        "     0197 0499 0829 1187 1553 1933 2333 2711 3121 3539 ",
        "     0199 0503 0839 1193 1559 1949 2339 2713 3137 3541 ",
        "     0211 0509 0853 1201 1567 1951 2341 2719 3163 3547 ",
        "     0223 0521 0857 1213 1571 1973 2347 2729 3167 3557 ",
        "     0227 0523 0859 1217 1579 1979 2351 2731 3169 3559 ",
        "     0229 0541 0863 1223 1583 1987 2357 2741 3181 3571 ",
    };
    __ASSERT_EQ(expects.size(), outputs.size());
    for (size_t i = 0; i < expects.size(); ++i) {
        __ASSERT_EQ(expects[i].size(), outputs[i].size());
        __ASSERT_EQ(expects[i], outputs[i]);
    }
}

}  // namespace test
