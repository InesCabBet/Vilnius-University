{-
  VILNIUS UNIVERSITY
  FUNCTIONAL PROGRAMMING
  @author Inés Cabrera Betancor
  @initialDate 18 SEP 2025
  @finalDate  04 OCT 2025
  @brief First assignment using haskell and primitive recursion
-}

module ExerciseSet1 where

-- Exercise 1 
nAnd_1 :: Bool -> Bool -> Bool
nAnd_1 x y = not (x && y)

nAnd_2 :: Bool -> Bool -> Bool
nAnd_2 True y = not y
nAnd_2 False _ = True

nAnd_3 :: Bool -> Bool -> Bool
nAnd_3 True True = False
nAnd_3 True False = True
nAnd_3 False True = True
nAnd_3 False False = True

nAnd_4 :: Bool -> Bool -> Bool
nAnd_4 True True = False
nAnd_4 _ _ = True

-- Exercise 2
nDigits :: Integer -> Int
nDigits n 
  | n >= 0 = length (show n)
  | otherwise = length (show n) - 1

-- Exercise 3
nRoots :: Float -> Float -> Float -> Int
nRoots a b c
  | a == 0 = error "The first argument should be non-zero."
  | b*b > 4.0 * a * c = 2
  | b*b == 4.0 * a * c = 1
  | otherwise = 0

--- Exercise 4
smallerRoot :: Float -> Float -> Float -> Float
smallerRoot a b c
  | nRoots a b c == 0 = error "There are no quadratic roots"
  | nRoots a b c == 1 = -b / (2*a)
  | nRoots a b c == 2 && root1 < root2 = root1
  | otherwise = root2
  where
    root1 = (-b + sqrt(b*b - 4*a*c)) / (2*a)
    root2 = (-b - sqrt(b*b - 4*a*c)) / (2*a)

largerRoot :: Float -> Float -> Float -> Float
largerRoot a b c
  | nRoots a b c == 0 = error "There are no quadratic roots"
  | nRoots a b c == 1 = -b / (2*a)
  | nRoots a b c == 2 && root1 > root2 = root1
  | otherwise = root2
  where
    root1 = (-b + sqrt(b*b - 4*a*c)) / (2*a)
    root2 = (-b - sqrt(b*b - 4*a*c)) / (2*a)

--- Exercise 5
power2 :: Integer -> Integer
power2 n
  | n < 0 = 0
  | n == 0 = 1
  | n > 0 = 2* power2 (n-1)

--- Exercise 6
mult :: Integer -> Integer -> Integer
mult m n
  | m == 0 = 0
  | m > 0 = n + mult (m-1) n
  | m < 0 = (-n) + mult (m+1) n

--- Exercise 7
prod :: Integer -> Integer -> Integer
prod m n
  | m > n = error "The value of m must be < to the value of n"
  | (n - m) == 0 = m
  | (n - m) > 0 = m * prod (m + 1) n

factorial :: Integer -> Integer
factorial 0 = 1
factorial n = prod 1 n