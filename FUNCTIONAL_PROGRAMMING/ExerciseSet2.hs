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
average numbers
  | numbers == [] = 0