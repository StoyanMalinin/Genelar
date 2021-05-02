#ifndef STRINGWITHSUFFIXES_CPP
#define STRINGWITHSUFFIXES_CPP

#include <memory>
#include <string>

#include "Hash.cpp"
#include "StringSuffix.cpp"

namespace gnl
{
    template <size_t alphSz>
    class StringSuffix;

    template <size_t alphSz>
    class StringWithSuffixes
    {
    public:
        int n;
        std::shared_ptr<std::string> s;

    private:
        Hash *h;
        uint8_t *alphMap;
        std::shared_ptr<StringSuffix<alphSz>> *suff;

    public:
        StringWithSuffixes(const std::string &s, uint8_t *alphMap)
        {
            this->n = s.size();
            this->s = std::make_shared<std::string>(s);
        
            this->h = new Hash[n];
            this->alphMap = alphMap;
            this->suff = new std::shared_ptr<StringSuffix<alphSz>>[n];

            Hash hCurr = Hash(alphMap);
            for(int i = 0;i<this->n;i++)
            {
                hCurr.addChar(s[i]);
                h[i] = hCurr;
            }

            for(int i = 0;i<n;i++)
            {
                suff[i] = std::make_shared<StringSuffix<alphSz>>(*(new StringSuffix<alphSz>(i, std::make_shared<StringWithSuffixes<alphSz>>(*this))));
            }
        }

    public:
        friend std::ostream& operator <<(std::ostream &o, const StringWithSuffixes &s)
        {
            o << *s.s;
            return o;
        }

        Hash getHash(int l, int r)
        {
            if(l==0) return h[r];
            return Hash::removePref(h[r], h[l-1]);
        }

        int lcp(int i1, int i2)
        {
            return StringSuffix<alphSz>::lcp(suff[i1], suff[i2]);
        }
    };
}

#endif