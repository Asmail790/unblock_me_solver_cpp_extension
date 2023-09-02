#include <utility>
#include <vector>
#include <string>

#include "entry.hpp"

namespace UnblockMe::Utils::Entry {
    using std::pair;
    using std::vector;
    using std::string;

    auto BoundingBox::width()->double const{
        return this->right - this->left;
    }

    auto BoundingBox::height()->double const {
        return this->bottom - this->top;
    }

    auto BoundingBox::topLeft()->pair<const double,const double> const{
        return pair<const double,const double>{this->left,this->top};
    }

}