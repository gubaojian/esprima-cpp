#ifndef __ESPRIMA_H__
#define __ESPRIMA_H__

#include <assert.h>
#include <string>
#include <vector>

// API from https://developer.mozilla.org/en-US/docs/SpiderMonkey/Parser_API

namespace esprima {

    struct Pool;

    struct Poolable {
        Poolable *poolable;
        Poolable(Pool &pool);
        virtual ~Poolable() {}
    };

    struct Pool {
        Poolable *first;
        Pool() : first() {}
        ~Pool() {
            while (first) {
                Poolable *poolable = first;
                first = first->poolable;
                delete poolable;
            }
        }
    };

    struct Position : Poolable {
        int line;
        int column;
        Position(Pool &pool) : Poolable(pool), line(), column() {}
    };

    struct SourceLocation {
        Position *start;
        Position *end;
        SourceLocation(Pool &pool) : start(), end() {}
    };

    struct Program;
    struct Identifier;
    struct BlockStatement;
    struct EmptyStatement;
    struct ExpressionStatement;
    struct IfStatement;
    struct LabeledStatement;
    struct BreakStatement;
    struct ContinueStatement;
    struct WithStatement;
    struct SwitchCase;
    struct SwitchStatement;
    struct ReturnStatement;
    struct ThrowStatement;
    struct CatchClause;
    struct TryStatement;
    struct WhileStatement;
    struct DoWhileStatement;
    struct ForStatement;
    struct ForInStatement;
    struct DebuggerStatement;
    struct FunctionDeclaration;
    struct VariableDeclarator;
    struct VariableDeclaration;
    struct ThisExpression;
    struct ArrayExpression;
    struct Property;
    struct ObjectExpression;
    struct FunctionExpression;
    struct SequenceExpression;
    struct UnaryExpression;
    struct BinaryExpression;
    struct AssignmentExpression;
    struct UpdateExpression;
    struct LogicalExpression;
    struct ConditionalExpression;
    struct NewExpression;
    struct CallExpression;
    struct MemberExpression;
    struct NullLiteral;
    struct RegExpLiteral;
    struct StringLiteral;
    struct NumericLiteral;
    struct BooleanLiteral;

    struct Visitor {
        virtual void visit(Program *node) = 0;
        virtual void visit(Identifier *node) = 0;
        virtual void visit(BlockStatement *node) = 0;
        virtual void visit(EmptyStatement *node) = 0;
        virtual void visit(ExpressionStatement *node) = 0;
        virtual void visit(IfStatement *node) = 0;
        virtual void visit(LabeledStatement *node) = 0;
        virtual void visit(BreakStatement *node) = 0;
        virtual void visit(ContinueStatement *node) = 0;
        virtual void visit(WithStatement *node) = 0;
        virtual void visit(SwitchCase *node) = 0;
        virtual void visit(SwitchStatement *node) = 0;
        virtual void visit(ReturnStatement *node) = 0;
        virtual void visit(ThrowStatement *node) = 0;
        virtual void visit(CatchClause *node) = 0;
        virtual void visit(TryStatement *node) = 0;
        virtual void visit(WhileStatement *node) = 0;
        virtual void visit(DoWhileStatement *node) = 0;
        virtual void visit(ForStatement *node) = 0;
        virtual void visit(ForInStatement *node) = 0;
        virtual void visit(DebuggerStatement *node) = 0;
        virtual void visit(FunctionDeclaration *node) = 0;
        virtual void visit(VariableDeclarator *node) = 0;
        virtual void visit(VariableDeclaration *node) = 0;
        virtual void visit(ThisExpression *node) = 0;
        virtual void visit(ArrayExpression *node) = 0;
        virtual void visit(Property *node) = 0;
        virtual void visit(ObjectExpression *node) = 0;
        virtual void visit(FunctionExpression *node) = 0;
        virtual void visit(SequenceExpression *node) = 0;
        virtual void visit(UnaryExpression *node) = 0;
        virtual void visit(BinaryExpression *node) = 0;
        virtual void visit(AssignmentExpression *node) = 0;
        virtual void visit(UpdateExpression *node) = 0;
        virtual void visit(LogicalExpression *node) = 0;
        virtual void visit(ConditionalExpression *node) = 0;
        virtual void visit(NewExpression *node) = 0;
        virtual void visit(CallExpression *node) = 0;
        virtual void visit(MemberExpression *node) = 0;
        virtual void visit(NullLiteral *node) = 0;
        virtual void visit(RegExpLiteral *node) = 0;
        virtual void visit(StringLiteral *node) = 0;
        virtual void visit(NumericLiteral *node) = 0;
        virtual void visit(BooleanLiteral *node) = 0;

