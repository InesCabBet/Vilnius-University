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

--- Exercise 2 -> generalised expression
data Expr a = Lit a | EVar Var | Op (Ops a) [Expr a]
type Ops a = [a] -> a
type Var = Char

--- Exercise 3 -> extend regular expression
option, plus :: RegExp -> RegExp

--- Exercise 4 -> maybe type
data Result a = OK a | Error String

composeResult :: (a -> Result b) -> (b -> Result c) -> (a -> Result c)
composeResult f g x = check (f x)
  where
    check (Error msg) = Error msg
    check (OK y) = g y

--- Exercise 5 -> Goldbach conjeture
primes :: [Integer]
primes = sieve [2 ..]

sieve :: [Integer] -> [Integer]
sieve (x:xs) =
  x : sieve [y | y <- xs, y `mod` x > 0]

goldbach :: Integer -> Bool
goldbach n 
  | n < 4 = False
  | n `mod` 2 /= 0 = False
  | otherwise = and [satisfies e | e <- [4,6..n]]
  where
    satisfies e = or [p + q == e | p <- takeWhile (<e) primes, q <- takeWhile (<e) primes]

--- Exercise 6 -> infinte data streams
data Stream a = Cons a (Stream a)

streamToList :: Stream a -> [a]
streamToList (Cons x xs) = x : streamToList xs

streamIterate :: (a -> a) -> a -> Stream a
streamIterate f x = Cons x (streamIterate  f (f x))

streamInterleave :: Stream a -> Stream a -> Stream a
streamInterleave (Cons x xs) ys = Cons x (streamInterleave ys xs)