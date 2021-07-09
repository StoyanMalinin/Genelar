#ifndef STRINGSUFFIXTREAPNODE_CPP
#define STRINGSUFFIXTREAPNODE_CPP

#include <memory>
#include <vector>
#include <numeric>

#include "..\TreapUtils\Treap.cpp"
#include "..\TreapUtils\TreapNode.cpp"
#include "..\StringUtils\StringSuffix.cpp"

namespace gnl
{
    template <size_t alphSz>
    class StringSuffixTreapNode : public TreapNode
    {
    private:
        StringSuffixTreapNode<alphSz> *counterpart;

    public:
        StringSuffixTreapNode<alphSz> *leftmostCounterPart;
        std::shared_ptr<StringSuffix<alphSz>> suff;

        StringSuffixTreapNode() : TreapNode() 
        {
            this->counterpart = nullptr;
            this->leftmostCounterPart = nullptr;            
        }
        StringSuffixTreapNode(std::shared_ptr<StringSuffix<alphSz>> suff, 
                              StringSuffixTreapNode<alphSz> *counterpart) : StringSuffixTreapNode()
        {
            this->suff = suff;
            this->counterpart = counterpart;
        }
        
        void externalRecalc(TreapFunction f) override
        {    
            if(f!=TreapFunction::Split && f!=TreapFunction::SplitSz)
            {
                leftmostCounterPart = counterpart;    
                if(L!=nullptr && leftmostCounterPart!=nullptr)
                {
                    StringSuffixTreapNode *other = ((StringSuffixTreapNode*)L)->leftmostCounterPart;
                    if(other==nullptr || *other < *leftmostCounterPart) 
                    {
                        leftmostCounterPart = other;
                    }
                }
                if(R!=nullptr && leftmostCounterPart!=nullptr)
                {
                    StringSuffixTreapNode *other = ((StringSuffixTreapNode*)R)->leftmostCounterPart;
                    if(other==nullptr || *other < *leftmostCounterPart) 
                    {
                        leftmostCounterPart = other;
                    }
                }
            }  
        }

        template <size_t currAlphSz> 
        friend bool operator <(const StringSuffixTreapNode<currAlphSz> &A, const StringSuffixTreapNode<currAlphSz> &B)
        {
            return A.suff < B.suff;
        }

        friend std::ostream& operator <<(std::ostream& o, const StringSuffixTreapNode &s)
        {
            o << "{" << "suff: " << *s.suff << ", id: " << s.suff->getStringId() << "}";
            return o;
        }

        static int opCnt;
        void findMatches(const std::string &pattern, std::vector <int> &ids)
        {
            int leftMostInd = std::numeric_limits<int>::max();
            findMatchesInternal(pattern, ids, leftMostInd);
        }

    private:
        void findMatchesInternal(const std::string &pattern, std::vector <int> &ids, int &leftmostInd, bool lOk = false, bool rOk = false)
        {
            recalc();
            pushLazy();
            externalRecalc(TreapFunction::Other);

            bool currOk = false;
            int matchingLen = 0;

            if(leftmostInd!=std::numeric_limits<int>::max())
            {
                int counterpartInd = ((leftmostCounterPart==nullptr)?-1:leftmostCounterPart->getInd());
                if(counterpartInd>leftmostInd) 
                {
                    return;
                }
            }

            if(lOk==true && rOk==true) currOk = true;
            else
            {
                opCnt++;
                while(matchingLen<pattern.size() && matchingLen<suff->len && pattern[matchingLen]==suff->getSymbol(matchingLen)) matchingLen++, opCnt++;
                if(matchingLen==pattern.size()) currOk = true;
            }

            if(currOk==true)
            {
                if(L!=nullptr) ((StringSuffixTreapNode*)L)->findMatchesInternal(pattern, ids, leftmostInd,  lOk, currOk);
                
                ids.push_back(suff->getStringId());
                if(leftmostInd==std::numeric_limits<int>::max()) 
                {
                    leftmostInd = getInd();
                }
                
                if(R!=nullptr) ((StringSuffixTreapNode*)R)->findMatchesInternal(pattern, ids, leftmostInd, currOk, rOk);
            }
            else
            {
                if(L!=nullptr && (matchingLen<suff->len && (matchingLen==pattern.size() || pattern[matchingLen]<suff->getSymbol(matchingLen))))
                    ((StringSuffixTreapNode*)L)->findMatchesInternal(pattern, ids, leftmostInd, lOk, currOk);
                    
                if(R!=nullptr && (matchingLen==suff->len || (matchingLen!=pattern.size() && pattern[matchingLen]>suff->getSymbol(matchingLen)))) 
                    ((StringSuffixTreapNode*)R)->findMatchesInternal(pattern, ids, leftmostInd, currOk, rOk);
            }
        }
    };
    template <size_t alphSz>
    int StringSuffixTreapNode<alphSz>::opCnt = 0;
}

#endif