        void visitChildren(Program *node);
        void visitChildren(Identifier *node);
        void visitChildren(BlockStatement *node);
        void visitChildren(EmptyStatement *node);
        void visitChildren(ExpressionStatement *node);
        void visitChildren(IfStatement *node);
        void visitChildren(LabeledStatement *node);
        void visitChildren(BreakStatement *node);
        void visitChildren(ContinueStatement *node);
        void visitChildren(WithStatement *node);
        void visitChildren(SwitchCase *node);
        void visitChildren(SwitchStatement *node);
        void visitChildren(ReturnStatement *node);
        void visitChildren(ThrowStatement *node);
        void visitChildren(CatchClause *node);
        void visitChildren(TryStatement *node);
        void visitChildren(WhileStatement *node);
        void visitChildren(DoWhileStatement *node);
        void visitChildren(ForStatement *node);
        void visitChildren(ForInStatement *node);
        void visitChildren(DebuggerStatement *node);
        void visitChildren(FunctionDeclaration *node);
        void visitChildren(VariableDeclarator *node);
        void visitChildren(VariableDeclaration *node);
        void visitChildren(ThisExpression *node);
        void visitChildren(ArrayExpression *node);
        void visitChildren(Property *node);
        void visitChildren(ObjectExpression *node);
        void visitChildren(FunctionExpression *node);
        void visitChildren(SequenceExpression *node);
        void visitChildren(UnaryExpression *node);
        void visitChildren(BinaryExpression *node);
        void visitChildren(AssignmentExpression *node);
        void visitChildren(UpdateExpression *node);
        void visitChildren(LogicalExpression *node);
        void visitChildren(ConditionalExpression *node);
        void visitChildren(NewExpression *node);
        void visitChildren(CallExpression *node);
        void visitChildren(MemberExpression *node);
        void visitChildren(NullLiteral *node);
        void visitChildren(RegExpLiteral *node);
        void visitChildren(StringLiteral *node);
        void visitChildren(NumericLiteral *node);
        void visitChildren(BooleanLiteral *node);
    };

    struct Node : Poolable {
        SourceLocation *loc;
        SourceLocation *groupLoc;
        int range[2];
        int groupRange[2];
        Node(Pool &pool) : Poolable(pool), loc(), groupLoc(NULL) { range[0] = range[1] = groupRange[0] = groupRange[1] = 0; }
        virtual ~Node() {}
        virtual void accept(Visitor *visitor) = 0;
        template <class T> bool is() {
            return dynamic_cast<T *>(this) != NULL;
        }
        template <class T> T *as() {
            T *t = dynamic_cast<T *>(this);
            assert(t != NULL);
            return t;
        }
    };

    struct Statement : Node {
        Statement(Pool &pool) : Node(pool) {}
    };

    struct Expression : Node {
        Expression(Pool &pool) : Node(pool) {}
    };

