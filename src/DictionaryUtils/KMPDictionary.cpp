#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace gnl
{
    class KMPDictionary
    {
    private:
    
    public:
        std::vector <std::pair<int, std::string>> all;
        void addString(int id, const std::string &s)
        {
            all.push_back({id, s});
        }

        void queryString(const std::string &s, std::vector <int> &ids, bool fixRes = false)
        {
            if(fixRes==true) ids.clear();
            
            std::vector <int> f;
            f.resize(s.size());
            
            f[0] = 0;
            int len = 0;
            for(int i = 1;i<s.size();i++)
            {
                while(s[i]!=s[len] && len!=0) len = f[len-1];

                if(s[len]==s[i])
                {
                    len++;
                    f[i] = len;
                }
                else
                {
                    f[i] = 0;
                }
            }

            for(std::pair <int, std::string> &item: all)
            {
                len = 0;
                bool found = false;

                for(int i = 0;i<item.second.size();i++)
                {
                    while(item.second[i]!=s[len] && len!=0) len = f[len-1];

                    if(s[len]==item.second[i])
                    {
                        len++;

                        if(len==s.size())
                        {
                            found = true;
                            break;
                        }
                    }
                }

                if(found==true)
                    ids.push_back(item.first);
            }
            
            if(fixRes==true)
            {
                std::sort(ids.begin(), ids.end());
                ids.resize(std::unique(ids.begin(), ids.end()) - ids.begin());
            }
        }
    };
}
