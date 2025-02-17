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

main :: IO()
main = do
  args <- getArgs

  if length args /= 2 then exitFailure else do

  let p = read (args !! 0) :: Integer
  let q = read (args !! 1) :: Integer

  if is_prime(p) == False then exitFailure else do
  if is_prime(q) == False then exitFailure else do

  let n = p * q
  let phi_n = (p - 1) * (q - 1)
  let e = fromMaybe 0 (gen_e phi_n)

  if e == 0 then exitFailure else do

  let d_1 = fromMaybe 0 (f_1 e phi_n 1)
  let d_2 = fromMaybe 0 (f_2 e phi_n 1)

  if (d_1 == 0 || d_2 == 0) then exitFailure else do

  let a = fromMaybe 0 (alpha d_1 d_2 e phi_n)

  if a == 0 then exitFailure else do

  let d = ceiling $ d_1 - fromIntegral a * d_2

  putStrLn $ "EEA : " ++ show (eea e phi_n)
  putStrLn $ "FET : " ++ show (fet e phi_n)
  putStrLn $ "NR  : Just " ++ show d