    struct Program : Node {
        std::vector<Statement *> body;
        Program(Pool &pool) : Node(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct Identifier : Expression {
        std::string name;
        Identifier(Pool &pool) : Expression(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct BlockStatement : Statement {
        std::vector<Statement *> body;
        BlockStatement(Pool &pool) : Statement(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    // This is a mixin, not a base class, and so isn't poolable
    struct Function {
        Identifier *id;
        std::vector<Identifier *> params;
        BlockStatement *body;
        Function() : id(), body() {}
    };

    struct EmptyStatement : Statement {
        EmptyStatement(Pool &pool) : Statement(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ExpressionStatement : Statement {
        Expression *expression;
        ExpressionStatement(Pool &pool) : Statement(pool), expression() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct IfStatement : Statement {
        Expression *test;
        Statement *consequent;
        Statement *alternate;
        IfStatement(Pool &pool) : Statement(pool), test(), consequent(), alternate() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct LabeledStatement : Statement {
        Identifier *label;
        Statement *body;
        LabeledStatement(Pool &pool) : Statement(pool), label(), body() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct BreakStatement : Statement {
        Identifier *label;
        BreakStatement(Pool &pool) : Statement(pool), label() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ContinueStatement : Statement {
        Identifier *label;
        ContinueStatement(Pool &pool) : Statement(pool), label() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct WithStatement : Statement {
        Expression *object;
        Statement *body;
        WithStatement(Pool &pool) : Statement(pool), object(), body() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct SwitchCase : Node {
        Expression *test;
        std::vector<Statement *> consequent;
        SwitchCase(Pool &pool) : Node(pool), test() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct SwitchStatement : Statement {
        Expression *discriminant;
        std::vector<SwitchCase *> cases;
        SwitchStatement(Pool &pool) : Statement(pool), discriminant() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ReturnStatement : Statement {
        Expression *argument;
        ReturnStatement(Pool &pool) : Statement(pool), argument() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ThrowStatement : Statement {
        Expression *argument;
        ThrowStatement(Pool &pool) : Statement(pool), argument() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct CatchClause : Node {
        Expression *param;
        BlockStatement *body;
        CatchClause(Pool &pool) : Node(pool), param(), body() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct TryStatement : Statement {
        BlockStatement *block;
        CatchClause *handler;
        BlockStatement *finalizer;
        TryStatement(Pool &pool) : Statement(pool), block(), handler(), finalizer() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct WhileStatement : Statement {
        Expression *test;
        Statement *body;
        WhileStatement(Pool &pool) : Statement(pool), test(), body() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct DoWhileStatement : Statement {
        Statement *body;
        Expression *test;
        DoWhileStatement(Pool &pool) : Statement(pool), body(), test() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ForStatement : Statement {
        Node *init; // Either a VariableDeclaration or an Expression
        Expression *test;
        Expression *update;
        Statement *body;
        ForStatement(Pool &pool) : Statement(pool), init(), test(), update(), body() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ForInStatement : Statement {
        Node *left; // Either a VariableDeclaration or an Expression
        Expression *right;
        Statement *body;
        ForInStatement(Pool &pool) : Statement(pool), left(), right(), body() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct DebuggerStatement : Statement {
        DebuggerStatement(Pool &pool) : Statement(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct Declaration : Statement {
        Declaration(Pool &pool) : Statement(pool) {}
    };

    struct FunctionDeclaration : Declaration, Function {
        FunctionDeclaration(Pool &pool) : Declaration(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct VariableDeclarator : Node {
        Identifier *id;
        Expression *init;
        VariableDeclarator(Pool &pool) : Node(pool), id(), init() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct VariableDeclaration : Declaration {
        std::vector<VariableDeclarator *> declarations;
        std::string kind;
        VariableDeclaration(Pool &pool) : Declaration(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ThisExpression : Expression {
        ThisExpression(Pool &pool) : Expression(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ArrayExpression : Expression {
        std::vector<Expression *> elements;
        ArrayExpression(Pool &pool) : Expression(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct Property : Node {
        std::string kind;
        Expression *key; // Either a Literal or an Identifier
        Expression *value;
        Property(Pool &pool) : Node(pool), key(), value() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ObjectExpression : Expression {
        std::vector<Property *> properties;
        ObjectExpression(Pool &pool) : Expression(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct FunctionExpression : Expression, Function {
        FunctionExpression(Pool &pool) : Expression(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct SequenceExpression : Expression {
        std::vector<Expression *> expressions;
        SequenceExpression(Pool &pool) : Expression(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct UnaryExpression : Expression {
        std::string operator_;
        bool prefix;
        Expression *argument;
        UnaryExpression(Pool &pool) : Expression(pool), prefix(), argument() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct BinaryExpression : Expression {
        std::string operator_;
        Expression *left;
        Expression *right;
        BinaryExpression(Pool &pool) : Expression(pool), left(), right() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct AssignmentExpression : Expression {
        std::string operator_;
        Expression *left;
        Expression *right;
        AssignmentExpression(Pool &pool) : Expression(pool), left(), right() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct UpdateExpression : Expression {
        std::string operator_;
        Expression *argument;
        bool prefix;
        UpdateExpression(Pool &pool) : Expression(pool), argument(), prefix() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct LogicalExpression : Expression {
        std::string operator_;
        Expression *left;
        Expression *right;
        LogicalExpression(Pool &pool) : Expression(pool), left(), right() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ConditionalExpression : Expression {
        Expression *test;
        Expression *alternate;
        Expression *consequent;
        ConditionalExpression(Pool &pool) : Expression(pool), test(), alternate(), consequent() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct NewExpression : Expression {
        Expression *callee;
        std::vector<Expression *> arguments;
        NewExpression(Pool &pool) : Expression(pool), callee() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct CallExpression : Expression {
        Expression *callee;
        std::vector<Expression *> arguments;
        CallExpression(Pool &pool) : Expression(pool), callee() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct MemberExpression : Expression {
        Expression *object;
        Expression *property; // Identifier if computed == false
        bool computed;
        MemberExpression(Pool &pool) : Expression(pool), object(), property(), computed() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct Literal : Expression {
        Literal(Pool &pool) : Expression(pool) {}
    };

    struct NullLiteral : Literal {
        NullLiteral(Pool &pool) : Literal(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct RegExpLiteral : Literal {
        std::string pattern;
        std::string flags;
        RegExpLiteral(Pool &pool) : Literal(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct StringLiteral : Literal {
        std::string value;
        StringLiteral(Pool &pool) : Literal(pool) {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct NumericLiteral : Literal {
        double value;
        NumericLiteral(Pool &pool) : Literal(pool), value() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct BooleanLiteral : Literal {
        bool value;
        BooleanLiteral(Pool &pool) : Literal(pool), value() {}
        void accept(Visitor *visitor) { visitor->visit(this); }
    };

    struct ParseError {
        std::string description;
        int index;
        int lineNumber;
        int column;
    };

    Program *parse(Pool &pool, const std::string &code);
}

#endif
