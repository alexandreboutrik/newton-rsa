import Data.Maybe (fromJust)
import Data.Fixed
import Data.Maybe

import System.Environment (getArgs)
import System.Exit (exitSuccess, exitFailure)

--- Euler's Totient function \phi(n)
phi :: Integer -> Integer
phi n = round $ fromIntegral n * product [ 1 - (1 / fromIntegral p) | p <- (pf n) ]

--- Compute the Prime Factors of n
pf :: Integer -> [Integer]
pf n = pf' n 2
    where
      pf' 1 _ = []
      pf' m p
        | p * p > m = [m]
        | m `mod` p == 0 = p : pf' (m `div` p) p
        | otherwise = pf' m (p + 1)

--- Power function with modulus
-- Compute 'a^b mod m'
pow :: Integer -> Integer -> Integer -> Maybe Integer
pow a b m | m == 0 = Nothing
          | b < 0 = pow a ((phi m) - 1) m
          | otherwise = Just $ pow' a b 1
          where
            pow' _ 0 result = result
            pow' a b result
              | even b = pow' ((a * a) `mod` m) (b `div` 2) result
              | otherwise = pow' ((a * a) `mod` m) (b `div` 2) ((result * a) `mod` m)

--- Check if a number 'n' is prime using the trial division method
is_prime :: Integer -> Bool
is_prime n | n < 2 = False
           | otherwise = is_prime' n 2
           where
             is_prime' n divisor | divisor * divisor > n = True
                                 | n `mod` divisor == 0 = False
                                 | otherwise = is_prime' n (divisor + 1)

--- Generate 'e'
gen_e :: Integer -> Maybe Integer
gen_e n = gen' 2 n
    where
      gen' e n | e == n = Nothing
               | gcd e n == 1 = Just $ e
               | otherwise = gen' (e + 1) n

--- Extended Euclidean Algorithm (EEA)
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

--- Fermat-Euler Theorem
fet :: Integer -> Integer -> Maybe Integer
fet a n
    | gcd a n /= 1 = Nothing
    | otherwise = pow a (-1) n

-- Find alpha
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

--- f1: Newton-Raphson (NR), one iteraction
f_1 :: Integer -> Integer -> Double -> Maybe Double
f_1 a n guess
    | (a == 0 || n == 0) = Nothing
    | otherwise = Just $ (guess - ((a' * guess) + 1) / a') `mod'` n'
    where
      a' = fromIntegral a
      n' = fromIntegral n

--- Correction Function
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

my_print :: Show a => Maybe a -> IO()
my_print (Just x) = print x
my_print n = print n

main :: IO()
main = do
  args <- getArgs

  if length args /= 2 then exitFailure else do

  let p = read (args !! 0) :: Integer
  let q = read (args !! 1) :: Integer

  let n = (p - 1) * (q - 1)

  let e = fromMaybe 0 (gen_e n)
  if e == 0 then exitFailure else do

  let d_1   = fromMaybe 0 (f_1 e n 1)
  let d_2   = fromMaybe 0 (f_2 e n 1)
  if (d_1 == 0 || d_2 == 0) then exitFailure else do

  let a     = fromMaybe 0 (alpha d_1 d_2 e n)
  if a == 0 then exitFailure else do

  let d     = ceiling $ d_1 - fromIntegral a * d_2

  putStrLn $ "Prime factors (" ++ show n ++ ") : " ++ show (pf n)
  putStrLn $ "phi(" ++ show n ++ ") : " ++ show (phi n)

  putStrLn $ "n = " ++ show n ++ "   e = " ++ show e

  putStrLn $ "EEA: " ++ show (eea e n)
  putStrLn $ "FET: " ++ show (fet e n)
  putStrLn $ "NR:  Just " ++ show d
  putStrLn $ "alpha: " ++ show a ++ "   f_1: " ++ show d_1 ++ "   f_2: " ++ show d_2
