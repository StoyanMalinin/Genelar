#include <iostream>
#include <cstring>

#include "..\TreapUtils\Treap.cpp"
#include "..\StringUtils\StringWithSuffixes.cpp"
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

            StringSuffixTreapNode<alphSz> *x = new StringSuffixTreapNode<alphSz>();
            Treap <StringSuffixTreapNode<alphSz>> *T = new Treap <StringSuffixTreapNode<alphSz>>();

            StringWithSuffixes<alphSz> *str = new StringWithSuffixes<alphSz>("pederast", alphMap);

            for(int i = 0;i<str->n;i++)
                T->addElement(std::shared_ptr<StringSuffixTreapNode<alphSz>>(new StringSuffixTreapNode<alphSz>(str->suff[i])));
            T->printTreap();
        }
    };
}