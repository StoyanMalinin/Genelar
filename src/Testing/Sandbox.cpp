#include <iostream>
#include <cstring>

#include "..\StringUtils\StringWithSuffixes.cpp"

namespace gnl
{
    class Sandbox
    {
    private:
        static const size_t alphSz = 26;
        uint8_t alphMap[256];

        void initLowercase()
        {
            memset(alphMap, -1, sizeof(alphMap));
            for(char c = 'a';c<='z';c++)
                alphMap[c] = c - 'a';
        }

    public:
        void run()
        {
            HashingData::init();
            initLowercase();

            StringWithSuffixes<alphSz> *s = new StringWithSuffixes<alphSz>("alabala", alphMap);
            std::cout << *s << '\n';

            std::cout << s->getHash(0, 2).h[0] << " == " << s->getHash(4, 6).h[0] << '\n';
            std::cout << (s->getHash(0, 1)==s->getHash(2, 3)) << '\n';

            std::cout << s->lcp(0, 4) << " " << s->lcp(1, 2) << " " << s->lcp(0, 2) << '\n';
        }
    };
}