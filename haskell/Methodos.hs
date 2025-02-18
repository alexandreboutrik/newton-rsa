-- Methodos.hs
module Methodos where

import Data.Maybe (fromJust)
import Data.Maybe -- fromMaybe
import Data.Fixed -- mod'
import Data.List (nub)

-- Euler's Totient function
phi :: Integer -> Integer
phi n = round $ fromIntegral n * product [ 1 - (1 / fromIntegral p) | p <- nub (pf n) ]

-- Prime Factors of n
pf :: Integer -> [Integer]
pf n = pf' n 2
  where
    pf' 1 _ = []
    pf' m p
      | p * p > m = [m]
      | m `mod` p == 0 = p : pf' (m `div` p) p
      | otherwise = pf' m (p + 1)

-- Power with modulus - (a^b) mod m
pow :: Integer -> Integer -> Integer -> Maybe Integer
pow a b m
  | m == 0 = Nothing
  | b < 0 = pow a ((phi m) - 1) m
  | otherwise = Just $ pow' a b 1
  where
    pow' _ 0 result = result
    pow' a b result
      | even b = pow' ((a * a) `mod` m) (b `div` 2) result
      | otherwise = pow' ((a * a) `mod` m) (b `div` 2) ((result * a) `mod` m)

-- Extended Euclidean Algorithm (EEA)
eea :: Integer -> Integer -> Maybe Integer
eea a n
  | a' == 1 = Just $ x `mod` n
  | otherwise = Nothing
  where
    (a', x, _) = egcd a n
    egcd :: Integer -> Integer -> (Integer, Integer, Integer)
    egcd 0 b = (b, 0, 1)
    egcd a b = (a', y' - (b `div` a) * x', x')
      where
      (a', x', y') = egcd (b `mod` a) a

-- Fermat-Euler Theorem (FET)
fet :: Integer -> Integer -> Maybe Integer
fet a n
  | gcd a n /= 1 = Nothing
  | otherwise = pow a (-1) n

-- a: Alpha
alpha :: Double -> Double -> Integer -> Integer -> Maybe Integer
alpha f_1 f_2 a n
  | (n == 0 || f_1 == 0 || f_2 == 0) = Nothing
  | otherwise = alpha' a n 1
  where
    alpha' a n x
      | x == a = Nothing
      | (a * ceiling (f_1 - x' * f_2)) `mod` n == 1 = Just $ x
      | otherwise = alpha' a n (x + 1)
      where
        x' = fromIntegral x

-- f_1: Newton-Raphson (NR)
f_1 :: Integer -> Integer -> Double -> Maybe Double
f_1 a n guess
  | (a == 0 || n == 0) = Nothing
  | otherwise = Just $ (guess - ((a' * guess) + 1) / a') `mod'` n'
  where
    a' = fromIntegral a
    n' = fromIntegral n

-- f_2: Correction Function
f_2 :: Integer -> Integer -> Double -> Maybe Double
f_2 a n guess
  | gcd a n /= 1 = Nothing
  | otherwise = f_2' a n guess (guess - 1)
  where
    f_2' a n guess old_guess
      | guess == old_guess = Just $ guess
      | otherwise = f_2' a n (guess * (2 - a' * guess / n')) guess
      where
        a' = fromIntegral a
        n' = fromIntegral n

-- Newton-Raphson (NR)
nr :: Integer -> Integer -> Maybe Integer
nr a n
  | gcd a n /= 1 = Nothing
  | otherwise = Just $ ceiling $ d1 - fromIntegral alp * d2
  where
    d1 = fromMaybe 0 (f_1 a n 1)
    d2 = fromMaybe 0 (f_2 a n 1)
    alp = fromMaybe 0 (alpha d1 d2 a n)
