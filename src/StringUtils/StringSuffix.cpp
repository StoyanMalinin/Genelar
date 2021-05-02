#ifndef STRINGSUFFIX_CPP 
#define STRINGSUFFIX_CPP

#include <memory>
#include <string>

#include "Hash.cpp"
#include "StringWithSuffixes.cpp"

namespace gnl
{
    template <size_t alphSz>
    class StringWithSuffixes;

    template <size_t alphSz>
    class StringSuffix 
    {
    private:
        int ind, len;
        std::shared_ptr <StringWithSuffixes<alphSz>> s;

    public:
        StringSuffix (){}
        StringSuffix(int ind, std::shared_ptr <StringWithSuffixes<alphSz>> s)
        {
            this->ind = ind;
            this->s = s;
        
            this->len = s->n - this->ind;
        } 
        
    public:
        Hash getHash(int l)
        {
            return s->getHash(ind, ind+l-1);
        }

        template <size_t currAlphSz>
        static int lcp(std::shared_ptr<StringSuffix<currAlphSz>> a, std::shared_ptr <StringSuffix<currAlphSz>> b)
        {
            int cnt = 0;
            int l = 1, r = std::min(a->len, b->len), mid; 
        
            while(l+1<r)
            {
                mid = (l+r)/2;

                if(a->getHash(mid)==b->getHash(mid)) l = mid;
                else r = mid - 1;
            }

            if(a->getHash(r)==b->getHash(r)) return r;
            if(a->getHash(l)==b->getHash(l)) return l;
            return 0;
        }
    };
}

#endif