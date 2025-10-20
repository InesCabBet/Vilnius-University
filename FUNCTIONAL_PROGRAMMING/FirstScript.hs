module FirstScript where

-- The value size is an integer
size :: Integer
size = 25

-- The function to square an integer
square :: Integer -> Integer
square n = n * n

-- The function to duble an integer
double :: Integer -> Integer
double n = 2 * n

-- An example using double, square, and size
example :: Integer
example = double (size - square (2+2))

-- Examples at home
evaluate :: Integer -> Bool -- Ponemos integer a bool pq recibe un entero y devuelve un booleano
evaluate n = (n == size)