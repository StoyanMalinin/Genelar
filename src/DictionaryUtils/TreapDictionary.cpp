#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "..\TreapUtils\Treap.cpp"
#include "StringSuffixTreapNode.cpp"
#include "..\StringUtils\StringWithSuffixes.cpp"

namespace gnl
{
    template <size_t alphSz>
    class TreapDictionary
    {
    private:
        uint8_t *alphMap;
        Treap<StringSuffixTreapNode<alphSz>> *T;

    public:
        TreapDictionary(uint8_t *alphMap)
        {
            this->alphMap = alphMap;
            this->T = new Treap<StringSuffixTreapNode<alphSz>>();
        }

    public:
        void addString(int id, const std::string &s)
        {
            StringWithSuffixes<alphSz> *str = new StringWithSuffixes<alphSz>(id, s, alphMap);

            std::vector <StringSuffix<alphSz>> suffs;
            for(int i = 0;i<str->n;i++)
                suffs.push_back(*(str->suff[i]));
            std::sort(suffs.begin(), suffs.end());

            StringSuffixTreapNode<alphSz>* last = nullptr;
            for(int i = 0;i<suffs.size();i++)
            {
                StringSuffixTreapNode<alphSz> *curr = 
                new StringSuffixTreapNode<alphSz>(std::make_shared<StringSuffix<alphSz>>(suffs[i]), last);

                T->addElement(curr);

                last = curr;
            } 
        }

        void queryString(const std::string&s, std::vector <int> &ids)
        {
            T->root->findMatches(s, ids);
        }
    };
}
