#include <memory>

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
    };
}