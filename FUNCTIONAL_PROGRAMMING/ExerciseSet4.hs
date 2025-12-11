{-
  VILNIUS UNIVERSITY
  FUNCTIONAL PROGRAMMING
  @author Inés Cabrera Betancor
  @initialDate 03 DEC 2025
  @finalDate xx DEC 2025
  @brief Fourth assignment using haskell and structures and function application
-}

module ExerciseSet4 where

--- Exercise 1 -> Trees
data GTree a = Leaf a | Gnode [GTree a]

depth :: GTree a -> Int 
depth (Leaf _) = 1
depth (Gnode xs) = 1 + maximum (map depth xs)

occurs :: Eq a => a -> GTree a -> Bool
occurs x (Leaf y) = x == y
occurs x (Gnode xs) = any (occurs x) xs

mapGTree :: (a -> b) -> GTree a -> GTree b
mapGTree f (Leaf x) = Leaf (f x)
mapGTree f (Gnode xs) = Gnode (map (mapGTree f) xs)
