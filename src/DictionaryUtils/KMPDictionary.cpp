#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace gnl
{
    class KMPDictionary
    {
    private:
        std::map <int, const std::string*> mp;
    
    public:
        void addString(int id, const std::string &s)
        {
            mp[id] = new std::string(s);
        }

        void removeString(int id)
        {
            mp.erase(id);
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

            for(std::pair <int, const std::string*> item: mp)
            {
                len = 0;
                bool found = false;

                const std::string &text = *item.second;
                for(int i = 0;i<text.size();i++)
                {
                    while(text[i]!=s[len] && len!=0) len = f[len-1];

                    if(s[len]==text[i])
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
