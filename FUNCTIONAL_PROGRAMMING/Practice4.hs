--- Dada una lista de enteros devuelve el cuadrado de los pares mayores que 5
f :: [Int] -> [Int]
f xs = [x | x <- xs, x > 5 && x `mod` 2 == 0]

-- Dada dos listas devuelve los pares tal que x < y y x + y par
g :: [Int] -> [Int] -> [(Int, Int)]
g xs ys = [(x,y) | x <- xs, y <- ys, x < y && (x+y) `mod` 2 == 0]

--- Extrae valores Just multiplicados por 10
h :: [a] -> [a]
h = map (*10) . map (\) . filter(/= Nothing)

--- Hacer map con foldr
mapF :: (a -> b) -> [a] -> [b]
mapF func list = foldr (\x acc -> func x) [] list

--- contar elementos mayor a cero
countPos :: [Int] -> Int
countPos = foldr (\x acc -> if x > 0 then acc + 1 else acc) 0
