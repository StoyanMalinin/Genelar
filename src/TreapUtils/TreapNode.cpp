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
        std::shared_ptr<TreapNode> L, R;
        
        TreapNode()
        {
            this->L = nullptr;
            this->R = nullptr;

            len = 1;
            this->priority = rnd();
        }

        virtual void recalc()
        {
            len = 1;
            if(L!=nullptr) len += L->len;
            if(R!=nullptr) len += R->len;
        }
    };
    std::mt19937 TreapNode::rnd = std::mt19937(22); 
}

#endif