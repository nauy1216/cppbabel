#ifndef BABEL_PARSER_util_location_H_
#define BABEL_PARSER_util_location_H_
#include <string>
using namespace std;

namespace util_location
{

    struct Pos
    {
        int start;
    };

    // These are used when `options.locations` is on, for the
    // `startLoc` and `endLoc` properties.

    class Position
    {
    public:
        int line;
        int column;
        int index;

        Position(int line, int col, int index)
        {
            this->line = line;
            this->column = col;
            this->index = index;
        }
    };

    class SourceLocation
    {
    public:
        Position *start;
        Position *end;
        string filename;
        string identifierName;

        SourceLocation(Position *start, Position *end)
        {
            this->start = start;
            // (may start as null, but initialized later)
            this->end = end;
        };
    };

    /**
     * creates a new position with a non-zero column offset from the given position.
     * This function should be only be used when we create AST node out of the token
     * boundaries, such as TemplateElement ends before tt.templateNonTail. This
     * function does not skip whitespaces.
     */
    Position createPositionWithColumnOffset(Position *position, int columnOffset)
    {
        return Position(position->line, position->column + columnOffset, position->index + columnOffset);
    }

}

#endif // BABEL_PARSER_util_location_H_