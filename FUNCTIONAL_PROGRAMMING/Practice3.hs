--- 1. Verificador de signos
signo :: Int -> String
signo num
  | num < 0 = "negativo"
  | num > 0 = "positivo"
  | otherwise = "cero"

--- 2. Suma de cuadrados. Devuelve la suma de los cuadrados de los elementos de una lista
sumaCuad :: [Int] -> Int
sumaCuad [] = 0
sumaCuad (x:xs) = sum [x * x | x <- xs]

--- 3. Contador de vocales 
contarVocales :: String -> Int
contarVocales str = foldr (\c acc -> if c `elem` "aeiouAEIOU" then acc + 1 else acc) 0 str

--- 4. Lista de multiplos con los primeros m multiplos de n
multiplos :: Int -> Int -> [Int]
multiplos m n 
  | m <= 0 = [] 
  | otherwise = multiplos (m - 1) n ++ [m * n]

--- 5. Funcion que comprueba si una string es palindroma
palindroma :: String -> Bool
palindroma str = str == reversed
  where
    reversed = reverse str

--- 6. Maximo de una lista
maximoLista :: [Int] -> Int
maximoLista [x] = x
maximoLista (x:xs) = max x (maximoLista xs)

maximoListaF :: [Int] -> Int
maximoListaF (x : xs) = foldr max x xs

--- 7. Filtrar por palabras largas. Devuelve las cadenas que sean mayor o igual a n
filtrarLargas :: [String] -> Int -> [String]
filtrarLargas str n 
  | n <= 0 = error "number should be > 0"
  | otherwise = [x | x <- str, length x >= n]

--- 8. Aplicar una funcion a cada elemento
aplicarTodo :: (a -> a) -> [a] -> [a]
aplicarTodo func list = map func list 

--- 9. Conctenar lista de cadenas
concatenar :: [String] -> String
concatenar [] = ""
concatenar (x:xs) = x ++ concatenar xs

--- 10. Devuelve true si todos los numeros de la lista son positivos 
todosPos :: [Int] -> Bool
todosPos [] = error "Empty list"
todosPos xs = all (>0) xs 

--- HOJA PDF 3 - EJERCICIOS DE LA IA
--- 1. Funcion area
data Shape = Circle Float | Rectangle Float Float

area :: Shape -> Float
area (Circle r) = pi * r * r
area (Rectangle w h) = w * h

--- 2. Filtrar y transformar
filtraPosYDup :: [Int] -> [Int]
filtraPosYDup list = concat (map (\x -> replicate 2 x ) (filter (>= 0) list))

--- 3. comprobar si todos los elementos de una lsita satisfacen el predicado dado
cumple :: (a -> Bool) -> [a] -> Bool
cumple func list = all func list

--- 4. Longitud de una lista
longitud :: [a] -> Int
longitud = sum . map (\_ -> 1)

--- 5. Suma con limite
sumLimit :: Int -> [Int] -> Int
sumLimit limit xs = sum [y + z | y <- xs, z <- xs, y + z < limit]

--- 6. Inversion de lista con foldr
myRev :: [a] -> [a]
myRev = foldr(\c acc -> acc ++ [c]) []

--- 7. Filtrar y contar
contarSi :: (a -> Bool) -> [a] -> Int
contarSi func list = longitud (map func list)

--- 8. foldr para sumar
sumarF :: [Int] -> Int
sumarF list = foldr (+) 0 list

-- 9. Dividir la lista en dos partes
divide :: Int -> [a] -> ([a], [a])
divide num list = splitAt num list

--- 10. Composicion repetida simple
aplicarN :: Int -> (a -> a) -> a -> a
aplicarN n func x 
  | n == 0 = x
  | otherwise = aplicarN (n - 1) func (func x)