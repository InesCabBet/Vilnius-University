{-
  VILNIUS UNIVERSITY
  FUNCTIONAL PROGRAMMING
  @author Inés Cabrera Betancor
  @initialDate 16 NOV 2025
  @finalDate 22 NOV 2025
  @brief Third assignment using haskell and structures and function application
-}

module ExerciseSet3 where

--- Exercise 1 -> Overlaping shapes
data Shape = Circle Float (Float, Float) | Rectangle Float Float (Float, Float) |
  deriving (Show, Ord, Eq)

distance :: (Float, Float) -> (Float, Float) -> Float
distance (x1, y1) (x2,y2) = sqrt((x1 - x2) ^2 + (y1 - y2)^2)

overlaps :: Shape -> Shape -> Bool
overlaps (Circle r1 c1) (Circle r2 c2) = distance c1 c2 < (r1 + r2)

overlaps (Rectangle w1 h1 (x1, y1)) (Rectangle w2 h2 (x2, y2)) =
  abs (x1 - x2) < (w1/2 + w2/2) && abs (y1 - y2) < (h1/2 + h2/2)

overlaps (Circle r (cx, cy)) (Rectangle w h (rx, ry)) = (cx - closestX)^2 + (cy - closestY)^2 < r*r 
  where
    halfW = w / 2
    halfH =  h / 2
    closestX = max (rx - halfW) (min cx (rx + halfW))
    closestY = max (ry - halfH) (min cy (ry + halfH))

overlaps rect@(Rectangle _ _ _) circ@(Circle _ _) =
  overlaps circ rect

--- Exercise 2 -> Redifining standard functions
--- VERSION 1 - using filter
myAnyFilter:: (a -> Bool) -> [a] -> Bool
myAnyFilter condition elements = not (null (filter condition elements))

myAllFilter:: (a -> Bool) -> [a] -> Bool
myAllFilter condition elements = length (filter condition elements) == length elements

--- VERSION 2 -> usinf foldr
myAny :: (a -> Bool) -> [a] -> Bool
myAny condition elements = foldr (||) False (map condition elements)

myAll :: (a -> Bool) -> [a] -> Bool
myAll condition elements = foldr (\x y -> x && y) True (map condition elements)

--- Exercise 3 -> Redifine unzip
myUnzip :: [(a, b)] -> ([a], [b])
myUnzip = foldr (\(x, y) (list1, list2) -> (x : list1, y : list2)) ([], [])

--- Exercise 4 -> Redine length
lengthMap :: [a] -> Int
lengthMap = sum . map (\_ -> 1)

lengthFold :: [a] -> Int
lengthFold = foldr (\_ acc -> acc + 1) 0

--- Exercise 5 -> function definition
ff :: Integer -> [Integer] -> Integer
ff max = takeWithoutExceed max . map (*10) . filter(>= 0)

takeWithoutExceed :: Integer -> [Integer] -> Integer
takeWithoutExceed max = go 0
  where
    go current [] = current
    go current (x : list)
      | current + x > max = current
      | otherwise = go (current + x) list

--- Exercise 6 -> function total
total :: (Integer -> Integer) -> Integer -> Integer
total func num = foldr (\x acc -> func x + acc) 0 [0..num]

--- Exercise 7 -> function iter
iterRec :: Integer -> (a -> a) -> (a -> a)
iterRec num func
  | num <= 0 = id
  | otherwise = func . iterRec (num - 1) func

iterFold :: Integer -> (a -> a) -> (a -> a)
iterFold num func
  | num <= 0 = id
  | otherwise = foldr (.) id (replicate (fromInteger num) func)

--- Exercise 8 -> function split
splits :: [a] -> [([a], [a])]
splits xs = [ splitAt i xs | i <- [0 .. length xs] ]
