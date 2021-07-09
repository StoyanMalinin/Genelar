#ifndef TREAP_CPP 
#define TREAP_CPP

#include <memory>
#include <vector>

#include "TreapNode.cpp"

namespace gnl
{
    enum class TreapFunction
    {
        Merge,
        Split,
        SplitSz,
        Other
    };

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
            }
            if(big!=nullptr)
            {
                big->recalc();
                big->pushLazy();
            }

            if(small==nullptr) return big;
            if(big==nullptr) return small;

            if(small->priority > big->priority)
            {
                small->R = Merge((NodeType*)(small->R), big);
                
                small->recalc();
                small->pushLazy();
                small->externalRecalc(TreapFunction::Merge);

                return small;
            }
            else
            {
                big->L = Merge(small, (NodeType*)(big->L));
                
                big->recalc();
                big->pushLazy();
                big->externalRecalc(TreapFunction::Merge);

                return big;
            }
        }

        static std::pair <NodeType*, NodeType*> Split(NodeType* T, const NodeType &x)
        {
            if(T==nullptr) return {nullptr, nullptr};
            
            T->recalc();
            T->pushLazy();

            if(*T < x)
            {
                auto splitRes = Split((NodeType*)(T->R), x);

                T->R = splitRes.first;
                
                T->parent = nullptr;
                T->recalc();
                T->pushLazy();
                T->externalRecalc(TreapFunction::Split);

                if(splitRes.second!=nullptr) 
                {
                    splitRes.second->parent = nullptr;
                 
                    splitRes.second->recalc();
                    splitRes.second->pushLazy();
                    //splitRes.second->externalRecalc(TreapFunction::Split);
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
                T->externalRecalc(TreapFunction::Split);

                if(splitRes.first!=nullptr) 
                {
                    splitRes.first->parent = nullptr;

                    splitRes.first->recalc();
                    splitRes.first->pushLazy();
                    //splitRes.first->externalRecalc(TreapFunction::Split);
                }

                return {splitRes.first, T};
            }
        }

        static std::pair <NodeType*, NodeType*> SplitSz(NodeType* T, int k)
        {
            if(T==nullptr) return {nullptr, nullptr};
            if(k==0) return {nullptr, T};

            T->recalc();
            T->pushLazy();

            int lSz = ((T->L==nullptr)?0:T->L->len); 
            if(k >= lSz+1)
            {
                auto splitRes = SplitSz((NodeType*)T->R, k-lSz-1);
                
                T->R = splitRes.first;

                T->recalc();
                T->pushLazy();
                T->externalRecalc(TreapFunction::SplitSz);

                if(splitRes.second != nullptr)
                {
                    splitRes.second->parent = nullptr;
                 
                    splitRes.second->recalc();
                    splitRes.second->pushLazy();
                }

                return {T, splitRes.second};
            }
            else
            {
                auto splitRes = SplitSz((NodeType*)T->L, k);

                T->L = splitRes.second;
                
                T->parent = nullptr;
                T->recalc();
                T->pushLazy();
                T->externalRecalc(TreapFunction::Split);

                if(splitRes.first!=nullptr) 
                {
                    splitRes.first->parent = nullptr;

                    splitRes.first->recalc();
                    splitRes.first->pushLazy();
                }

                return {splitRes.first, T};
            }
        }

        void printTreapInternal(TreapNode *x)
        {
            x->recalc();
            x->pushLazy();
            x->externalRecalc(TreapFunction::Other);

            if(x->L!=nullptr) printTreapInternal(x->L);
            std::cout << (*((NodeType*)x)) << " ";
            if(x->R!=nullptr) printTreapInternal(x->R);
        }

    public:
        void printTreap()
        {
            if(root!=nullptr) printTreapInternal(root);
            std::cout << '\n';
        }

        void findMatches(const std::string&s, std::vector <int> &ids)
        {
            if(root==nullptr)
            {
                ids = {};
                return;
            }

            root->findMatches(s, ids);
        }
        
        void addElement(NodeType *x)
        {
            auto help = Split(root, *x);

            root = Merge(help.first, x);
            root = Merge(root, help.second);
        }

        void addElements(const std::vector <NodeType*> &elements)
        {
            NodeType *last = root;

            NodeType *merged = nullptr;
            for(NodeType *x: elements)
            {
                auto help = Split(last, *x);

                merged = Merge(merged, help.first);
                merged = Merge(merged, x);
                
                last = help.second;
            }
            merged = Merge(merged, last);

            root = merged;
        }

        void removeElements(const std::vector <NodeType*> &elements)
        {
            NodeType *last = root;

            NodeType *merged = nullptr;
            for(NodeType *x: elements)
            {
                auto help = Split(last, *x);

                merged = Merge(merged, help.first);
                last = SplitSz(help.second, 1).second;
            }
            merged = Merge(merged, last);

            root = merged;
        }
    };
}

#endif