--- 1. Funcione que devuelve la suma de los cuadrados de los elementos de una lista
sumSquares :: [Integer] -> Integer
sumSquares [] = 0
sumSquares xs =  sum (squares xs)
  where
    squares xs = [x*x | x <- xs]

-- 2. Devuelve la media solo de los numeros positivos
meanPositive :: [Float] -> Float
meanPositive [] = 0.0
meanPositive xs = (sum filtered / fromIntegral(length filtered)) 
  where
    filtered = filter (>=0) xs

-- 3. Cuenta cuantas veces aparece un numero en la lista
count :: Integer -> [Integer] -> Integer
count _ [] = 0
count number (x:xs) 
  | number == x = 1 + count number xs 
  | otherwise = count number xs -- Está medio mal

-- 4. Devuelve cuantos digitos pares tiene un numero entero. Usar guards para numeros negativos
countEvenDigits :: Integer -> Integer
countEvenDigits number = helper (abs number)
  where
    helper x 
      | x == 0 = 0
      | even (x `mod` 10) = 1 + helper (x `div` 10)
      | otherwise = helper (x `div` 10)

--- 5. Maximo comun divisor
myGcd :: Integer -> Integer -> Integer
myGcd a b
  | b == 0 = a
  | a < b = myGcd b a
  | otherwise = myGcd b (a `mod` b)

--- 6. Comprobar si el primer string es sufijo del segundo
suffix :: String -> String -> Bool
suffix st1 st2
  | length st1 > length st2 = False
  | drop ((length st2) - (length st1)) st2 == st1 = True
  | otherwise = False

--- 7. Comprueba si el primer string aparece dentro del segundo
substringFrom :: String -> String -> Integer -> Bool
substringFrom st1 st2 num
  | num < 0 = error "Position must be positive"
  | length st1 > length st2 = False
  | num == 0 = st1 == st2
  | otherwise = take (length st1) (drop (fromIntegral num) st2) == st1 

--- 8. Comprueba si todos los elementos de la primera lista aparecen en la segunda
subset :: [Integer] -> [Integer] -> Bool
subset [] [] = True
subset xs ys = length xs == length helper
  where 
    helper = [y | y <- ys, x <- xs, y == x]

--- 9. Devuelve la lista de elementos comunes, respetando repeticiones
intersection :: [Integer] -> [Integer] -> [Integer]
intersection [] [] = []
intersection xs ys = [x | x <- xs, y <- ys, x == y]

--- 10. Elimina todo menos las letras minisculas
onlyLower :: String -> String
onlyLower str = filter (\c -> c >= 'a' && c <='z') str

--- 11. Devuelve todos los pares (x,y) tales que 
pairsSum :: Integer -> [(Integer, Integer)]
pairsSum num = [(x,y) | x <- [0..num], y <- [0..num], x + y == num]

--- 12. Definir usando foldr myLength
myLength :: [a] -> Integer
myLength [] = 0
myLength list = foldr (\_ acc -> acc + 1) 0 list

--- 13. Definir usando foldr myReverse
myReverse :: [a] -> [a]
myReverse [] = []
myReverse list = foldr (\x acc -> acc ++ [x]) [] list

--- 14. Definir permut con foldr
remove :: Integer -> [Integer] -> [Integer]
remove _ [] = []
remove x (y:ys)
  | x == y = ys
  |otherwise = y : remove x ys

permut :: [Integer] -> [Integer] -> Bool
permut xs ys
  | length xs /= length ys = False
  | otherwise = null (foldr remove ys xs)

