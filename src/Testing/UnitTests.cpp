#include <vector>
#include <iostream>
#include <assert.h>
#include <functional>

#include "..\StringUtils\StringWithSuffixes.cpp"

namespace gnl
{
    class UnitTests
    {
    private:
        static const size_t alphSz = 26;
        static uint8_t *alphMap;

        void initLowercase()
        {
            memset(alphMap, -1, sizeof(alphMap));
            for(char c = 'a';c<='z';c++)
                alphMap[c] = c - 'a';
        }

    private:
        std::vector<std::function<std::string()>> allTests;

        static std::string test1()
        {
            StringWithSuffixes<alphSz> *s = new StringWithSuffixes<alphSz>("alabala", alphMap);

            assert(s->getHash(0, 2).h[0]==s->getHash(4, 6).h[0]);
            assert(s->getHash(0, 2).h[0]!=s->getHash(4, 5).h[0]);
            assert((s->getHash(0, 1)!=s->getHash(2, 3)));
            assert(s->lcp(0, 4)==3);
            assert(s->lcp(1, 2)==0);
            assert(s->lcp(0, 2)==1);

            return "[Test 1] is OK";
        }

    public:
        UnitTests()
        {
            HashingData::init();
            initLowercase();

            allTests.push_back(test1);
        }

    public:
        void runAllTests()
        {
            std::cout << "Starting tests" << '\n';
            for(auto &test: allTests)
                std::cout << test() << '\n';
            std::cout << "All tests completed" << '\n' << '\n';
        }

    };
    uint8_t* UnitTests::alphMap =  new uint8_t[256];
}
