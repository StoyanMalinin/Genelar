#include <memory>
#include <vector>

#include "..\TreapUtils\TreapNode.cpp"
#include "..\StringUtils\StringSuffix.cpp"

namespace gnl
{
    template <size_t alphSz>
    struct StringSuffixTreapNode : public TreapNode
    {
        std::shared_ptr <StringSuffix<alphSz>> suff;

        StringSuffixTreapNode() : TreapNode() {}
        StringSuffixTreapNode(std::shared_ptr<StringSuffix<alphSz>> suff) : StringSuffixTreapNode()
        {
            this->suff = suff;
        }

        void recalc()
        {
            TreapNode::recalc();
        }               
        
        template <size_t currAlphSz> 
        friend bool operator <(const StringSuffixTreapNode<currAlphSz> &A, const StringSuffixTreapNode<currAlphSz> &B)
        {
            return *(A.suff) < *(B.suff);
        }

        friend std::ostream& operator <<(std::ostream& o, const StringSuffixTreapNode &s)
        {
            o << *s.suff;
            return o;
        }

        void findMatches(const std::string &pattern, std::vector <int> &ids, bool lOk = false, bool rOk = false)
        {
            bool currOk = false;
            int matchingLen = 0;
            std::cout << "tarsq " << *suff << '\n';

            if(lOk==true && rOk==true) currOk = true;
            else
            {
                while(matchingLen<pattern.size() && matchingLen<suff->len && pattern[matchingLen]==suff->getSymbol(matchingLen)) matchingLen++;
                if(matchingLen==pattern.size()) currOk = true;
            }

            if(currOk==true)
            {
                ids.push_back(suff->getStringId());
                std::cout << "otkrih go pri " << *suff << " " << suff->len << '\n';

                if(L!=nullptr) Treap<StringSuffixTreapNode<alphSz>>::toNodeType(L).findMatches(pattern, ids, lOk, currOk);
                if(R!=nullptr) Treap<StringSuffixTreapNode<alphSz>>::toNodeType(R).findMatches(pattern, ids, currOk, rOk);
            }
            else
            {
                if(L!=nullptr && (matchingLen<suff->len && (matchingLen==pattern.size() || pattern[matchingLen]<suff->getSymbol(matchingLen))))
                    Treap<StringSuffixTreapNode<alphSz>>::toNodeType(L).findMatches(pattern, ids, lOk, currOk);
                    
                if(R!=nullptr && (matchingLen==suff->len || (matchingLen!=pattern.size() && pattern[matchingLen]>suff->getSymbol(matchingLen)))) 
                    Treap<StringSuffixTreapNode<alphSz>>::toNodeType(R).findMatches(pattern, ids, currOk, rOk);
            }
        }
    };
}