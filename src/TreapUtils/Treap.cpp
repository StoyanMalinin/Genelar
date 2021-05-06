#ifndef TREAP_CPP 
#define TREAP_CPP

#include <memory>

#include "TreapNode.cpp"

namespace gnl
{
    template <class NodeType>
    class Treap
    {
    public:
        NodeType* root;

        static NodeType* Merge(NodeType *small, NodeType *big)
        {
            if(small!=nullptr)
            {
                small->recalc();
                small->pushLazy();
                //small->externalRecalc();
            }
            if(big!=nullptr)
            {
                big->recalc();
                big->pushLazy();
                //big->externalRecalc();
            }

            if(small==nullptr) return big;
            if(big==nullptr) return small;

            if(small->priority > big->priority)
            {
                small->R = Merge((NodeType*)(small->R), big);
                
                small->recalc();
                small->pushLazy();
                small->externalRecalc();

                return small;
            }
            else
            {
                big->L = Merge(small, (NodeType*)(big->L));
                
                big->recalc();
                big->pushLazy();
                big->externalRecalc();

                return big;
            }
        }

        static std::pair <NodeType*, NodeType*> Split(NodeType* T, const NodeType &x)
        {
            if(T==nullptr) return {nullptr, nullptr};
            
            T->recalc();
            T->pushLazy();
            //T->externalRecalc();

            if(*T < x)
            {
                auto splitRes = Split((NodeType*)(T->R), x);

                T->R = splitRes.first;
                
                T->parent = nullptr;
                T->recalc();
                T->pushLazy();
                T->externalRecalc();

                if(splitRes.second!=nullptr) 
                {
                    splitRes.second->parent = nullptr;
                 
                    splitRes.second->recalc();
                    splitRes.second->pushLazy();
                    //splitRes.second->externalRecalc();
                }

                return {T, splitRes.second};
            }
            else
            {
                auto splitRes = Split((NodeType*)(T->L), x);

                T->L = splitRes.second;
                
                T->parent = nullptr;
                T->recalc();
                T->pushLazy();
                T->externalRecalc();

                if(splitRes.first!=nullptr) 
                {
                    splitRes.first->parent = nullptr;

                    splitRes.first->recalc();
                    splitRes.first->pushLazy();
                    //splitRes.first->externalRecalc();
                }

                return {splitRes.first, T};
            }
        }

        void printTreapInternal(TreapNode *x)
        {
            x->recalc();
            x->pushLazy();
            x->externalRecalc();

            if(x->L!=nullptr) printTreapInternal(x->L);
            std::cout << "{" << *((NodeType*)x) << ", " << x->getInd() << " || " << (*((NodeType*)(&(*x)))).suff->getStringId() << " && " 
                      << ((((NodeType*)x)->leftmostCounterPart)==nullptr?-1:(((NodeType*)x)->leftmostCounterPart)->getInd()) << "}" << " ";
            if(x->R!=nullptr) printTreapInternal(x->R);
        }

    public:
        void printTreap()
        {
            if(root!=nullptr) printTreapInternal(root);
            std::cout << '\n';
        }

        void dfs(NodeType *x, int depth = 0)
        {
            int ind = x->getInd();

            for(int i = 0;i<depth;i++) std::cout << " ";
            std::cout << "at " << *(x->suff) << " -> " << "ind: " << ind << " | " << "len: " << x->len
                      << " " << "priority: " << x->priority
                      << " || " << "counterPartInd: " << ((x->leftmostCounterPart==nullptr)?-1:(x->leftmostCounterPart->getInd()))  <<  '\n';

            if(x->L!=nullptr) dfs((NodeType*)(x->L), depth+1);
            if(x->R!=nullptr) dfs((NodeType*)(x->R), depth+1);
        }
        
        void addElement(NodeType *x)
        {
            auto help = Split(root, *x);

            root = Merge(help.first, x);
            root = Merge(root, help.second);
        }
    };
}

#endif