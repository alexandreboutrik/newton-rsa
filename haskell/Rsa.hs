module Rsa where

import Methodos

import Data.Maybe (fromJust)
import Data.Maybe -- fromMaybe

import System.Environment (getArgs)
import System.Exit (exitSuccess, exitFailure)

-- Trial division method
is_prime :: Integer -> Bool
is_prime n
  | n < 2 = False
  | otherwise = is_prime' n 2
  where
    is_prime' n divisor
      | divisor * divisor > n = True
      | n `mod` divisor == 0 = False
      | otherwise = is_prime' n (divisor + 1)

-- Generate 'e'
gen_e :: Integer -> Maybe Integer
gen_e n = gen' 2 n
  where
    gen' e n
      | e == n = Nothing
      | gcd e n == 1 = Just $ e
      | otherwise = gen' (e + 1) n
