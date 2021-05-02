#include <array>

namespace gnl
{
    namespace HashingData
    {
        static constexpr int hCnt = 2;
        static constexpr long long key[hCnt] = {269, 271};
        static constexpr long long mod[hCnt] = {(long long)1e9+7, (long long)1e9+9};

        static const int MAXLEN = 1e6;
        static std::array <int[hCnt], MAXLEN> pVal;

        static void init()
        {
            for(int i = 0;i<hCnt;i++) pVal[0][i] = 1;
            for(int i = 1;i<MAXLEN;i++)
            {
                for(int j = 0;j<hCnt;j++)
                {
                    pVal[i][j] = (pVal[i-1][j]*1LL*key[j])%mod[j];
                }
            }
        }
    };
}