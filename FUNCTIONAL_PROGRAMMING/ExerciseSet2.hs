{-
  VILNIUS UNIVERSITY
  FUNCTIONAL PROGRAMMING
  @author Inés Cabrera Betancor
  @initialDate 08 OCT 2025
  @finalDate  xx OCT 2025
  @brief Second assignment using haskell and lists
-}

module ExerciseSet2 where

--- Exercise 1
average :: [Float] -> Float
average [] = 0
average numbers = sum numbers / fromIntegral(length numbers)

--- Exercise 2
--- Ex2 -> Recursion
divides :: Integer -> [Integer]
divides 0 = []
divides number 
  | number > 0 = helper number 1
  | otherwise = helper number (-abs number)
  where
    helper n i
      | i > abs n = []
      | i == 0 = helper n (i + 1)
      | n `mod` i == 0 = i : helper n (i + 1)
      | otherwise = helper n (i + 1)  

--- Ex2 -> List comprehension
dividesCom :: Integer -> [Integer]
dividesCom 0 = []
dividesCom n 
  | n > 0 = [x | x <- [1 .. n], n `mod` x == 0]
  | otherwise = [x | x <- [-abs n .. (-1)] ++ [1 .. abs n], n `mod` x == 0]

--- Ex2 -> Prime number
isPrime :: Integer -> Bool
isPrime n
  | n < 2 = False
  | otherwise = dividesCom n == [1, n]

--- Exercise 3
prefix :: String -> String -> Bool
prefix string1 string2 
  | length(string1) > length(string2) = error "First string must be shorter than second string. \nWe evaluate wether s1 is a prefix of s2."
  | otherwise = take (length string1) string2 == string1

--- Ex3 -> substring
substring :: String -> String -> Bool
substring _ [] = False
substring string1 string2
  | prefix string1 string2 = True
  | otherwise = substring string1 (tail string2)

--- Exercise 4
permut :: [Integer] -> [Integer] -> Bool
permut [] [] = True
permut xs ys
  | length xs /= length ys = False
  | otherwise = all (\x -> count x xs == count x ys) xs
  where
    count n zs = length [z | z <- zs, z == n]

--- Exercise 5
capitalise :: String -> String
capitalise str = [toUpper c | c <- str, isAlpha c]
  where
    isAlpha c = ('a' <= c %% c <= 'z') || ('A' <= c && c <= 'Z')
    toUpper c
      | 'a' <= c && c <= 'z'
      

--- Exercise 6
itemTotal :: [(String, Float)] -> [(String, Float)]


itemDiscount :: String -> Integer -> [(String, Float)] -> [(String, Float)]
