#include <iostream>
#include <cstring>

#include "..\TreapUtils\Treap.cpp"
#include "..\StringUtils\StringWithSuffixes.cpp"
#include "..\DictionaryUtils\TreapDictionary.cpp"
#include "..\DictionaryUtils\StringSuffixTreapNode.cpp"

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
            initLowercase();
            HashingData::init();
            std::cout << "INSIDE SANDBOX" << '\n';

            TreapDictionary<alphSz> *td = new TreapDictionary<alphSz>(alphMap);

            td->addString(1, "alabala");
            td->addString(2, "abababababababababababababababababababababababababababababababab");
            td->addString(3, "abcabcabz");

            std::vector <int> ids;
            td->queryString("ab", ids);

            std::cout << "ids: ";
            for(int id: ids) std::cout << " " << id;
            std::cout << "\n";

            std::cout << "END OF SANDBOX" << '\n';
        }
    };
}