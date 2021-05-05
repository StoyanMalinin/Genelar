#include <set>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <functional>

#include "..\StringUtils\StringWithSuffixes.cpp"
#include "..\DictionaryUtils\TreapDictionary.cpp"

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

        static void test3()
        {
            std::chrono::high_resolution_clock clock;
            auto startTime = clock.now();

            std::vector <int> ids;
            TreapDictionary<alphSz> *td = new TreapDictionary<alphSz>(alphMap);

            td->addString(1, "alabala");
            td->addString(2, "abababababababababababababababababababababababababababababababab");
            td->addString(3, "abcabcabz");

            td->queryString("ab", ids, true);
            assert((ids==std::vector<int>{1, 2, 3}));
            
            td->queryString("a", ids, true);
            assert((ids==std::vector<int>{1, 2, 3}));

            td->queryString("z", ids, true);
            assert((ids==std::vector<int>{3}));

            td->queryString("x", ids, true);
            assert((ids==std::vector<int>{}));

            td->addString(4, "xyz");

            td->queryString("z", ids, true);
            assert((ids==std::vector<int>{3, 4}));

            td->queryString("x", ids, true);
            assert((ids==std::vector<int>{4}));

            td->queryString("a", ids, true);
            assert((ids==std::vector<int>{1, 2, 3}));
            
            td->addString(5, "al");

            td->queryString("al", ids, true);
            assert((ids==std::vector<int>{1, 5}));

            td->queryString("ala", ids, true);
            assert((ids==std::vector<int>{1}));

            auto endTime = clock.now();
            std::cout << "Test 3 is OK" << " " << (std::chrono::duration<float>(endTime-startTime)).count() << "s" << '\n';
        }

        static void test4()
        {
            std::mt19937 rnd(22);

            std::chrono::high_resolution_clock clock;
            auto startTime = clock.now();

            std::vector <int> ids;
            TreapDictionary<alphSz> *td = new TreapDictionary<alphSz>(alphMap);

            int idSum = 0, idCnt = 0;
            for(int iter = 0;iter<10*1000;iter++)
            {
                if(iter%1000==0)
                    std::cout << iter << '\n';

                std::string s = "";
                if(iter%5==0) 
                {
                    for(int i = 0;i<400;i++) s += char('a' + (rnd()%26));
                    td->addString((iter+1)/2+1, s);
                }
                else
                {
                    for(int i = 0;i<2;i++) s += char('a' + (rnd()%26));
                    td->queryString(s, ids, true);
                
                    idCnt++;
                    idSum += ids.size();
                }
            }

            auto endTime = clock.now();
            std::cout << "Test 4 passed (it has no checking)" << " " << (std::chrono::duration<float>(endTime-startTime)).count() << "s"
                      << " || " << (double)idSum / (double)idCnt <<  '\n';
        }

    public:
        UnitTests()
        {
            HashingData::init();
            initLowercase();

            allTests.push_back(test1);
            allTests.push_back(test2);
            allTests.push_back(test3);
            allTests.push_back(test4);
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
