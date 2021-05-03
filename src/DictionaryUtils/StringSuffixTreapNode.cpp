#ifndef STRINGSUFFIXTREAPNODE_CPP
#define STRINGSUFFIXTREAPNODE_CPP

#include <memory>
#include <vector>
#include <numeric>

#include "..\TreapUtils\TreapNode.cpp"
#include "..\StringUtils\StringSuffix.cpp"

namespace gnl
{
    template <size_t alphSz>
    class StringSuffixTreapNode : public TreapNode
    {
    private:
        StringSuffixTreapNode<alphSz> *counterpart;
        StringSuffixTreapNode<alphSz> *leftmostCounterPart;

    public:
        std::shared_ptr <StringSuffix<alphSz>> suff;

        StringSuffixTreapNode() : TreapNode() {}
        StringSuffixTreapNode(std::shared_ptr<StringSuffix<alphSz>> suff, 
                              StringSuffixTreapNode<alphSz> *counterpart) : StringSuffixTreapNode()
        {
            this->suff = suff;
            this->counterpart = counterpart;
        }
        
        void externalRecalc()
        {
            int bestInd = ((counterpart==nullptr)?-1:counterpart->getInd());
            leftmostCounterPart = counterpart;
            
            if(L!=nullptr)
            {
                int currInd = ((((StringSuffixTreapNode*)L)->leftmostCounterPart==nullptr)?-1:((StringSuffixTreapNode*)L)->leftmostCounterPart->getInd());
                if(currInd<bestInd) 
                {
                    bestInd = currInd;
                    leftmostCounterPart = ((StringSuffixTreapNode*)L)->leftmostCounterPart;
                }
            }
            if(R!=nullptr)
            {
                int currInd = ((((StringSuffixTreapNode*)R)->leftmostCounterPart==nullptr)?-1:((StringSuffixTreapNode*)R)->leftmostCounterPart->getInd());

                if(currInd<bestInd) 
                {
                    bestInd = currInd;
                    leftmostCounterPart = ((StringSuffixTreapNode*)R)->leftmostCounterPart;
                }
            }
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
            externalRecalc();

            bool currOk = false;
            int matchingLen = 0;

            int counterpartInd = ((leftmostCounterPart==nullptr)?-1:leftmostCounterPart->getInd());
            if(counterpartInd>leftmostInd) return;

            if(lOk==true && rOk==true) currOk = true;
            else
            {
                while(matchingLen<pattern.size() && matchingLen<suff->len && pattern[matchingLen]==suff->getSymbol(matchingLen)) matchingLen++;
                if(matchingLen==pattern.size()) currOk = true;
            }

            if(currOk==true)
            {
                if(L!=nullptr) ((StringSuffixTreapNode*)L)->findMatchesInternal(pattern, ids, leftmostInd,  lOk, currOk);
                
                ids.push_back(suff->getStringId());
                if(leftmostInd==std::numeric_limits<int>::max()) leftmostInd = getInd();

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
}

#endif