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
        int n, id;
        std::shared_ptr<std::string> s;
        std::shared_ptr<StringSuffix<alphSz>> *suff;

    private:
        Hash *h;
        uint8_t *alphMap;

    public:
        StringWithSuffixes(int id, const std::string &s, uint8_t *alphMap) : StringWithSuffixes(s, alphMap)
        {
            this->id = id;
        }
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
        template <size_t currAlphSz>
        friend std::ostream& operator <<(std::ostream &o, const StringWithSuffixes <currAlphSz> &s)
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