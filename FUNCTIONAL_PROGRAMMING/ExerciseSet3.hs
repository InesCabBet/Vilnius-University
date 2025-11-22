{-
  VILNIUS UNIVERSITY
  FUNCTIONAL PROGRAMMING
  @author Inés Cabrera Betancor
  @initialDate 16 NOV 2025
  @finalDate   NOV 2025
  @brief Third assignment using haskell and structures and function application
-}

module ExerciseSet3 where

--- Exercise 1 -> Overlaping shapes
data Shape = Circle Float (Float, Float) | Rectangle Float Float (Float, Float)
  deriving (Show, Ord, Eq)

distance :: (Float, Float) -> (Float, Float) -> Float
distance (x1, y1) (x2,y2) = sqrt((x1 - x2) ^2 + (y1 - y2)^2)

overlaps :: Shape -> Shape -> Bool
overlaps (Circle r1 c1) (Circle r2 c2) = distance c1 c2 < (r1 + r2)

overlaps (Rectangle w1 h1 (x1, y1)) (Rectangle w2 h2 (x2, y2)) =
  abs (x1 - x2) < (w1/2 + w2/2) && abs (y1 - y2) < (h1/2 + h2/2)

overlaps (Circle r (cx, cy)) (Rectangle w h (rx, ry)) = (cx - closestX) ^ 2 + (cy - closestY) ^ 2 r*r 
  where
    halfW = w / 2
    halfH =  h / 2
    closestX = max (rx - halfW) (min cx (rx + halfW))
    closestX = max (ry - halfH) (min cy (ry + halfH))

overlaps rect@(Rectangle _ _ _) circ@(Circle _ _) =
  overlaps circ rect

--- Exercise 2 -> Redifining standard functions
--- VERSION 1 - using filter
myAnyFilter:: (a -> Bool) -> [a] -> Bool
myAnyFilter condition elements = not (null (filter condition elements))

myAllFilter:: (a -> Bool) -> [a] -> Bool
myAllFilter condition elements = length (filter condition elements) == length elements

myAny :: (a -> Bool) -> [a] -> Bool
myAny condition elements = foldr (||) False (map condition elements)

myAll :: (a -> Bool) -> [a] -> Bool
myAll condition elements = foldr (&&) False (map condition elements)

--- Exercise 3 -> Redifine unzip
unzip :: [(a, b)] -> ([a], [b])
unzip = foldr (\(x, y) (list1, list2) -> (x : list1, y : list2)) ([], [])
