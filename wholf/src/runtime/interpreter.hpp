#ifndef WHOLF_INTERPRETER_HPP
#define WHOLF_INTERPRETER_HPP

#include "parser.hpp"
#include <memory>
#include <unordered_map>
#include <string>

namespace Wholf {
    class Interpreter {
    public:
        void interpret(const std::vector<std::shared_ptr<Stmt>>& statements);
        
    private:
        std::unordered_map<std::string, std::shared_ptr<Object>> globals;
        
        void evaluate(std::shared_ptr<Expr> expr);
        void execute(std::shared_ptr<Stmt> stmt);
        void executeBlock(const std::vector<std::shared_ptr<Stmt>>& statements);
        
        // Expression evaluation
        void visitLiteralExpr(std::shared_ptr<LiteralExpr> expr);
        void visitGroupingExpr(std::shared_ptr<GroupingExpr> expr);
        void visitUnaryExpr(std::shared_ptr<UnaryExpr> expr);
        void visitBinaryExpr(std::shared_ptr<BinaryExpr> expr);
        void visitVariableExpr(std::shared_ptr<VariableExpr> expr);
        void visitAssignExpr(std::shared_ptr<AssignExpr> expr);
        void visitLogicalExpr(std::shared_ptr<LogicalExpr> expr);
        void visitCallExpr(std::shared_ptr<CallExpr> expr);
        
        // Statement execution
        void visitExpressionStmt(std::shared_ptr<ExpressionStmt> stmt);
        void visitPrintStmt(std::shared_ptr<PrintStmt> stmt);
        void visitVarStmt(std::shared_ptr<VarStmt> stmt);
        void visitBlockStmt(std::shared_ptr<BlockStmt> stmt);
        void visitIfStmt(std::shared_ptr<IfStmt> stmt);
        void visitWhileStmt(std::shared_ptr<WhileStmt> stmt);
        void visitFunctionStmt(std::shared_ptr<FunctionStmt> stmt);
        void visitReturnStmt(std::shared_ptr<ReturnStmt> stmt);
        void visitClassStmt(std::shared_ptr<ClassStmt> stmt);
    };
}

#endif // WHOLF_INTERPRETER_HPP
