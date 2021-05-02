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
        std::shared_ptr <StringWithSuffixes<alphSz>> s;

    public:
        int ind, len;
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

        char getSymbol(int i) const
        {
            return (*(s->s))[ind+i];
        }

        static int lcp(std::shared_ptr <StringSuffix<alphSz>> a, std::shared_ptr <StringSuffix<alphSz>> b)
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

        template <size_t currAlphSz>
        friend bool operator <(const StringSuffix<currAlphSz> &A, const StringSuffix<currAlphSz> &B)
        {
            int lcpLen = StringSuffix<alphSz>::lcp(std::make_shared<StringSuffix<alphSz>>(A), std::make_shared<StringSuffix<alphSz>>(B));

            if(lcpLen==B.len) return false;
            if(lcpLen==A.len) return true;  

            if((A.getSymbol(lcpLen) != B.getSymbol(lcpLen)))
                return (A.getSymbol(lcpLen) < B.getSymbol(lcpLen));
        
            return A.s->id < B.s->id;
        }

        template <size_t currAlphSz>
        friend std::ostream& operator <<(std::ostream& o, const StringSuffix <currAlphSz> &s)
        {
            for(int i = s.ind;i<s.s->n;i++)
                o << (*(s.s->s))[i];

            return o;
        }
    };
}

#endif