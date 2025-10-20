{-
  VILNIUS UNIVERSITY
  FUNCTIONAL PROGRAMMING
  @author Inés Cabrera Betancor
  @initialDate 06 OCT 2025
  @finalDate  xx OCT 2025
  @brief Second assignment using haskell and lists
-}

module ExerciseSet2 where

--- Exercise 1
average:: [Float] -> Float
average [] = 0
average numbers = sum numbers / fromIntegral(length numbers)

--- Exercise 2
--- Ex2 -> Recursion
divides:: Integer -> [Integer]
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
dividesCom:: Integer -> [Integer]
dividesCom 0 = []
dividesCom n 
  | n > 0 = [x | x <- [1 .. n], n `mod` x == 0]
  | otherwise = [x | x <- [-abs n .. (-1)] ++ [1 .. abs n], n `mod` x == 0]

--- Ex2 -> Prime number
isPrime :: Integer -> Bool
isPrime n
  | n < 2 = False
  | otherwise = dividesCom n == [1, n]

