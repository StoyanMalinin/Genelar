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
            }
            if(R!=nullptr)
            {
                len += R->len;
            }
        }
 
        virtual void pushLazy()
        {
            if(L!=nullptr) 
            {
                L->parent = this;
            }
            if(R!=nullptr) 
            {
                R->parent = this;
            }
        }

        virtual void externalRecalc()
        {
            
        }

        inline int getInd(bool toAdd = true)
        {
            recalc();
            pushLazy();
    
            if(toAdd==true)
            {
                if(parent==nullptr) return ((L==nullptr)?0:L->len);
                return 1 + ((L==nullptr)?0:L->len) + parent->getInd((parent->R==this));
            }
            else
            {
                if(parent==nullptr) return -1;
                return parent->getInd((parent->R==this));
            }
        }
    };
    std::mt19937 TreapNode::rnd = std::mt19937(22); 
}

#endif