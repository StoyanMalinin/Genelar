#ifndef HASH_CPP
#define HASH_CPP

#include <cstring>

#include "HashingData.cpp"

namespace gnl
{
    struct Hash
    {
        int len;
        int h[HashingData::hCnt];

        uint8_t *alphMap;

        Hash(){}
        Hash(uint8_t *alphMap) 
        {
            this->alphMap = alphMap;

            this->len = 0;
            memset(this->h, 0, sizeof(this->h));
        }

        void addChar(char c)
        {
            len++;
            for(int i = 0;i<HashingData::hCnt;i++)
            {
                h[i] = (h[i]*1LL*HashingData::key[i] + (alphMap[c]+1))%HashingData::mod[i];
            }
        }

        static Hash removePref(Hash big, const Hash &small)
        {
            for(int i = 0;i<HashingData::hCnt;i++)
            {
                big.h[i] = (big.h[i] - small.h[i]*1LL*HashingData::pVal[big.len-small.len][i] 
                            + HashingData::mod[i]*HashingData::mod[i])%HashingData::mod[i];
            }
            big.len -= small.len;

            return big;
        }
    };

    Hash operator +(Hash A, const Hash &B)
    {
        A.len += B.len;
        for(int i = 0;i<HashingData::hCnt;i++)
        {
            A.h[i] = (A.h[i]*1LL*HashingData::pVal[B.len][i] + B.h[i])%HashingData::hCnt;
        }

        return A;
    }

    bool operator ==(const Hash &A, const Hash &B)
    {
        if(A.len!=B.len) return false;
        for(int i = 0;i<HashingData::hCnt;i++)
        {
            if(A.h[i]!=B.h[i]) return false;
        }

        return true;
    }

    bool operator !=(const Hash &A, const Hash &B)
    {
        return (!(A==B));
    }
}

#endif