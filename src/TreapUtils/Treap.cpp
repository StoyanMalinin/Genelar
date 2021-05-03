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
            if(small==nullptr) return big;
            if(big==nullptr) return small;

            big->recalc();
            big->externalRecalc();

            small->recalc();
            small->externalRecalc();
            
            if(small->priority > big->priority)
            {
                small->R = Merge((NodeType*)(small->R), big);
                small->externalRecalc();
                small->recalc();

                return small;
            }
            else
            {
                big->L = Merge(small, (NodeType*)(big->L));
                big->externalRecalc();
                big->recalc();

                return big;
            }
        }

        static std::pair <NodeType*, NodeType*> Split(NodeType* T, NodeType x)
        {
            if(T==nullptr) return {nullptr, nullptr};
            T->externalRecalc();
            T->recalc();

            if(*T < x)
            {
                auto splitRes = Split((NodeType*)(T->R), x);

                T->R = splitRes.first;
                T->parent = nullptr;
                T->externalRecalc();
                T->recalc();

                if(splitRes.second!=nullptr) 
                {
                    splitRes.second->parent = nullptr;
                    splitRes.second->externalRecalc();
                    splitRes.second->recalc();
                }

                return {T, splitRes.second};
            }
            else
            {
                auto splitRes = Split((NodeType*)(T->L), x);

                T->L = splitRes.second;
                T->parent = nullptr;
                T->recalc();

                if(splitRes.first!=nullptr) 
                {
                    splitRes.first->parent = nullptr;
                    splitRes.first->recalc();
                }

                return {splitRes.first, T};
            }
        }

        void printTreapInternal(TreapNode *x)
        {
            x->recalc();
            x->externalRecalc();

            if(x->L!=nullptr) printTreapInternal(x->L);
            std::cout << "{" << *((NodeType*)x) << ", " << x->getInd() << "|" << (*((NodeType*)(&(*x)))).suff->getStringId() << "}" << " ";
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
            std::cout << "at " << ((NodeType*)x) << " -> " << "ind: " << ind << " | " << "len: " << x->len
                      << " " << "priority: " << x->priority << '\n';

            if(x->L!=nullptr) dfs(x->L, depth+1);
            if(x->R!=nullptr) dfs(x->R, depth+1);
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