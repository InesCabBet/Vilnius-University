--- 1. Arbol general definir funciones:
--- 1.1 que calculen el numero total de nodos del arbol
--- 1.2 devuelvan la lista de valores almacenados en las hojas
--- 1.3 determinen si todos los valores del arbol cumplen un predicado dado

data Tree a = Node a [Tree a]

contar :: Tree a -> Int
contar (Node _ hs) = 1 + sum (map contar hs)

listVal :: Tree a -> [a]
listVal (Node val hs) = val : concatMap listVal hs

comprueba :: Tree a -> (a -> Bool) -> Bool
comprueba (Node val hs) f = val && all (\t -> comprueba t f) hs 

--- 2. Arbol binario
--- 2.1 Comprobar si el arbol está balanceado
--- 2.2 Calcular la altura
--- 2.3 Convertir el arbol en una lista usando un recorrido in-order
data BTree a = Empty | Branch a (BTree a) (BTree a)

altura :: BTree a -> Int
altura Empty = 0
altura (Branch _ izq der) = 1 + max (altura izq) (altura der)

balanceado :: BTree a -> Bool
balanceado Empty = True
balanceado (Branch _ izq der) =
  balanceado izq && balanceado der && abs (altura izq - altura der) <= 1

inOrder :: BTree a -> [a]
inOrder Empty = []
inOrder (Branch val izq der) = [inOrder izq] ++ [val] ++ [inOrder der]

--- 3. Expresiones aritmeticas
--- 3.1 funcion evalAExpr :: AExpr -> Int
--- 3.2 fundion que cuente cuantas operaciones hay en la expresion
--- 3.3 una funcion que sustituya todos los numeros negativos por 0.
data AExpr = Num Int | Add AExpr AExpr | Mul AExpr AExpr

evalAExpr :: AExpr -> Int
evalAExpr (Num n) = n
evalAExpr (Add x y) = evalAExpr x + evalAExpr y
evalAExpr (Mul x y) = evalAExpr x * evalAExpr y

cuenta :: AExpr -> Int
cuenta (Num _) = 0 
cuenta (Add x y) = 1 + cuenta x + cuenta y
cuenta (Mul x y) = 1 + cuenta x + cuenta y

sustituye :: AExpr -> AExpr
sustituye (Num n) 
  | n < 0 = 0
  | otherwise = n
sustituye (Add x y) = Add (sustituye x) (sustituye y)
sustituye (Mul x y) = Mul (sustituye x) (sustituye y)

--- 4. Expresiones con variables
type Env = [(Char, Int)]
data Expr = Val Int | Var Char | Plus Expr Expr

busca :: Char -> Env -> Int
buscar _ [] = 0
buscar c ((x,v): xs)
  | c == x = v
  | otherwise = busca c xs

eval :: Env -> Expr -> Int
eval _ (Val n) = n
eval env (Var x) = busca x env
eval env (Plus e1 e2) = eval env e1 + eval env e2

--- 5. Reimplementar con foldr

--- 6. Transformaciones encadenadas
--- 6.1 Elimine los numeros pares
--- 6.2 eleve al cuadrado los restantes
--- 6.3 sume los valores hasta que la suma supere el numero dado
gg:: Integer -> [Integer] -> Integer
gg num list = supera num (map (^2) (filter(\x -> x `mod`2 == 1) list))

supera :: Integer -> [Integer] -> Integer
supera _ [] = 0
supera n (x:xs)
  | x > n = x
  | otherwise = x + supera (n - x) xs

--- 7. Funcion acumulada
accumulate :: (a -> b -> b) -> b -> [a] -> [b]
accumulate func acc = foldr step [acc]
  where
    step x (y:ys) = func x y : y : ys