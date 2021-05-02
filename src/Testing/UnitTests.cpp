#include <set>
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
        std::vector<std::function<void()>> allTests;

        static void test1()
        {
            StringWithSuffixes<alphSz> *s = new StringWithSuffixes<alphSz>("alabala", alphMap);

            assert(s->getHash(0, 2).h[0]==s->getHash(4, 6).h[0]);
            assert(s->getHash(0, 2).h[0]!=s->getHash(4, 5).h[0]);
            assert((s->getHash(0, 1)!=s->getHash(2, 3)));
            assert(s->lcp(0, 4)==3);
            assert(s->lcp(1, 2)==0);
            assert(s->lcp(0, 2)==1);
            assert(s->lcp(0, 1)==0);

            std::cout << "Test 1 is OK" << '\n';
        }

        static void test2()
        {
            std::set <StringSuffix<alphSz>> s;

            s.clear();
            StringWithSuffixes<alphSz> *str = new StringWithSuffixes<alphSz>("abcd", alphMap);
            for(int i = 0;i<str->n;i++)
                s.insert(*(str->suff[i]));

            auto it = s.begin();
            assert(it->ind==0);it++;
            assert(it->ind==1);it++;
            assert(it->ind==2);it++;
            assert(it->ind==3);it++;

            s.clear();
            str = new StringWithSuffixes<alphSz>("pedala", alphMap);
            for(int i = 0;i<str->n;i++)
                s.insert(*(str->suff[i]));

            it = s.begin();
            assert(it->ind==5);it++;
            assert(it->ind==3);it++;
            assert(it->ind==2);it++;
            assert(it->ind==1);it++;
            assert(it->ind==4);it++;
            assert(it->ind==0);it++;

            std::cout << "Test 2 is OK" << '\n';
        }

    public:
        UnitTests()
        {
            HashingData::init();
            initLowercase();

            allTests.push_back(test1);
            allTests.push_back(test2);
        }

    public:
        void runAllTests()
        {
            std::cout << "Starting tests" << '\n';
            for(auto &test: allTests)
                test();
            std::cout << "All tests completed" << '\n' << '\n';
        }

    };
    uint8_t* UnitTests::alphMap =  new uint8_t[256];
}
