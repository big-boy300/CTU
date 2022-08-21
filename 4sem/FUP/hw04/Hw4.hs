-- not finished -- 
module Hw4 where
  
    import Control.Applicative
    import Data.Char
    import Parser
    import Hw3
  
    parseExpr :: Parser Expr
    parseExpr = parseVar <|> parseApp <|> parseLambda
  
    parseVar :: Parser Expr
    parseVar = do vars <- some alphaNum
                  return (Var (vars))
  
    parseLambda :: Parser Expr
    parseLambda = do char '('
                     char '\\'
                     var <- some alphaNum
                     char '.'
                     expr <- parseExpr
                     char ')'
                     return (Lambda var expr)
  
    parseApp :: Parser Expr
    parseApp = do char '('
                  expr1 <- parseExpr
                  sep
                  expr2 <- parseExpr
                  char ')'
                  return (App expr1 expr2)
  
    readPrg :: String -> Maybe Expr
    readPrg str = case (parse parseLambda str) of
        Just (expr, str) -> Just expr
        _ -> Nothing