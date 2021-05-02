#include <memory>

#include "TreapNode.cpp"

namespace gnl
{
    template <class NodeType>
    class Treap
    {
    public:
        std::shared_ptr <TreapNode> root;

        static NodeType toNodeType(std::shared_ptr<TreapNode> x)
        {
            return (*((NodeType*)(&(*x))));
        }

        static std::shared_ptr<TreapNode> Merge(std::shared_ptr<TreapNode> small, std::shared_ptr<TreapNode> big)
        {
            if(small==nullptr) return big;
            if(big==nullptr) return small;

            big->recalc();
            small->recalc();
            
            if(small->priority > big->priority)
            {
                small->R = Merge(small->R, big);
                small->recalc();

                return small;
            }
            else
            {
                big->L = Merge(small, big->L);
                big->recalc();

                return big;
            }
        }

        static std::pair <std::shared_ptr<TreapNode>, std::shared_ptr<TreapNode>> Split(std::shared_ptr <TreapNode> T, NodeType x)
        {
            if(T==nullptr) return {nullptr, nullptr};
            T->recalc();

            if(toNodeType(T) < x)
            {
                auto splitRes = Split(T->R, x);

                T->R = splitRes.first;
                T->parent = nullptr;
                T->recalc();

                if(splitRes.second!=nullptr) 
                {
                    splitRes.second->parent = nullptr;
                    splitRes.second->recalc();
                }

                return {T, splitRes.second};
            }
            else
            {
                auto splitRes = Split(T->L, x);

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

        void printTreapInternal(std::shared_ptr<TreapNode> x)
        {
            x->recalc();

            if(x->L!=nullptr) printTreapInternal(x->L);
            std::cout << "{" << (*((NodeType*)(&(*x)))) << ", " << x->getInd() << "}" << " ";
            if(x->R!=nullptr) printTreapInternal(x->R);
        }

    public:
        void printTreap()
        {
            if(root!=nullptr) printTreapInternal(root);
            std::cout << '\n';
        }

        void dfs(std::shared_ptr<TreapNode> x, int depth = 0)
        {
            int ind = x->getInd();

            for(int i = 0;i<depth;i++) std::cout << " ";
            std::cout << "at " << toNodeType(x) << " -> " << "ind: " << ind << " | " << "len: " << x->len
                      << " " << "priority: " << x->priority << '\n';

            if(x->L!=nullptr) dfs(x->L, depth+1);
            if(x->R!=nullptr) dfs(x->R, depth+1);
        }
        
        void addElement(std::shared_ptr<NodeType> x)
        {
            auto help = Split(root, *x);

            root = Merge(help.first, x);
            root = Merge(root, help.second);
        }
    };
}
