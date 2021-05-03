#ifndef TREAPNODE_CPP
#define TREAPNODE_CPP

#include <memory>
#include <random>

namespace gnl
{
    struct TreapNode
    {
        static std::mt19937 rnd;

        int len;
        int priority;
        
        TreapNode *L, *R;
        TreapNode *parent;
        
        TreapNode()
        {
            this->L = nullptr;
            this->R = nullptr;
            this->parent = nullptr;

            len = 1;
            this->priority = rnd();
        }

        virtual void recalc()
        {
            len = 1;
            if(L!=nullptr) 
            {
                len += L->len;
                L->parent = this;
            }
            if(R!=nullptr) 
            {
                len += R->len;
                R->parent = this;
            }
        }
 
        virtual void pushLazy()
        {

        }

        virtual void externalRecalc()
        {
            
        }

        int getInd(bool toAdd = true)
        {
            recalc();

            int before = 0;
            if(toAdd==true) before += 1 + ((L==nullptr)?0:L->len);

            if(parent==nullptr) return before - 1;
            return before + parent->getInd((parent->R!=nullptr && parent->R->priority==priority));//((parent->R==nullptr)?-69:parent->R->priority)==this->priority); 
        }
    };
    std::mt19937 TreapNode::rnd = std::mt19937(22); 
}

#endif