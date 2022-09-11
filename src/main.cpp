#include <iostream>
#include <cstring>
#include <vector>

#include "Testing\Sandbox.cpp"
#include "Testing\UnitTests.cpp"
#include "DictionaryUtils\TreapDictionary.cpp"
#include "StringUtils\HashingData.h"

const size_t alphSz = 26;
uint8_t alphMap[256];

gnl::TreapDictionary<alphSz>* init()
{
	memset(alphMap, -1, sizeof(alphMap));
	for(char c = 'a';c<='z';c++)
        alphMap[c] = c - 'a';
	gnl::HashingData::init();

	gnl::TreapDictionary<alphSz> *td = new gnl::TreapDictionary<alphSz>(alphMap);
	return td;
}

int main(int argc, char *argv[])
{
	gnl::TreapDictionary<alphSz> *td = init();

	while(true)
	{
		std::string cmd;
		std::cin >> cmd;

		if(cmd=="add")
        {
            int id;
            std::string s;
            std::cin >> id >> s;

            td->addString(id, s);
        }
        else if(cmd=="remove")
        {
            int id;
            std::cin >> id;

            td->removeString(id);
        }
        else if(cmd=="query")
        {
            std::string s;
            std::cin >> s;

            std::vector <int> ids;
            td->queryString(s, ids, true);

            std::cout << "Entries containing the queried string: ";
            for(int id: ids) std::cout << " " << id;
            std::cout << '\n';
        }
        else if(cmd=="quit")
        {
            break;
        }
        else
        {
            std::cout << "Invalid command" << '\n';
        }
	}

	delete td;
}
