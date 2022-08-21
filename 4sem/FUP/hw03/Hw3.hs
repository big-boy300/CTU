module Hw3 where 
    type Symbol = String
    data Expr = Var Symbol | App Expr Expr | Lambda Symbol Expr deriving Eq 
 
    instance (Show Expr) where
        show (Var var) = var  
        show (App exp1 exp2) = "(" ++ show exp1 ++ " " ++ show exp2 ++ ")"
        show (Lambda var exp) = "(\\" ++ var ++ "." ++ show exp ++ ")"  
 
    -- infinite stream of symbols --
    symbols :: [Symbol]
    symbols = ["a" ++ show x | x <- [0..]]
 
    -- get free variables in expression -- 
    getFreeVars :: Expr -> [Symbol]
    getFreeVars (App (Var expr1) (Var expr2)) = [expr1, expr2]
    getFreeVars (Var expr) = [expr]
    getFreeVars _ = []
 
    -- rename variables -- 
    renameVar :: Int -> Expr -> Symbol -> Expr -> Expr
    renameVar idx (Lambda symb expr) var val = if elem symb (getFreeVars val) 
        then (Lambda (symbols !! idx) (substitute (idx + 1) (substitute idx expr symb val') var val))
        else (Lambda symb (substitute idx expr var val))
        where val' = Var (symbols !! idx)
 
    -- substitute variables --
    substitute :: Int -> Expr -> Symbol -> Expr -> Expr
    substitute idx (Var expr) var val = if expr == var then val else (Var expr)
    substitute idx (Lambda symb expr) var val = if var == symb 
        then (Lambda symb expr) 
        else (renameVar idx (Lambda symb expr) var val)
    substitute idx (App expr1 expr2) var val = (App (substitute idx expr1 var val) (substitute idx expr2 var val))
     
    -- reduces leftmost outermost redex not inside a lambda abstraction first --
    callByNameReduce :: Int -> Expr -> Expr
    callByNameReduce idx (Var expr) = (Var expr)
    callByNameReduce idx (Lambda symb expr) = (Lambda symb expr)
    callByNameReduce idx (App expr1 expr2) = case (callByNameReduce idx expr1) of 
        (Lambda symb expr) -> (callByNameReduce idx (substitute idx expr symb expr2))
        expr1' -> (App expr1' expr2)
 
    -- reduces leftmost outermost redex first --
    normalOrderReduce :: Int -> Expr -> Expr
    normalOrderReduce idx (Var expr) = (Var expr)
    normalOrderReduce idx (Lambda symb expr) = (Lambda symb (normalOrderReduce idx expr))
    normalOrderReduce idx (App expr1 expr2) = case (callByNameReduce idx expr1) of
        (Lambda symb expr) -> (normalOrderReduce idx (substitute idx expr symb expr2))
        expr1' -> (App expr1'' (normalOrderReduce idx expr2)) where expr1'' = (normalOrderReduce idx expr1')
 
    -- main func --
    eval :: Expr -> Expr
    eval expr = normalOrderReduce 0 expr
    