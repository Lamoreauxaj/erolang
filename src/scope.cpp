#include "scope.h"

map<int, map<string, Data>> scope_levels;
map<int, int> parent_scope;
map<Node*, int> node_scopes;

static int scope_counter;
static queue<pair<Stmts*, int>> scope_queue;

static void scope_stmts(Stmts *stmts, int scope);
static void scope_expr(Expr *expr, int scope);

static void scope_binary_expr(BinaryExpr *expr, int scope) {
    if (expr->op.type == ASSIGN) {
        // create new variable
    }
    else {
        scope_expr(expr->left, scope);
    }
    scope_expr(expr->right, scope);
}

static void scope_unary_expr(UnaryExpr *expr, int scope) {

}

static void scope_real_expr(RealExpr *expr, int scope) {

}

static void scope_tuple_expr(TupleExpr *expr, int scope) {
    for (Expr *val : expr->vals)
        scope_expr(val, scope);
}

static void scope_call_expr(CallExpr *expr, int scope) {
    scope_expr(expr->val, scope);
    scope_tuple_expr(expr->args, scope);
}

static void scope_identifier_expr(IdentifierExpr *expr, int scope) {
    string id = expr->val.text;
    while (true) {
        if (scope_levels[scope].count(id)) {

            break;
        }
        scope = parent_scope[scope];
        if (scope == 0) {
            log_error("unable to resolve variable");
            break;
        }
    }
    /*
    string id = expr->val.text;
    if (!scope_levels[0].count(id)) {
        scope_levels[0][id] = Data(DATA_SEGMENT, id);
    }
    */
}

static void scope_expr(Expr *expr, int scope) {
    if (expr->type == BINARYEXPR) scope_binary_expr((BinaryExpr*) expr, scope);
    else if (expr->type == UNARYEXPR) scope_unary_expr((UnaryExpr*) expr, scope);
    else if (expr->type == REALEXPR) scope_real_expr((RealExpr*) expr, scope);
    else if (expr->type == IDENTIFIEREXPR) scope_identifier_expr((IdentifierExpr*) expr, scope);
    else if (expr->type == CALLEXPR) scope_call_expr((CallExpr*) expr, scope);
    else {
        log_error("unexpected expr type");
        return;
    }
}

static void scope_while_stmt(WhileStmt *stmt, int scope) {
    scope_expr(stmt->cond, scope);
    parent_scope[scope_counter + 1] = scope;
    scope_queue.push({stmt->block, ++scope_counter});
}

static void scope_if_stmt(IfStmt *stmt, int scope) {
    scope_expr(stmt->cond, scope);
    parent_scope[scope_counter + 1] = scope;
    scope_queue.push({stmt->block, ++scope_counter});
}

static void scope_expr_stmt(ExprStmt *stmt, int scope) {
    scope_expr(stmt->expr, scope);
}

static void scope_stmt(Stmt *stmt, int scope) {
    if (stmt->type == EXPRSTMT) scope_expr_stmt((ExprStmt*) stmt, scope);
    else if (stmt->type == IFSTMT) scope_if_stmt((IfStmt*) stmt, scope);
    else if (stmt->type == WHILESTMT) scope_while_stmt((WhileStmt*) stmt, scope);
    else {
        log_error("unexpected statement type");
        return;
    }
}

static void scope_stmts(Stmts *stmts, int scope) {
    node_scopes[stmts] = scope;
    for (Stmt *stmt : stmts->stmts)
        scope_stmt(stmt, scope);
}

void scope_variables(Stmts *tree) {
    scope_counter = 0;
    scope_levels[0]["write"] = Data(DATA_SEGMENT, "write", new Var(CONSTRUCTIONV, (uint64_t) &ero_write));

    scope_queue.push({tree, scope_counter});
    while (!scope_queue.empty()) {
        auto [stmts, scope] = scope_queue.front();
        scope_queue.pop();
        scope_stmts(stmts, scope);
    }
}
