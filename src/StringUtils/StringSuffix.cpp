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
        int getStringId()
        {
            return s->id;
        }

        Hash getHash(int l) const
        {
            return s->getHash(ind, ind+l-1);
        }

        char getSymbol(int i) const
        {
            return (*(s->s))[ind+i];
        }

        static int lcp(std::shared_ptr <StringSuffix<alphSz>> a, std::shared_ptr <StringSuffix<alphSz>> b)
        {
            if(a->getSymbol(0)!=b->getSymbol(0))
                return 0;

            int res = 0;
            int l = 1, r = std::min(a->len, b->len), mid; 
        
            while(l<=r)
            {
                mid = (l+r)/2;

                if(a->getHash(mid)==b->getHash(mid)) 
                {
                    res = mid;
                    l = mid + 1;
                }
                else 
                    r = mid - 1;
            }

            return res;
        }

        static int lcp(const StringSuffix<alphSz> &a, const StringSuffix<alphSz> &b)
        {
            if(a.getSymbol(0)!=b.getSymbol(0))
                return 0;

            int res = 0;
            int l = 1, r = std::min(a.len, b.len), mid; 
        
            while(l<=r)
            {
                mid = (l+r)/2;

                if(a.getHash(mid)==b.getHash(mid)) 
                {
                    res = mid;
                    l = mid + 1;
                }
                else 
                    r = mid - 1;
            }

            return res;
        }

        template <size_t currAlphSz>
        friend bool operator <(const StringSuffix<currAlphSz> &A, const StringSuffix<currAlphSz> &B)
        {
            int lcpLen = StringSuffix<alphSz>::lcp(A, B);

            if(lcpLen==B.len && lcpLen!=A.len) return false;
            if(lcpLen==A.len && lcpLen!=B.len) return true;  

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