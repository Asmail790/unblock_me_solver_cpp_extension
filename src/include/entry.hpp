#ifndef UnblockMe_Utils_Entry_Header
#define UnblockMe_Utils_Entry_Header

#include <utility>
#include <vector>
#include <string>


namespace UnblockMe::Utils::Entry {
    using std::pair;
    using std::vector;
    using std::string;

    class BoundingBox{
        public:
            const double left;
            const double right;
            const double top;
            const double bottom;


            auto width()->double const;

            auto height()->double const;

            auto topLeft()->pair<const double,const double> const;
    };

    class NextStep {
        public:
            const BoundingBox from;
            const BoundingBox to;
            const string message;
    };

    class IGuider{
        public:
            virtual auto guideOneStep(const vector<const BoundingBox>& boundingBoxes)->NextStep = 0;
    };
}

#endif